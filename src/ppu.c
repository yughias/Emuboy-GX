#include "integer.h"
#include "SDL_MAINLOOP.h"
#include "ppu.h"
#include "memory.h"
#include "dma.h"

#include <stdlib.h>

typedef enum {NO_BG, TILED, AFFINE} bgType;
typedef enum {IN_WIN0 = 0, IN_WIN1 = 1, IN_WINOUT = 2, IN_OBJWIN = 3, WIN_DISABLED = 0xFF} winType; 

void renderLineModeTiled(int y, bgType* bg_type);
void renderLineModeBitmap(int y, int mode);
void renderLine(int y);

void renderLineBitmap3(int y, u8* blend_info);
void renderLineBitmap4(int y, u8* blend_info);
void renderLineBitmap5(int y, u8* blend_info);

void renderLineRegBg(int y, int i, u8* blend_info, bool* obj_win_mask);
void renderLineAffBg(int y, int i, u8* blend_info, bool* obj_win_mask);
void renderLineSprite(int y, u16* obj_attr_ptr, bool mapping_1d, u8* blend_info, bool* obj_win_mask);
void getObjMask(int y, u16* obj_attr_ptr, bool mapping_1d, bool* obj_win_mask);

u16 getRgb555FromMemory(u8* palettePtr, int idx);
u32 getTilePixel(u8* tilePtr, u8 px, u8 py, u8* palettePtr, u32 startPaletteIdx, bool is8bpp, bool* transparent);
u32 rgb555torgb888(u16 rgb555);
void getSpriteDim(u16* attrib_ptr, int* width_ptr, int* height_ptr);
void getSpritePos(u16* attrib_ptr, int* x_ptr, int* y_ptr);
void applyRotScaleMat(i16* mat, i32* x, i32* y);
bool windowShouldDraw(u8 x, u8 y, int renderType, bool obj_win_mask, winType* winType_out);
bool isInsideWindow(u8 x, u8 y, u8 winId);

bool isBldTop(u8 type);
bool isBldBot(u8 type);
int brightnessBlend(int col, int mode);
int colorBlend(int topCol, int botCol);
int applyColorEffect(int inCol, u8 topType, u8 botType, int backCol, winType winType);

i32 wrapValue(i32 input, i32 limit);
i32 geti28(i32 val);

bool isHblank = false;
bool oldVcounter = false;

void updatePPU(int cycles){
    int inter_cycles = cycles % SCANLINE_CYCLES;
    VCOUNT = cycles / SCANLINE_CYCLES;

    if(inter_cycles >= DRAW_CYCLES){
        isHblank = true;
    } else
        isHblank = false;

    if(inter_cycles == DRAW_CYCLES){
        if(DISPSTAT & (1 << 4))
            IF |= 0b10;
        if(VCOUNT < SCREEN_HEIGHT){
            renderLine(VCOUNT);
            updateHblankDma();
        }
    }

    bool newVcounter = (VCOUNT == ((DISPSTAT >> 8) % 228));

    if((DISPSTAT & (1 << 5)) && newVcounter && !oldVcounter)
        IF |= 0b100;

    oldVcounter = newVcounter;

    if(cycles == VBLANK){
        if(DISPSTAT & (1 << 3))
            IF |= 0b1;
        renderPixels();
        updateVblankDma();
        for(int i = 0; i < 2; i++){
            INTERNAL_BGX[i] = (i32)BGX[i];
            INTERNAL_BGY[i] = (i32)BGY[i];
        }
    }
}
  
void renderLine(int y){
    bgType bg_type[4];
    switch(DISPCNT & 0b111){
        case 0:
        bg_type[0] = TILED;
        bg_type[1] = TILED;
        bg_type[2] = TILED;
        bg_type[3] = TILED;
        renderLineModeTiled(y, bg_type);
        break;

        case 1:
        bg_type[0] = TILED;
        bg_type[1] = TILED;
        bg_type[2] = AFFINE;
        bg_type[3] = NO_BG;
        renderLineModeTiled(y, bg_type);
        break;

        case 2:
        bg_type[0] = NO_BG;
        bg_type[1] = NO_BG;
        bg_type[2] = AFFINE;
        bg_type[3] = AFFINE;
        renderLineModeTiled(y, bg_type);
        break;

        case 3:
        renderLineModeBitmap(y, 3);
        break;

        case 4:
        renderLineModeBitmap(y, 4);
        break;

        case 5:
        renderLineModeBitmap(y, 5);
        break;

        default:
        printf("UNSUPPORTED RENDERING %d!\n", DISPCNT & 0b111);
    }

    for(int i = 0; i < SCREEN_WIDTH; i++){
        int col = rgb555torgb888(pixels[i + y*SCREEN_WIDTH]);
        pixels[i + y * SCREEN_WIDTH] = col;
    }
}

void renderLineRegBg(int y, int i, u8* blend_info, bool* obj_win_mask){
    u8 char_base_block = (BGCNT[i] >> 2) & 0b11;
    bool mosaic = (BGCNT[i] >> 6) & 1;
    bool color_bpp = (BGCNT[i] >> 7) & 1;
    u8* screen_base_block = &VRAM[((BGCNT[i] >> 8) & 0b11111) << 11];
    u8 bg_size = (BGCNT[i] >> 0xE);
    int bg_width = 256 * (1 + ((bg_size & 1)));
    int bg_height = 256 * (1 + ((bg_size >> 1)));
    winType win_type;

    for(int x = 0; x < SCREEN_WIDTH; x++){
        if(!windowShouldDraw(x, y, i, obj_win_mask[x], &win_type))
            continue;
        int offX = (x + (BGHOFS[i] & 0x1FF)) % bg_width;
        int offY = (y + (BGVOFS[i] & 0x1FF)) % bg_height;
        int sbx = offX / 256;
        int sby = offY / 256;

        int internal_offX = (offX >> 3) % 32;
        int internal_offY = (offY >> 3) % 32;
        u16* sb_map = (u16*)&screen_base_block[sbx * 0x800 + sby * (bg_width << 3)];

        u16 tileData = sb_map[internal_offX + internal_offY * 32];
        int tileIdx = tileData & 0x3FF;
        bool h_flip = (tileData >> 0xA) & 1;
        bool v_flip = (tileData >> 0xB) & 1;
        u8 paletteIdx = tileData >> 12;
        u8 stride = color_bpp ? 64 : 32;
        u8* tilePtr = &VRAM[(char_base_block << 14) + tileIdx*stride];
        u8 px = offX % 8;
        u8 py = offY % 8;

        bool transparent = false;
        int bg_col = getTilePixel(tilePtr, h_flip ? 7 - px : px, v_flip ? 7 - py : py, PALETTE_RAM, paletteIdx*32, color_bpp, &transparent);
        if(!transparent){
            int out_col = applyColorEffect(bg_col, i, blend_info[x], pixels[x + y * SCREEN_WIDTH], win_type);
            pixels[x + y * SCREEN_WIDTH] = out_col;
            blend_info[x] = i;
        }
    }
}

void renderLineAffBg(int y, int i, u8* blend_info, bool* obj_win_mask){
    int aff_idx = i-2;
    u8 char_base_block = (BGCNT[i] >> 2) & 0b11;
    bool mosaic = (BGCNT[i] >> 6) & 1;
    u8* screen_base_block = &VRAM[((BGCNT[i] >> 8) & 0b11111) << 11];
    bool wrapping = (BGCNT[i] >> 0xD) & 1;
    u8 bg_size = (BGCNT[i] >> 0xE);
    int bg_width = 128 << bg_size;
    int bg_height = 128 << bg_size;
    i16 dx = BGP[aff_idx*4 + 0];
    i16 dy = BGP[aff_idx*4 + 2];
    i16 dmx = BGP[aff_idx*4 + 1];
    i16 dmy = BGP[aff_idx*4 + 3];
    winType win_type;

    i32 startX = geti28(INTERNAL_BGX[aff_idx]);
    i32 startY = geti28(INTERNAL_BGY[aff_idx]);

    for(int x = 0; x < SCREEN_WIDTH; x++){
        i32 offX = startX;
        i32 offY = startY;
        startX = geti28(startX + dx);
        startY = geti28(startY + dy);
        if(!windowShouldDraw(x, y, i, obj_win_mask[x], &win_type))
            continue;
        offX >>= 8;
        offY >>= 8;
        if(!wrapping){
            if(offX < 0 || offX >= bg_width)
                continue;
            if(offY < 0 || offY >= bg_height)
                continue;
        } else {
            offX = wrapValue(offX, bg_width);
            offY = wrapValue(offY, bg_height);
        }
        u8 tileIdx = screen_base_block[(offX >> 3) + (offY >> 3) * (bg_width >> 3)];
        u8* tilePtr = &VRAM[(char_base_block << 14) + tileIdx*64];
        u8 px = offX % 8;
        u8 py = offY % 8;

        bool transparent = false;
        int bg_col = getTilePixel(tilePtr, px, py, PALETTE_RAM, 0, true, &transparent);
        if(!transparent){
            int out_col = applyColorEffect(bg_col, i, blend_info[x], pixels[x + y * SCREEN_WIDTH], win_type);
            pixels[x + y * SCREEN_WIDTH] = out_col;
            blend_info[x] = i;
        }
    }

    INTERNAL_BGX[aff_idx] = geti28(INTERNAL_BGX[aff_idx] + dmx);
    INTERNAL_BGY[aff_idx] = geti28(INTERNAL_BGY[aff_idx] + dmy);
}

void renderLineModeTiled(int y, bgType* bg_type){
    int backdrop_col = getRgb555FromMemory(PALETTE_RAM, 0);
    for(int x = 0; x < SCREEN_WIDTH; x++)
        pixels[x + y * SCREEN_WIDTH] = backdrop_col;

    u8 blend_info[SCREEN_WIDTH] = { [0 ... 239] = 5 };
    bool obj_win_mask[SCREEN_WIDTH] = {[0 ... 239] = false};
    bool mapping_1d = DISPCNT & (1 << 6);

    if(DISPCNT & 0x8000){
        for(int i = 0; i < 128; i++){
            u16* obj_attr_ptr = (u16*)(&OAM[i*8]);
            getObjMask(y, obj_attr_ptr, mapping_1d, obj_win_mask);
        }
    }

    for(int prio = 3; prio >= 0; prio--){
        for(int i = 3; i >= 0; i--){
            bool bg_on = DISPCNT & (1 << (8 + i));
            u8 bg_prio = BGCNT[i] & 0b11;
            if(bg_on && bg_prio == prio)
                switch(bg_type[i]){
                    case NO_BG:
                    break;

                    case TILED:
                    renderLineRegBg(y, i, blend_info, obj_win_mask);
                    break;

                    case AFFINE:
                    renderLineAffBg(y, i, blend_info, obj_win_mask);
                    break;
                }
        }

        if(!(DISPCNT & (1 << 12)))
            continue;

        for(int i = 127; i >= 0; i--){
            u16* obj_attr_ptr = (u16*)(&OAM[i*8]);
            u8 obj_prio = (obj_attr_ptr[2] >> 0xA) & 0b11;
            if(obj_prio == prio)
                renderLineSprite(y, obj_attr_ptr, mapping_1d, blend_info, obj_win_mask);
        }
    }
}

void renderLineBitmap3(int y, u8* blend_info){
    for(int x = 0; x < SCREEN_WIDTH; x++){
        int idx = x + y * SCREEN_WIDTH;
        u16 col555 = getRgb555FromMemory(VRAM, idx);
        pixels[idx] = col555;
        blend_info[x] = 2;
    }
}

void renderLineBitmap4(int y, u8* blend_info){
    int bg_offset = ((bool)(DISPCNT & (1 << 4))) * 0xA000;
    for(int x = 0; x < SCREEN_WIDTH; x++){
        int idx = x + y * SCREEN_WIDTH;
        u8 palIdx = VRAM[bg_offset + idx];
        if(!palIdx)
            continue;
        u16 col555 = getRgb555FromMemory(PALETTE_RAM, palIdx);
        pixels[idx] = col555;
        blend_info[x] = 2;
    }
}

void renderLineBitmap5(int y, u8* blend_info){
    if(y >= 128)
        return;
    int bg_offset = ((bool)(DISPCNT & (1 << 4))) * 0xA000;
    for(int x = 0; x < 160; x++){
        int vram_idx = x + y * 160;
        int screen_idx = x + y * SCREEN_WIDTH;
        u16 col555;
        col555 = getRgb555FromMemory(VRAM + bg_offset, vram_idx);
        pixels[screen_idx] = col555;
        blend_info[x] = 2;
    }
}

void renderLineModeBitmap(int y, int mode){
    int backdrop_col = getRgb555FromMemory(PALETTE_RAM, 0);
    for(int x = 0; x < SCREEN_WIDTH; x++)
        pixels[x + y * SCREEN_WIDTH] = backdrop_col;

    u8 blend_info[SCREEN_WIDTH] = { [0 ... 239] = 5 };
    bool obj_win_mask[SCREEN_WIDTH] = { [0 ... 239] = false};
    bool mapping_1d = DISPCNT & (1 << 6);

    for(int prio = 3; prio >= 0; prio--){
        bool bg_on = DISPCNT & (1 << 10);
        u8 bg_prio = BGCNT[2] & 0b11;
        if(bg_on && bg_prio == prio){
            switch(mode){
                case 3:
                renderLineBitmap3(y, blend_info);
                break;

                case 4:
                renderLineBitmap4(y, blend_info);
                break;

                case 5:
                renderLineBitmap5(y, blend_info);
                break;
            }
        }

        if(!(DISPCNT & (1 << 12)))
            continue;

        for(int i = 127; i >= 0; i--){
            u16* obj_attr_ptr = (u16*)(&OAM[i*8]);
            u8 obj_prio = (obj_attr_ptr[2] >> 0xA) & 0b11;
            u16 tid = obj_attr_ptr[2] & 0x3FF;
            if(obj_prio == prio && tid >= 512){
                renderLineSprite(y, obj_attr_ptr, mapping_1d, blend_info, obj_win_mask);
            }
        }
    }
}

u16 getRgb555FromMemory(u8* palettePtr, int idx){
    return palettePtr[idx*2] | (palettePtr[idx*2+1] << 8);
}

u32 getTilePixel(u8* tilePtr, u8 px, u8 py, u8* palettePtr, u32 startPaletteIdx, bool is8bpp, bool* transparent){
    u8 paletteIdx;
    int colorIdx;
    u8 byte;
    if(!is8bpp){
        colorIdx = (px >> 1) + py * 4;
        byte = tilePtr[colorIdx];
        paletteIdx = px & 1 ? byte >> 4 : byte & 0xF;
        *transparent = !paletteIdx;
        return getRgb555FromMemory(palettePtr + startPaletteIdx, paletteIdx);
    } else {
        colorIdx = px + py * 8;
        *transparent = !tilePtr[colorIdx];
        return getRgb555FromMemory(palettePtr, tilePtr[colorIdx]);   
    }
}

u32 rgb555torgb888(u16 rgb555){
    u8 red = rgb555 & 0x1F;
    u8 green = (rgb555 >> 5) & 0x1F;
    u8 blue = (rgb555 >> 10) & 0x1F;
    red = red & 1 ? (red << 3) | 0b111 : red << 3;
    blue = blue & 1 ? (blue << 3) | 0b111 : blue << 3;
    green = green & 1 ? (green << 3) | 0b111 : green << 3;
    return color(red, green, blue);
}

void drawPaletteRam(SDL_Window* win, u8* ptr){
    SDL_Surface* surface = SDL_GetWindowSurface(win);

    for(int y = 0; y < 16; y++){
        for(int x = 0; x < 16; x++){
            int idx = x + y * 16;
            u16 col555 = getRgb555FromMemory(ptr, idx);
            u32 col888 = rgb555torgb888(col555);
            SDL_Rect rect = {.x = x*16, .y = y*16, .w = 16, .h = 16};
            SDL_FillRect(surface, &rect, col888);
        }
    }
}

void drawTileMap(SDL_Window* win){
    SDL_Surface* surface = SDL_GetWindowSurface(win);
    int* pixels = (int*)surface->pixels;

    for(int tileY = 0; tileY < 64; tileY++){
        for(int tileX = 0; tileX < 32; tileX++){
            int tileIdx = tileX + tileY * 32;
            for(int y = 0; y < 8; y++){
                for(int x = 0; x < 8; x++){
                    u8* tilePtr = &VRAM[tileIdx*32];
                    bool transparent;
                    int col = rgb555torgb888(getTilePixel(tilePtr, x, y, PALETTE_RAM, 0, false, &transparent));
                    int pixIdx = (x + tileX*8) + (y + tileY*8) * 256;
                    pixels[pixIdx] = col;
                }
            }
        }
    }
}

void getSpriteDim(u16* attrib_ptr, int* width_ptr, int* height_ptr){
    static u8 sprite_width_array[16] = {
         8, 16, 32, 64,
        16, 32, 32, 64,
         8,  8, 16, 32
    };

    static u8 sprite_height_array[16] = {
         8, 16, 32, 64,
         8,  8, 16, 32,
        16, 32, 32, 64
    };
    
    int sprite_shape = attrib_ptr[0] >> 0xE;
    int sprite_size = attrib_ptr[1] >> 0xE;
    int idx = sprite_size + sprite_shape * 4;
    *width_ptr = sprite_width_array[idx];
    *height_ptr = sprite_height_array[idx];
}

void getSpritePos(u16* attrib_ptr, int* x_ptr, int* y_ptr){
    *y_ptr = attrib_ptr[0] & 0xFF;
    *x_ptr = attrib_ptr[1] & 0x1FF;
}

bool windowShouldDraw(u8 x, u8 y, int renderType, bool obj_win_mask, winType* winType_out){
    bool win_active[2];
    bool obj_win_active = (DISPCNT >> 15) & 1;
    win_active[0] = (DISPCNT >> 13) & 1;
    win_active[1] = (DISPCNT >> 14) & 1;

    if(!win_active[0] && !win_active[1] && !obj_win_active){
        *winType_out = WIN_DISABLED;
        return true;
    }

    for(int i = 0; i < 2; i++){
        if(win_active[i] && isInsideWindow(x, y, i)){
            *winType_out = i; 
            return WININ & (1 << (renderType + 0x8 * i));
        }
    }

    if(obj_win_active && obj_win_mask){
        *winType_out = IN_OBJWIN;
        return WINOUT & (1 << (renderType + 0x8));
    }

    // outside case
    *winType_out = IN_WINOUT;
    return WINOUT & (1 << renderType);
}

bool isInsideWindow(u8 x, u8 y, u8 winId){
    u8 left = WINH[winId] >> 8;
    u8 right = WINH[winId] & 0xFF;
    u8 top = WINV[winId] >> 8;
    u8 bottom = WINV[winId] & 0xFF;

    return x >= left && x < right && y >= top && y < bottom; 
}

void composeDispstat(){
    DISPSTAT &= 0xFFFFFFF8;
    if(VCOUNT >= SCREEN_HEIGHT)
        DISPSTAT |= 0b1;
    if(isHblank)
        DISPSTAT |= 0b10;
    if(VCOUNT == (DISPSTAT >> 8))
        DISPSTAT |= 0b100;
}

bool isBldTop(u8 type){
    return BLDCNT & (1 << type);
}

bool isBldBot(u8 type){
    return BLDCNT & (1 << (0x8 + type));
}

int brightnessBlend(int col, int mode){
    u8 ey = (BLDY & 0x1F);
    if(ey > 16)
        ey = 16;
    u16 out = 0;
    for(int i = 0; i < 3; i++){
        u8 component = (col >> (i*5)) & 0x1F;
        u8 factor = mode == 1 ? 31 - component : component;
        int new_component = component + ((mode * factor * ey) >> 4) ;
        if(new_component > 31)
            new_component = 31;
        if(new_component < 0)
            new_component = 0;
        out |= new_component << (i*5);
    }
    return out;
}

int colorBlend(int topCol, int botCol){
    u8 evTop = BLDALPHA & 0x1F;
    if(evTop > 16)
        evTop = 16;
    u8 evBot = (BLDALPHA >> 8) & 0x1F;
    if(evBot > 16)
        evBot = 16;
    u16 out = 0;
    for(int i = 0; i < 3; i++){
        u8 topComp = (topCol >> (i*5)) & 0x1F;
        u8 botComp = (botCol >> (i*5)) & 0x1F;
        int new_component = ((topComp * evTop) >> 4) +  ((botComp * evBot) >> 4) ;
        if(new_component > 31)
            new_component = 31;
        out |= new_component << (i*5);
    }
    return out;
}

int applyColorEffect(int inCol, u8 topType, u8 botType, int backCol, winType winType){
    if(winType != WIN_DISABLED){
        if(winType <= IN_WIN1)
            if(!(WININ & (1 << (5 + 8 * winType))))
                return inCol;
        if(winType == IN_OBJWIN && !(WINOUT & (1 << 0xD)))
            return inCol;
        if(winType == IN_WINOUT && !(WINOUT & (1 << 5)))
            return inCol;
    }

    u8 blend_mode = (BLDCNT >> 6) & 0b11;
    switch(blend_mode){ 
        case 0b00:
        return inCol;
        break;

        case 0b01:
        return isBldTop(topType) && isBldBot(botType) ? colorBlend(inCol, backCol) : inCol;
        break;

        case 0b10:
        return isBldTop(topType) ? brightnessBlend(inCol, 1) : inCol;
        break;

        case 0b11:
        return isBldTop(topType) ? brightnessBlend(inCol, -1) : inCol;
    }
}

void renderLineSprite(int y, u16* obj_attr_ptr, bool mapping_1d, u8* blend_info, bool* obj_win_mask){
    u8 mode = (obj_attr_ptr[0] >> 8) & 0b11;
    if(mode == 0b10)
        return;

    u8 gfx_mode = (obj_attr_ptr[0] >> 0xA) & 0b11;
    if(gfx_mode == 0b10)
        return;

    bool is_8bpp = (obj_attr_ptr[0] >> 0xD) & 1;
    bool h_flip;
    bool v_flip;
    int sprite_width;
    int sprite_height;
    int sprite_x;
    int sprite_y;
    int signed_sprite_x;
    int signed_sprite_y;
    int render_limit_width;
    int render_limit_height;
    u8 stride = is_8bpp ? 64 : 32;
    bool alpha_blending = ((obj_attr_ptr[0] >> 0xA) & 0b11) == 0b01;
    i16 aff_mat[4];
    winType win_type;
    getSpriteDim(obj_attr_ptr, &sprite_width, &sprite_height);
    getSpritePos(obj_attr_ptr, &sprite_x, &sprite_y);
    signed_sprite_x = sprite_x & 0x100 ? 0xFFFFFE00 | sprite_x : sprite_x;
    render_limit_width = sprite_width;
    render_limit_height = sprite_height;

    if(mode == 0b00){
        h_flip = (obj_attr_ptr[1] >> 0xC) & 1;
        v_flip = (obj_attr_ptr[1] >> 0xD) & 1;
    } else {
        u8 mat_idx = (obj_attr_ptr[1] >> 0x9) & 0x1F;
        aff_mat[0] = *(i16*)(&OAM[mat_idx*0x20 + 0x06]);
        aff_mat[1] = *(i16*)(&OAM[mat_idx*0x20 + 0x0E]);
        aff_mat[2] = *(i16*)(&OAM[mat_idx*0x20 + 0x16]);
        aff_mat[3] = *(i16*)(&OAM[mat_idx*0x20 + 0x1E]);
        if(mode == 0b11){
            render_limit_width <<= 1;
            render_limit_height <<= 1;
        }
    }

    int y_min = sprite_y & 255;
    int y_max = (y_min + render_limit_height) & 255;
    if(y_max < y_min)
        y_min -= 256;

    if(y < y_min || y >= y_max)
        return;

    u16 tid = obj_attr_ptr[2] & 0x3FF;
    u8 palBank = obj_attr_ptr[2] >> 0xC;

    for(int x = 0; x < render_limit_width; x++){
        int actual_sprite_x = signed_sprite_x + x;
        u8* blend_info_ptr = &blend_info[actual_sprite_x];
        if(actual_sprite_x < 0 || actual_sprite_x >= SCREEN_WIDTH)
            continue;
        if(!windowShouldDraw(actual_sprite_x, y, 4, obj_win_mask[actual_sprite_x], &win_type))
            continue;
        bool transparent;
        u8 px;
        u8 py;
        u8 offX;
        u8 offY;
        if(mode == 0b00){
            px = h_flip ? (sprite_width - 1 - x) % 8 : x % 8;
            py = v_flip ? (sprite_height - 1 - (y - y_min)) % 8 : (y - y_min) % 8;
            offX = h_flip ? (sprite_width - 1 - x) >> 3 : x >> 3;
            offY = v_flip ? (sprite_height - 1 - (y - y_min)) >> 3 : (y - y_min) >> 3;
        } else {
            i32 center_x = (sprite_width << 7);
            i32 center_y = (sprite_height << 7);
            i32 aff_x = (x << 8) - center_x;
            i32 aff_y = ((y - y_min) << 8) - center_y;
            if(mode == 0b11){
                aff_x -= sprite_width << 7;
                aff_y -= sprite_height << 7;
            }
            applyRotScaleMat(aff_mat, &aff_x, &aff_y);
            aff_x += center_x;
            aff_y += center_y;
            aff_x >>= 8;
            aff_y >>= 8;
            if(aff_x < 0 || aff_x >= sprite_width)
                continue;
            if(aff_y < 0 || aff_y >= sprite_height)
                continue;
            offX = aff_x >> 3;
            offY = aff_y >> 3;
            px = aff_x % 8;
            py = aff_y % 8;
        }
        u8* tilePtr = &VRAM[0x10000 +  tid*32];
        if(mapping_1d)
            tilePtr += (offX + offY * (sprite_width >> 3)) * stride;
        else
            tilePtr += (offX * stride + offY * 32 * 32);
        int sprite_col = getTilePixel(tilePtr, px, py, &PALETTE_RAM[512], palBank*32, is_8bpp, &transparent);
        if(!transparent) {
            int out_col;
            if(gfx_mode == 0b01 && isBldBot(blend_info[actual_sprite_x]))
                out_col = colorBlend(sprite_col, pixels[actual_sprite_x + y * SCREEN_WIDTH]);
            else 
                out_col = applyColorEffect(sprite_col, 4, blend_info[actual_sprite_x], pixels[actual_sprite_x + y * SCREEN_WIDTH], win_type);
            pixels[actual_sprite_x + y * SCREEN_WIDTH] = out_col;
            blend_info[actual_sprite_x] = 4;
        }
    }
}

void getObjMask(int y, u16* obj_attr_ptr, bool mapping_1d, bool* obj_win_mask){
    u8 mode = (obj_attr_ptr[0] >> 8) & 0b11;
    if(mode == 0b10)
        return;

    u8 gfx_mode = (obj_attr_ptr[0] >> 0xA) & 0b11;
    if(gfx_mode != 0b10)
        return;

    bool is_8bpp = (obj_attr_ptr[0] >> 0xD) & 1;
    bool h_flip;
    bool v_flip;
    int sprite_width;
    int sprite_height;
    int sprite_x;
    int sprite_y;
    int signed_sprite_x;
    int signed_sprite_y;
    int render_limit_width;
    int render_limit_height;
    u8 stride = is_8bpp ? 64 : 32;
    bool alpha_blending = ((obj_attr_ptr[0] >> 0xA) & 0b11) == 0b01;
    i16 aff_mat[4];
    getSpriteDim(obj_attr_ptr, &sprite_width, &sprite_height);
    getSpritePos(obj_attr_ptr, &sprite_x, &sprite_y);
    signed_sprite_x = sprite_x & 0x100 ? 0xFFFFFE00 | sprite_x : sprite_x;
    render_limit_width = sprite_width;
    render_limit_height = sprite_height;

    if(mode == 0b00){
        h_flip = (obj_attr_ptr[1] >> 0xC) & 1;
        v_flip = (obj_attr_ptr[1] >> 0xD) & 1;
    } else {
        u8 mat_idx = (obj_attr_ptr[1] >> 0x9) & 0x1F;
        aff_mat[0] = *(i16*)(&OAM[mat_idx*0x20 + 0x06]);
        aff_mat[1] = *(i16*)(&OAM[mat_idx*0x20 + 0x0E]);
        aff_mat[2] = *(i16*)(&OAM[mat_idx*0x20 + 0x16]);
        aff_mat[3] = *(i16*)(&OAM[mat_idx*0x20 + 0x1E]);
        if(mode == 0b11){
            render_limit_width <<= 1;
            render_limit_height <<= 1;
        }
    }

    int y_min = sprite_y & 255;
    int y_max = (y_min + render_limit_height) & 255;
    if(y_max < y_min)
        y_min -= 256;

    if(y < y_min || y >= y_max)
        return;

    u16 tid = obj_attr_ptr[2] & 0x3FF;
    u8 palBank = obj_attr_ptr[2] >> 0xC;

    for(int x = 0; x < render_limit_width; x++){
        int actual_sprite_x = signed_sprite_x + x;
        if(actual_sprite_x < 0 || actual_sprite_x >= SCREEN_WIDTH)
            continue;
        bool transparent;
        u8 px;
        u8 py;
        u8 offX;
        u8 offY;
        if(mode == 0b00){
            px = h_flip ? (sprite_width - 1 - x) % 8 : x % 8;
            py = v_flip ? (sprite_height - 1 - (y - y_min)) % 8 : (y - y_min) % 8;
            offX = h_flip ? (sprite_width - 1 - x) >> 3 : x >> 3;
            offY = v_flip ? (sprite_height - 1 - (y - y_min)) >> 3 : (y - y_min) >> 3;
        } else {
            i32 center_x = (sprite_width << 7);
            i32 center_y = (sprite_height << 7);
            i32 aff_x = (x << 8) - center_x;
            i32 aff_y = ((y - y_min) << 8) - center_y;
            if(mode == 0b11){
                aff_x -= sprite_width << 7;
                aff_y -= sprite_height << 7;
            }
            applyRotScaleMat(aff_mat, &aff_x, &aff_y);
            aff_x += center_x;
            aff_y += center_y;
            aff_x >>= 8;
            aff_y >>= 8;
            if(aff_x < 0 || aff_x >= sprite_width)
                continue;
            if(aff_y < 0 || aff_y >= sprite_height)
                continue;
            offX = aff_x >> 3;
            offY = aff_y >> 3;
            px = aff_x % 8;
            py = aff_y % 8;
        }
        u8* tilePtr = &VRAM[0x10000 +  tid*32];
        if(mapping_1d)
            tilePtr += (offX + offY * (sprite_width >> 3)) * stride;
        else
            tilePtr += (offX * stride + offY * 32 * 32);
        getTilePixel(tilePtr, px, py, &PALETTE_RAM[512], palBank*32, is_8bpp, &transparent);
        if(!transparent)
            obj_win_mask[actual_sprite_x] = true;
    }
}

void applyRotScaleMat(i16* mat, i32* x, i32* y){
    i32 new_x = mat[0]*(*x) + mat[1]*(*y);
    i32 new_y = mat[2]*(*x) + mat[3]*(*y);
    *x = new_x >> 8;
    *y = new_y >> 8;
}

i32 wrapValue(i32 input, i32 limit){
    return input >= 0 ? input % limit : limit - abs(input) % limit;
}

i32 geti28(i32 val){
    return val >> 27 ? val | 0xF8000000 : val & ~0xF8000000;
}
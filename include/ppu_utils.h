#include "integer.h"

#define INLINE static inline __attribute__ ((always_inline))

INLINE u16 getRgb555FromMemory(u8* palettePtr, int idx){
    return palettePtr[idx*2] | (palettePtr[idx*2+1] << 8);
}

INLINE u32 rgb555torgb888(u16 rgb555){
    u8 red = rgb555 & 0x1F;
    u8 green = (rgb555 >> 5) & 0x1F;
    u8 blue = (rgb555 >> 10) & 0x1F;
    red = red & 1 ? (red << 3) | 0b111 : red << 3;
    blue = blue & 1 ? (blue << 3) | 0b111 : blue << 3;
    green = green & 1 ? (green << 3) | 0b111 : green << 3;
    return color(red, green, blue);
}

INLINE bool isInsideWindow(u8 x, u8 y, u16 winh, u16 winv){
    u8 left = winh >> 8;
    u8 right = winh & 0xFF;
    u8 top = winv >> 8;
    u8 bottom = winv & 0xFF;

    return x >= left && x < right && y >= top && y < bottom; 
}

INLINE bool isBldTop(u8 bldcnt_reg, u8 type){
    return bldcnt_reg & (1 << type);
}

INLINE bool isBldBot(u8 bldcnt_reg, u8 type){
    return bldcnt_reg & (1 << (0x8 + type));
}

INLINE int brightnessBlend(u8 bldy, int col, int mode){
    u8 ey = (bldy & 0x1F);
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

INLINE int colorBlend(u8 bldalpha, int topCol, int botCol){
    u8 evTop = bldalpha & 0x1F;
    if(evTop > 16)
        evTop = 16;
    u8 evBot = (bldalpha >> 8) & 0x1F;
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

INLINE void getSpriteDim(u16* attrib_ptr, int* width_ptr, int* height_ptr){
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

INLINE u32 getTilePixel(u8* tilePtr, u8 px, u8 py, u8* palettePtr, u32 startPaletteIdx, bool is8bpp, bool* transparent){
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

INLINE void getSpritePos(u16* attrib_ptr, int* x_ptr, int* y_ptr){
    *y_ptr = attrib_ptr[0] & 0xFF;
    *x_ptr = attrib_ptr[1] & 0x1FF;
}

INLINE void applyRotScaleMat(i16* mat, i32* x, i32* y){
    i32 new_x = mat[0]*(*x) + mat[1]*(*y);
    i32 new_y = mat[2]*(*x) + mat[3]*(*y);
    *x = new_x >> 8;
    *y = new_y >> 8;
}

INLINE i32 wrapValue(i32 input, i32 limit){
    return input >= 0 ? input % limit : limit - abs(input) % limit;
}

INLINE i32 geti28(i32 val){
    return val >> 27 ? val | 0xF8000000 : val & ~0xF8000000;
}
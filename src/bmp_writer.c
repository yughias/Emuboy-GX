#include "bmp_writer.h"

#include <stdlib.h>
#include <string.h>

void* bmp_write(void* pixels, int width, int height, int bpp, size_t* size){
    const int BITMAP_FILE_HEADER = 14;
    const int BITMAPINOFHEADER_SIZE = 40;
    const int ROW_SIZE = (bpp*width+31)/32*4;
    const int PIXEL_ARRAY_SIZE = ROW_SIZE * height;
    const int FILE_SIZE = BITMAP_FILE_HEADER + BITMAPINOFHEADER_SIZE + PIXEL_ARRAY_SIZE;
    const int START_ARRAY_OFFSET = BITMAP_FILE_HEADER + BITMAPINOFHEADER_SIZE;
    unsigned char* bytes = malloc(FILE_SIZE);
    memset(bytes, 0, FILE_SIZE);
    
    // creating bitmap file header
    char signature[2] = "BM";
    memcpy(bytes+0x00, &signature, 2);
    memcpy(bytes+0x02, &FILE_SIZE, 4);
    memcpy(bytes+0x0A, &START_ARRAY_OFFSET, 4);

    // creating BITMAPINOFHEADER
    bytes[0x0E] = 40;
    memcpy(bytes+0x12, &width, 4);
    memcpy(bytes+0x16, &height, 4);
    bytes[0x1A] = 1;
    bytes[0x1C] = bpp;

    unsigned char* data_ptr = bytes + START_ARRAY_OFFSET;
    for(int y = 0; y < height; y++)
        memcpy(data_ptr + y*ROW_SIZE, pixels + (height-1-y)*width*(bpp/8),  width*(bpp/8));

    *size = FILE_SIZE;
    return bytes;
}
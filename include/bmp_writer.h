#ifndef __BMP_WRITER_H__
#define __BMP_WRITER_H__

#include <stddef.h>

void* bmp_write(void* pixels, int width, int height, int bpp, size_t* size);

#endif
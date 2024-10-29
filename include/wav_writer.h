#ifndef __WAV_WRITER_H__
#define __WAV_WRITER_H__

#include <stdint.h>
#include <stddef.h>

typedef struct wav_settings {
    uint16_t num_channels;
    uint32_t sample_rate;
    uint16_t bits_per_sample;
} wav_settings;

uint8_t* wav_create(void* buffer, size_t buffer_len, wav_settings* settings);
size_t wav_get_file_size(size_t buffer_len);

#endif
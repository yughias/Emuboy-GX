#include "wav_writer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct wav_header {
    char riff_header[4];    // "RIFF"
    uint32_t wav_size;      // File size - 8 bytes
    char wave_header[4];    // "WAVE"
    char fmt_header[4];     // "fmt "
    uint32_t fmt_chunk_size;// Size of the fmt chunk (16 for PCM)
    uint16_t audio_format;  // Audio format (1 for PCM)
    uint16_t num_channels;  // Number of channels
    uint32_t sample_rate;   // Sampling frequency
    uint32_t byte_rate;     // byte_rate = sample_rate * num_channels * bits_per_sample / 8
    uint16_t block_align;   // Block align = num_channels * bits_per_sample / 8
    uint16_t bits_per_sample; // Bits per sample (8, 16, etc.)
    char data_header[4];    // "data"
    uint32_t data_bytes;    // Number of data bytes
} wav_header;

size_t wav_get_file_size(size_t buffer_len){
    return sizeof(wav_header) + buffer_len;
}

uint8_t* wav_create(void* buffer, size_t buffer_len, wav_settings* settings){
    wav_header header;

    // Calculate values for header
    int num_samples = buffer_len / (settings->bits_per_sample / 8) / settings->num_channels;
    int byte_rate = settings->sample_rate * settings->num_channels * (settings->bits_per_sample / 8);
    int block_align = settings->num_channels * (settings->bits_per_sample / 8);
    int data_bytes = buffer_len;

    // Fill in WAV header fields
    memcpy(header.riff_header, "RIFF", 4);
    header.wav_size = 36 + buffer_len;
    memcpy(header.wave_header, "WAVE", 4);
    memcpy(header.fmt_header, "fmt ", 4);
    header.fmt_chunk_size = 16;
    header.audio_format = 1; // PCM
    header.num_channels = settings->num_channels;
    header.sample_rate = settings->sample_rate;
    header.byte_rate = byte_rate;
    header.block_align = block_align;
    header.bits_per_sample = settings->bits_per_sample;
    memcpy(header.data_header, "data", 4);
    header.data_bytes = data_bytes;

    uint8_t* out = malloc(sizeof(wav_header) + buffer_len);
    if(!out)
        return NULL;

    memcpy(out, &header, sizeof(wav_header));
    memcpy(out + sizeof(wav_header), buffer, buffer_len);

    return out;
}
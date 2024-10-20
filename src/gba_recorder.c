#include "gba_recorder.h"

#include "wav_writer.h"
#include "vector.h"
#include "apu.h"

#include <stdio.h>

static vector_t record_vector;
bool isRecordingAudio;

void recordAudioCallback(void* userdata, Uint8* stream, int len){
    atomic_fifo_t* fifo = userdata;
    int sample_len = len / sizeof(sample_t);
    for(int i = 0; i < sample_len; i++){
        ((sample_t*)stream)[i] = fifo->data[fifo->r_idx];
        vector_add(&record_vector, &((sample_t*)stream)[i], sizeof(sample_t));
        if(fifo->size >= sample_len){
            fifo->r_idx = (fifo->r_idx + 1) % SAMPLE_BUFFER_SIZE; 
            fifo->size -= 1;
        }
    }
}

void startGbaRecorder(){
    printf("recording started!\n");
    if(!record_vector.buffer){
        vector_init(&record_vector, (1 << 16));
    }
    isRecordingAudio = true; 
}

void stopGbaRecorder(const char* filename){
    isRecordingAudio = false;
    
    wav_settings settings = {
        .bits_per_sample = 16,
        .num_channels = 2,
        .sample_rate = 44100
    };

    u8* file_data = wav_create(record_vector.buffer, record_vector.size, &settings);
    size_t file_size = wav_get_file_size(record_vector.size);

    FILE* fptr = fopen(filename, "wb");
    if(fptr){
        fwrite(file_data, file_size, 1, fptr);
        fclose(fptr);
    }

    printf("audio saved!\n");

    record_vector.size = 0;
}

void freeGbaRecorder(){
    vector_free(&record_vector);
}
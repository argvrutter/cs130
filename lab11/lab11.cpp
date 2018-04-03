#include <cstdio>
#include <string.h>
#include <iostream>
#include <stdint.h>
/*
Author: Aiden Rutter
CS130 - Lab 11
Description:
Scale volume of left and right channels of a .wav file
*/
/*
WAV notes
fmt and data
*/

/*
arguments:
filein name(str),
fileoutname(str),
left channel scale(double),
right channel scale(double)
*/
//fmt offset is 12 from start
struct Fmt
{
    //char* chunkID[4];
    uint16_t wFormatTag;//should be 1
    uint16_t nChannels;//should equal to 2
    uint32_t nSamplesPerSec;
    uint32_t nAvgBytesPerSec;
    uint16_t nBlockAlign;
    uint16_t wBitsPerSample;
};

class Data
{
    Data(uint16_t bit_depth, )

}

int main(int argc, char **argv)
{
    FILE *fin, *fout;
    Fmt format;
    char chunkID[5];
    uint32_t data_size, chunk_size, junk_size, pos;
    unsigned long num_samples, sample_size;
    double duration_s;
    char *buf;

    if(argc < 5)
    {
        perror("Arguments: <in.wav> <out.wav> <left channel scale> <right channel scale>");
        return -1;
    }
    //open file
    fin = fopen(argv[1], "rb");
    if (fin == nullptr)
    {
        perror(argv[1]);
        return -1;
    }
    fout = fopen(argv[2], "wb");
    //read header

    fscanf(fin, "%4s", chunkID);
    if(strcmp(chunkID,"RIFF") != 0)
    {
        perror("Chunk ID (RIFF) different than expected");
        return -1;
    }
    fread(&chunk_size, 1, sizeof(chunk_size), fin);
    fscanf(fin, "%4s", chunkID);//WAV
    if(strcmp(chunkID,"WAVE") != 0)
    {
        perror("Chunk ID (WAVE) different than expected");
        return -1;
    }

    fscanf(fin, "%4s", chunkID);//fmt
    if(strcmp(chunkID,"fmt") != 0)
    {
        perror("Chunk ID (fmt) different than expected");
        return -1;
    }
    fseek(fin, 20, SEEK_SET);

    fread(&format, 1, sizeof(format), fin);
    printf("fmt: %hu %hu %u %u %hu %hu \n", format.wFormatTag, format.nChannels, format.nSamplesPerSec, format.nAvgBytesPerSec, format.nBlockAlign, format.wBitsPerSample);
    fseek(fin, 36, SEEK_SET);
    fscanf(fin, "%4s", chunkID);//data

    while(strcmp(chunkID,"data") != 0 && feof(fin) == 0)
    {
        printf("%s \n", chunkID);
        fread(&junk_size, 1, sizeof(junk_size), fin);
        fseek(fin, junk_size, SEEK_CUR);
        fscanf(fin, "%4s", chunkID);
        if(feof(fin) != 0)
        {
            perror("Reached EOF, data chunk not found");
            return -1;
        }
    }
    fscanf(fin, "%u", &data_size);
    printf("Size of data section: %d", data_size);

    num_samples = (8 * data_size) / (format.nChannels * format.wBitsPerSample);
    sample_size = (format.nChannels * format.wBitsPerSample)/8;
    duration_s = (double)chunk_size / format.nAvgBytesPerSec;

    pos = ftell(fin);
    buf = new char[chunk_size+8];
    rewind(fin);
    fread(&buf, 1, chunk_size+8, fin);
    fseek(fin, pos, SEEK_SET);
    //write

    for(int i=0; i<num_samples; i++)
    {
        pos = ftell(fin);
    }
    fclose(fin);
    fclose(fout);
    delete[] buf;
}

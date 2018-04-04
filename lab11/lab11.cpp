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
typedef char int24_t[3];
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
//n channel & templated type
template <class T>
struct Sample
{
    T *vals;
    Sample(uint32_t nChannels)
    {
        vals = new T[nChannels];
    }
    ~Sample()
    {
        delete[] vals;
    }
};
/*
struct Sample8 : public Sample
{
    uint8_t l,r;
};
struct Sample16 : public Sample
{
    int16_t l,r;
};
struct Sample24 : public Sample
{
    int24_t l,r;
};
struct Sample32 : public Sample
{
    int32_t l,r;
};
struct Sample64 : public Sample
{
    int64_t *samples;
    Sample64(uint32_t nChannels)
    {
        samples = new int64_t[nChannels];
    }
    ~Sample64()
    {
        delete[] samples;
    }
};
*/
int main(int argc, char **argv)
{
    FILE *fin, *fout;
    Fmt format;
    char chunkID[5];
    double lScale, rScale;
    uint32_t data_size, chunk_size, junk_size, pos, size;
    unsigned long num_samples, sample_size;
    double duration_s;
    char *headerBuf, *sampleBuf, fmt[20];
    //printf("struct sizes: %d , %d , %d , %d, %d", sizeof(Sample8), sizeof(Sample16), sizeof(Sample24), sizeof(Sample32), sizeof(Sample64));
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
    printf("%s pos %d\n", chunkID, ftell(fin));

    fread(&data_size, 1, sizeof(data_size), fin);
    printf("Size of data section: %d", data_size);

    num_samples = (8 * data_size) / (format.nChannels * format.wBitsPerSample);
    sample_size = (format.nChannels * format.wBitsPerSample)/8;
    duration_s = (double)chunk_size / format.nAvgBytesPerSec;

    printf("Num samples: %d \n", num_samples);
    pos = ftell(fin);

    fseek(fin, 0, SEEK_END);
    size = ftell(fin);
    headerBuf = new char[size-data_size+8];

    fseek(fin, 0, SEEK_SET);
    fflush(fin);
    printf("pos: %d read size: %d\n", ftell(fin), size-data_size+8);
    sprintf(fmt, "%%%uc", size-data_size+8);
    //fread(&headerBuf, 1, sizeof(headerBuf), fin);
    fscanf(fin, fmt, headerBuf);
    //fseek(fin, pos, SEEK_SET);
    fwrite(headerBuf, 1, sizeof(headerBuf), fout);

    /*
    switch(format.wBitsPerSample)
    {
        case 8:
        {
            samples = new Sample8[num_samples];
            //using Sample = Sample8;
            break;
        }
        case 16:
        {
            samples = new Sample16[num_samples];
            using Sample = Sample16;
            std::cout << sizeof(samples);
            break;
        }
        case 24:
        {
            samples = new Sample24[num_samples];
            using Sample = Sample24;
            break;
        }
        case 32:
        {
            samples = new Sample32[num_samples];
            using Sample = Sample32;
            break;
        }
        default:
        {
            printf("Bit depth %d not supported", format.wBitsPerSample);
            return -1;
        }
    }*/
    //auto samples;
    switch(format.wBitsPerSample)
    {
        case 8:
        {
            Sample<uint8_t> sample(3);
            std::cout << std::endl << "sizeof tempsample: " << sizeof(sample) << std::endl << std::endl;
            //using Sample = Sample8;
            break;
        }/*
        case 16:
        {
            samples = new Sample<uint8_t>[num_samples];

            break;
        }
        case 24:
        {
            samples = new Sample24[num_samples];
            using Sample = Sample24;
            break;
        }
        case 32:
        {
            samples = new Sample32[num_samples];
            using Sample = Sample32;
            break;
        }*/
        default:
        {
            printf("Bit depth %d not supported", format.wBitsPerSample);
            return -1;
        }
    }
    //parse headerBuf size of sample
    //fread(samples, 1, data_size, fin);
    //printf("sizeof samples %d bytes to read %d \n", sizeof(samples), data_size);

/*
    for(int i=0; i<num_samples; i++)
    {
        static_cast<Sample*>(samples)[i].l *= lScale;
        samples[i].r *= rScale;
    }*/
    //char *dataheaderBuf

    delete[] headerBuf;
    //delete[] samples;
    fclose(fin);
    fclose(fout);
}

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
template<class T>
T bufToInt(char* buf)
{
    T val = 0;
    if(sizeof(buf) < sizeof(T))
    {
        printf("Invalid buffer to int");
        throw;
    }
    for (uint32_t i = 0; i < sizeof(T); i++)
    {
        val |= (buf[i] << 8*(sizeof(T) - (i+1)));
    }
    return val;
}

int main(int argc, char **argv)
{
    FILE *fin, *fout;
    Fmt format;
    char chunkID[5];
    double scale[2];
    uint32_t data_size, chunk_size, junk_size, pos, size;
    unsigned long num_samples, sample_size, data_pos;
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
    scale[0] = atof(argv[3]);
    scale[1] = atof(argv[4]);
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
    data_pos = ftell(fin);
    fread(&data_size, 1, sizeof(data_size), fin);
    printf("Size of data section: %d", data_size);

    num_samples = (8 * data_size) / (format.nChannels * format.wBitsPerSample);
    sample_size = (format.nChannels * format.wBitsPerSample)/8;

    printf("Num samples: %d \n", num_samples);
    pos = ftell(fin);

    fseek(fin, 0, SEEK_END);
    size = ftell(fin);
    //headerBuf = new char[data_pos];
    headerBuf = (char*)malloc(data_pos);
    std::cout << "size of header: " << sizeof(headerBuf) << std::endl;

    fseek(fin, 0, SEEK_SET);
    fflush(fin);
    printf("pos: %d read size: %d\n", ftell(fin), size-data_size+8);
    sprintf(fmt, "%%%uc", data_pos);
    fread(headerBuf, 1, data_pos, fin);
    //fscanf(fin, fmt, headerBuf);
    //fseek(fin, pos, SEEK_SET);
    std::cout << "size of header: " << sizeof(&headerBuf[0]) << std::endl;
    fwrite(headerBuf, 1, sizeof(headerBuf), fout);
    sampleBuf = new char[data_size];
    sprintf(fmt, "%%%uc", data_size);

    //fread(&sampleBuf, 1, data_size, fin);
    fscanf(fin, fmt, sampleBuf);

    char miniBuf[format.wBitsPerSample/8];
    int i=0;
    bool j=0;
    uint8_t val8;
    int16_t val16;
    int24_t val24;
    int32_t val32;
    double temp;
    std::cout << "sizeof samplebuf " << sizeof(sampleBuf) << std::endl;
    for(char s : std::string(sampleBuf))
    {
        std::cout << "got here " << std::endl;

        if(i+1 == format.wBitsPerSample/8)
        {
            switch(i)
            {
                case 0://8
                {
                    //fwrite(static_cast<uint8_t>(static_cast<double>(static_cast<uint8_t>(miniBuf)) * scale[j]), sizeof(uint8_t), 1, fout);
                    val8 = bufToInt<uint8_t>(miniBuf);
                    temp = static_cast<double>(val8) * scale[j];
                    val8 = static_cast<uint8_t>(temp);
                    fwrite(&val8, sizeof(uint8_t), 1, fout);
                    break;
                }
                case 1://16
                {
                    val16 = bufToInt<int16_t>(miniBuf);
                    temp = static_cast<double>(val16) * scale[j];
                    val16 = static_cast<int16_t>(temp);
                    std::cout << "got here " << std::endl;

                    fwrite(&val16, sizeof(int16_t), 1, fout);
                    break;
                }
                case 2://24
                {
                    //val24 = bufToInt<int24_t>(miniBuf);
                    break;
                }
                case 3://32
                {
                    val32 = bufToInt<int32_t>(miniBuf);
                    temp = static_cast<double>(val32) * scale[j];
                    val32 = static_cast<int32_t>(temp);
                    fwrite(&val32, sizeof(int32_t), 1, fout);
                    break;
                }
                default:
                {
                    printf("Invalid bit depth.");
                    return -1;
                }
            }
            i=0;
            j=!j;
        }
        miniBuf[i] = s;
        i++;
    }


    delete[] headerBuf;
    delete[] sampleBuf;
    fclose(fin);
    fclose(fout);
}

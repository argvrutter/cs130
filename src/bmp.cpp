#include <fstream>
using namespace std;
#include <iostream>

struct Pixel {
//store pixel color channels
unsigned char b,g,r;
};

int main(int argc, char **argv) {
int offset, width, height, bytes_padding, size;
ifstream fin(argv[1], ios::binary | ios::ate);
size = fin.tellg();
ofstream fout(argv[2], ios::binary);
unsigned char bmp[size];

fin.seekg(0,ios::beg);
fin.read(reinterpret_cast<char*>(&bmp), sizeof(bmp));

//seek offset, width, height
offset = *reinterpret_cast<int*>(&bmp[10]);
width = *reinterpret_cast<int*>(&bmp[18]);
height = *reinterpret_cast<int*>(&bmp[22]);
bytes_padding = (width * sizeof(Pixel))%4;

//1d pixel pointer array
Pixel *image = new Pixel[(1+width)*height];
//iterates through each bit linearly and assigns to BRG

for(int i=0; i<(size-offset); i++)
{
  //b
  if(!(i%3)) {
    image[i/sizeof(Pixel)].b=(255-bmp[i + offset]);
  }
  //g
  else if(!((i-1)%sizeof(Pixel))) {
    image[i/sizeof(Pixel)].g=(255-bmp[i + offset]);
  }
  //r
  else if(!((i-2)%sizeof(Pixel))) {
    image[i/sizeof(Pixel)].r=(255-bmp[i + offset]);
  }
}

fout.write(reinterpret_cast<char*>(&bmp),offset);
fout.write(reinterpret_cast<char*>(image),(size-offset));
//invert, 255-red


fout.close();
fin.close();
delete[] image;

return 0;
}

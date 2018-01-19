/*
 * Author: Aiden Rutter
 * Lab 2: Thermostat
 * COSC130 - SPRING2018
 */

//          globals
unsigned short m_desiredBCDTemp, m_currentBCDTemp;
//display globals
const int DATA_DIO = 8;
const int LATCH_DIO = 4;
const int CLK_DIO = 7;
const int SEGMENTS[] = {0b11110001, 0b11110010, 0b11110100, 0b11111000};
const int DIGITS[] = {0b11000000, /* 0 */
0b11111001, /* 1 */ 
0b10100100, /* 2 */ 
0b10110000, /* 3 */ 
0b10011001, /* 4 */ 
0b10010010, /* 5 */
0b10000010, /* 6 */
0b11111000, /* 7 */ 
0b10000000, /* 8 */ 
0b10010000, /* 9 */ 
0b10111111, /* - <dash> */ 
0b11111111, /* <blank> */
};
const int NUM_SEGMENTS = sizeof(SEGMENTS) / sizeof(SEGMENTS[0]); 
const int NUM_DIGITS = sizeof(DIGITS) / sizeof(DIGITS[0]);
const int B_LEFT = A1, B_MID=A2, B_RIGHT = A3;

//          prototypes
/*
 * Read: returns value of specified digit of packed BCD
 * shift right 4*digit times
*/
int Read(short bcd, int digit);
/*
 * writes half a char, checks b/t 0 and 9 
 */
void Write(unsigned short &bcd, int digit, char value);
/*
 * Increments BCD value by one, if it's 9999 do nothing 
 * Can use non binary arithmetic
 */
void Inc(unsigned short &bcd);
/*
 * Decrements BCD by one, do nothing if 0. 
 * Can use non binary arithmetic
 */
void Dec(unsigned short &bcd);
/*
 * Returns encodes BCD value as normal integer value
 */
int GetBCD(short bcd);
/*
 * Takes a normal int and encodes it into bcd format. If < 0, encode as 0, if > 9999, encode as 9999 
 * hint use read function
 */
void setBCD(short &bcd, int value);

void setup() 
{
  //        pinmodes
  // LED's
  pinMode(10, OUTPUT);//heating element activated
  pinMode(13, OUTPUT);//power light

  // 8-seg display
  pinMode(CLK_DIO, OUTPUT);
  pinMode(DATA_DIO, OUTPUT);
  pinMode(LATCH_DIO, OUTPUT);

  //Potentiometer: temp, ignore changes +-5
  pinMode(A0, INPUT);

  //pushbuttons
  pinMode(B_LEFT, INPUT);//power
  pinMode(B_MID, INPUT);//temp up
  pinMode(B_RIGHT, INPUT);//temp down
  
}

void loop() 
{
  

}

int Read(short bcd, int digit)
{
  
}

void Write(unsigned short &bcd, int digit, char value)
{
  
}

void Inc(unsigned short &bcd)
{
  
}

void Dec(unsigned short &bcd)
{
  
}

int GetBCD(short bcd)
{
  
}

void setBCD(short &bcd, int value)
{
  
}


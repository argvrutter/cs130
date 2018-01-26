/*
   Author: Aiden Rutter
   Lab 3: Binary calculator
   COSC130 - SPRING2018
*/

//      globals
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
const int B_LEFT = A1, B_MID = A2, B_RIGHT = A3;

//prototypes
/*
 * Add using only logical operators, returns result.
 * recursive, so that means it is cool.
 */
short Add(short left, short right);
/*
 * Twos complement with logical operators
 */
short Twos(short value);
/*
 * multiplies via logical operators
 */
int Mul(short left, short right);
/*
 * sets digits n such
 */
void SetDigit(int segment, int value);
//sets us up with some sweet pins
void setup() 
{
  // 8-seg display
  pinMode(CLK_DIO, OUTPUT);
  pinMode(DATA_DIO, OUTPUT);
  pinMode(LATCH_DIO, OUTPUT);

  //pushbuttons
  pinMode(B_LEFT, INPUT);//power
  pinMode(B_MID, INPUT);//temp up
  pinMode(B_RIGHT, INPUT);//temp down

  //LEDS
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

}
//main loop, the big kahuna
void loop() 
{
  
}

void SetDigit(int segment, int value) 
{
  if((value >= 0 && value < NUM_DIGITS) && (segment >= 0 && segment < NUM_SEGMENTS)) 
  { 
    digitalWrite(LATCH_DIO, LOW); 
    shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, DIGITS[value]); 
    shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENTS[segment]); 
    digitalWrite(LATCH_DIO, HIGH);
  }
}

short Add(short left, short right)
{
  if(right == 0)
  {
    return left; 
  }
  else
  {
    return Add(left ^ right, (left & right) << 1);
  }
}

short Twos(short value)
{
  return Add(~value, 1);
}

int Mul(short left, short right)
{
  bool neg = false;
  int sum = 0;
  //checking signs
  if(left & (1 << 15))
  {
    left = Two(left);
    neg = !neg;
  }
  if(right & (1 << 15))
  {
    right = Two(right);
    neg = !neg;
  }
  //multiplication is just adding the left term right times.
  for(int i=0; i<right; i++)
  {
    sum = Add(sum, left);
  }
  if(neg)
  {
    sum = Twos(sum);
  }
  return sum;
}


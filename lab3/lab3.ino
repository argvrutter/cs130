/*
   Author: Aiden Rutter
   Lab 3: Binary calculator
   COSC130 - SPRING2018
*/
struct int_4
{
  signed t:4;
};
//      globals
int m_state=-1;
int m_total;
char m_num;
bool m_once=1;
unsigned short m_init;
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
/*
 * Returns the button state
 */
int readState();
/*
 * handles buttons and such
 */
void buttonHandler(int bState);
/*
 * displays da result
 */
void displayResult();
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
  pinMode(10, OUTPUT);//1
  pinMode(11, OUTPUT);//2
  pinMode(12, OUTPUT);//4
  pinMode(13, OUTPUT);//8

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
    left = Twos(left);
    neg = !neg;
  }
  if(right & (1 << 15))
  {
    right = Twos(right);
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

int readState()
{
  //button must be pressed, then released
  int priorState=m_state, n;
  if(((m_state > -1) && (m_state < 3)) && digitalRead(B_LEFT)
  == HIGH && digitalRead(B_MID) == HIGH && digitalRead(B_RIGHT) == HIGH)
  {
    if(!m_once && m_state == 0)
    {
      m_once = 1;
      //if held 3 seconds does not also add
      return -1;
    }
    n = m_state;
    m_state = -1;
    return n;
  }
  //negates number if held for 3 seconds
  if(digitalRead(B_LEFT)== LOW)
  {
    //saves time of first press
    if(priorState == -1)
    {
      m_init = millis();
      
    }
    else if((millis() - m_init > 3000) && m_once)
    {
      m_total = Twos(m_total);
      m_once = 0;
    }
    m_state = 0;
  }
  else if(digitalRead(B_MID) == LOW)
  {
    m_state = 1;
  }
  else if(digitalRead(B_RIGHT) == LOW)
  {
    m_state = 2;
  }
  return -1;
}

void buttonHandler(int bState)
{
  switch(bState)
  {
    case 0:
    {
      
      break;
    }
    case 1:
    {

      break;
    }
    case 2:
    {
      
      break;
    }
  }
}


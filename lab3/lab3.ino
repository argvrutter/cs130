/*
   Author: Aiden Rutter
   Lab 3: Binary calculator
   COSC130 - SPRING2018
*/
// takes a byte but only uses 4 bits of it
struct int_4
{
  signed t:4;
};
//      globals
int_4 m_num;
int m_state=-1;
int m_total=0;
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
  Serial.begin(9600);
  m_num.t = 0;
}
//main loop, the big kahuna
void loop() 
{
  buttonHandler(readState());
  displayResult();
  //short temp = 1;
  //Serial.println('\n');
  //Serial.println(Twos(temp));
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
  return Add((~value), 1);
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
      Serial.println('here');
      m_total = Twos(m_total);
      m_once = 0;
    }
    m_state = 0;
  }
  // add logic so that if a2, a3 held @ same time, reset current value
  else if(digitalRead(B_MID) + digitalRead(B_RIGHT) == LOW)
  {
    m_state = 3;
  }
  else if(digitalRead(B_MID) == LOW && priorState != 3)
  {
    m_state = 1;
  }
  else if(digitalRead(B_RIGHT) == LOW && priorState != 3)
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
      m_num.t++;
      break;
    }
    case 1:
    {
      m_total = Add(m_total, m_num.t);
      break;
    }
    case 2:
    {
      m_total = Mul(m_total, m_num.t);
      break;
    }
    case 3:
    {
      Serial.println("got here 2");
      m_total = 0;
      break;
    }
  }
  if(m_total > 999)
  {
    m_total = 999;
  }
  else if(m_total < -999)
  {
    m_total = -999;
  }
}

void displayResult()
{
  if( m_total >= 0)
  {
    for(int i=0; i<4; i++)
    {
      if(m_num.t & (1 << i))
      {
        digitalWrite(10+i, LOW);
      }
      else
      {
        digitalWrite(10+i, HIGH);
      }
      //formula for extraction of digit
      SetDigit((3-i), (m_total / static_cast<int>(pow(10, i)) % 10));
    }
  }
  else
  {
    SetDigit(0,10);
    for(int i=1; i<4; i++)
    {
      //Serial.println(m_total);
      //Serial.println((abs(m_total) / static_cast<int>(pow(10, i)) % 10));
      SetDigit(i, (abs(m_total) / static_cast<int>(pow(10, (3-i))) % 10));
    }
  }
}


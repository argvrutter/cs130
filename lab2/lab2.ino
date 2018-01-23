/*
   Author: Aiden Rutter
   Lab 2: Thermostat
   COSC130 - SPRING2018
*/

//          globals
short m_desiredBCDTemp, m_currentBCDTemp;
int m_state=-1;
bool m_on;
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

//          prototypes
/*
   Read: returns value of specified digit of packed BCD
   shift right 4*digit times
*/
int Read(short bcd, int digit);
/*
   writes half a char, checks b/t 0 and 9
*/
void Write(short &bcd, int digit, char value);
/*
   Increments BCD value by one, if it's 9999 do nothing
   Can use non binary arithmetic
*/
void Inc(short &bcd);
/*
   Decrements BCD by one, do nothing if 0.
   Can use non binary arithmetic
*/
void Dec(short &bcd);
/*
   Returns encodes BCD value as normal integer value
*/
int GetBCD(short bcd);
/*
   Takes a normal int and encodes it into bcd format. If < 0, encode as 0, if > 9999, encode as 9999
   hint use read function
*/
void setBCD(short &bcd, int value);
/*
 * Provided LCD setting function
 */
void SetDigit(int segment, int value);
/*
 * Returns the button state
 */
int readState();
/*
 * manages actions taken upon reading change in state
 */
void handleInput(int bState);
/*
 * self explanatory displays the temperature
 */
void displayTemp();
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

  //init desired and current
  setBCD(m_desiredBCDTemp, analogRead(A0));
  setBCD(m_currentBCDTemp, analogRead(A0));
}

void loop()
{
  displayTemp();
  handleInput(readInput());
}

int Read(short bcd, int digit)
{
  short mask = 0xf << (digit << 2);
  bcd &= mask;
  bcd >>= (digit << 2);
  return bcd;
}

void Write(short &bcd, int digit, char value)
{
  short mask= 0xf << (digit << 2);
  mask = ~mask;
  if(value > 9)
  {
    return;
  }
  //wipes numbers at given digit
  bcd &= mask;
  //replaces with value
  bcd |= static_cast<short>(value) << (digit << 2);
}

void Inc(short &bcd)
{
  //a bit more efficient than just reading the int value, adding, writing back to bcd
  int value;
  for(int i=0; i<4; i++)
  {
    value=Read(bcd, i);
    if(value < 9)
    {
      Write(bcd, i, value+1);
      return;
    }
    else
    {
      //assuming value = 9
      Write(bcd, i, 0);
    }
  }
  //bcd was 9999
  bcd = 0b1001100110011001;
}

void Dec(short &bcd)
{
  int value;
  bool carry=false;
  for(int i=0; i<4; i++)
  {
    value=Read(bcd, i);
    if(value > 0)
    {
      Write(bcd, i, value-1);
      if(carry)
      {
        Write(bcd, i-1, 9);
        carry = false;
      }
      return;
    }
    else
    {
       carry = true;
    }
  }
}

int GetBCD(short bcd)
{
  int digit, value=0;
  for(int i=0; i<4; i++)
  {
    digit = Read(bcd, i);
    value |= digit << (i << 2); 
  }
  return value;
}

void setBCD(short &bcd, int value)
{
  char digit;
  if(value > 9999)
  {
    value = 9999;
  }
  else if(value < 0)
  {
    value = 0;
  }
  for(int i=0; i<4; i++)
  {
    //math, extracts digit
    digit = (value / static_cast<int>(pow(10, i))) % 10;
    Write(bcd, i, digit);
  }
}

void SetDigit(int segment, int value) 
{
  if ((value >= 0 && value < NUM_DIGITS) && (segment >= 0 && segment < NUM_SEGMENTS)) 
  { 
    digitalWrite(LATCH_DIO, LOW); 
    shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, DIGITS[value]); 
    shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENTS[segment]); 
    digitalWrite(LATCH_DIO, HIGH);
  }
}

int readState()
{
  //button must be pressed, then released
  int temp = analogRead(A0);
  // device is on and desired temp greater than current
  if(m_on && (GetBCD(m_desiredBCDTemp) > GetBCD(m_currentBCDTemp)))
  {
    digitalWrite(10, LOW);
    if(abs(temp-GetBCD(m_currentBCDTemp)) > 5)
    {
      setBCD(m_currentBCDTemp, temp);
    }
  }
  else
  {
    digitalWrite(10, HIGH);
  }
  if(((m_state > -1) && (m_state < 3)) && digitalRead(B_LEFT)
  == HIGH && digitalRead(B_MID) == HIGH && digitalRead(B_RIGHT) == HIGH)
  {
    return m_state;
  }
  if(digitalRead(B_LEFT)== LOW)
  {
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
  else
  {
    m_state = -1;
    return m_state;
  }
}

void handleInput(int bState)
{
  switch(bState)
  {
    case -1:
    {
      
    }
    case 0:
    {
      
    }
    case 1:
    {
      
    }
    case 2:
    {
      
    }
  }
}

void displayTemp()
{
  for(int i=0; i<4; i++)
  {
    
  }
}




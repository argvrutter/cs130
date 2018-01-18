/*
 * Author: Aiden Rutter
 * Lab 1: Time Bomb
 * COSC 130 - Spring 2018
 */
//constants
int m_tryCount, m_second;
long m_code[4];
unsigned long m_elapsed, m_timeout, m_lastCount, m_lastPress=0;
bool m_disarm;
const int B_LEFT = A1, B_MID=A2, B_RIGHT = A3;

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

//prototypes
void countdown();
void delayAndRead(int guess);
int readState();
void SetDigit(int segment, int value);

void setup() 
{
  // pushbuttons
  pinMode(B_LEFT, INPUT);
  pinMode(B_MID, INPUT);
  pinMode(B_RIGHT, INPUT);
  
  // LED's
  pinMode(10, OUTPUT);//bottom LED
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);//top LED
  
  // Buzzer
  pinMode(3, OUTPUT);
  
  // 8-seg display
  pinMode(CLK_DIO, OUTPUT);
  pinMode(DATA_DIO, OUTPUT);
  pinMode(LATCH_DIO, OUTPUT);

  //random seed
  randomSeed(analogRead(A0)+millis());
}
//main loop
void loop() 
{
  //resetting variables, generating new code
  unsigned long ms_init = millis();
  m_tryCount = 0;
  m_second=25;
  m_disarm = 0;
  for(int i=0; i<4; i++)
  {
    m_code[i] = random(3);
    digitalWrite((10+i), HIGH);
  }
  digitalWrite(3, HIGH);
  
  while((millis() < (ms_init + 25000)) && !m_disarm)
  {
    //counts down from 25
    countdown();
    //manages interrupts of countdown
    delayAndRead(readState());
  }
  if(m_disarm)
  {
    ms_init = millis();
    while(millis() < (ms_init + 3000))
    {
      for(int i=0; i<4; i++)
      {
        SetDigit(i, 10); 
      }
    }
  }
  else
  {
    ms_init = millis();
    digitalWrite(3, LOW);
    while(millis() < (ms_init + 3000))
    {
      for(int i=0; i<4; i++)
      {
        SetDigit(i, 0); 
      }
    }
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
  //one button press per 250 ms
  if(millis() - m_lastPress > 250)
  {
    if(digitalRead(B_LEFT)== LOW)
    {
      m_tryCount++;
      m_lastPress = millis();
      return 0;
    }
    else if(digitalRead(B_MID) == LOW)
    {
      m_tryCount++;
      m_lastPress = millis();
      return 1;
    }
    else if(digitalRead(B_RIGHT) == LOW)
    {
      m_tryCount++;
      m_lastPress = millis();
      return 2;
    }
  }
  return -1;
}
void countdown()
{
  if((millis() - m_lastCount) > 1000)
  {
     m_second--;
     m_lastCount = millis();
  }
  SetDigit(0, 0);
  SetDigit(1, 0);
  SetDigit(2, (m_second/10));
  SetDigit(3, (m_second%10));
}

//handles button input
void delayAndRead(int guess)
{
  if(guess == -1)
  {
    return;
  }
  if(guess == m_code[m_tryCount-1])
  {
    digitalWrite((9+m_tryCount),LOW); 
    if(m_tryCount == 4)
    {
      m_disarm = true;
    }
  }
  else
  {
    for(int i=0; i<4; i++)
    {
      digitalWrite((10+i), HIGH);
    }
    m_tryCount = 0;
  }
}


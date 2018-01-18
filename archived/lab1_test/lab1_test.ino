/*
 * Author: Aiden Rutter
 * Lab 1: Time Bomb
 */

//globals
const int DATA_DIO = 8;
const int LATCH_DIO = 4;
const int CLK_DIO = 7;
int guess=0;
int response, j;
int code[4];
const int B_LEFT = A1, B_MID=A2, B_RIGHT = A3;
unsigned long m_ms;

//prototypes
void SetDigit(int segment, int value);
void myDelay(unsigned long ms);
int readState();

void setup() {
  //debugging
  Serial.begin(9600);
  
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

}
int readState()
{
  //assumes 1 button press at a time
  
  if(digitalRead(B_LEFT)== HIGH)
  {
    return 0;
    guess++;
  }
  else if(digitalRead(B_MID) == HIGH)
  {
    guess++;
    return 1;
  }
  else if(digitalRead(B_RIGHT) == HIGH)
  {
    guess++;
    return 2;
  }
  else
  {
    return -1;
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
void myDelay(unsigned long ms)
{
  unsigned long ms_init = millis();
  //refreshes all of LCD's segments for the duration of the delay
  while(millis() < (ms + ms_init))
  {
    response = readState();
    if(response != -1)
    {
      if(response == code[guess])
      {
        Serial.println("guess: ");
        Serial.print(guess);
        digitalWrite((10+guess),HIGH); 
        if(guess == 3)
        {
          for(int i=0; i<4; i++)
          {
            SetDigit(i, 10);
          }
          break;
        }
      }
      
      SetDigit(2, (j/10));
      SetDigit(3, (j%10));
    }
    else
    {
       guess=0;
    }
  }
  
}
void loop() 
{
  //code generation
  digitalWrite(3, LOW);
  randomSeed(analogRead(A0)+millis());
  guess = 0;
  for(int i=0; i<4; i++)
  {
    code[i] = random(0, 2);
    digitalWrite((10+i), LOW);
  }
  //25 second countdown
  for(j=25; j>0; j--)
  {
  
    myDelay(1000);
    if((guess == 3) && (response == code[guess]))
    {
      break; 
    }
  }
  if((guess == 3) && (response == code[guess]))
  {
      
  }
  else
  {
    for(int i=0; i<4; i++)
    {
      SetDigit(i, 0); 
    }
    //digitalWrite(3, HIGH);
    delay(3000);
  }
}

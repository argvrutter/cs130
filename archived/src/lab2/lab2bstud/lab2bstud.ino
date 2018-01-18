////////////////////////////////////////
// COSC 130, Lab 2 Template File
// Modify the functions below
//
////////////////////////////////////////

String decimal_to_bin(int input)
{
  String output;
  int mask1, mask2;
  // Write the binary value of input into
  // the string output
  for(int i=31; i >= 0; i--)
  {
    mask1 = (1 << i);
    mask2 = mask1 & input;
    if(mask1 == mask2)
    {
      output += 1;
    }
    else
    {
      output += 0;
    }
  }
  return output;
}
const char hexValues[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
String decimal_to_hex(int input)
{
  String output;
  int mask;
  // Write the hex value of input into
  // the string output
  for(int i=7; i>=0; i--)
  {
    mask = (15 << (i*4));
    mask = input & mask;
    mask = (mask >> (i*4));
    if(mask >= 0)
    {
      output += hexValues[mask];
    }
    else
    {
      output += hexValues[16+mask];
    }
  }
  return output;
}

String decimal_to_oct(int input)
{
  String output;
  int mask;
  // Write the octal value of input into
  // the string output
  mask = (3 << 30);
  mask = input & mask;
  mask = (mask >> 30);
  if(mask >= 0)
  {
    output += mask;
  }
  else
  {
    output += (4+mask);
  }
  for(int i=9; i>=0; i--)
  {
    mask = (7 << i*3);
    mask = input & mask;
    mask = (mask >> i*3);
    if(mask >= 0)
    {
      output += mask;
    }
    else
    {
      output += (8+mask);
    }
  }
  return output;
}

////////////////////////////////////////
//
// DO NOT MODIFY ANY FUNCTIONS BELOW
//
////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial && (Serial.available() > 0)) {
    String input = Serial.readString();
    int i_input = input.toInt();

    Serial.println("Dec: " + input);
    Serial.println("Bin: " + decimal_to_bin(i_input));
    Serial.println("Oct: " + decimal_to_oct(i_input));
    Serial.println("Hex: " + decimal_to_hex(i_input));
    Serial.print("\n");
    
  }
  else {
    delay(115);
  }
}

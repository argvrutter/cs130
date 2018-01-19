/*
 * Author: Aiden Rutter
 * Lab 2: Thermostat
 * COSC130 - SPRING2018
 */

//globals
unsigned short m_desiredBCDTemp, m_currentBCDTemp;
//prototypes
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
 * Returns BCD value as normal integer value
 */
int GetBCD(short bcd);
/*
 * Takes a normal int and encodes it into bcd format. If < 0, encode as 0, if > 9999, encode as 9999 
 */
void setBCD(short &bcd, int value);

void setup() {
  

}

void loop() {
  

}

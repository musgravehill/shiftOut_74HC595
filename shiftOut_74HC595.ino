/*
Shift registers at 74HC595
 
 ===TODO===
 ^^ - inverted pin
 
 ÊŇ--GND registers controls output
 ÊŇ--VCC set all output is LOW (high impedans)
 
 ŘŜŤ--GND  reset 74HC595
 ŘŜŤ--VCC  normal mode
 
 ÊŇ---10k-VCC 
 
 */

uint8_t dataPin = 3; //DS of 74HC595
uint8_t latchPin = 4;//ST_CP of 74HC595
uint8_t clockPin = 5; //SH_CP of 74HC595
uint8_t enInvertedPin = 6; //ÊŇ of 74HC595 (inverted)enInvertedPin

const uint8_t dataArraySize = 6;
byte dataByte;
byte dataArray[dataArraySize];

void setup() {  
  pinMode(dataPin, OUTPUT);  
  pinMode(latchPin, OUTPUT); 
  pinMode(clockPin, OUTPUT); 
  pinMode(enInvertedPin, OUTPUT); 

  digitalWrite(enInvertedPin, 1); //all outputs is LOW

  dataArray[0] = 0b10000000;
  dataArray[1] = 0b01000000;
  dataArray[2] = 0b00100000;
  dataArray[3] = 0b00100000;
  dataArray[4] = 0b01000000;
  dataArray[5] = 0b10000000;  

  testBlinkAll();
}

void loop() {  
  for (int j = 0; j < dataArraySize; j++) {    
    dataByte = dataArray[j];    
    pushByte(dataByte);     
    delay(80);
  }
}

void testBlinkAll() { 
  pushByte(0b11111111);
  delay(3000);
  
  pushByte(0b00000000);
  delay(3000);
}

void pushByte(byte dataByte){
  //MSBFIRST,LSBFIRST (Most Significant Bit First, or, Least Significant Bit First) 
  digitalWrite(enInvertedPin, 1); //all outputs is LOW
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, LSBFIRST, dataByte);  
  digitalWrite(latchPin, 1);
  digitalWrite(enInvertedPin, 0); //all outputs are controlled by registers
}


/*void shiftOutMy(int myDataPin, int myClockPin, byte myDataOut) {
 // This shifts 8 bits out MSB first, 
 //on the rising edge of the clock,
 //clock idles low
 
 //internal function setup
 int i=0;
 int pinState;
 pinMode(myClockPin, OUTPUT);
 pinMode(myDataPin, OUTPUT);
 
 //clear everything out just in case to
 //prepare shift register for bit shifting
 digitalWrite(myDataPin, 0);
 digitalWrite(myClockPin, 0);
 
 //for each bit in the byte myDataOut�
 //NOTICE THAT WE ARE COUNTING DOWN in our for loop
 //This means that %00000001 or "1" will go through such
 //that it will be pin Q0 that lights. 
 for (i=7; i>=0; i--)  {
 digitalWrite(myClockPin, 0);
 
 //if the value passed to myDataOut and a bitmask result 
 // true then... so if we are at i=6 and our value is
 // %11010100 it would the code compares it to %01000000 
 // and proceeds to set pinState to 1.
 if ( myDataOut & (1<<i) ) {
 pinState= 1;
 }
 else {  
 pinState= 0;
 }
 
 //Sets the pin to HIGH or LOW depending on pinState
 digitalWrite(myDataPin, pinState);
 //register shifts bits on upstroke of clock pin  
 digitalWrite(myClockPin, 1);
 //zero the data pin after shift to prevent bleed through
 digitalWrite(myDataPin, 0);
 }
 
 //stop shifting
 digitalWrite(myClockPin, 0);
 }
 */









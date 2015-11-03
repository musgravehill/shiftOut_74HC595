/*
Shift registers at 74HC595
 */

int dataPin = 3; //DS of 74HC595
int latchPin = 4;//ST_CP of 74HC595
int clockPin = 5; //SH_CP of 74HC595


const uint8_t dataArraySize = 6;
byte dataByte;
byte dataArray[dataArraySize];

void setup() {  
  pinMode(dataPin, OUTPUT);  
  pinMode(latchPin, OUTPUT); 
  pinMode(clockPin, OUTPUT); 

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
    digitalWrite(latchPin, 0);    
    //MSBFIRST,LSBFIRST (Most Significant Bit First, or, Least Significant Bit First) 
    shiftOut(dataPin, clockPin, LSBFIRST, dataByte);    
    digitalWrite(latchPin, 1);
    delay(100);
  }
}

void testBlinkAll() { 
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, 0b11111111);  
  digitalWrite(latchPin, 1);
  delay(3000);

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000);  
  digitalWrite(latchPin, 1);
  delay(3000);
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






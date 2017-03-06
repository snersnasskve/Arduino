/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
  #include "pitches.h"
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 2;

int ditLength = 50;

// the setup routine runs once when you press reset:
void setup() {                
    
}

// the loop routine runs over and over again forever:
void loop() {
   delay(3000);               // wait for a second

  morseL();
  morseO();
  morseN();
  morseD();
  morseO();
  morseN();
  delay(6 * ditLength);
  morseB();
  morseA();
  morseB();
  morseY();
  delay(12 * ditLength);

}

void myLong(){
  /*
    // wait for a second
digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);  
*/
    tone(8, NOTE_C6);
   int pauseBetweenNotes = 3 * ditLength;
   delay(pauseBetweenNotes);
   noTone(8);
   delay(ditLength);               // wait for a second

// wait for a second

}

void myShort(){
  /*
    // wait for a second
digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(500);               // wait for a second
*/
    tone(8, NOTE_C6);
    int pauseBetweenNotes = ditLength;
    delay(pauseBetweenNotes);
    noTone(8);
    delay(ditLength);               // wait for a second

}

void morseA(){
  myShort();
  myLong();
  delay(3 * ditLength);
}

void morseB(){
  myLong();
  myShort();
  myShort();
  myShort();
  delay(3 * ditLength);
}

void morseD(){
  myLong();
  myShort();
  myShort();
  delay(3 * ditLength);
}

void morseL(){
  myShort();
  myLong();
  myShort();
  myShort();
  delay(3 * ditLength);
}

void morseN(){
  myLong();
  myShort();
  delay(3 * ditLength);
}

void morseO(){
  myLong();
  myLong();
  myLong();
  delay(3 * ditLength);
}

void morseY(){
  myLong();
  myShort();
  myLong();
  myLong();
  delay(3 * ditLength);
}



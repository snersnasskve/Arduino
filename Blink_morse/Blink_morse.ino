/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 12;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
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
  delay(1000);
  morseB();
  morseA();
  morseB();
  morseY();
  delay(2000);

}

void myLong(){
    // wait for a second
digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second

}

void myShort(){
    // wait for a second
digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(500);               // wait for a second

}

void morseA(){
  myShort();
  myLong();
  delay(1000);
}

void morseB(){
  myLong();
  myShort();
  myShort();
  myShort();
  delay(1000);
}

void morseD(){
  myLong();
  myShort();
  myShort();
  delay(1000);
}

void morseL(){
  myShort();
  myLong();
  myShort();
  myShort();
  delay(1000);
}

void morseN(){
  myLong();
  myShort();
  delay(1000);
}

void morseO(){
  myLong();
  myLong();
  myLong();
  delay(1000);
}

void morseY(){
  myLong();
  myShort();
  myLong();
  myLong();
  delay(1000);
}



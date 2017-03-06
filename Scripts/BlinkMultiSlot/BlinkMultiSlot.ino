/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led11 = 11;
int led9 = 9;
int led7 = 7;
int led5 = 5;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led11, OUTPUT);     
  pinMode(led9, OUTPUT);     
  pinMode(led7, OUTPUT);     
  pinMode(led5, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led11, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led11, LOW);    // turn the LED off by making the voltage LOW
 // delay(1000);               // wait for a second
  digitalWrite(led9, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led9, LOW);    // turn the LED off by making the voltage LOW
  //delay(1000);               // wait for a second
  digitalWrite(led7, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led7, LOW);    // turn the LED off by making the voltage LOW
 // delay(1000);               // wait for a second
  digitalWrite(led5, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led5, LOW);    // turn the LED off by making the voltage LOW
  //delay(1000);               // wait for a second
}

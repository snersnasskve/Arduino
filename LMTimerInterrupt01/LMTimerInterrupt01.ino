#include <TimerOne.h>

int motherLoopLedBlue = 7;
int timerInterruptLed = 8;

volatile boolean onOrOff = LOW;        // set led on or off inside the ISR
volatile unsigned long functionCounter = 0; // count how many times the function is called

unsigned int motherLoopCounter = 0; // to pick up the value of the function loop

void setup() {
  
  pinMode(timerInterruptLed, OUTPUT);
  pinMode(motherLoopLedBlue, OUTPUT);
  Timer1.initialize(2000000); // 2 million microseconds is 2 seconds
  Timer1.attachInterrupt(function);
  Serial.begin(9600);

}

void loop() {
  noInterrupts();
  motherLoopCounter =  functionCounter;
  interrupts();
  Serial.print("function is called = ");
  Serial.println(motherLoopCounter);

 if(motherLoopCounter == 12){
  functionCounter = 0; 
  }

  
  digitalWrite(motherLoopLedBlue, HIGH);
  delay(500);
  digitalWrite(motherLoopLedBlue, LOW);
  delay(500);
}

//interrupt service routine function
void function(){
  
  digitalWrite(timerInterruptLed, onOrOff);
  onOrOff =! onOrOff;
  functionCounter  ++;
  
  }

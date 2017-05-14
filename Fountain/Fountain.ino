/*
WDT BYTE variables for setting timer value
WTT0_30MS
WDTO_60MS
WDTO_120MS
WDTO_250MS
WDTO_500MS
WDTO_1S
WDTO_2S
WDTO_4S
WDTO_8S
*/
#include <avr/sleep.h>
// We use part of the WDT library, but have to use registers as well since library does not support interrupt for WDT
#include <avr/wdt.h>

int photocellLeft   = A2;
int photocellRight  = A3;

//int sleepTime  = 100000; // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
long sleepTime = 100000;
int dir = 1;

int motorSpeed = 1200;  //variable to set stepper speed

 int motorPin1 = 4;    // Blue   - 28BYJ48 pin 1
 int motorPin2 = 5;    // Pink   - 28BYJ48 pin 2
 int motorPin3 = 6;   // Yellow - 28BYJ48 pin 3
 int motorPin4 = 7;   // Orange - 28BYJ48 pin 4

int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};

void setup() {
  wdt_disable(); //  Datasheet recommeds disabling WDT right away in case of low probability event
  // put your setup code here, to run once:
  pinMode(motorPin1, OUTPUT);
   pinMode(motorPin2, OUTPUT);
   pinMode(motorPin3, OUTPUT);
   pinMode(motorPin4, OUTPUT);
   
   //  Timer1.initialize(40000); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
 // Timer1.attachInterrupt( wakeUp ); // attach the service routine here



   Serial.begin(9600);
   
}

void loop() {
        //LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  

  Serial.println("looping");
   //delay(3000);

  
  // put your main code here, to run repeatedly:
   Serial.print("Left = ");
     int brightnessLeft = analogRead(photocellLeft);  
     char str[15];
     sprintf(str, "%d", brightnessLeft);
     Serial.println(str);     // the raw analog reading

     Serial.print("Right = ");
     int brightnessRight = analogRead(photocellRight);  
     sprintf(str, "%d", brightnessRight);
     Serial.println(str);     // the raw analog reading
     if (brightnessRight - 5 > brightnessLeft) {
        Serial.println("Moving to the right");    
          for (int i = 0 ; i < 20 ; i++) {
           moveStep(1);
       }

     }
      else if (brightnessLeft - 5 > brightnessRight)
      {
          Serial.println("Moving to the Left");    
          for (int i = 0 ; i < 20 ; i++) {
              moveStep(-1);
          }

      }
        
  delay(500);
  delayWDT(WDTO_1S);
  
}

///////
//  Interrupt
///////
void wakeUp() {
  Serial.println("woken");
    //  detachInterrupt(0);
}

void delayWDT(byte timer) {
  sleep_enable(); // enable the sleep capability
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); //  set the type of sleep mode. Default is idle
}
/*
void sleepNow()
{
    // Choose our preferred sleep mode:
    set_sleep_mode(SLEEP_MODE_ADC);
 
    // Set sleep enable (SE) bit:
    sleep_enable();
 
    // Put the device to sleep:
    sleep_mode();
 
    // Upon waking up, sketch continues from this point.
    sleep_disable();
}
*/

void moveStep(int dir)
{
   for(int motorPhase = 0; motorPhase < 8; motorPhase++)
   {
     if (dir == 1) {
 
        setOutputDir(motorPhase);
     } else
    
        setOutputDir(7-motorPhase);
      
    }
     delayMicroseconds(motorSpeed);
}



void setOutputDir(int motorPhase)
{

   digitalWrite(motorPin1, bitRead(lookup[motorPhase], 0));
   digitalWrite(motorPin2, bitRead(lookup[motorPhase], 1));
   digitalWrite(motorPin3, bitRead(lookup[motorPhase], 2));
   digitalWrite(motorPin4, bitRead(lookup[motorPhase], 3));

}


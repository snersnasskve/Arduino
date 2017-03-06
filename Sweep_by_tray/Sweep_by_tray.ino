// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
int photocellPin = 0;
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
} 

 

 
void loop() 
{ 
  int lightLevel = analogRead(photocellPin);
  Serial.print("Light level: ");
  Serial.println(lightLevel);
  
  if  (lightLevel < 100) 
  {
    if ( pos < 180)
    {
    pos ++;
    }  
  }  

  else 
  { 
    if (pos > 0)
    {
    pos --; 
    }
  }                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
   
} 

#include <Ultrasonic.h>

 //  Proximity sensor
int proximityTrig = 11;
int proximityEcho = 12;
Ultrasonic ultrasonic(proximityTrig,proximityEcho); // (Trig PIN,Echo PIN)


void setup() {
  // put your setup code here, to run once:
  
   pinMode(proximityTrig, OUTPUT);
   pinMode(proximityEcho, INPUT);
    
   
   Serial.begin(9600);
   
}

void loop() {
  // put your main code here, to run repeatedly:
delay(1000);

      Serial.print("Distance = ");
     int distance = ultrasonic.Ranging(CM);  
     Serial.println(distance);     // the raw analog reading
   

}

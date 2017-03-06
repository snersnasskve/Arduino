#include <Adafruit_NeoPixel.h>
#include <Ultrasonic.h>

// This example drives the stepper motors directly
// It makes the robot perform the "HullPixelBot Dance"
// See if you can change the moves.
// www.robmiles.com/hullpixelbot
////////////////////////////////////////////////

//declare variables for the motor pins
 int rmotorPin1 = 17;    // Blue   - 28BYJ48 pin 1
 int rmotorPin2 = 16;    // Pink   - 28BYJ48 pin 2
 int rmotorPin3 = 15;   // Yellow - 28BYJ48 pin 3
 int rmotorPin4 = 14;   // Orange - 28BYJ48 pin 4
                        // Red    - 28BYJ48 pin 5 (VCC)

 int lmotorPin1 = 4;    // Blue   - 28BYJ48 pin 1
 int lmotorPin2 = 5;    // Pink   - 28BYJ48 pin 2
 int lmotorPin3 = 6;   // Yellow - 28BYJ48 pin 3
 int lmotorPin4 = 7;   // Orange - 28BYJ48 pin 4
                        // Red    - 28BYJ48 pin 5 (VCC)
                        
//  Proximity sensor
int proximityTrig = 12;
int proximityEcho = 13;
Ultrasonic ultrasonic(proximityTrig,proximityEcho); // (Trig PIN,Echo PIN)


#define PIN 3

Adafruit_NeoPixel strip = Adafruit_NeoPixel(2, PIN, NEO_GRB + NEO_KHZ800);

int motorSpeed = 1200;  //variable to set stepper speed
int count = 0;          // count of steps made
int countsperrev = 512; // number of steps per full revolution
int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};


int photocellLeft   = 4;
int photocellRight  = 5;

float lengthOfRotation = 180.0f;

//////////////////////////////////////////////////////////////////////////////
 void setup() {
   //declare the motor pins as outputs
   pinMode(lmotorPin1, OUTPUT);
   pinMode(lmotorPin2, OUTPUT);
   pinMode(lmotorPin3, OUTPUT);
   pinMode(lmotorPin4, OUTPUT);
   pinMode(rmotorPin1, OUTPUT);
   pinMode(rmotorPin2, OUTPUT);
   pinMode(rmotorPin3, OUTPUT);
   pinMode(rmotorPin4, OUTPUT);
   
   pinMode(proximityTrig, OUTPUT);
   pinMode(proximityEcho, INPUT);
   
 
   Serial.begin(9600);
   strip.begin();
   strip.setPixelColor(0, 00,20,20);
   strip.show();    
 }

const int STOP = 0;
const int FORWARD = 1;
const int BACK = 2;
const int LEFT = 3;
const int RIGHT = 4;
const int SHARPLEFT = 5;
const int SHARPRIGHT = 6;

int moveState = FORWARD;

int storDistance = 0;
int storLight = 0;

void loop(){ 
   if(count < (countsperrev / 10) ) {
     moveStep();
   }
   else 
   {
   
     Serial.print("Right = ");
     int brightnessRight = analogRead(photocellRight);  
     Serial.println(brightnessRight);     // the raw analog reading
  
     Serial.print("Distance = ");
     int distance = ultrasonic.Ranging(CM);  
     Serial.println(distance);     // the raw analog reading
   
     if (moveState == RIGHT || moveState == SHARPRIGHT)
     {
        if (distance < 10)
        {
            Serial.println("---      Keep on turning right");
        }
        else if (brightnessRight >= storLight)
        {
           //  good decision, go straight 
            Serial.println("---      Good decision, go straight");

           moveState = FORWARD;
        }
        else
        {
           //  bad decision, go back
           Serial.println("---      Bad decision, go back left");

           moveState = LEFT;
        }
     }
   
      else if (moveState == LEFT || moveState == SHARPLEFT)
     {
        if (distance < 10)
        {
            Serial.println("---      Keep on turning left");
        }
        else if (brightnessRight >= storLight)
        {
           //  good decision, go straight 
            Serial.println("---      Good decision, go straight");
           moveState = FORWARD;
        }
        else
        {
           //  bad decision, go back
              Serial.println("---      bad decision, go right now");
           moveState = RIGHT;
        }
     }
      else if (moveState == FORWARD)
      {
          if (distance < 10)
          {
              Serial.println("---      Keep on straight");
              moveState = SHARPRIGHT;
          }
          else if (brightnessRight >= storLight)
          {
             //  good decision, go straight 
             moveState = FORWARD;
               Serial.println("---      Keep on straight");
         }
          else
          {
             //  bad decision, go back
             moveState = RIGHT;
                Serial.println("---     bad decision try right");
        }
      }
        storDistance = distance;
        storLight = brightnessRight;
 
   
   //  We need to measure, decide, measure, decide 
    count=0;
 
   }
   count++;
}

void moveStep()
{
   for(int i = 0; i < 8; i++)
   {
    switch(moveState)
    {
      case STOP:
        return;
      case FORWARD:
        setOutputDir(i,7-i);
       // delay(500);
      //    digitalWrite(pixel, LOW);
      break;
      case BACK:
        setOutputDir(7-i,i);
        break;
      case LEFT:
        setOutputDir(i,0);
        break;
      case RIGHT:
        setOutputDir(0,7-i);
        break;
       case SHARPLEFT:
        setOutputDir(7-i,7-i);
        break;
     case SHARPRIGHT:
        setOutputDir(i,i);
        break;
  }
     delayMicroseconds(motorSpeed);
   }
}

void setOutputDir(int leftOut, int rightOut)
{
  
   digitalWrite(lmotorPin1, bitRead(lookup[leftOut], 0));
   digitalWrite(lmotorPin2, bitRead(lookup[leftOut], 1));
   digitalWrite(lmotorPin3, bitRead(lookup[leftOut], 2));
   digitalWrite(lmotorPin4, bitRead(lookup[leftOut], 3));

   digitalWrite(rmotorPin1, bitRead(lookup[rightOut], 0));
   digitalWrite(rmotorPin2, bitRead(lookup[rightOut], 1));
   digitalWrite(rmotorPin3, bitRead(lookup[rightOut], 2));
   digitalWrite(rmotorPin4, bitRead(lookup[rightOut], 3));
}


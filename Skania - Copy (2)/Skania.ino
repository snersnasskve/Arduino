#include <Adafruit_NeoPixel.h>
#include <Ultrasonic.h>
#include <Stepper.h>


//  Thanks www.robmiles.com/hullpixelbot for the starting point
//  Most of the code has now been changed.
////////////////////////////////////////////////

/* Todo
Implement Stepper egs
Make a method for turning
*/
//  Method declarations
void doRecce();

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
int proximityTrig = 11;
int proximityEcho = 12;
Ultrasonic ultrasonic(proximityTrig,proximityEcho); // (Trig PIN,Echo PIN)


#define PIN 3

Adafruit_NeoPixel strip = Adafruit_NeoPixel(2, PIN, NEO_GRB + NEO_KHZ800);

int motorSpeed = 1200;  //variable to set stepper speed
int count = 0;          // count of steps made
int countsperrev = 512; // number of steps per full revolution
//  skania width = 3; wheel radius = 1
float turningFactor = 3 / 1;  //  It's only a ratio, you dont' need units
float degrees360sharp = (countsperrev * turningFactor) / 2;
float degrees360slow = (countsperrev * turningFactor);

int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};

int photocellLeft   = 5;
int photocellRight  = 4;

//  

struct PositionData {
  int left;
  int right;
  int distance;
  int turnAngle;
};
PositionData bestPosition;

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

//  how do you do enum in C?
const int EXPLORE_PHASE = 0;
const int MOVE_PHASE = 1;

int phase = MOVE_PHASE;
int moveState = FORWARD;

/*
 think the usual way of dealing with an obstacle is to back of a limited random distance 
 then turn 90 degrees in a random direction. 
 Turning 180 degrees would work but leads to rather boring behaviour.

Another interesting addition is to have battery charging point 
identified by a light flashing at a certain rhythm 
and when the robot senses that it is low on powe rit seeks the charging point.
*/
void loop(){
  if (EXPLORE_PHASE == phase)
  {
    doRecce();
     Serial.print("BEST DIRECTION = ");
     Serial.print("Left = ");
     Serial.println(bestPosition.left);     // the raw analog reading
     Serial.print("Right = ");
     Serial.println(bestPosition.right);     // the raw analog reading
     Serial.print("Distance = ");
     Serial.println(bestPosition.distance);     // the raw analog reading
     Serial.print("Direction = ");
     Serial.println(bestPosition.turnAngle);     // the raw analog reading

  }
  else if(count < 30 ) {
     moveStep();
   }
   else 
   {
     Serial.print("Left = ");
     int brightnessLeft = analogRead(photocellLeft);  
     Serial.println(brightnessLeft);     // the raw analog reading

     Serial.print("Right = ");
     int brightnessRight = analogRead(photocellRight);  
     Serial.println(brightnessRight);     // the raw analog reading
  
     Serial.print("Distance = ");
     int distance = ultrasonic.Ranging(CM);  
     Serial.println(distance);     // the raw analog reading
   
   if (distance < 10 && distance != 0)
    {
       Serial.println("---      Back");
       moveState = BACK;
    }
    else if ( brightnessLeft == brightnessRight)
    {
       Serial.println("---      Forward");
       moveState = FORWARD;
    }
    else  if (brightnessLeft > brightnessRight)
    {
       if (distance < 20)
       {
          moveState = LEFT;
          Serial.println("---      Turning  Left");
      }
       else
       {
         moveState = LEFT;
         Serial.println("---      Turning  Left");
     }
    }
    else if (brightnessLeft < brightnessRight)
    {
           if (distance < 20)
       {
         moveState = RIGHT;
         Serial.println("---      Turning Right");
      }
       else
       {
         moveState = RIGHT;
       Serial.println("---      Turning Right");
      }
    }
    else
    {
      Serial.println("Not equal, not less than and not greater than!");
    }
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
   
   Stepper(5, lmotorPin1, lmotorPin2);
}


void doRecce()
{
  int stepSize = 10;
  moveState = SHARPRIGHT;
   for (int stepCounter = 0; stepCounter < ceil(degrees360sharp) ; stepCounter += stepSize)
  {
     int leftBrightness    = analogRead(photocellLeft);  
     int rightBrightness   = analogRead(photocellRight);  
     int distance          = ultrasonic.Ranging(CM);  
     
        Serial.print("RECCE = ");
     Serial.print("Left = ");
     Serial.println(leftBrightness);     // the raw analog reading
     Serial.print("Right = ");
     Serial.println(rightBrightness);     // the raw analog reading
     Serial.print("Distance = ");
     Serial.println(distance);     // the raw analog reading
     Serial.print("Direction = ");
     Serial.println(stepCounter);     // the raw analog reading

     bool thisPositionIsGood = false;
     if (0 == stepCounter || (distance > bestPosition.distance))
     {
       thisPositionIsGood = true;
     }
     else if (distance == bestPosition.distance && leftBrightness > bestPosition.left)
     {
       thisPositionIsGood = true;
     }
     else if (distance == bestPosition.distance && leftBrightness == bestPosition.left &&
     rightBrightness > bestPosition.right)
     {
       thisPositionIsGood = true;
     }

     if (thisPositionIsGood)
     {
       bestPosition.left      = leftBrightness;
       bestPosition.right     = rightBrightness;
       bestPosition.distance  = distance;
       bestPosition.turnAngle = stepCounter;
    }
    
    //  and turn by 1 degree
     moveStep();
  } 
  //  By the time we end this loop, we should have a good position
}


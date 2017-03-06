#include <Ultrasonic.h>

//  Logging and delaying takes way to long, so we'll do one or tother

int logging = false;

//  Keep track of what we're doing so we can take the appropriate action
enum DriveState {DRIVE, TURN} ;
DriveState state = DRIVE;

enum Strategy (SQUARE, GOTOGOAL};

//declare variables for the motor pins
 int lmotorPin1 = 17;    // Blue   - 28BYJ48 pin 1
 int lmotorPin2 = 16;    // Pink   - 28BYJ48 pin 2
 int lmotorPin3 = 15;   // Yellow - 28BYJ48 pin 3
 int lmotorPin4 = 14;   // Orange - 28BYJ48 pin 4
                        // Red    - 28BYJ48 pin 5 (VCC)

 int rmotorPin1 = 4;    // Blue   - 28BYJ48 pin 1
 int rmotorPin2 = 5;    // Pink   - 28BYJ48 pin 2
 int rmotorPin3 = 6;   // Yellow - 28BYJ48 pin 3
 int rmotorPin4 = 7;   // Orange - 28BYJ48 pin 4
                        // Red    - 28BYJ48 pin 5 (VCC)
                        
 //  Proximity sensor
int proximityTrig = 12;
int proximityEcho = 13;
Ultrasonic ultrasonic(proximityTrig,proximityEcho); // (Trig PIN,Echo PIN)

int motorSpeed = 1200;  //variable to set stepper speed
int count = 0;          // count of steps made
int countsperrev = 4096; // number of steps per full revolution
int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};


//  Controls
long clickCounter = 0;
int leftPhase = 0;    //  Start at the bottom
int leftDirection = -1;

int rightPhase = 7;    //  Start at the top
int rightDirection = 1;

int leftSpeed = 1;
int rightSpeed = 1;

//  Wheel diameter = 76
//  Wheel base = 12
//  Converting to mm
int rad = 38;
int skaniaWidth = 120;
int rotationDistance = 2 * rad * floor(M_PI);
int distanceTravelled = 0; // in mm


long metreMarker;
long fullCircleCount; 

//  methods
void moveStep();
long clickCountForDistanceCm(float dist);
long clickCountForRotationDegrees(float dist);

void setup() {
  // put your setup code here, to run once:
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
   
   //  (7.5 * M_PI) is wheel perimeter
   metreMarker = clickCountForDistanceCm(50.0f);
   if (logging) {
     Serial.print("metreMarker = ");
     Serial.println(metreMarker);
   }
   fullCircleCount = clickCountForRotationDegrees(90.0f);
    if (logging) {
      Serial.print("fullCircleCount = ");
      Serial.println(fullCircleCount);
    }

}

int left_i;
int right_i;

////////////////////////////////////////////////////
void loop() {
////////////////////////////////////////////////////
  if (DRIVE == state && clickCounter < metreMarker) {
    moveStep();
   if (logging) {
     distanceTravelled = ((7.5 * M_PI * clickCounter) / (1.0 * countsperrev));
     Serial.print("Distance Travelled = ");
      Serial.println(distanceTravelled); 
     } 
  }
  else   if (TURN == state && clickCounter < fullCircleCount ) {

   //  Turn right
   rightSpeed = 0;
    moveStep();
    if (logging) {
      Serial.print("Turning = ");
      Serial.println(clickCounter - metreMarker); 
    }
  }
  else {
    //  reset
    clickCounter = 0;
   rightSpeed = 1;
   state = (DRIVE == state) ? TURN : DRIVE;
  }
}
 
////////////////////////////////////////////////////
void moveStep() {
 ////////////////////////////////////////////////////
 if ((leftSpeed != 0) && (clickCounter % leftSpeed == 0)) {
   	   digitalWrite(lmotorPin1, bitRead(lookup[leftPhase], 0));
	   digitalWrite(lmotorPin2, bitRead(lookup[leftPhase], 1));
	   digitalWrite(lmotorPin3, bitRead(lookup[leftPhase], 2));
	   digitalWrite(lmotorPin4, bitRead(lookup[leftPhase], 3));
	leftPhase += leftDirection ;	// reset if it gets to 8
        leftPhase = (leftPhase + 8) % 8;
 
   
 }
  
 if ((rightSpeed != 0) && (clickCounter % rightSpeed == 0)) {
   	   digitalWrite(rmotorPin1, bitRead(lookup[rightPhase], 0));
	   digitalWrite(rmotorPin2, bitRead(lookup[rightPhase], 1));
	   digitalWrite(rmotorPin3, bitRead(lookup[rightPhase], 2));
	   digitalWrite(rmotorPin4, bitRead(lookup[rightPhase], 3));
	rightPhase += rightDirection ;	// reset if it gets to 8
        rightPhase = (rightPhase + 8) % 8;
  
   
 }
  
 clickCounter++;
 if (!logging) {
   delay(1);
   }
}

////////////////////////////////////////////////////
long clickCountForDistanceCm(float dist) {
////////////////////////////////////////////////////
return floor((dist * countsperrev) / (7.5 * M_PI));
}

////////////////////////////////////////////////////
long clickCountForRotationDegrees(int angle) {
////////////////////////////////////////////////////
  float skaniaRatio = (1.0f * skaniaWidth) / (1.0f * rad);
  float angleFloat = (1.0 * angle) / 360.0f;
return floor(skaniaRatio * (1.0f * countsperrev) * angleFloat);
}


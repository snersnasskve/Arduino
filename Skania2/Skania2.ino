#include <Ultrasonic.h>

//  Logging and delaying takes way to long, so we'll do one or tother

int logging = true;

//  Using a centimetre scale
struct Point {
  int x;    
  int y;    
  Point(int inX, int inY) {
    x = inX;
    y = inY;
  }
};


enum Strategy {NOSTRATEGY, SQUARE, GOTOGOAL};


struct State {
  Strategy strategy;
  long clickCounter;
  int leftDirection;

  int rightDirection;

  int leftSpeed;
  int rightSpeed;

  State() {
    strategy = NOSTRATEGY;
    clickCounter = 0;
    leftDirection = -1;
    rightDirection = 1;
    leftSpeed = 1;
    rightSpeed = 1;
  }
  
};

Strategy strategy = SQUARE;
int strategyPhase = 0;  //  Each strategy to use this as appropriate

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
int skaniaWidth = 110;
int rotationDistance = round(M_PI * 2 * rad);
int distanceTravelled = 0; // in mm


long driveClicks;
long turnClicks; 

//  methods
void moveStep();
long clickCountForDistanceCm(float dist);
long clickCountForRotationDegrees(float dist);
void setStrategy(Strategy newStrat);
void doSquare();
Point getDestinationForGoal(int goalDistance, int goalAngle);


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
   
  setStrategy(SQUARE);
}

int left_i;
int right_i;

////////////////////////////////////////////////////
void loop() {
////////////////////////////////////////////////////

 if (strategy == SQUARE) {
   doSquare();
 } else  if (strategy == GOTOGOAL) {
   doGoToGoal();
 }
}
 
////////////////////////////////////////////////////
void setStrategy(Strategy newStrat) {
////////////////////////////////////////////////////
//  Reset various
  clickCounter = 0;
  leftPhase = 0;
  rightPhase = 7;

  if (SQUARE == newStrat) {
     //  (7.5 * M_PI) is wheel perimeter
   driveClicks = clickCountForDistanceCm(50.0f);
   if (logging) {
     Serial.print("driveClicks(sq) = ");
     Serial.println(driveClicks);
   }
   turnClicks = clickCountForRotationDegrees(90.0f);
    if (logging) {
      Serial.print("turnClicks9sq) = ");
      Serial.println(turnClicks);
    }

  }
  else   if (GOTOGOAL == newStrat) {
    int goalDistance = 200;
    int goalAngle    = 0;  //  Where positive is go_left, and negative is go_right

   //  We're not going to use this yet. This is only useful if we're tracking which we aren't
   // Point destination = getDestinationForGoal(goalDistance, goalAngle);
   driveClicks = clickCountForDistanceCm(50.0f);
   if (logging) {
     Serial.print("driveClicks(gtg) = ");
     Serial.println(driveClicks);
   }
   
   float rotation = 45.0f;
   turnClicks = clickCountForRotationDegrees(rotation);
   if (rotation <= 180) {
     //  Turn left
     strategyPhase = 1;
   } else {
     //  Turn right
     strategyPhase = 5;
   }

   
    if (logging) {
      Serial.print("turnClicks(gtg) = ");
      Serial.println(turnClicks);
      Serial.print("strategy = ");
      Serial.println(strategy);
    }

  }
}
 
////////////////////////////////////////////////////
void doSquare() {
////////////////////////////////////////////////////

//  strategyPhases are 0, - 15
//  all evens are drive
//  < 8 are turn right
//  > 8 are turn left
  if ( strategyPhase % 2 == 0 && clickCounter < driveClicks) {
    moveStep();
   if (logging) {
    // distanceTravelled = ((7.5 * M_PI * clickCounter) / (1.0 * countsperrev));
    // Serial.print("Distance Travelled = ");
    //  Serial.println(distanceTravelled); 
     } 
  }
  else   if ( strategyPhase < 8 && clickCounter < turnClicks ) {

   //  Turn right
   rightSpeed = 0;
    moveStep();
    if (logging) {
      //Serial.print("Turning = ");
      //Serial.println(clickCounter - driveClicks); 
    }
  }
  else   if ( strategyPhase < 16 && clickCounter < turnClicks ) {

   //  Turn left
   leftSpeed = 0;
    moveStep();
    if (logging) {
      //Serial.print("Turning = ");
      //Serial.println(clickCounter - driveClicks); 
    }
  }
  else {
    //  reset
    clickCounter = 0;
   rightSpeed = 1;
   leftSpeed = 1;
   strategyPhase = (strategyPhase < 15) ? strategyPhase + 1 : 0;
   if (logging) {
      Serial.print("New phase = ");
      Serial.println(strategyPhase); 
    }
  } 
  clickCounter++;
}

 
////////////////////////////////////////////////////
void doGoToGoal() {
////////////////////////////////////////////////////
//  Strategy phases are 1, 2 = turn left then go straight
//                      5, 6 = turn right then go straight

 if ( strategyPhase % 2 == 0 && clickCounter < driveClicks) {
    moveStep();
   if (logging) {
     distanceTravelled = ((7.5 * M_PI * clickCounter) / (1.0 * countsperrev));
     //Serial.print("Distance Travelled = ");
      //Serial.println(distanceTravelled); 
     } 
  }
  else   if ( strategyPhase == 5 && clickCounter < turnClicks ) {

   //  Turn right
   rightSpeed = 0;
    moveStep();
    if (logging) {
      //Serial.print("Turning = ");
      //Serial.println(clickCounter - driveClicks); 
    }
  }
  else   if ( strategyPhase == 1 && clickCounter < turnClicks ) {

   //  Turn left
   leftSpeed = 0;
    moveStep();
    if (logging) {
      Serial.print("Turning = ");
      Serial.println(clickCounter - driveClicks); 
    }
  }
  else {
    //  stop
    strategy = NOSTRATEGY;
  
  }
  clickCounter++;
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
   delay(1 + ! leftSpeed + ! rightSpeed);

}

////////////////////////////////////////////////////
long clickCountForDistanceCm(float dist) {
////////////////////////////////////////////////////
return (long)((dist * countsperrev) / (7.5 * M_PI) * 2.0f);
}

////////////////////////////////////////////////////
long clickCountForRotationDegrees(float angle) {
////////////////////////////////////////////////////
  float skaniaRatio = (1.0f * skaniaWidth) / (1.0f * rad);
  float angleFraction = angle / 360.0f;
return (long)(skaniaRatio * (2.0f * countsperrev) * angleFraction);
}

////////////////////////////////////////////////////
Point getDestinationForGoal(int goalDistance, int goalAngle) {
////////////////////////////////////////////////////
  float angleRadians = (M_PI * goalAngle) / 180.0f;
  float x = round(sin(angleRadians) * goalDistance);
  float y = round(cos(angleRadians) * goalDistance);
  return Point(x, y);
}

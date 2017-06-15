#include <Ultrasonic.h>

//  Logging and delaying takes way to long, so we'll do one or tother

//  Investigate - turning = 0,
//  Distance wiring is dodgy
bool logging = false;

//  Using a centimetre scale
struct Point {
  int x;    
  int y;    
  Point(int inX, int inY) {
    x = inX;
    y = inY;
  }
};

struct Pose {
  Point point = Point(0, 0);    
  int angle = 0;  // degrees   - angles increase positively in the anti-clockwise direction
  Pose() {
  }
};


//  
enum Strategy {NOSTRATEGY, SQUARE, GOTOGOAL, WANDER, LASTSTRAT};


struct State {
  Strategy strategy = NOSTRATEGY;
  int strategyPhase = 0;            //  Each strategy to use this as appropriate
  Pose pose = Pose();          // Convention: x is the direction we are facing, so I suppose y is to our left;
  long clickCounter = 0;
  int leftDirection = -1;

  int rightDirection = 1;

  int leftSpeed = 1;
  int rightSpeed = 1;

  State() {
  }
  
};

State state;

//Strategy strategy = SQUARE;

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
int proximityTrig = 11;
int proximityEcho = 12;
Ultrasonic ultrasonic(proximityTrig,proximityEcho); // (Trig PIN,Echo PIN)

const int touchPin = 3;
//  store the time when last touch event happened
unsigned long lastTouchEvent = 0;


//  Controls
int motorSpeed = 1200;  //variable to set stepper speed
int countsperrev = 4096; // number of steps per full revolution
int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};

int leftPhase = 0;    //  Start at the bottom
int rightPhase = 7;    //  Start at the top

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
    
   pinMode(touchPin, INPUT);
   
   Serial.begin(9600);
   
  setStrategy(NOSTRATEGY);
}


////////////////////////////////////////////////////
void loop() {
////////////////////////////////////////////////////
//delay(1000);
 
 if (state.clickCounter % 10 == 0) {
      Serial.print("Distance = ");
     int distance = ultrasonic.Ranging(CM);  
     Serial.println(distance);     // the raw analog reading
     if (distance < 40) {
       //  Avoid
       state.strategyPhase = 1;
       turnClicks = clickCountForRotationDegrees(45.0f);
     }
 }
 if (state.strategy == SQUARE) {
   doSquare();
 } else  if (state.strategy == GOTOGOAL) {
   doGoToGoal();
 } else  if (state.strategy == WANDER) {
   doWander();
 }
 
 
  int touchState = digitalRead(touchPin);
  if (touchState == HIGH) {
    Serial.println("touched");
  //if 50ml has passed since last HIGH pulse, it means that the
    //  touch sensor has been touched, released and touched again }
    if (millis() - lastTouchEvent > 50) {
          Serial.println("changing mode");

    setStrategy(static_cast<Strategy> ((state.strategy == GOTOGOAL) ? LASTSTRAT : state.strategy + 1));
    }
    // remember when last even happened
    lastTouchEvent = millis();
  }
   
}
 
////////////////////////////////////////////////////
void setStrategy(Strategy newStrat) {
////////////////////////////////////////////////////
//  Reset various
  state = State();
  state.strategy = newStrat;
  state.clickCounter = 0;
  leftPhase = 0;
  rightPhase = 7;

  if (SQUARE == newStrat) {
     //  (7.5 * M_PI) is wheel perimeter
   driveClicks = clickCountForDistanceCm(100.0f);
   if (logging) {
     Serial.print("driveClicks(sq) = ");
     Serial.println(driveClicks);
   }
   turnClicks = clickCountForRotationDegrees(45.0f);
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
     state.strategyPhase = 1;
   } else {
     //  Turn right
     state.strategyPhase = 5;
   }

   
    if (logging) {
      Serial.print("turnClicks(gtg) = ");
      Serial.println(turnClicks);
      Serial.print("strategy = ");
      Serial.println(state.strategy);
    }

  }
  else if (WANDER == state.strategy)
  {
  }
}
 
////////////////////////////////////////////////////
void doSquare() {
////////////////////////////////////////////////////

//  strategyPhases are 0, - 15
//  all evens are drive
//  < 8 are turn right
//  > 8 are turn left
  if ( state.strategyPhase % 2 == 0 && state.clickCounter < driveClicks) {
    moveStep();
   if (logging) {
     distanceTravelled = ((7.5 * M_PI * state.clickCounter) / (1.0 * countsperrev));
     Serial.print("Distance Travelled = ");
      Serial.println(distanceTravelled); 
     } 
  }
  else   if ( state.strategyPhase < 8 && state.clickCounter < turnClicks ) {

   //  Turn right
   state.rightSpeed = 0;
    moveStep();
    if (logging) {
      //Serial.print("Turning = ");
      //Serial.println(clickCounter - driveClicks); 
    }
  }
  else   if ( state.strategyPhase < 16 && state.clickCounter < turnClicks ) {

   //  Turn left
   state.leftSpeed = 0;
    moveStep();
    if (logging) {
      //Serial.print("Turning = ");
      //Serial.println(clickCounter - driveClicks); 
    }
  }
  else {
    //  reset
   state.clickCounter = 0;
   state.rightSpeed = 1;
   state.leftSpeed = 1;
   state.strategyPhase = (state.strategyPhase < 15) ? state.strategyPhase + 1 : 0;
   if (logging) {
      Serial.print("New phase = ");
      Serial.println(state.strategyPhase); 
    }
  } 
  state.clickCounter++;
}

 
////////////////////////////////////////////////////
void doGoToGoal() {
////////////////////////////////////////////////////
//  Strategy phases are 1, 2 = turn left then go straight
//                      5, 6 = turn right then go straight
//Serial.println("doGoToGoal()");

 if ( state.strategyPhase % 2 == 0 && state.clickCounter < driveClicks) {
    moveStep();
   if (logging) {
     distanceTravelled = ((7.5 * M_PI * state.clickCounter) / (1.0 * countsperrev));
     //Serial.print("Distance Travelled = ");
      //Serial.println(distanceTravelled); 
     } 
  }
  else   if ( state.strategyPhase == 5 && state.clickCounter < turnClicks ) {

   //  Turn right
   state.rightSpeed = 0;
    moveStep();
    if (logging) {
      //Serial.print("Turning = ");
      //Serial.println(clickCounter - driveClicks); 
    }
  }
  else   if ( state.strategyPhase == 1 && state.clickCounter < turnClicks ) {

   //  Turn left
   state.leftSpeed = 0;
    moveStep();
    if (logging) {
      Serial.print("Turning = ");
      Serial.println(state.clickCounter - driveClicks); 
    }
  }
  else {
    //  stop
    state.strategy = NOSTRATEGY;
  
  }
  state.clickCounter++;
}

 
////////////////////////////////////////////////////
void doWander() {
////////////////////////////////////////////////////


  state.clickCounter++;
}


////////////////////////////////////////////////////
void moveStep() {
 ////////////////////////////////////////////////////
 

 
 if ((state.leftSpeed != 0) && (state.clickCounter % state.leftSpeed == 0)) {
   	   digitalWrite(lmotorPin1, bitRead(lookup[leftPhase], 0));
	   digitalWrite(lmotorPin2, bitRead(lookup[leftPhase], 1));
	   digitalWrite(lmotorPin3, bitRead(lookup[leftPhase], 2));
	   digitalWrite(lmotorPin4, bitRead(lookup[leftPhase], 3));
	leftPhase += state.leftDirection ;	// reset if it gets to 8
        leftPhase = (leftPhase + 8) % 8;
 
   
 }
  
 if ((state.rightSpeed != 0) && (state.clickCounter % state.rightSpeed == 0)) {
   	   digitalWrite(rmotorPin1, bitRead(lookup[rightPhase], 0));
	   digitalWrite(rmotorPin2, bitRead(lookup[rightPhase], 1));
	   digitalWrite(rmotorPin3, bitRead(lookup[rightPhase], 2));
	   digitalWrite(rmotorPin4, bitRead(lookup[rightPhase], 3));
	rightPhase += state.rightDirection ;	// reset if it gets to 8
        rightPhase = (rightPhase + 8) % 8;
  
   
 }
  
 state.clickCounter++;
   //delay(1 + ! state.leftSpeed + ! state.rightSpeed);
   delay(2);

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

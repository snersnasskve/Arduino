#define lmotorPin1 4
#define lmotorPin2 5
#define lmotorPin3 6
#define lmotorPin4 7

#define rmotorPin1 17
#define rmotorPin2 16
#define rmotorPin3 15
#define rmotorPin4 14

int turningAngle = 0;  //  radians please
int stepCounter = 0;

float turningFactor = 11.5 / 7.5;  //  It's only a ratio, you dont' need units

//#define SKANIA_WIDTH 11.5
//#define WHEEL_RADIUS 7.5
#define STEPS_PER_ROTATION  4096
const  float SKANIA_WIDTH = 11.5;
const float WHEEL_RADIUS = 7.5;
//#define STEPS_PER_ROTATION 4096

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
   
    Serial.begin(9600);
  
}

void loop() {

  rotate(0.5);
 stepCounter++;
 if (stepCounter >= STEPS_PER_ROTATION) {  
 stepCounter = 0; 
 turningAngle += (PI / 180.0) ; // 1 degree
 }
}

void rotate(float rotations) {
  int totalSteps = (rotations * STEPS_PER_ROTATION);
  float modAngle = atan2(sin (turningAngle), cos(turningAngle));
  // rightWheelSpeed = (2*v + angleradians * SkaniaWidth) / (2 * wheelRadius)
  // leftWheelSpeed = (2*v - angleradians * SkaniaWidth) / (2 * wheelRadius)
  float rightWheelSpeed = ((2.0 * 100.0) + (modAngle * SKANIA_WIDTH)) / (2.0 * WHEEL_RADIUS);
  float leftWheelSpeed = ((2.0 * 100.0) - (modAngle * SKANIA_WIDTH)) / (2.0 * WHEEL_RADIUS);
  Serial.print("right...........");
  Serial.println(rightWheelSpeed);
  Serial.print("left...........");
  Serial.println(leftWheelSpeed);
  for (int stepCount = 0; stepCount < totalSteps ; stepCount++) {
    rotate_steps(leftWheelSpeed, lmotorPin1, lmotorPin2, lmotorPin3, lmotorPin4);
    rotate_steps(rightWheelSpeed, rmotorPin4, rmotorPin3, rmotorPin2, rmotorPin1);
  }
}

int phase = 0;
byte phases[] = { 1, 3, 2, 6, 4, 12, 8, 9 };

void rotate_steps(int steps, int motorPin1, int motorPin2, int motorPin3, int motorPin4)
{
    int dir = (steps > 0) - (steps < 0);
    steps *= dir;
    long laststep = 0;
    for (int i = 0; i < steps;) {
      long now = micros();
      if (now - laststep < 1000) continue;
      laststep = now;
      stepper_writepins(phases[phase], motorPin1, motorPin2, motorPin3, motorPin4);
      phase = (8 + phase + dir) % 8;
      i++;
  }
  stepper_writepins(0, motorPin1, motorPin2, motorPin3, motorPin4);
}


void stepper_writepins(int bitmap, int motorPin1, int motorPin2, int motorPin3, int motorPin4) {
    digitalWrite(motorPin1, bitmap & 8 ? HIGH : LOW);
    digitalWrite(motorPin2, bitmap & 4 ? HIGH : LOW);
    digitalWrite(motorPin3, bitmap & 2 ? HIGH : LOW);
    digitalWrite(motorPin4, bitmap & 1 ? HIGH : LOW);
}

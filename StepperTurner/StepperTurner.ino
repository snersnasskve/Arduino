#define leftIN1 8
#define leftIN2 9
#define leftIN3 10
#define leftIN4 11

#define rightIN1 4
#define rightIN2 5
#define rightIN3 6
#define rightIN4 7

/*
So, we have two choices - 1 = change speed of one wheel but keep both revolving in synch
    ie left right left right - you won't be able to notice
    2 = keep the speed up but change the distance and then do something like left left right or 
      whatever adds up to the required speed.
Having build this class, we also need to bear in mind that we need to be responsive to change in the 
  environment ie something moving into the line of sight that needs avoiding
  or other reason for change such as tracking light, the light source moved.
So with single core and 256k of total memory, we need to make this work threaded - OK overkill but 
    you get the picture
*/

#define STEPS_PER_ROTATION 4096

void setup()
{
    pinMode(leftIN1, OUTPUT);
    pinMode(leftIN2, OUTPUT);
    pinMode(leftIN3, OUTPUT);
    pinMode(leftIN4, OUTPUT);
    pinMode(rightIN1, OUTPUT);
    pinMode(rightIN2, OUTPUT);
    pinMode(rightIN3, OUTPUT);
    pinMode(rightIN4, OUTPUT);
    delay(100);
}

void loop()
{
    rotate(1);
    delay(2000);
    rotate(-1);
    delay(2000);
}

void rotate(float rotations) {
    rotate_steps(rotations * STEPS_PER_ROTATION);
}

int phase = 0;
byte phases[] = { 1, 3, 2, 6, 4, 12, 8, 9 };

void rotate_steps(int steps)
{
    int dir = (steps > 0) - (steps < 0);
    steps *= dir;
    long laststep;
    for (int i = 0; i < steps;) {
      long now = micros();
      if (now - laststep < 1000) continue;
      laststep = now;
      stepper_writepins(phases[phase]);
      phase = (8 + phase + dir) % 8;
      i++;
  }
  stepper_writepins(0);
}


void stepper_writepins(int bitmap) {
    digitalWrite(leftIN1, bitmap & 8 ? HIGH : LOW);
    digitalWrite(leftIN2, bitmap & 4 ? HIGH : LOW);
    digitalWrite(leftIN3, bitmap & 2 ? HIGH : LOW);
    digitalWrite(leftIN4, bitmap & 1 ? HIGH : LOW);
}

#include <Servo.h>

Servo myservo;

void setup()
{
 myservo.attach(10);
 
}

void loop()
{
 myservo.writeMicroseconds(2000); 
  delay(1000);
  myservo.writeMicroseconds(1000);
    delay(1000);

}

//  http://qqtrading.com.my/ir-infrared-obstacle-detaction-sensor-module-fc-5

//  Adjust detection distance. CCW decreases distance.
//                              CW increases distance
//  It is sensitive from the top
// IR Obstacle Collision Detection Module

int LED = 13; // Use the onboard Uno LED
int isObstaclePin = 7; // This is our input pin
int isObstacle = HIGH; // HIGH MEANS NO OBSTACLE

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(isObstaclePin, INPUT);
    Serial.begin(9600);
}

void loop() {
    isObstacle = digitalRead(isObstaclePin);
    if (isObstacle == LOW) {
        Serial.println("OBSTACLE!!, OBSTACLE!!");
        digitalWrite(LED, HIGH);
    } else {
        Serial.println("clear");
        digitalWrite(LED, LOW);
    }
    delay(200);
}

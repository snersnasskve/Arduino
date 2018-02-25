
const int ledPin = 13;
const int touchPin = 3;

//  store the time when last event happened
unsigned long lastEvent = 0;
//  store the state of LED
boolean ledOn = false;

void setup() {
  // put your setup code here, to run once:
pinMode(ledPin, OUTPUT);
pinMode(touchPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int touchState = digitalRead(touchPin);
  
  //  only interested in the HIGH signal
  if (touchState == HIGH) {
    //if 50ml has passed since last HIGH pulse, it means that the
    //  touch sensor has been touched, released and touched again }
    if (millis() - lastEvent > 50) {
      //  toggle LED and set the output
      ledOn = !ledOn;
      digitalWrite(ledPin, ledOn ? HIGH : LOW);
    }
    // remember when last even happened
    lastEvent = millis();
  }
 }

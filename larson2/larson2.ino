int loopCount = 100;
int brightnesses[4];
int first_led = 1; // The pin number of the first LED
void setup() {
// initialize the digital pin as an output.
for (int i=0; i<4; i++){
pinMode(first_led + i, OUTPUT);
}
brightnesses[0] = 5;
brightnesses[1] = 25;
brightnesses[2] = 50;
brightnesses[3] = 100;
}
void loop() {
loopCount = loopCount - 1;
if (loopCount==0){
loopCount = 100;
}
for (int i=0;i<4;i++){
if (loopCount <= brightnesses[i]) {
digitalWrite(first_led + i, HIGH);
} else {
digitalWrite(first_led + i, LOW);
}
}
}

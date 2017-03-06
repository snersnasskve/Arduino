/*
Larson1
A really poor quality Larson scanner
Peter Robinson 2014
*/
int led = 1; // First LED pin
int led_count = 7; // Number of LEDs in scanner
int step_delay = 100; // milliseconds between scan steps

void setup() {
// initialize all required digital pins as outputs.
for (int i=0; i<led_count; i++){
pinMode(led+i, OUTPUT);
}
}
// The loop routine repeats as long as the arduino has power
void loop() {
// Light one LED at a time, in sequence
// Scan left to right
for (int i=0; i<led_count;i++){
digitalWrite(led+i, HIGH); // turn the LED on (HIGH is the voltage level)
delay(step_delay); // wait for a while
digitalWrite(led+i, LOW); // turn the LED off by making the voltage LOW
}
// Scan right to left
for (int i=led_count - 1; i>=0;i--){
digitalWrite(led+i, HIGH); // turn the LED on (HIGH is the voltage level)
delay(step_delay); // wait for a second
digitalWrite(led+i, LOW); // turn the LED off by making the voltage LOW
}
}

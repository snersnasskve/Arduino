int loopCount = 100;
int brightnesses[7] = {5,10,15,20, 25, 30, 35} ;
// Initialise the array as we create it
int first_led = 1; // The pin number of the first LED
long lastTime = 0;
// Store the previous millis() value
void setup() {
  for (int i=0; i<7; i++){
    pinMode(first_led + i, OUTPUT);
  }
}
void loop() {
  loopCount = loopCount - 1;
  if (loopCount==0){
    loopCount = 100;
  }
  if (millis() > lastTime + 20){
    lastTime = millis();
      for (int i=0;i<7;i++){
 
    brightnesses[i] = brightnesses[i] + 1;
     
    if (brightnesses[i] > 100){
       brightnesses[i] = 0;
    }
   }
  }
  for (int i=0;i<7;i++){
    digitalWrite(first_led + i, loopCount <= brightnesses[i]);
  }
}

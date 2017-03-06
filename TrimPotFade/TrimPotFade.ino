/* Analog Read to LED
 * ------------------ 
 *
 * turns on and off a light emitting diode(LED) connected to digital  
 * pin 13. The amount of time the LED will be on and off depends on
 * the value obtained by analogRead(). In the easiest case we connect
 * a potentiometer to analog pin 2.
 *
 * Created 1 December 2005
 * copyleft 2005 DojoDave <http://www.0j0.org>
 * http://arduino.berlios.de
 *
 */
 
 //Take the brightness from fade below

int potPin = 2;    // select the input pin for the potentiometer
int val = 0;       // variable to store the value coming from the sensor

int led = 9;           // the pin that the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
int brightMax = 0;

void setup() {
  pinMode(led, OUTPUT);  // declare the ledPin as an OUTPUT
    Serial.begin(9600);

}

void loop() {
  val = analogRead(potPin);    // read the value from the sensor
 
 if (val > brightMax)
 {
   brightMax = val;
 }
 
 brightness = val * (255.0 / (1.0 * brightMax) );
 if (brightness > 255)
 {
   Serial.print ("max too high *************= ");
     Serial.print (brightness);
        Serial.print (",    val= ");
                Serial.print (val);
       Serial.print (",    max= ");
                Serial.print (brightMax);


  brightness = 255;
 }
    Serial.println (brightness);

 if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ;
  }
  analogWrite(led, brightness);
 // stop the program for some time
}


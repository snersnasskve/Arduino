
// Arduino RGB colour sensor
// Written by Peter Robinson, www.robinsonia.com/wp
// September 2014

// Setting up the pin definitions for the LEDs as constants
// makes it easier to change them without modifying lots of code
#define LED_R  5
#define LED_G  6
#define LED_B  7

const int buttonPin = 3;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status

int ldr_pin = 3;     // Rhe analog input pin for the light sensor
int ldr_delay = 300; // Delay in milliseconds for sensor to respond to light changes

// Variables used to calibrate the sensor
float min_r = 0;
float max_r = 0;
float min_g = 0;
float max_g = 0;
float min_b = 0;
float max_b = 0;

// Calculated values of red, green and blue light intensities
float r = 0;
float g = 0;
float b = 0;

int temp = 0;

void setup()  { 
  
  pinMode(LED_R,OUTPUT);
  pinMode(LED_G,OUTPUT);
  pinMode(LED_B,OUTPUT);
  
    pinMode(buttonPin, INPUT);     


  Serial.begin(9600);
  Serial.println("Starting");
  
  Serial.println("Hold up a white object");
  calibrate_max();
  Serial.println("Hold up a black object");
  calibrate_min();  
  
  Serial.println("Calibration complete.  Now detecting.");
  delay(1000);
} 

void LED_on(int pin)
{
  digitalWrite(pin, HIGH);
}

void LED_off(int pin)
{
  digitalWrite(pin, LOW);
}

void LEDs_off()
{
  LED_off(LED_R);
  LED_off(LED_G);
  LED_off(LED_B);
}

// In the main body of the program, fade the LED in and out
void loop()  { 
  while (true)
  {
    measure();    // Take the readings
    interpret();  // Work out which colour the readings represent
  }
}

void measure()
{

    LEDs_off();
    delay(ldr_delay);           
    // Illuminate with red light    
    LED_on(LED_R);              
    // Give the LDR time to respond to the light change
    delay(ldr_delay);
    // Read the light intensity
    temp = analogRead(ldr_pin);
    // Calculate the red value as a proportion of the min/max range calibrated earlier
    r = (temp - min_r) / (max_r - min_r);
    LEDs_off();

    // Repeat for green and blue components
    LED_on(LED_G);
    delay(ldr_delay);                            
    temp = analogRead(ldr_pin);
    g = (temp - min_g) / (max_g - min_g);
    LEDs_off();

    LED_on(LED_B);
    delay(ldr_delay);                            
    temp = analogRead(ldr_pin);
    b = (temp - min_b) / (max_b - min_b);
    LEDs_off();
 
}

void interpret()
{
    buttonState = digitalRead(buttonPin);
        Serial.println(buttonState);

  if (buttonState == HIGH)    
  {
    Serial.println("rgb");
  Serial.println( r);
 Serial.println( g);
Serial.println( b);
    Serial.println("---");

if ((r>0.6) && (g<0.6) && (b<0.6))
    Serial.println("Red!");
 else if ((r<0.6) && (g>0.6) && (b<0.6))
    Serial.println("Green!");
 else if ((r<0.6) && (g<0.6) && (b>0.6))
    Serial.println("Blue!");
  else    if ((r>0.6) && (g>0.6) && (b<0.6))
    Serial.println("Yellow!");
    else  if ((r<0.6) && (g>0.6) && (b>0.6))
    Serial.println("Turquoise!");
   else  if ((r>0.6) && (g<0.6) && (b>0.6))
    Serial.println("Purple!");
   else if ((r<0.6) && (g<0.6) && (b<0.6))
    Serial.println("Black!");
  else  if ((r>0.6) && (g>0.6) && (b>0.6))
    Serial.println("White!");
else
    Serial.println("Grey!");
  }


}

// Use a white sample to get maximum readings
void calibrate_max()
{
    LED_on(LED_R);
    LED_on(LED_G);
    LED_on(LED_B);
    delay(3000);                            
    LEDs_off();
    LED_on(LED_R);
    delay(ldr_delay);                            
    max_r = analogRead(ldr_pin);
    LEDs_off();
    LED_on(LED_G);
    delay(ldr_delay);                            
    max_g = analogRead(ldr_pin);
    LEDs_off();
    LED_on(LED_B);
    delay(ldr_delay);                            
    max_b = analogRead(ldr_pin);
    LEDs_off();
}

// Use a black sample to get minimum readings
void calibrate_min()
{
    LEDs_off();
    delay(3000);                            
    LED_on(LED_R);
    delay(ldr_delay);                            
    min_r = analogRead(ldr_pin);
    LEDs_off();
    LED_on(LED_G);
    delay(ldr_delay);                            
    min_g = analogRead(ldr_pin);
    LEDs_off();
    LED_on(LED_B);
    delay(ldr_delay);                            
    min_b = analogRead(ldr_pin);
    LEDs_off();
}



//TMP36 Pin Variables
int sensorPin = 0; //Says we are working with a sensor in analog pin 0
int LED = 13; //defines LED pin
int buttonpin= 3; //says we are look at digtial 3 as well
int val; 
/*
* setup() 
-
this function runs once when you turn your Arduino on
* We initialize the serial connection with the computer
*/
void setup()
{
pinMode (LED, OUTPUT); //define LED as output interface
pinMode (buttonpin, INPUT); //defines digital pin 3 as input for LED
Serial.begin(9600);  //Start the serial connection with the computer
//to view the result open the serial monitor 
}
void loop()                     // run over and over again
{
//getting the voltage reading from the temperature sensor
int reading = analogRead(sensorPin);  
// converting that reading to voltage, for 3.3v arduino use 3.3
float voltage = reading * 5.0;
voltage /= 1024.0; 
// print out the voltage to the serial monitor
Serial.print(voltage); Serial.println(" volts");
val = digitalRead (buttonpin); //read the data from the digital pin
//if (val==HIGH) //when the sensor detects a magnetic field
if (voltage > 2.5) 
{digitalWrite (LED, HIGH);

}
else
{digitalWrite (LED, LOW);
}
delay(100);                                     //waiting a second
}

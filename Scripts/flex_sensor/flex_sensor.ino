int sensorPin = A0;
int sensorValue = 0;
int sensorNormal = 0;

void setup()
{
   Serial.begin(9600);
    delay(1000);
    sensorNormal = analogRead(sensorPin);
    
     Serial.print("Normal: ");
     Serial.println(sensorNormal);
     Serial.println("Setup Complete");

}

void loop()
{
   sensorValue = analogRead(sensorPin);
  
   
   if (sensorValue < sensorNormal)
   {
       Serial.print("Flex: ");
       Serial.println(sensorValue);
       delay(500); 
   }
}

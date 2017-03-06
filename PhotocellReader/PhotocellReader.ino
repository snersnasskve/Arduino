int photocellPin = 0;
void setup()
{
Serial.begin(9600);
}
void loop()
{
int lightLevel = analogRead(photocellPin);
Serial.print("Light level: ");
Serial.println(lightLevel);
delay(1000);
}

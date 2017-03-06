int dialPin = 0;
int speakerPin = 7;
int buttonPin = 6;
boolean oldButtonState;

void setup()
{
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  oldButtonState = digitalRead(buttonPin);
}

void loop()
{
  boolean newButtonState = digitalRead(buttonPin);

  if (oldButtonState != newButtonState)
  {
    Serial.println(newButtonState);
    //  button state has changed
    if (!newButtonState)
    {
      int freq;
      int length = 30;
      int i;
       for (i = 0 ; i < 50 ; i = i + 1)
      {
        freq = random(1000, 2000);
        length = random(30, 40);
        tone(speakerPin, freq, length);
        delay(length + 1);
        tone(speakerPin, 50, length);
         delay(length + 1);
     }
     }
  }
  oldButtonState = newButtonState;
  
}

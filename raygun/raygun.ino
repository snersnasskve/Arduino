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
      int length = 20;
       for (freq = 100 ; freq < 1800 ; freq = freq + 200)
      {
        tone(speakerPin, freq, length);
        delay(length + 1);

      }
       delay(length + 20);
       
       for (freq = 1800 ; freq > 1199 ; freq = freq - 100) 
     {
        tone(speakerPin, freq, length);
        delay(length + 1);

      }
    tone(speakerPin, 1200, length*2);
    delay(length*2 + 1);
    
     for (freq = 1600 ; freq < 2100 ; freq = freq + 100)
      {
        tone(speakerPin, freq, length);
        delay(length + 1);

      }
          for (freq = 2100 ; freq > 100 ; freq = freq - 200)
      {
        tone(speakerPin, freq, length);
        delay(length + 1);

      }
  
      /*
      int freq = 600;
      int length = 100;
      tone(speakerPin, freq, length);
      delay(101);
        freq = 400;
      tone(speakerPin, freq, length);
      delay (101);
      freq = 200;
      length = 200;
      tone(speakerPin, freq, length);
      delay (201);
      freq = 700;
      length = 400;
      tone(speakerPin, freq, length);
      */
  //  delay(length + 1);
    }
  }
  oldButtonState = newButtonState;
  
}

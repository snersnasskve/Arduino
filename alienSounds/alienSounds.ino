int dialPin = 0;
int speakerPin = 7;
int buttonPin = 6;

void setup()
{
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
}

void loop()
{
  int val = analogRead(dialPin);
  if (!digitalRead(buttonPin))
  {
    int freq;
    Serial.println(val);
    if (val >20){
      freq = val;
    }
    else {
      freq = 20;
    }
    int length = 30;
    int gap = 20;
    tone(speakerPin, freq, length);
    delay (gap);
  }
}

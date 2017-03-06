//  Wire an led to each of these pins
int pinCount = 5;
int leds [5] = {7, 6, 5, 4, 3 };           // the pin that the LED is attached to

int timer = 0;


void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < pinCount ; i++)
  {
    pinMode(leds[i], OUTPUT);
  }
   Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);              // wait for a second
  timer++;
  Serial.println(timer);
   
  showTimer();
}

void showTimer()
{

   turnLightsOff();
  
  //  Convert to base 2
  int workingTot = timer;
  int bbase = 2;    //  For binary
  int currentLed = pinCount - 1;
  while (workingTot > 0)
  {

    if (currentLed < 0)
    {
       resetMyTimer(); 
       break;
    }
    int remainder = workingTot % bbase;
    workingTot -= remainder;
    workingTot /= bbase;
    if (remainder > 0)
    {
      digitalWrite(leds[currentLed], HIGH);    // turn the LED off by making the voltage LOW
    }
    currentLed--;
  }
  
}

void resetMyTimer()
{

  turnLightsOff();
  timer = 0;
  delay (5000);
}

void turnLightsOff()
{
  for (int i = 0; i < pinCount ; i++)
  {
    digitalWrite(leds[i], LOW);   // turn the LED on (HIGH is the voltage level)
  }
}

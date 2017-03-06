int seconds;
int minutes;

void setup() {
  // put your setup code here, to run once:
  seconds = 0;
  minutes = 0;
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(minutes );
    Serial.print(":");
  Serial.println(seconds);
delay(1000);
  if (60 == seconds)
  {
    minutes++;
    seconds = 0;
  }
  else
  {
    seconds ++;
  }
}

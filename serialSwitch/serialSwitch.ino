int led = 7;


void setup() {
  // put your setup code here, to run once:
 pinMode(led, OUTPUT);
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int input = Serial.read();
  if ('1' == input)
  {
    Serial.println("on");
    digitalWrite(led, HIGH);
  }
  else if ('0' == input)
  {
     Serial.println("off");
   digitalWrite(led, LOW);
  }
  else
  {
        Serial.println(input);

  }
  delay(1000);
}

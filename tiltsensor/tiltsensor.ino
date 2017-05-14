int Led=13;
//  S = buttonpin
//  - = ground
//  the other one is +
int buttonpin=3; 
int val;
void setup()
{
  pinMode(Led,OUTPUT); 
  pinMode(buttonpin,INPUT); 
}
void loop()
{
  val=digitalRead(buttonpin);
  if(val==HIGH)
{
  digitalWrite(Led,HIGH);
}
else
{
  digitalWrite(Led,LOW);
}
}


int DS_pin = 8;       //  leg 14 on the chip
int STCP_pin = 9;     //  leg 12 on the chip = RCLK = LATCH
int SHCP_pin = 10;    //  leg 11 on the chip = SRCLK = CLOCK

/*
 * Other wiring
 * 
 * leg 10 = Master Rest = must be pulled HIGH 
 *        to make sure you don't clear the register
 *          - join it to +
 * leg 13 = Output Enable = 
 *        inverted pin meaning low is enabled, high is not enabled
 *          - join it to -
 */
 /*
 * 16 = VCC
 * 14 = Data Line = DATA_PIN
 * 13 = Output Enable = BLANK = when this is low, then all outputs are enabled 
 * 12 = RCLK = Shift Register Clock = LATCH_PIN
 * 11 = SRCLK = Storage Register Clock = CLOCK_PIN
 * 10 = SRCLR = Serial Clear = when this is high then will not clear = when low it clears = CLEAR
 * 15 and 9 are used for joining up multiple shift registers together
 *  9 of this register (out) should link to 15 of the second shift register (in)
 *  all other pins above are joined to their matching pins on the second register
 * 
 */
void setup() {
  // put your setup code here, to run once:
  pinMode(DS_pin, OUTPUT);
  pinMode(STCP_pin, OUTPUT);
  pinMode(SHCP_pin, OUTPUT);
  writereg();
}

boolean registers[8];



void writereg()
{
  digitalWrite(SHCP_pin, LOW);
  for (int i = 7 ; i >= 0 ; i--)
  {
      digitalWrite(STCP_pin, LOW);
      digitalWrite(DS_pin, registers[i]);
      digitalWrite(STCP_pin, HIGH);

  }
    digitalWrite(SHCP_pin, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(500); // delay between loops
  for (int i = 0 ; i < 8 ; i++)
  {
    registers[i] = HIGH;
    delay(100);
    writereg();
  }
  delay(500); // delay between loops
  
  for (int i = 7 ; i >=0 ; i--)
  {
    registers[i] = LOW;
    delay(100);
    writereg();
  }
}


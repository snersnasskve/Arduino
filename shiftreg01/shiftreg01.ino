#define DATA_PIN 8
#define LATCH_PIN 9
#define CLOCK_PIN 10

char lastChar;
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

byte d0 = 0b01111101;
byte d1 = 0b00100100;
byte d2 = 0b01111010;
byte d3 = 0b01110110;
byte d4 = 0b00100111;
byte d5 = 0b01010111;
byte d6 = 0b01011111;
byte d7 = 0b01100100;
byte d8 = 0b01111111;
byte d9 = 0b01110111;


/*
byte d0 = 0b01000000;
byte d1 = 0b00100000;
byte d2 = 0b00010000;
byte d3 = 0b00001000;
byte d4 = 0b00000100;
byte d5 = 0b00000010;
byte d6 = 0b00000001;
byte d7 = 0b00000000;
byte d8 = 0b01111111;
byte d9 = 0b00000000;
*/
byte lightsoff = 0b0000000; // all off
byte lightson = 0b01111111; // all off

// add a break out clause
bool capturing = true;

void setup() {
  pinMode(DATA_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  //  If we have something to read
  char digit = lastChar;
    byte byteToWrite = d0;
  if (true  && Serial.available() > 0)
  {
    digit = Serial.read();
    lastChar = digit;
    Serial.println(digit);
  }
  
    switch (digit)
    {
      case '0':
         byteToWrite = d0; break;
      case '1':
         byteToWrite = d1; break;
      case '2':
         byteToWrite = d2; break;
      case '3':
         byteToWrite = d3; break;
      case '4':
         byteToWrite = d4; break;
      case '5':
         byteToWrite = d5; break;
      case '6':
         byteToWrite = d6; break;
      case '7':
         byteToWrite = d7; break;
      case '8':
         byteToWrite = d8; break;
      case '9':
         byteToWrite = d9; break;
      default: 
         capturing = false;

  }
    writeToShift(byteToWrite);
    delay(10800);
}

void writeToShift(byte byteToWrite)
{
      Serial.print("Writing:- ");
      Serial.println(byteToWrite);

  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, byteToWrite);
  digitalWrite(LATCH_PIN, HIGH);

}

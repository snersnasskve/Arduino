

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

byte one = 0b11111001;
byte two = 0b10100100;
byte three = 0b10110000;
byte four = 0b10011001;
byte five = 0b10010010;
byte six = 0b10000010;
byte seven = 0b11111000;
byte eight = 0b10000000;

byte nine = 0b10010000;
byte zero = 0b11000000;
byte test = 0b10000000;
byte empty = 0b00000000;
byte numbers[] = {zero,one,two,three,four,five,six,seven,eight,nine};

byte led0 = 0b00000000;
byte led1 = 0b00000001;
byte led2 = 0b00000011;
byte led3 = 0b00000111;
byte led4 = 0b00001111;
byte led5 = 0b00011111;
byte led6 = 0b00111111;
byte led7 = 0b01111111;
byte led8 = 0b11111111;
byte leds[] = {led0,led1,led2,led3,led4,led5,led6,led7,led8,led8};

// Number of digits attached
int const numberOfRegisters = 2;
byte data;
byte dataBuffer[numberOfRegisters];

void shiftOut(int myDataPin, int myClockPin, byte myDataOut);
void writeBuffer();
void addToBuffer(int digit);

void setup() {
  // put your setup code here, to run once:
  pinMode(DS_pin, OUTPUT);
  pinMode(STCP_pin, OUTPUT);
  pinMode(SHCP_pin, OUTPUT);
  //writereg();
  addToBuffer(0);
}





void loop() {
 for (int i = 0 ; i < 10 ; i++) {
  addToBuffer(i);
  delay(500);
 }
}


void writeBuffer(){
  digitalWrite(STCP_pin, 0);
  
  for (int a = sizeof(dataBuffer) - 1; a >= 0  ; a--) {
    shiftOut(DS_pin, SHCP_pin, dataBuffer[a]);
  }
  
  digitalWrite(STCP_pin, 1);
}

void addToBuffer(int digit){
  // clear buffer
  memset(dataBuffer, 0, sizeof(dataBuffer)* numberOfRegisters);

  int c = 0;

  byte b = numbers [digit % 10];
  byte l = leds [digit % 10];
  dataBuffer[0] = b;
  
  dataBuffer[1] = l;

  writeBuffer();
}

void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low
  
  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);
  
  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);
  
  //for each bit in the byte myDataOut�
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=0; i<=7; i++)  {
    digitalWrite(myClockPin, 0);
    
    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {  
      pinState= 0;
    }
    
    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }
}

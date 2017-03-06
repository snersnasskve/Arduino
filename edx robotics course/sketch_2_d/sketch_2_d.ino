//***************************************************************************************
//  EE40LX
//  Sketch 2.D
//
//  Description; Output an alternating high and low voltage to P1.0,
//     turning a red LED on the MSP430G2 Launch Pad on and off.
//     This time, we add serial communication to enable debugging.
//
//  Tom Zajdel
//  University of California, Berkeley
//  December 17, 2014
//
//***************************************************************************************

void setup()
{
  // start the serial monitor
  Serial.begin(9600);
  
  // set P1.0 to output
  pinMode(P1_0, OUTPUT);
  Serial.println("Pin 1.0 set as output");
}

void loop()
{
  digitalWrite(P1_0, HIGH);  // set the pin to high, turning LED on
  Serial.println("LED on");  // write this to the serial monitor
  
  sleep(1000);               // wait 1000 ms
  
  digitalWrite(P1_0, LOW);   // set the pin to low, turning LED off
  Serial.println("LED off"); // write this to the serial monitor
  
  sleep(1000);               // wait 1000 ms
}

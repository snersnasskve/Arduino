/*
 Analog Input game
  Uses the Flex sensor as a target, and gives you 30 seconds to hit it three
  times with a NERF dart 
 
 Created by Peter Robinson
 1 Apr 2014
 
 This example code is in the public domain.
 */

int buttonPin = 2;
int sensorPin = A0;    // select the input pin for the potentiometer

int ledPinB = 12;      // select the pin for the LED
int ledPinG = 11;      // select the pin for the LED
int ledPinR = 10;      // select the pin for the LED
int speakerPin = 7;   // select the pin for the speaker

int sensorValue = 0;   // variable to store the value coming from the sensor
int buttonValue = 0;   // variable to store the value coming from the button

const int GAME_OVER=0;
const int GAME_STARTING=1;
const int GAME_PLAYING=2;
const int GAME_WIN=3;
const int GAME_LOSE=4;

int gameState=GAME_OVER;

const int START_BEEPS = 3; // Number of beeps before game starts
int score =0;

const unsigned long GAME_DURATION = 30000;  // Length of a game in milliseconds
unsigned long gameEndTime =0;

void TurnOffLeds()
{
    digitalWrite(ledPinG, LOW);  
    digitalWrite(ledPinR, LOW);  
    digitalWrite(ledPinB, LOW);  
}

void setup() {
  // declare the led pins as OUTPUTs:
  pinMode(ledPinR, OUTPUT);  
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinB, OUTPUT);  
  pinMode(speakerPin, OUTPUT);  
  
  // declare the button pin as an INPUT:
  pinMode(buttonPin,INPUT);
}

void loop() {
  if (gameState == GAME_OVER)
  {
    TurnOffLeds();
    
    if (digitalRead(buttonPin)==0)
    {
      gameState = GAME_STARTING;
      score=0;
    }
  }
  
  if (gameState == GAME_STARTING)
  {
    for (int i=0; i<START_BEEPS; i++)
    {
      digitalWrite(ledPinG, HIGH);  
      digitalWrite(ledPinR, HIGH);  
      digitalWrite(ledPinB, LOW);  
      tone(speakerPin,800,300);
      delay(500);
      TurnOffLeds();
      delay(500);
    }
    digitalWrite(ledPinG, HIGH);  
    digitalWrite(ledPinR, LOW);  
    digitalWrite(ledPinB, LOW);  
    tone(7,600,600);
    delay(500);
    TurnOffLeds();
    gameState=GAME_PLAYING;
    gameEndTime = millis()+GAME_DURATION;
  }
  
  if (gameState == GAME_PLAYING) 
  {
    if(millis()<gameEndTime)
    {
      // read the value from the sensor:
      sensorValue = analogRead(sensorPin);    
  
      if (sensorValue>750)
      {
        // turn the ledPin on
        digitalWrite(ledPinB, HIGH);  
        tone(7,1000,300);
        delay(1000);
        digitalWrite(ledPinB, LOW);   
        score = score + 1;
        if (score >= 3)
        {
          gameState = GAME_WIN;
        }
      }
    }
    else // Game time has ended
    {
      if (score < 3)
      {
        gameState = GAME_LOSE;
      }
    }
    
    if (gameState==GAME_WIN)
    {
        digitalWrite(ledPinR, LOW);   
        digitalWrite(ledPinB, LOW);   
        digitalWrite(ledPinG, HIGH);  
        tone(7,1800,500);
        delay(2000);
        gameState = GAME_OVER;
    }

    if (gameState==GAME_LOSE)
    {
        digitalWrite(ledPinR, HIGH);   
        digitalWrite(ledPinB, LOW);   
        digitalWrite(ledPinG, LOW);  
        tone(7,500,500);
        delay(1000);
        tone(7,200,2000);
        delay(3000);
        gameState = GAME_OVER;
    }
  }
}


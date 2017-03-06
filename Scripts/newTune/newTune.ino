/*
  Melody
 
 Plays a melody 
 
 circuit:
 * 8-ohm speaker on digital pin 8
 
 created 21 Jan 2010
 modified 30 Aug 2011
 by Tom Igoe 

This example code is in the public domain.
 
 http://arduino.cc/en/Tutorial/Tone
 
 */
 #include "pitches.h"

// notes in the melody:
//int melody[] = {
//  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4};
  
int ledNotes[] = {
    4, 5, 5, 4,2,0,3,4 };

void setup() {
  
   for (int thisNote = 1; thisNote < 6; thisNote++) {
   digitalWrite(thisNote, LOW);

   }
   
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(8, melody[thisNote],noteDuration);
    digitalWrite(ledNotes[thisNote], HIGH);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
   digitalWrite(ledNotes[thisNote], LOW);
  // stop the tone playing:
    noTone(8);
  }
  
    for (int thisNote = 1; thisNote < 6; thisNote++) {
   digitalWrite(thisNote, LOW);
   }
    digitalWrite(1, LOW);
}

void loop() {
  // no need to repeat the melody.
}

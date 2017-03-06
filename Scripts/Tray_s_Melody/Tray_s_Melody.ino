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
 
 /*************************************************
 * Public Constants
 *************************************************/

#define ccs  1915
#define d  1700
#define es  1519
#define f  1432
#define ss  1352
#define g  1275
#define a  1136
#define V  1073
#define b  1014
#define C  956
#define D  852
#define E  758
#define nn  0


// notes in the melody:
int melody[] = {
  ccs,f,f,f,g,a,g,a,V,C,a,V,a,f,g,g,f,ccs,f,f,f,g,a,g,a,V,C,a,V,a,f,g,g,f,f,a,C,D,C,V,a,g,f,g,a,V,C,ccs,f,a,g,f,ccs,ccs,f,f,f,g,a,g,a,V,C,a,V,a,f,g,g,f};  
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
   2,2,2,2,2,1,1,1,1,2,2,2,1,1,2,2,6,2,2,2,2,2,1,1,1,1,2,2,2,1,1,2,2,6,1,1,3,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,4,4,2,2,2,2,1,1,1,1,2,2,2,1,1,2,2,6,2};

void setup() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 72; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(8, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}


void loop() {
  // no need to repeat the melody.
}



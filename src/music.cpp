#include <Arduino.h>
#include "music.h"

//int track{1};

// change this to make the song slower or faster
int tempo = 120;

  // iterate over the notes of the melody. 
  // Remember, the array is twice the number of notes (notes + durations)
void playM(int & track){
  // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
  // there are two values per note (pitch and duration), so for each note there are four bytes
  int notes = sizeof(melody[track]) / sizeof(melody[track][0]) / 2;
  // this calculates the duration of a whole note in ms
  int wholenote = (60000 * 4) / tempo;
  int divider = 0, noteDuration = 0;
  //to break when melody has ebded. All melody size is set to array element size.
  //If melody is shorter, rest of element is filled with zeros. 
  //break if counted 3 zeros in a row. (hope no melody uses 3 zeros in a row).
  int break_on_3_zeros = 0;
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2)
  {
    // calculates the duration of each note
    divider = melody[track][thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }
    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[track][thisNote], noteDuration*0.9);
    // Wait for the specief duration before playing the next note.
    delay(noteDuration);    
    // stop the waveform generation before the next note.
    noTone(buzzer);

    //BREAK on following 3 zeros in a row
    if (melody[track][thisNote]==0){
      break_on_3_zeros ++;
      if (break_on_3_zeros == 3) break;
    } else {
      break_on_3_zeros = 0;
    }
  }
}

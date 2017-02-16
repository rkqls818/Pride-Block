/*
 * References 
 *  Setting up RFID Reader with Arduino:  http://randomnerdtutorials.com/
 *      Modified by Rui Santos
 *      Created by FILIPEFLOP
 *  Adding Melody: http://www.arduino.cc/en/Tutorial/Tone
 */
 
#include <SPI.h>
#include <MFRC522.h>
#include "pitch.h" //directory for the notes

 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

int speaker = 7;     //speaker connection 

//Jurassic Park Theme Song - Notes
int melody[] = 
{
  NOTE_G2, NOTE_C3, NOTE_G3, NOTE_C3, NOTE_A3, NOTE_A3, NOTE_B3, NOTE_C4, NOTE_C4, NOTE_B3, NOTE_G3, NOTE_A3, 0, 
  NOTE_C4, NOTE_B3, NOTE_G3, NOTE_GS3, NOTE_E3, NOTE_A3, NOTE_B3, NOTE_C4, 0, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4
};

//Jurassic Park Theme Song - Rythm 
int noteDurations[] = {
  375, 375, 500, 500, 700, 125, 125, 375, 125, 250, 250, 750, 250, 250, 250, 250, 375, 125, 125, 125, 375, 250, 500, 125, 125, 500, 125, 125, 125, 150};


void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

  String content= "";
 
  if (content) //when PICC is put near the RFID reader
  for (int thisNote = 0; thisNote < 30; thisNote++) {

    //speed multiplyer (currently set at 80%)
    int noteDuration = 0.8 * noteDurations[thisNote];
    tone(speaker, melody[thisNote], noteDuration);
    
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    digitalWrite(speaker, LOW);

  }
}
 
 

/*
  FILENAME:   WalkieTalkieWorkshop.ino
  DATE: November 28, 2018
  Modified example from Orlando S. Hoilett, orlandohoilett@gmail.com 2015
  RF24 Audio Library TMRh20 2014

*/

#include <userConfig.h>
#include <RF24.h>
#include <SPI.h>
#include <RF24Audio.h>
#include "printf.h"    // General includes for radio audio lib

int radioID = 50;     
int talkButton = 3;

RF24 radio(7,8);                    // Set radio up using pins 7 (CE) 8 (CS)
RF24Audio rfAudio(radio,radioID);   // Set up the audio using the radio, and set radio identifier number to 'radioID'


void setup() {      
  Serial.begin(115200);

  
  
  printf_begin();
  radio.begin();                    //initializes radio library
  radio.setChannel(radioID);        //sets radio to address between 0 - 124, aka 2.4GHz- 2.525GHz
  radio.printDetails();             //prints radio info to serial monitor
  rfAudio.begin();                  //initializes radio audio library
  rfAudio.broadcast(radioID);       //cestablish private radio channel

  pinMode(talkButton, INPUT);

  //sets interrupt to check for button talk abutton press
  attachInterrupt(digitalPinToInterrupt(talkButton), talk, CHANGE);
  
  //sets the default state for each module to recevie
  rfAudio.receive();
}


//void talk()
//Called in response to interrupt. Checks the state of the button.
//If the button is pressed (and held) enters transmit mode to send
//audio. If button is released, enters receive mode to listen.
void talk()
{
  if (digitalRead(talkButton)) rfAudio.transmit();
  else rfAudio.receive();
}


void loop()
{
}

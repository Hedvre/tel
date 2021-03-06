#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Keypad.h>

//Radio
char msg[1];
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int SW1 = A0;

//Keypad
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'-','0','+', 'D'}
};
byte rowPins[ROWS] = {4, 3, 2, A5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6, 5}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup(void){
Serial.begin(9600);
radio.begin();
radio.openWritingPipe(pipe);
}


void loop(void){

  msg[0] = 'A';
  radio.write(msg, 1);

  while(1){
    char key = keypad.getKey();
    if (key){
      if(key == 'D' && digitalRead(SW1) == HIGH){key = 'E';}
      Serial.println(key);
      msg[0] = 'A';
      radio.write(msg, 1);
      radio.write(&key, sizeof(char));
      
    }
  }
}

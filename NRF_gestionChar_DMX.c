#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <DmxSimple.h>


///////////NRF
int msg[1];
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

/*
Wiring

Wire nRF24L01+ to Arduino UNO

GND <–> GND
VCC <–> Arduino 3.3V
CE <–> Arduino pin 9
CSN <–> Arduino pin 10
SCK <–> Arduino pin 13
MOSI <–> Arduino pin 11
MISO <–> Arduino pin 12
*/

//////////GestionChar
/*
Input char from Keypad 4*4
{
{1,2,3,A},
{4,5,6,B},
{7,8,9,C},
{-,0,+,D}
}
A: valeur canal
B: set canal
C: clear all
D/E: mettre à une valeur plusieurs canaux conjoints/selection de plusieurs canaux disjoints(jusqu'à 16)
*/
char c = '0';
char x = '0';
int value = 0;
int channel = 0;
typedef enum {normal, thru, add} mode;
mode state = normal;

int i, j = 0;
//déclarations pour modes Add et thru
int tab[16] = {0}; // contient des n° de canal
int iAdd = 0; // increment pour tableau
int jAdd = 0; // increment pour boucles
int iThru = 0;
int jThru = 0;


//Def fonction
void gestionChar(char c);




void setup(void){
Serial.begin(9600);
radio.begin();
radio.openReadingPipe(1,pipe);
radio.startListening();
}



void loop(void){
    char rx ='R';
  if (radio.available()){
    bool done = false;
    while (!done){
      done = radio.read(msg, 1);
      rx = msg[0];
      Serial.println(rx);
      gestionChar(rx);
      }
  }
}




void gestionChar(char c){
  /* code */
  //gestion des chiffres
  if ((c>='0') && (c<='9')) {
        value = 10*value + c - '0';
    }

    //fonction clear all
  else if (c=='C'){
    state = normal;
    //DmxSimple.clear();
    Serial.print("clear all\n");
    for(i=1; i<=255; ++i){
      Serial.print("channel "); Serial.print(i); Serial.println(" value 0");
      DmxSimple.write(i, 0);
    }
    channel = 0;
    value = 0;
    for(i=0; i<16; ++i){
      tab[i] =0;
    }
  }

  // set state THRU
  else if (c=='D'){
    Serial.print("state THRU\n");
    state = thru;
    iThru = 0;
    value = 0;
  }

  //set state ADD
  else if (c=='E'){
    Serial.print("state ADD\n");
    state = add;
    iAdd = 0;
    value = 0;
  }

    else{
  switch(state){
    //state normal
    case normal :
      if(c=='A'){
        channel = value;
        value = 0;
      }
      else if (c=='B'){
        DmxSimple.write(channel, value);
        Serial.print("channel "); Serial.print(channel); Serial.print(" value "); Serial.println(value);
        value = 0;
      }
      else if (c=='+'){
        DmxSimple.write(channel, 0);
        Serial.print("channel "); Serial.print(channel); Serial.println(" value 0");
        channel += 1;
        DmxSimple.write(channel, 255);
        Serial.print("channel "); Serial.print(channel); Serial.println(" value 255");
      }
      else if (c=='-'){
        DmxSimple.write(channel, 0);
        Serial.print("channel "); Serial.print(channel); Serial.println(" value 0");
        channel -= 1;
        DmxSimple.write(channel, 255);
        Serial.print("channel "); Serial.print(channel); Serial.println(" value 255");
      }
      break;

    //state thru
    case thru :
      if(c=='A'){
        tab[1] = value;
        value = 0;
      }
      else if (c=='B'){
        if (tab[0]<=tab[1]){
          for(iThru = tab[0]; iThru<= tab[1]; ++iThru){
            ///!!!! à modifier pour que le DMX envoi aussi aux premiers canaux et
            ///pas seulement à partir de tab[0]
            DmxSimple.write(iThru, value);
            Serial.print("channel "); Serial.print(iThru); Serial.print(" value "); Serial.println(value);
          }
        }
        else{
          for(iThru = tab[1]; iThru <= tab[0]; ++iThru){
            ///!!!! à modifier pour que le DMX envoi aussi aux premiers canaux et
            ///pas seulement à partir de tab[1]
            DmxSimple.write(iThru, value);
            Serial.print("channel "); Serial.print(iThru); Serial.print(" value "); Serial.println(value);
          }
        }
        value = 0;
      }

      else if (c =='+'){
        tab[0] = value;
        value = 0;
      }
      else if (c =='-'){
      /* code */
      }
      break;

    /*Mode ADD : permet d'Affecter une valeur à plusieurs canaux
    procédure : E - n° canal - +/A - n° canal - +/A - valeur - B
    */
    case add :

      if(c=='A'){
        tab[iAdd] = value;
        value = 0;
        if(iAdd<16){
          ++iAdd;
        }
      }
      else if (c=='B'){
        for(jAdd=0; jAdd<iAdd; ++jAdd){
          DmxSimple.write(tab[jAdd], value);
          Serial.print("channel "); Serial.print(tab[jAdd]); Serial.print(" value "); Serial.println(value);
        }
        value = 0;
      }
      else if (c=='+'){
        tab[iAdd] = value;
        value = 0;
        if(iAdd<16){
          ++iAdd;
        }
      }
      else if (c=='-'){
        /* code */
      }
      break;    
          }
    }
}

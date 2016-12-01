#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
int msg[1];
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int LED1 = 3;

void setup(void){
Serial.begin(9600);
radio.begin();
radio.openReadingPipe(1,pipe);
radio.startListening();
pinMode(LED1, OUTPUT);}

void loop(void){
  char rx ='R';
if (radio.available()){
bool done = false;
while (!done){
done = radio.read(msg, 1);
rx = msg[0];
Serial.println(rx);
if (msg[0] == 65){
  delay(10);
  digitalWrite(LED1, HIGH);}
else {
  digitalWrite(LED1, LOW);}
delay(10);}}
else{
  //Serial.println("No radio available");
  }
  }

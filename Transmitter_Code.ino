#include <SPI.h>  
#include "RF24.h"
#include <nRF24L01.h>
const byte address[6] = "00001";
RF24 myRadio (9, 10);
void setup()
{
  Serial.begin(9600);
  delay(1000);
  myRadio.begin();
  myRadio.setPALevel(RF24_PA_MIN); 
  myRadio.openWritingPipe(address);
  myRadio.stopListening();
  delay(1000);
}
void loop(){
  delay(5);
  int joy1 = analogRead(A0);
  int angleJoy1 = map(joy1, 0, 1023, 0, 180);
  myRadio.write(&angleJoy1, sizeof(angleJoy1));
  Serial.println(angleJoy1);

  int joy2 = analogRead(A1);
  int angleJoy2 = map(joy2, 0, 1023, 0, 180);
  myRadio.write(&angleJoy2, sizeof(angleJoy2));
  Serial.println(angleJoy2);
  delay(5);

}

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
  delay(10);
  int yAxis = analogRead(A2);
  myRadio.write(&yAxis, sizeof(yAxis));
  Serial.println(yAxis);
  
  delay(10);
  
  int xAxis = analogRead(A1);
  myRadio.write(&xAxis, sizeof(xAxis));
  Serial.println(xAxis);
  

  delay(10);
}

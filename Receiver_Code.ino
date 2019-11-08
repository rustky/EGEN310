#include <SPI.h>  
#include "RF24.h"
#include <nRF24L01.h>
RF24 myRadio (9, 10);
#define EnA 5
#define In1 6
#define In2 7
#define EnB 3
#define In3 2
#define In4 4

const byte address[6] = "00001"; 
void setup() 
{
  Serial.begin(9600);
  myRadio.begin(); 
  myRadio.openReadingPipe(0,address);
  myRadio.setPALevel(RF24_PA_MIN);  
  myRadio.startListening();
  pinMode(EnA, OUTPUT);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(EnB, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
}
void loop() {
  delay(5);
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  myRadio.startListening();
  int angleJoy1;
  int angleJoy2;
  if ( myRadio.available()) {
      myRadio.read(&angleJoy1, sizeof(angleJoy1));
      if( angleJoy1 > 80  ){
         analogWrite(EnA, 200);
      }
      else {
        analogWrite(EnA, 0);
        }
      Serial.println(angleJoy1);
      delay(5);
    }
      myRadio.read(&angleJoy2, sizeof(angleJoy2));
      if( angleJoy2 > 120 ){
         analogWrite(EnB, 200);
      }
      else {
        analogWrite(EnB, 0);
        }
      Serial.println(angleJoy2);
      delay(5);
    }
   //Serial.println(myRadio.available());

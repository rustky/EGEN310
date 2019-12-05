#include <SPI.h>  //Include libraries needed to call certain methods
#include "RF24.h"
#include <nRF24L01.h>
const byte address[6] = "00001";  //Sets up transmission address
RF24 myRadio (9, 10);             //Sets pins 9 and 10 on the Arduino as the transciever radio pins

void setup()
{
  Serial.begin(9600);             //Begins serial monitor for debugging
  delay(1000);                    //Delay to let things boot up
  myRadio.begin();                //Begins radio transmission
  myRadio.setPALevel(RF24_PA_MIN);  //Sets radio power level to low
  myRadio.openWritingPipe(address);  //Opens radio transmitting line
  myRadio.stopListening();          //Ensures transciever is not trying to receive any data
  delay(1000);                    //Short delay
}
//Everything below this line was written by student
void loop(){                      //Loops infinitely
  delay(10);                      //Delay to try to line up transmission timing with the receiver
  int yAxis = analogRead(A2);     //Reads the value of the y angle of the joystick from analog pin 2 and stores as an integer
  myRadio.write(&yAxis, sizeof(yAxis)); //Sends the value of y angle and the size of the data
  Serial.println(yAxis);          //Prints y angle for debugging
  
  delay(10);                      //Delay for timing with receiver
  
  int xAxis = analogRead(A1);     //Reads the value of the x angle of the joystick from analog pin 1 and stores as an integer
  myRadio.write(&xAxis, sizeof(xAxis)); //Sends the value of x angle and the size of the data
  Serial.println(xAxis);          //Prints x angle for debugging
  

  delay(10);                      //Short delay before looping
}

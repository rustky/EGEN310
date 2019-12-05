#include <SPI.h>  //Includes libraries needed to call certain methods
#include "RF24.h"
#include <nRF24L01.h>
RF24 myRadio (9, 10); //Establishes digital pins 9 and 10 as radio transmission pins
#define enA 5   //Sets up which logic control pins map to which digital pins on the Arduino board
#define in1 6
#define in2 7
#define enB 3
#define in3 2
#define in4 4

const byte address[6] = "00001";  //Sets up address for radio transmission with other transceiver
void setup() 
{
  Serial.begin(9600);             //Begins Serial monitor for debugging
  myRadio.begin();                //Turns on radio
  myRadio.openReadingPipe(0,address); //Opens radio reading at previously defined address
  myRadio.setPALevel(RF24_PA_MIN);    //Set radio power level to low
  myRadio.startListening();       //Starts radio listening 
  pinMode(enA, OUTPUT);           //Sets up each digital pin as an output to control motor status
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
}
void loop() {                     //Loops infinitley
  myRadio.startListening();       //Sets transceiver to transceive 
  int yAxis;                      //Sets up yAxis angle as an integer
  int xAxis;                      //Sets up xAxis angle as an integer
  if ( myRadio.available()) {     //If radio transmission is available, continue
      delay(10);                  //Delay to adjust for timing error
      myRadio.read(&yAxis, sizeof(yAxis));  //Read the transmitted value of the y axis angle
      delay(10);                  //Delay to adjsut for timing error
      myRadio.read(&xAxis, sizeof(xAxis));  //Read the transmitted value of the x axis angle
      Serial.println(xAxis);      //Print x and y angles for debugging
      Serial.println(yAxis);
  // Y-axis used for forward and backward control
  if (xAxis > 470 && xAxis <700) {    //Helps ensure car stays stationary if the x axis on the joystick hasn't been adjusted
  if (yAxis > 700) {                  //If the joystick is moved to the forward, continue
      // Set Motor A forward
      digitalWrite(in1, HIGH);        
      digitalWrite(in2, LOW);
      // Set Motor B forward
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(enA, 255); // Send PWM signal to motor A
      analogWrite(enB, 255); // Send PWM signal to motor B
  }
  else if (yAxis < 400) {           //If the joystick is moved to the backward, continue
      // Set Motor A backward
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      // Set Motor B backward
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      analogWrite(enA, 255); // Send PWM signal to motor A
      analogWrite(enB, 255); // Send PWM signal to motor B
  }
  // If joystick stays in middle the motors are not moving
  else {
      analogWrite(enA, 0); // Send PWM signal to motor A
      analogWrite(enB, 0); // Send PWM signal to motor B
  }
  }
  
  else {
  // X-axis used for left and right control
  if (xAxis < 400) {          //If the joystick is moved to the left, continue
      //Set the right motor only forward
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enA, 255); // Send PWM signal to motor A
      analogWrite(enB, 0); // Send PWM signal to motor B
    }

  else if (xAxis > 700) { //If the joystick is the moved to the right, continue
      //Set only right motor forward
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(enA, 0); // Send PWM signal to motor A
      analogWrite(enB, 255); // Send PWM signal to motor B
      
  }
  
  else{ //Helps ensure motors will remain motionless otherwise
      analogWrite(enA, 0); // Send PWM signal to motor A
      analogWrite(enB, 0); // Send PWM signal to motor B
  }
  }
  delay(10);  //Delay for a very brief time before looping
  }
}

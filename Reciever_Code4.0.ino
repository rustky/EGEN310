#include <SPI.h>  
#include "RF24.h"
#include <nRF24L01.h>
RF24 myRadio (9, 10);
#define enA 5
#define in1 6
#define in2 7
#define enB 3
#define in3 2
#define in4 4

const byte address[6] = "00001"; 
void setup() 
{
  Serial.begin(9600);
  myRadio.begin(); 
  myRadio.openReadingPipe(0,address);
  myRadio.setPALevel(RF24_PA_MIN);  
  myRadio.startListening();
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
}
void loop() {
  myRadio.startListening();
  int yAxis;
  int xAxis;
  if ( myRadio.available()) {
      delay(10);
      myRadio.read(&yAxis, sizeof(yAxis));
      delay(10);
      myRadio.read(&xAxis, sizeof(xAxis));
      Serial.println(xAxis);
      Serial.print(" boi");
      Serial.println(yAxis);
      Serial.print(" bitch");
       // Y-axis used for forward and backward control

  if (xAxis > 470 && xAxis <700) {
  if (yAxis > 700) {
      // Set Motor A forward
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      // Set Motor B forward
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(enA, 255); // Send PWM signal to motor A
      analogWrite(enB, 255); // Send PWM signal to motor B
  }
  else if (yAxis < 400) {
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
  if (xAxis < 400) {
      // Convert the declining X-axis readings from 470 to 0 into increasing 0 to 255 value
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enA, 255); // Send PWM signal to motor A
      analogWrite(enB, 0); // Send PWM signal to motor B
    }

  else if (xAxis > 700) {
      // Convert the increasing X-axis readings from 550 to 1023 into 0 to 255 value
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(enA, 0); // Send PWM signal to motor A
      analogWrite(enB, 255); // Send PWM signal to motor B
      
  }
  // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
  else{
      analogWrite(enA, 0); // Send PWM signal to motor A
      analogWrite(enB, 0); // Send PWM signal to motor B
  }
  }
  delay(10);
  }
}

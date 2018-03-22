#include <SPI.h>
#include <PS4BT.h>
#include <Servo.h>

USB usb;
BTD btd(&usb);
PS4BT ps4(&btd);

const byte mtrRF [3] = {22,23,11}; // Right-Front Motor pins
const byte mtrRB [3] = {29,28,8}; // Right Back Motor pins
const byte mtrLF [3] = {36,37,6}; // Left Front Motor pins
const byte mtrLB [3] = {44,45,4}; // Left Back Motor pins
/* index 0 = input a
 * index 1 = input b 
 * index 2 = PWM */

/*
 * 
  analogWrite(mtrRF[2], 255);
  analogWrite(mtrRB[2], 255);
  analogWrite(mtrLF[2], 255);
  analogWrite(mtrLB[2], 255);
  digitalWrite(mtrRF[0], );
  digitalWrite(mtrRF[1], );
  digitalWrite(mtrRB[0], );
  digitalWrite(mtrRB[1], );
  digitalWrite(mtrLF[0], );
  digitalWrite(mtrLF[1], );
  digitalWrite(mtrLB[0], );
  digitalWrite(mtrLB[1], );

  write(pin1, HIGH) + write(pin2, LOW) = counterClockwise
  write(pin1, LOW) + write(pin2, HIGH) = clockwise
  
 * 
 */

void neutral () {
  digitalWrite(mtrRF[0], LOW);
  digitalWrite(mtrRF[1], LOW);
  digitalWrite(mtrRB[0], LOW);
  digitalWrite(mtrRB[1], LOW);
  digitalWrite(mtrLF[0], LOW);
  digitalWrite(mtrLF[1], LOW);
  digitalWrite(mtrLB[0], LOW);
  digitalWrite(mtrLB[1], LOW);
}

void stopAll() {
  analogWrite(mtrRF[2], 255);
  analogWrite(mtrRB[2], 255);
  analogWrite(mtrLF[2], 255);
  analogWrite(mtrLB[2], 255);
  digitalWrite(mtrRF[0], LOW);
  digitalWrite(mtrRF[1], LOW);
  digitalWrite(mtrRB[0], LOW);
  digitalWrite(mtrRB[1], LOW);
  digitalWrite(mtrLF[0], LOW);
  digitalWrite(mtrLF[1], LOW);
  digitalWrite(mtrLB[0], LOW);
  digitalWrite(mtrLB[1], LOW);
}

void backwards() {
  analogWrite(mtrRF[2], 255);
  analogWrite(mtrRB[2], 255);
  analogWrite(mtrLF[2], 255);
  analogWrite(mtrLB[2], 255);
  digitalWrite(mtrRF[0], LOW);
  digitalWrite(mtrRF[1], HIGH);
  digitalWrite(mtrRB[0], LOW);
  digitalWrite(mtrRB[1], HIGH);
  digitalWrite(mtrLF[0], HIGH);
  digitalWrite(mtrLF[1], LOW);
  digitalWrite(mtrLB[0], HIGH);
  digitalWrite(mtrLB[1], LOW);
}

void forward() {
  analogWrite(mtrRF[2], 255);
  analogWrite(mtrRB[2], 255);
  analogWrite(mtrLF[2], 255);
  analogWrite(mtrLB[2], 255);
  digitalWrite(mtrRF[0], HIGH);
  digitalWrite(mtrRF[1], LOW);
  digitalWrite(mtrRB[0], HIGH);
  digitalWrite(mtrRB[1], LOW);
  digitalWrite(mtrLF[0], LOW);
  digitalWrite(mtrLF[1], HIGH);
  digitalWrite(mtrLB[0], LOW);
  digitalWrite(mtrLB[1], HIGH);
}

void left(){
  analogWrite(mtrRF[2], 255);
  analogWrite(mtrRB[2], 255);
  analogWrite(mtrLF[2], 255);
  analogWrite(mtrLB[2], 255);
  digitalWrite(mtrRF[0], LOW);
  digitalWrite(mtrRF[1], HIGH);
  digitalWrite(mtrRB[0], HIGH);
  digitalWrite(mtrRB[1], LOW);
  digitalWrite(mtrLF[0], LOW);
  digitalWrite(mtrLF[1], HIGH);
  digitalWrite(mtrLB[0], HIGH);
  digitalWrite(mtrLB[1], LOW);
}

void right(){
  analogWrite(mtrRF[2], 255);
  analogWrite(mtrRB[2], 255);
  analogWrite(mtrLF[2], 255);
  analogWrite(mtrLB[2], 255);
  digitalWrite(mtrRF[0], HIGH);
  digitalWrite(mtrRF[1], LOW);
  digitalWrite(mtrRB[0], LOW);
  digitalWrite(mtrRB[1], HIGH);
  digitalWrite(mtrLF[0], HIGH);
  digitalWrite(mtrLF[1], LOW);
  digitalWrite(mtrLB[0], LOW);
  digitalWrite(mtrLB[1], HIGH);
}

void backRight(){
  analogWrite(mtrRF[2], 255);
  analogWrite(mtrRB[2], 255);
  analogWrite(mtrLF[2], 255);
  analogWrite(mtrLB[2], 255);
  digitalWrite(mtrRF[0], LOW);
  digitalWrite(mtrRF[1], LOW);
  digitalWrite(mtrRB[0], LOW);
  digitalWrite(mtrRB[1], HIGH);
  digitalWrite(mtrLF[0], HIGH);
  digitalWrite(mtrLF[1], LOW);
  digitalWrite(mtrLB[0], LOW);
  digitalWrite(mtrLB[1], LOW);
}

void backLeft() {
  analogWrite(mtrRF[2], 255);
  analogWrite(mtrRB[2], 255);
  analogWrite(mtrLF[2], 255);
  analogWrite(mtrLB[2], 255);
  digitalWrite(mtrRF[0], LOW);
  digitalWrite(mtrRF[1], HIGH);
  digitalWrite(mtrRB[0], LOW);
  digitalWrite(mtrRB[1], LOW);
  digitalWrite(mtrLF[0], LOW);
  digitalWrite(mtrLF[1], LOW);
  digitalWrite(mtrLB[0], HIGH);
  digitalWrite(mtrLB[1], LOW);
}

void forwardLeft() {
  analogWrite(mtrRF[2], 255);
  analogWrite(mtrRB[2], 255);
  analogWrite(mtrLF[2], 255);
  analogWrite(mtrLB[2], 255);
  digitalWrite(mtrRF[0], LOW);
  digitalWrite(mtrRF[1], LOW);
  digitalWrite(mtrRB[0], HIGH);
  digitalWrite(mtrRB[1], LOW);
  digitalWrite(mtrLF[0], LOW);
  digitalWrite(mtrLF[1], HIGH);
  digitalWrite(mtrLB[0], LOW);
  digitalWrite(mtrLB[1], LOW);
}

void forwardRight() {
  analogWrite(mtrRF[2], 255);
  analogWrite(mtrRB[2], 255);
  analogWrite(mtrLF[2], 255);
  analogWrite(mtrLB[2], 255);
  digitalWrite(mtrRF[0], HIGH);
  digitalWrite(mtrRF[1], LOW);
  digitalWrite(mtrRB[0], LOW);
  digitalWrite(mtrRB[1], LOW);
  digitalWrite(mtrLF[0], LOW);
  digitalWrite(mtrLF[1], LOW);
  digitalWrite(mtrLB[0], LOW);
  digitalWrite(mtrLB[1], HIGH);
}

void rotateClockwise() {
  analogWrite(mtrRF[2], 255);
  analogWrite(mtrRB[2], 255);
  analogWrite(mtrLF[2], 255);
  analogWrite(mtrLB[2], 255);
  digitalWrite(mtrRF[0], HIGH);
  digitalWrite(mtrRF[1], LOW);
  digitalWrite(mtrRB[0], HIGH);
  digitalWrite(mtrRB[1], LOW);
  digitalWrite(mtrLF[0], HIGH);
  digitalWrite(mtrLF[1], LOW);
  digitalWrite(mtrLB[0], HIGH);
  digitalWrite(mtrLB[1], LOW);
}

void rotateCounter() {
  analogWrite(mtrRF[2], 255);
  analogWrite(mtrRB[2], 255);
  analogWrite(mtrLF[2], 255);
  analogWrite(mtrLB[2], 255);
  digitalWrite(mtrRF[0], LOW);
  digitalWrite(mtrRF[1], HIGH);
  digitalWrite(mtrRB[0], LOW);
  digitalWrite(mtrRB[1], HIGH);
  digitalWrite(mtrLF[0], LOW);
  digitalWrite(mtrLF[1], HIGH);
  digitalWrite(mtrLB[0], LOW);
  digitalWrite(mtrLB[1], HIGH);
}

void setup() {
  Serial.begin(9600);    //initialize serial @ 9600 baudrate
  pinMode(mtrRF[0], OUTPUT);
  pinMode(mtrRF[1], OUTPUT);
  
  pinMode(mtrRB[0], OUTPUT);
  pinMode(mtrRB[1], OUTPUT);
  
  pinMode(mtrLF[0], OUTPUT);
  pinMode(mtrLF[1], OUTPUT);

  pinMode(mtrLB[0], OUTPUT);
  pinMode(mtrLB[1], OUTPUT);

//
//  if (usb.Init() == -1) {
//    Serial.print("USB failed to start");
//    while(1); // STOP
//  }
  Serial.println("PS4 Bluetooth Started");
}

int xIN;
int yIN;
const float root2over2 = 0.7071068;

char data;

void loop() {  
  // Control Servos
  while (Serial.available() > 0) 
  {
    //save it to character 'data'
    data = Serial.read();
    //print it on serial monitor
    Serial.println(data);
    if (data == 'S') {
      stopAll();
    }
    if (data == 'F') {
      forward();
    }
    if (data == 'B'){
      backwards();
    }
    if (data == 'L'){
      left();
    }
    if (data == 'R'){
      right();
    }
    if (data == 'I') {
      forwardRight();
    }
    if (data == 'G') {
      forwardLeft();
    }
    if (data == 'H') {
      backLeft();
    }
    if (data == 'J') {
      backRight();
    }
    if (data == '0' || data == '1' || data == '2' || data == '3') {
      rotateCounter(); 
    }
    if (data == '7' || data == '8' || data == '9' || data == 'q') {
      rotateClockwise();
    }
    //Neutral
    if (data == '4' || data == '5' || data == '6')
    {
      neutral();
    }
  }

//  Serial.println("GO");
}



// ROTATE FORWARD
//  digitalWrite(mtrRF[0], HIGH);
//  digitalWrite(mtrRF[1], LOW);
//  digitalWrite(mtrRB[0], HIGH);
//  digitalWrite(mtrRB[1], LOW);
//  digitalWrite(mtrLF[0], HIGH);
//  digitalWrite(mtrLF[1], LOW);
//  digitalWrite(mtrLB[0], HIGH);
//  digitalWrite(mtrLB[1], LOW);




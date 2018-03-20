#include <Servo.h>
#include <SPI.h>
#include <PS4BT.h>
#include <Servo.h>

USB usb;
BTD btd(&usb);
PS4BT ps4(&btd);

const byte mtrLF [3] = {22,23,11}; // Right-Front Motor pins
const byte mtrLB [3] = {28,29,8}; // Right Back Motor pins
const byte mtrRF [3] = {36,37,6}; // Left Front Motor pins
const byte mtrRB [3] = {44,45,4}; // Left Back Motor pins
/* index 0 = input a
 * index 1 = input b 
 * index 2 = PWM */
 
Servo right;
Servo left;

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

  right.attach(48);
  left.attach(49);

//  if (usb.Init() == -1) {
//    Serial.print("USB failed to start");
//    while(1); // STOP
//  }
  Serial.println("PS3 Bluetooth Started");
}

int xIN;
int yIN;
const float root2over2 = 0.7071068;

void loop() {  
  // Control Servos
  if (ps4.getButtonPress(R1)){
    right.write(180);
  }
  else if (ps4.getButtonPress(R2)){
    right.write(0);
  }
  if(ps4.getButtonPress(L1)){
    left.write(180);
  }
  else if (ps4.getButtonPress(L2)){
    left.write(0);
  }
  
  xIN = ps4.getAnalogHat(LeftHatX);
  yIN = ps4.getAnalogHat(LeftHatY);

  // Convert raw x and y to polar coordinates
  float radius = sqrt((xIN * xIN) + (yIN * yIN));
  float theta = acos(xIN / radius);

  // subtract/add the appropriate
  float RFandLB = theta + PI/4; 
  float RBandLF = theta - PI/4;

  analogWrite(mtrRF[2], cos(RFandLB) * 255);
  analogWrite(mtrRB[2], cos(RBandLF) * 255);
  analogWrite(mtrLF[2], cos(RFandLB) * 255);
  analogWrite(mtrLB[2], cos(RBandLF) * 255);


  //Move right front and left back wheels forwards
  if (sin(RFandLB) > 0) {
    digitalWrite(mtrRF[0], HIGH);
    digitalWrite(mtrRF[1], LOW);
    digitalWrite(mtrLB[0], HIGH);
    digitalWrite(mtrLB[1], LOW);
  }
  //Move Backwards
  else {
    digitalWrite(mtrRF[0], LOW);
    digitalWrite(mtrRF[1], HIGH);
    digitalWrite(mtrLB[0], LOW);
    digitalWrite(mtrLB[1], HIGH);
  }

  
  //Move right back and left front wheels forwards
  if(sin(RBandLF) > 0){
    digitalWrite(mtrRB[0], HIGH);
    digitalWrite(mtrRB[1], LOW);
    digitalWrite(mtrLF[0], HIGH);
    digitalWrite(mtrLF[1], LOW);
  }
  // Move Backwards
  else{
    digitalWrite(mtrRB[0], LOW);
    digitalWrite(mtrRB[1], HIGH);
    digitalWrite(mtrLF[0], LOW);
    digitalWrite(mtrLF[1], HIGH);
  }
  Serial.println("GO");
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




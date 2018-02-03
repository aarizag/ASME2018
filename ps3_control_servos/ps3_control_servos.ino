#include <SPI.h>
#include <PS3BT.h>                                                    //Include the necessary libraries.
#include <Servo.h>

USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd);

Servo servo1;                                                         //Create instances of type Servo. servo1 is the steering servo and servo2 is the ESC.
Servo servo2;
bool start = false;

void setup() {
   Serial.begin(115200);
  
   if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
}
void loop()
{
 
  Usb.Task();
  
//  Serial.println("PS3 Connected");
//  Serial.println(PS3.PS3Connected);

  if(PS3.getButtonPress(PS)) {
    start = true;
    if (!servo1.attached()){
      servo1.attach(3);                                               
      servo2.attach(5);
    }
  }
  
  if (start) {
    servo1.write(map(PS3.getAnalogHat(RightHatX), 0, 1023, 0, 180));
    servo2.write(map(PS3.getAnalogHat(LeftHatY), 0, 1023, 180, 0));
//    Serial.println(map(PS3.getAnalogHat(RightHatX), 0, 1023, 0, 180));
  }
//  if (PS3.getButtonClick(UP)) {
//    digitalWrite(LED1, HIGH);
//
//    Serial.print(F("\r\nUp"));
//
//     if (PS3.PS3Connected) {
//      PS3.setLedOff();
//      PS3.setLedOn(LED1);
//
//    }
//  }
//    
//  if (PS3.getButtonClick(UP)) {
//    digitalWrite(LED1, HIGH);
//
//    Serial.print(F("\r\nUp"));
//
//     if (PS3.PS3Connected) {
//      PS3.setLedOff();
//      PS3.setLedOn(LED1);
//
//    }
//  }
}


#include <SPI.h>
#include <PS3BT.h>                                                    //Include the necessary libraries.
#include <Servo.h>

USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd);

Servo right;                                                         //Create instances of type Servo. servo1 is the steering servo and servo2 is the ESC.
Servo left;
bool start = false;

void setup() {
   Serial.begin(9600);
  
   if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
}

int x;
int y;
void loop()
{
 
  Usb.Task();
  
//  Serial.println("PS3 Connected");
//  Serial.println(PS3.PS3Connected);

  if(PS3.getButtonPress(PS)) {
    start = true;
    if (!right.attached()){
      right.attach(3);                                               
      left.attach(5);
    }
  }
  
  if (start) {
    x = PS3.getAnalogHat(LeftHatX);
    Serial.print("X: ");
    Serial.println(x);
    y = PS3.getAnalogHat(LeftHatY);
    Serial.print("Y: ");
    Serial.print(y);

  // Wheels move forward at 0
  // Wheels stand still at ~122
  // x Axis 0 is left
  // y axis 0 is top
  // ROTATE LEFT : xy=(0,122) -> rl=(0, 255) 
  // ROTATE RIGHT: xy=(255, 122) -> rl=(255, 0)
      // y = 255 - x
      
  // FORWARD: xy=(122,0) -> rl=(0, 0) 
      // x = y
  // BACKWARD: xy=(122,255) -> rl=(255, 255)
      // x = y
      

    right.write(map(x, 0, 1023, 0, 180));
    left.write(map(y, 0, 1023, 180, 0)); //CHANGED
//    Serial.println(map(PS3.getAnalogHat(RightHatX), 0, 1023, 0, 180));
  }
}

int rightWheelMove(x, y){
  int value = 0;
  if (value < 50){
    return 0;
  }
  else{
    return value;
  }
}

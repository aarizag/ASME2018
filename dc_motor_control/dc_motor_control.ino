#include <SPI.h>
#include <PS3BT.h>
#include <DCMotor.h>

 
/* Create global Variables for Startup*/
USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd);

/*TODO Get Motor Pin from EEs*/
DCMotor right;
DCMotor left;
 
void setup() 
{ 
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
} 


/* Create global Variables for loop*/
int leftVal;   // Altered value to be used in the left servo 
int rightVal;  // Altered value to be used in the right servo
int x;         // Raw x-axis input from analog
int y;         // Raw y-axis input from analog
           // x and y will return a value between 0 and 255
           // 0 will rotate servo forward, 255 will rotate backwards
           
bool start = false;  // Bool variable used to prevent premature servo rotation

void loop() 
{ 
  if (Serial.available())
  {
    int speed = Serial.parseInt();
    if (speed >= 0 && speed <= 255)
    {
      analogWrite(motorPin, speed);
    }
  }
} 

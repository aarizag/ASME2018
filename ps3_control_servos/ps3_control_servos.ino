/*Include the necessary libraries.*/
#include <SPI.h>
#include <PS3BT.h>
#include <Servo.h>

/* Create global Variables for Startup*/
USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd);


void setup() {
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

/*Create instances of type Servo. 'right' is the right side servo and 'left' is the left side servo.*/
Servo right;                                                         
Servo left;
Servo launcherRight;
Servo launcherLeft;

bool start = false;  // Bool variable used to prevent premature servo rotation

void loop()
{
 
  Usb.Task();
  
  if(PS3.getButtonPress(PS)) {
    // Do not start the program until the PS3 PS button has been pressed
    start = true;
    if (!right.attached()){
      // Attach servos to power once PS button is pressed
      right.attach(3);                                               
      left.attach(5);
      launcherRight.attach(4);
      launcherLeft.attach(2);
    }
  }
  
  if (start) {
    x = PS3.getAnalogHat(LeftHatX);
    Serial.print("X: ");
    Serial.print(x);

    y = PS3.getAnalogHat(LeftHatY);
    Serial.print("       Y: ");
    Serial.println(y);
    
    leftVal = y - (x - 127);
    Serial.print("Left: ");
    Serial.print(valCap(leftVal));
    
    rightVal = x + (y - 127);
    Serial.print("          Right: ");
    Serial.println(valCap(rightVal));
    
    right.write(map(255 - valCap(rightVal), 0, 1023, 0, 180));
    left.write(map(255 - valCap(leftVal), 0, 1023, 180, 0)); 
 
    if(PS3.getButtonPress(R1)){
      launcherRight.write(180);
      launcherLeft.write(180);
    }
    else{
      launcherRight.write(127);
      launcherLeft.write(127);
    }
  }
}

  /* Cap maximum value at 255
   * cap minimum value at 0
   * create "deadzone" in the middle of the analog to prevent servo drift
   */
int valCap(int val){
  
  if (val > 122 && val < 132){
    return 127;
  }
  else if (val > 250){
    return 255;
  }
  else if (val < 5) {
    return 0;
  }
}

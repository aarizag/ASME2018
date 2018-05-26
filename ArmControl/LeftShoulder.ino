#include<Servo.h>           //Include The servo library for the functions used

// DC Motors are to be treated and controlled as Servos
Servo forwardBackPivot;
    // This motor will pivot the arm forwards and backwards relative to Melo
Servo leftRightPivot;
    // This motor will pivot the arm left and right (outwards, inwards) relative to Melo

void setup()
{
    forwardBackPivot.attach(3);
    leftRightPivot.attach(4);
    // Shoulder has pins 3,4
    // elbow has pin 3

    Serial.begin(9600);      //Begin Reading/Open Serial Monitor
}

int joyX;
int joyY;

void loop(){
    // Read Joystick Input and mind the dead zone
    joyX = deadZone(analogRead(A1));
    joyY= deadZone(analogRead(A0));


    // Re-map the values to be written onto the motors
    outX = map(mapX, 0, 1023, 1000, 2000);
    outY = map(mapY, 0, 1023, 1000, 2000);

    // Output to the motors
    forwardBackPivot.writeMicroseconds(outY);
    leftRightPivot.writeMicroseconds(outX);

     if (analogRead(A0) > 400 && analogRead(A0) < 600){
      esc.writeMicroseconds(1500);
     }
 }

 // Create a "dead zone" with +/- 64 from 512
 // Where 512 is the middle value of the Joystick
  int deadZone(val) {
      if (val > 576) && (val < 448) {
          return 512;
      }
      return val;
  }

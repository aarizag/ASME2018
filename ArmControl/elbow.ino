#include<Servo.h>           //Include The servo library for the functions used

// DC Motors are to be treated and controlled as Servos
Servo elbow;
    // This motor will pivot the elbow

void setup()
{
    elbow.attach(3);
    // elbow has pin 3

    Serial.begin(9600);      //Begin Reading/Open Serial Monitor
}

int joyX;

void loop(){
    // Read Joystick Input and mind the dead zone
    joyX = deadZone(analogRead(A0));

    // Re-map the values to be written onto the motors
    outX = map(mapX, 0, 1023, 1000, 2000);

    // Output to the motors
    elbow.writeMicroseconds(outX);
 }

// Create a "dead zone" with +/- 64 from 512
// Where 512 is the middle value of the Joystick
 int deadZone(val) {
     if (val > 576) && (val < 448) {
         return 512;
     }
     return val;
 }

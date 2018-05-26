/*
 * Movement and Action Control
 * ASME Robotics Competition : Attack Robot
 *
 * Author: Adryel Arizaga
 * Date Written: 25 April 2018
 *
 */

#include <SPI.h>
#include <PS3BT.h>
#include <Servo.h>


// Create a structure for DC Motors to contain associated pins
typedef struct {
    byte pwm;
        //NOTE pwm pins receive a speed input from 0 -> 255
    byte dir;
        //NOTE dir pins receive a HIGH or LOW, corresponds to flow of elec current
} DCmotor;


/* USB, Bluetooth, and PS3 declarations */
USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd);

/* Motor Declarations */
// Declare DC motor pins with the structure defined above
DCmotor rightM {6, 7}; // Right motor
DCmotor leftM {8, 9}; // Left motor

// Declare Servos
Servo arm;
Servo launcherRight;
Servo launcherLeft;

/* Setup function
 * Declare Serial Channel
 * set DC motor pins to output
 * initialize USB
 */
void setup(){
    Serial.begin(9600);
    // Declare all DC motor pins as OUTPUT
    pinMode(rightM.pwm,OUTPUT);
    pinMode(rightM.dir,OUTPUT);
    pinMode(leftM.pwm,OUTPUT);
    pinMode(leftM.dir,OUTPUT);

    // Check if the USB initialized properly
    if (Usb.Init() == -1) {
        Serial.print("USB failed to start");
        while(1); // Stop the program if the USB fails
    }
    Serial.println("PS3 Bluetooth Started");
}

/*Non-static Variables to be used in the Loop */
byte xIN; // x input from the ps3 controller
byte yIN; // y input   ""    ""    ""

int xRotate; // modified x, rotated each point ~45 deg Counter-Clockwise, along the square
int yRotate; // modified y,    ""        ""        ""

byte rOUT; // output to the Right wheel deduced from the x-input
byte lOUT; //output to the Left wheel deduced from the y-input

bool start = false; // Prevent Servos from receiving ghost input before controller is connected


/* Loop
 * receive values from PS3 controller
 * initialize Servo Pins once the PS3 Start button has been pressed (prevent servo drift)
 * modify x/y inputs and output to motors/servos
 */
void loop (){
    Usb.Task();

    // Do not start the program until the PS3 PS button has been pressed
    if(PS3.getButtonPress(PS)) {
        start = true;
        // Attach servos to power once PS button is pressed
        launcherRight.attach(4);
        launcherLeft.attach(5);
        arm.attach(3);
    }

    if (start) {
        xIN = PS3.getAnalogHat(LeftHatX);
        yIN = PS3.getAnalogHat(LeftHatY);
        yRotate = valCap(yIN - (xIN - 127));
        xRotate = valCap(xIN + (yIN - 127));

        // Control the right motor
        if (xRotate < 127){
            digitalWrite(rightM.dir, HIGH);
            rOUT = (127-xRotate) * 2;
            analogWrite(rightM.pwm,rOUT);
        }
        else {
            // TODO TEST WHEEL CONTROL FOR rOUT > 127
            digitalWrite(rightM.dir, LOW);
            rOUT = (xRotate-127) * 2;
            analogWrite(rightM.pwm, rOUT);
        }
        // Debug Serial Print
        Serial.println(rOUT);

        // Control the left motor
        if (yRotate < 127){
            digitalWrite(leftM.dir, HIGH);
            lOUT = (127-yRotate) * 2;
            analogWrite(leftM.pwm,lOUT);
        }
        else {
            // TODO TEST WHEEL CONTROL FOR lOUT > 127
            digitalWrite(leftM.dir, LOW);
            lOUT = (yRotate-127) * 2;
            analogWrite(leftM.pwm, lOUT);
        }
        // Debug Serial Print
        Serial.println(lOUT);

        /* NOTE: The shape of the graph created by rOUT or lOUT resembles
         *       a parabola.
         *       This is because of the origin of the points being centered
         *       around 127, with larger speed (lOUT/rOUT) values required when
         *       xRotate/yRotate approach 0 and 254.
         */

        // Bring arm up
        if(PS3.getButtonPress(L1)){
            Serial.println("Arm Moving Up");
            arm.write(150);
        }
        // Bring arm down
        else if(PS3.getButtonPress(L2)){
            Serial.println("Arm Moving Down");
            arm.write(30);
        }

        // Activate Launcher
        if (PS3.getButtonPress(R1)){
            Serial.println("I'M FIRIN MAH LAZERRRRRRRRR");
            launcherRight.write(180);
            launcherLeft.write(180);
        }
        // Deactivate Launcher
        else {
            launcherRight.write(90);
            launcherLeft.write(90);
        }
    }
}


/* valCap function:
 * creates a "dead zone" in the middle of the joystick to prevent drift
 * ensures values returned to the motors are within range (0 - 254)
 *
 * Range max is 254 to prevent byte overflow of lOUT/rOUT when
 * xRotate/yRotate >= 127
 */
int valCap(int val){
    if (val > 122 && val < 132){
        return 127;
    }
    else if (val > 250){
        return 254;
    }
    else if (val < 5) {
        return 0;
    }
}

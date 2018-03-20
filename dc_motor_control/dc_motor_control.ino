#include <SPI.h>
#include <PS3BT.h>
#include <Servo.h>

USB usb;
BTD btd(&usb);
PS3BT ps3(&btd, PAIR);

const byte mtr1 [2] = {9,10}; // motor 1 pins
//const byte mtr2 [2]; // motor 2 pins
/* index 0 = pwm
 * index 1 = dir */

void setup(){
  Serial.begin(9600);

  pinMode(mtr1[0],OUTPUT); //declare motor1 pwm pin as OUTPUT
  pinMode(mtr1[1],OUTPUT); //declare motor2 dir pin as OUTPUT

    if (usb.Init() == -1) {
    Serial.print("USB failed to start");
    while(1); // STOP
  }
  Serial.println("PS3 Bluetooth Started");
}

int xIN; // x input from the ps3 controller
int yIN; // y input
int xOUT; // modified x output to wheels
int yOUT; // modified y


bool start = false;

void loop (){
    usb.Task();

    if(ps3.getButtonPress(PS)) {
        // Do not start the program until the PS3 PS button has been pressed
        start = true;
    }

    if (start) {
        xIN = ps3.getAnalogHat(LeftHatX);
        yIN = ps3.getAnalogHat(LeftHatY);

        yOUT = valCap(yIN - (xIN - 127));
        xOUT = valCap(xIN + (yIN - 127));

//        String debug = "x: " + xIN + " -> " + xOUT + " | " + "y: " + yIN + " -> " + yOUT;
//        Serial.println(debug);

        if (xOUT < 127){
            digitalWrite(mtr1[1],HIGH);
            Serial.println(valCap(((255-xOUT) -127) * 2));
            analogWrite(mtr1[0],valCap(((255-xOUT) -127) * 2));
        }
        else {
            digitalWrite(mtr1[1],LOW);
            Serial.println(valCap((xOUT-127) * 2));
            analogWrite(mtr1[0],valCap((xOUT-127) * 2));
        }
        if (yOUT < 127){
            digitalWrite(mtr1[1],HIGH);
            Serial.println(valCap(((255-yOUT) -127) * 2));
            analogWrite(mtr1[0],valCap(((255-yOUT) -127) * 2));
        }
        else {
            digitalWrite(mtr1[1],LOW);
            Serial.println(valCap((yOUT-127) * 2));
            analogWrite(mtr1[0],valCap((yOUT-127) * 2));
        }
    }
}

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

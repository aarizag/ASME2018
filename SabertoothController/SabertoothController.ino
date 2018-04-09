#include <SPI.h>
#include <PS3BT.h>
#include <Servo.h>

USB usb;
BTD btd(&usb);
PS3BT ps3(&btd);

Servo mtr1;

void setup(){
  Serial.begin(9600);

  mtr1.attach(9, 1000,2000);

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
        Serial.print((int) (valCap(xOUT) * 0.7058823));
        Serial.print("           Left: ");
        Serial.print(valCap(yOUT));
        Serial.print("          Right: ");
        Serial.println(valCap(xOUT));

        

//        mtr1.write((int) (valCap(xOUT) * 0.7058823));

        mtr1.write(150);
        delay(500);
        mtr1.write(30);
        delay(500);
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

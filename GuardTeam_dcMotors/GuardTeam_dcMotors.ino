#include <SPI.h>
#include <PS3BT.h>
#include <Servo.h>

USB usb;
BTD btd(&usb);
PS3BT ps3(&btd);

int in1=9;
int in2=8;
int in3=7;
int in4=6;
/*define channel enable output pins*/
int ENA=10;
int ENB=5;
Servo right;                                                         
Servo left;

void _mLeft()
{ 
  digitalWrite(in1,LOW);//digital output
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  Serial.println("Left");
}

/*define back function*/
void _mRight()
{
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  Serial.println("Right");
}

/*define left function*/
void _mDown()
{
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  Serial.println("Down");
}

/*define right function*/
void _mUp()
{
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  Serial.println("Up");
}

void _stop()
{
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}
  


void setup(){
  Serial.begin(9600);


  Serial.begin(9600);
//  pinMode(in1,OUTPUT);
//  pinMode(in2,OUTPUT);
//  pinMode(in3,OUTPUT);
//  pinMode(in4,OUTPUT);
//   pinMode(ENB,OUTPUT);
//  pinMode(ENA,OUTPUT);
//  analogWrite(ENA,250);
//  analogWrite(ENB,250);
// _stop();
    if (usb.Init() == -1) {
    Serial.print("USB failed to start");
    while(1); // STOP
  }
  Serial.println("PS3 Bluetooth Started");
}

bool start = false;

void loop (){
    usb.Task();
//  if (!right.attached()){
//      // Attach servos to power once PS button is pressed
//      right.attach(3);                                               
//      left.attach(5);
//    }
    if (ps3.getButtonPress(START)&&!start){
          pinMode(in1,OUTPUT);
          pinMode(in2,OUTPUT);
          pinMode(in3,OUTPUT);
          pinMode(in4,OUTPUT);
//           pinMode(ENB,OUTPUT);
//          pinMode(ENA,OUTPUT);
          analogWrite(ENA,255);
          analogWrite(ENB,255);
          Serial.print("START");
          start=true;
          
    }

    if (ps3.getButtonPress(UP)){
        _mUp();
    }
    else if (ps3.getButtonPress(DOWN)){
        _mDown();
    }
    else if (ps3.getButtonPress(LEFT)){
        _mLeft();
    }
    else if (ps3.getButtonPress(RIGHT)){
        _mRight();
    }
//    else if (ps3.getButtonPress(R1)){
//       right.write(map(255, 0, 1023, 0, 180));
//    }
    else{
        _stop();
    }
}


  

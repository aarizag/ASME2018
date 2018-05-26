
#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <Servo.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <Encoder.h>
#include <std_msgs/Float32.h>

// This is roscpp
ros::NodeHandle  nh;

const byte STOP = 90;  // The stopping point for the servos is 90 degrees
const float THRESHOLD = 0.01;

// TODO : Determine Transistor pin
const byte TRAN; // Sending a signal to the transistor/relay

// DC Motors are to be treated and controlled as Servos
Servo forwardBack;
    // This motor will pivot the arm forwards and backwards relative to Melo
Servo leftRight;
    // This motor will pivot the arm left and right (outwards, inwards) relative to Melo

void servo_cb(const geometry_msgs::Twist& cmd_msg){
  // @param direction_left: speed to be written to the Servos

  int direction_left  = STOP;
  int direction_right = STOP;

  float linear = cmd_msg.linear.x;
  float angular = cmd_msg.angular.z;

  if (linear > THRESHOLD || linear < -THRESHOLD) {
    // Go forward
    direction_left = int ( STOP * (1 - LEFT_SCALE * linear) );
    direction_right = int ( STOP * (1 + RIGHT_SCALE * linear) );

    Serial.print("Translate\n");
  } else if (angular > THRESHOLD || angular < -THRESHOLD) {
    // Rotate counter clockwise
    direction_left = int ( STOP * (1 + LEFT_SCALE * angular) );
    direction_right = int ( STOP * (1 + RIGHT_SCALE * angular) );

    Serial.print("Rotate\n");
  } else {
    // STOP!

    // TODO: engage the brakes here...
    direction_left = STOP;
    direction_right = STOP;

    Serial.print("Stop\n");
  }

  servo_left.write(direction_left); //set servo_left angle
  servo_right.write(direction_right); //set servo_right angle
}

// TODO : Check Subscribe target string
ros::Subscriber<geometry_msgs::Twist> sub_cmd_vel("cmd_vel", servo_cb); // Topic used to be "cmd_vel". New topic is "cmd_vel"ard"


void setup(){
  nh.initNode();
  nh.subscribe(sub_cmd_vel);
  nh.advertise(left_count);
  nh.advertise(right_count);

  servo_left.attach(8); //attach it to pin 8
  servo_right.attach(9); //attach it to pin 9

 pinMode(TRAN, OUTPUT);
}

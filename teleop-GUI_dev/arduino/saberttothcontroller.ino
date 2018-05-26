#include <Servo.h>
Servo myservo;
// This only works in the second controller configuration
void setup () {
  myservo.attach(14); // Use PWM pin 14 to control Sabertooth.
}

void loop() {  
  // 31 means full power in one direction.
  // A smaller value won't drive the motor.
  myservo.write(31); 
  delay(2000);
  
//  // 90 means stopping the motor.
 myservo.write(90); 
  delay(2000);  
    
  // 159 means full power in the other direction.
  // A larger value won't drive the motor either.
  myservo.write(159); 
  delay(2000);

   myservo.write(90); 
  delay(2000);  
}

#include <Servo.h>

// ************************************************
//
// TODO REWRITE ARM CONTROL CODE
//
//*************************************************
/*
 * Robot Arm Code
 *
 * Created 7-8-2017 by Matthew Tran
 *
 * Edited by Adryel Arizaga, starting 4-18-18
 */

//5 DOF Robot Arm Joints' Names
  //Shoulder Pitch - forward back
  //Shoulder Yaw - left right
  //Elbow
  //Wrist Pitch - up down
  //Wrist Roll - rotational
//Preferred Coordinate System is clockwise,right,and upwards are positive

const byte motorMinimumVal = 30;
const byte motorMaximumVal = 150;
const byte motorNeutralVal = 90;

Servo shoulder; // NOTE: be careful when moving motor since esc is sensitive
                // TODO: explore validity and necessity of this warning

const byte shoulderPins [4] = {3, 8, 9, 7}
    // Index:
    //      0: Motor pin
    //      1: Encoder Pin A (A8)
    //      2: Encoder Pin B (A9)
    //          -NOTE: 2 channels per encoder for positioning
    //      3: Encoder Pin H (A7)
    //          -NOTE: Homing Pin

/* TODO :  Determine Values for Shoulder Pin Encoders
    *    const int spEncoderAMax = ;
    *    const int spEncoderBMin = ;
    *    const int spEncoderAMin = ;
    *    const int spEncoderBMax = ;
    *    const int spEncoderHTrigger = ; //below this homing pin is "triggered"
    *    double spPos = 0; //position of joint, about ~200° in both directions from pointing down
    *    const double spPosMin = ; //experimentally determined
    *    const double spPosMax = ;
    *    const double spPosH = ; //position to set to when homed
    */

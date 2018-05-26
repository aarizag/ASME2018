#!/bin/bash
# A script to start the Joystick Node

function finish () {
  # Cleanup code here
  echo "Started Cleanup..."
  killall -9 roscore
  echo "Killed roscore..."
  killall -9 rosmaster
  echo "Killed rosmaster..."
  echo "Finished cleanup"

}

function start_joy () {
    gnome-terminal -e "bash -c 'rosparam set joy_node/dev \"/dev/input/js0\";echo \"Set Parameters and Start Joy_Node\";rosrun joy joy_node;exec $SHELL'"
#    gnome-terminal -e rosparam set joy_node/dev "/dev/input/js0" &
#    gnome-terminal rosrun joy joy_node &
#    echo "Set Parameters and Started Joy_Node"
}

function echo_joy (){
    sleep 3 # delay to allow roscore to finish loading
    gnome-terminal -e "bash -c 'rostopic echo joy;exec $SHELL'"
}

trap finish 1 2 3 6

roscore & 
start_joy &
echo_joy

wait
finish


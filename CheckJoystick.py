from evdev import InputDevice, categorize, ecodes

def map (x, in_min=-1, in_max=1, out_min=0, out_max=180):
    val = (x - in_min) * (out_max-out_min) / (in_max - in_min) + out_min
    return int(val)


controller = InputDevice('/dev/input/event15')

print(controller)
for event in controller.read_loop():
    if event.type == 3:
        print(event)
        
        
# rosrun rosserial_python serial_node.py _port:=/dev/ttyACM0 _baud:=57600

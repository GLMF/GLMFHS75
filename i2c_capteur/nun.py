#! /usr/bin/python

import smbus
import sys
import time

try:
	bus = smbus.SMBus(1)
except IOError:
	print "Please load i2C_bcm2708 and i2c_dev modules"
	sys.exit(1)

# Initialize the nunchnuk (address = 0x52)
# Write 0x00 in register 0x40 for white Wii nunchunk.
# Write 0x55 in register 0xF0 then 0x00 in reg. 0xFB for black one.
try:
	bus.write_byte_data(0x52, 0x40, 0x00)
except IOError:
	print "No nunchunk found"
	sys.exit(1)

# Wait a moment to allow nunchunk initialization.
time.sleep(0.01)

while True:
    try:
        # Send a byte 0x00 to the nunchunk.
        bus.write_byte(0x52,0x00)
        # Wait a few milliseconds.
        time.sleep(0.05)
        joystick_x      =  bus.read_byte(0x52)
        joystick_y      =  bus.read_byte(0x52)
        accelerometer_x =  bus.read_byte(0x52)
        accelerometer_y =  bus.read_byte(0x52)
        accelerometer_z =  bus.read_byte(0x52)
        miscellaneous   =  bus.read_byte(0x52)
        accelerometer_x = accelerometer_x << 2
        accelerometer_y = accelerometer_y << 2
        accelerometer_z = accelerometer_z << 2
        accelerometer_x += (miscellaneous & 0x0C) >> 2
        accelerometer_y += (miscellaneous & 0x30) >> 4
        accelerometer_z += (miscellaneous & 0xC0) >> 6
	# For buttons, the simplier way is to unroll all cases.
        if ((miscellaneous & 0x03) == 0):
            button_c = 0
            button_z = 1
	elif ((miscellaneous & 0x03) == 1):
            button_c = 1
            button_z = 0
        elif ((miscellaneous & 0x03) == 2):
            button_c = 1
            button_z = 1
        else:
            button_c = 0
            button_z = 0
        sys.stdout.write('Joystick: (%3d, %3d), ' % (
               joystick_x, joystick_y))
        sys.stdout.write('Accelerometer: (%4d, %4d, %4d), ' %(
               accelerometer_x, accelerometer_y, accelerometer_z))
        sys.stdout.write('Buttons: (%d,%d)\n'     % (
                      button_c, button_z))
    except KeyboardInterrupt:
        sys.exit(0)
    except IOError:
        print "Nunchunk disconnected"
        sys.exit(1)


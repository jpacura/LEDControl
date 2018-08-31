import sys
import time
import serial
import requests

apiurl = "http://api.thingspeak.com/channels/1417/field/1/last.json"
objectName = "field1"

colors = {  'red' : (255, 0, 0) ,
			'green' : (0, 255, 0) ,
			'blue' : (0, 0, 255) ,
			'cyan' : (0, 255, 255) ,
			'white' : (255, 255, 255) ,
			'oldlace' : (253, 245, 230) ,
			'warmwhite' : (253, 245, 230) ,
			'purple' : (128, 0, 128) ,
			'magenta' : (255, 0, 255) ,
			'yellow' : (255, 255, 0) ,
			'orange' : (255, 165, 0) ,
			'pink' : (255, 192, 203) }

if len(sys.argv) != 2:
	print("Invalid number of arguments. Usage: python CheerLightsAdapter.py ArduinoSerialPort")
	sys.exit()

def main():
	serialport = sys.argv[1]

	print("INFO: Attempting to open serial port " + serialport)

	arduino = serial.Serial(serialport, 9600, timeout=10) # This will cause the Arduino to reboot

	print("INFO: Waiting for Arduino to be ready...")

	while arduino.in_waiting == 0:
		pass # Wait to receive message from Arduino

	if arduino.in_waiting != 1: # We should only receive 1 byte from the Arduino. Anything else is a problem
		print("ERROR: Serial port sent too much data!")
		sys.exit()

	if arduino.read() != b'\x00': # The Arduino should respond with a single 0 byte to indicate it is working. Anything else is a problem
		print("ERROR: Serial port sent unexpected data!")
		sys.exit()

	# We are now properly connected to the Arduino
	print("INFO: Now connected to Arduino on " + serialport)

	print("INFO: Attempting to get current CheerLights color from " + apiurl)

	request = requests.get(apiurl)

	if request.status_code != 200:
		print("ERROR: Unable to connect to API! Status code " + request.status_code)
		sys.exit()

	color = request.json()[objectName] # get the current color of the CheerLights

	print("INFO: Current CheerLights color is " + color)
	print("INFO: Setting Arduino to " + color)

	arduino.write(RGBToSerial(colors[color]).encode('utf-8'))
	currentcolor = color

	print("INFO: Now checking CheerLights every 15 seconds")

	time.sleep(15)

	while True:
		request = requests.get(apiurl)
		
		color = request.json()['field1'] # get the current color of the CheerLights
		
		if color != currentcolor:
			print("INFO: CheerLights changed color to " + color)
			arduino.write(RGBToSerial(colors[color]).encode('utf-8'))
			currentcolor = color
		
		time.sleep(15)
		
	

def RGBToSerial(rgb):
	return "3 -1 0 " + str(rgb[0]) + " 3 -1 1 " + str(rgb[1]) + " 3 -1 2 " + str(rgb[2])
	

if __name__ == "__main__": main()
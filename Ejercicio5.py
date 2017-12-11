import serial

arduino = serial.Serial('/dev/ttyACM0', 9600)

print("Starting!")

while True:
      comando = raw_input('Introduce un comando: ') #Input
      arduino.write(comando) #Mandar un comando hacia Arduino

arduino.close() #Finalizamos la comunicacion

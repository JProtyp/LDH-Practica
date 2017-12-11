import serial

arduino = serial.Serial('/dev/ttyACM0', 9600)

print("Starting!")

while True:
      comando = raw_input('Introduce un angulo de 0 a 180: ') #Input
      arduino.write(comando) #Mandar un comando hacia Arduino
      print('Servo apuntando a',comando)
arduino.close() #Finalizamos la comunicacion

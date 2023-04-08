import socket
import random
import time

UDP_IP = str(input(" Host/Ip:"))
UDP_PORT = int(input(" Port:"))

start_time = time.time()
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

while (time.time() - start_time) < 80:
    temperature = round(random.uniform(18.0, 30.0), 2)
    humidity = round(random.uniform(30.0, 80.0), 2)
    
    data = f"Temp: {temperature} C, Humidity: {humidity} %".encode()
    
    sock.sendto(data, (UDP_IP, UDP_PORT))
    
    time.sleep(1)

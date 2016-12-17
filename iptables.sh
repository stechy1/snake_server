# Zruší spojení
iptables -A OUTPUT -p tcp -d 127.0.0.1 --dport 10000 -j DROP

# Obnoví spojení
iptables -D OUTPUT 1

#Výpíše spojení
iptables -L --line-numbers
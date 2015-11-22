#! /usr/bin/python

number_of_hosts = 50

f = open('entrada_med.txt', 'w')

for i in range(0, number_of_hosts):
	f.write("set host h" + str(i) + "\n")

f.write("\nset router r0 " + str(number_of_hosts - 1) + "\nset router r1 3\n\n")

for i in range(0, number_of_hosts - 2):
	f.write("set duplex-link h" + str(i) + " r0." + str(i) + " 10Mbps 10ms\n")

f.write("set duplex-link r0."+ str(number_of_hosts - 2) +" 	r1.0	2Mbps		20ms\nset duplex-link r1.1	h" +str(number_of_hosts - 2)+ "		10Mbps	5ms\nset duplex-link r1.2	h"+str(number_of_hosts - 1)+"		5Mbps		2ms\n\n")

for i in range(0, number_of_hosts - 2):
	f.write("set ip h" + str(i) + " 10.0." + str(i) + ".1		10.0." + str(i) + ".2		192.168.1.1\n")

f.write("set ip h"+ str(number_of_hosts - 2) +" 192.168.2.2	192.168.2.3		192.168.1.1\nset ip h"+ str(number_of_hosts - 1) +" 192.168.1.1 	192.168.1.2 	1.1.1.1\n\n")

f.write("set ip r0")


for i in range(0, number_of_hosts - 2):
	f.write(" " + str(i) + " 10.0." + str(i) + ".2")

f.write(" " + str(number_of_hosts - 2) + " 192.168.3.3\nset ip r1 0 192.168.3.4 1 192.168.2.3 2 192.168.1.2\n\n")

f.write("set route r0")

for i in range(0, number_of_hosts - 2):
	f.write(" 10.0." + str(i) + ".0 " + str(i))

f.write(" 192.168.3.0 " + str(number_of_hosts - 2) + " 192.168.2.0 192.168.3.4 192.168.1.0 192.168.3.4\n")

f.write("set route r1 192.168.3.0 0 192.168.2.0 1 192.168.1.0 2")

for i in range(0, number_of_hosts - 2):
	f.write(" 10.0." + str(i) + ".0 192.168.3.3")

f.write("\n\nset performance r0 100us 0 1000 1 1000 2 1000\nset performance r1 20us 0 1000 1 1000 2 1000\n\n")

for i in range(0, number_of_hosts - 2):
	f.write("set ircc h" + str(i) + " irc" + str(i+1) + "\n")

f.write("set ircs h" + str(number_of_hosts - 2) + " irc" + str(number_of_hosts - 1) + "\n")
f.write("set dnss h" + str(number_of_hosts - 1) + " dns1\n\n")

f.write("set sniffer r0.2 r1.0 \"/tmp/sniffer1\"\nset sniffer h1 r0.1 \"/tmp/sniffer2\"\n\n")


for i in range(0, number_of_hosts - 2):
	f.write("simulate 1.0 irc"+ str(i+1)+" \"CONNECT h2 6667\"\n")

for i in range(0, number_of_hosts - 2):
	f.write("simulate 2.0 irc"+ str(i+1)+" \"USER usuario"+ str(i+1)+"\"\n")

for i in range(0, number_of_hosts - 2):
	f.write("simulate 3.0 irc"+ str(i+1)+" \"QUIT\"\n")

f.write("finish 4.0")
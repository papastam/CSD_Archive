import socket
import sys
import time
import os
import select

if len(sys.argv)<=1:
    print("Please specify the target IPs\nUsage: python3 client.py [Host1,Host2,...]")
    exit()
elif len(sys.argv)==2:
    print("Please enter two or more hosts\nUsage: python3 client.py [Host1,Host2.,,,]")
    exit()

#funtion to create the DNS lists
def listcreate(filename):
    list1=[]
    list2=[]

    f=open(filename)
    for line in f:
        splitedline=line.split(" ")
        list1.append(splitedline[0])
        list2.append(splitedline[1].strip("\n"))

    return list1, list2

#get the local ip from ifconfig
term = os.popen("ifconfig")
output=term.read().split("\n")
output=output[1].split(" ")
LOCAL_IP=output[9]

#initialize the rest of the values
TCP_PORT = 50000
funct_ret = listcreate("my_DNS.txt")
DNS_NAMES = funct_ret[0]
DNS_IPS = funct_ret[1]
REQUESTED_DOMAINS = []
MESSAGE = ''
BUFFER_SIZE=1000

#create a target list
for i in sys.argv[1:]:
    if i in DNS_NAMES:
        REQUESTED_DOMAINS.append(DNS_IPS[DNS_NAMES.index(i)])

#send the requested domains to each server
print("\n")
active_domains=[]
for ip in REQUESTED_DOMAINS:

    MESSAGE=''
    #create the message containing the desired domains for each host
    for messageip in REQUESTED_DOMAINS:
        if messageip != ip:
            MESSAGE=MESSAGE+messageip+"-"

    sendsocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        sendsocket.connect((ip,TCP_PORT))
        sendsocket.send(MESSAGE.encode())
        sendsocket.close()
        active_domains.append(ip)
        print("Sent: ",MESSAGE," to ",ip)
    except ConnectionRefusedError:
        print("Target ",ip," is unreachable, is the server running there?")

if len(active_domains)==0:
    print("\nNo target recieved the request, exiting....")
    exit()

#create the incoming answes socket
print("\nWaiting for answer from:",active_domains,"\n")
anssocketlist=[]
anssocket=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
anssocket.setblocking(0)
anssocket.bind((LOCAL_IP,TCP_PORT))
anssocket.listen(5)

#create the anssocket list for select.select
anssocketlist.append(anssocket)

#wait for the replies from the servers
replycount=0
writable=[]
err=[]
str4save=''
while anssocketlist:
    readysocket, writable, err = select.select(anssocketlist,anssocketlist,anssocketlist)
    
    for s in readysocket:
        #if the output of select is a socket, create the connection
        if s is anssocket:

            conn,addr=s.accept()
            print("New connection from: ",addr)
            conn.setblocking(0)
            anssocketlist.append(conn)
            if replycount==len(active_domains)-1:
                anssocketlist.remove(s)
        #if it is not a server it is a reafy file descriptor
        else:
            data=s.recv(BUFFER_SIZE)
            #get the data
            if data:
                replycount+=1
                print("Recieved answer from: ",s.getpeername()," (",replycount,"/",len(active_domains),")\n")    
                
                finalstr=''
                proccess=str(data).split("'")[1]
                proccess=proccess.split("\\n")
                proccess.remove('')
                #translate the ips sent by the server to names
                for line in proccess:
                    translatedstr=''
                    elements=line.split(" / ")

                    #translate the name of the meaurement
                    mname=elements[0].split("->")
                    translatedstr+=DNS_NAMES[DNS_IPS.index(mname[0])]+"->"+DNS_NAMES[DNS_IPS.index(mname[1])]+" / "+elements[1]+" / "+elements[2]+" / "
                    
                    #translate the names of the hops
                    route=elements[3].split(' - ')
                    for routeipindex in range(len(route)):
                        if route[routeipindex]=='':
                            continue
                        translatedstr+=DNS_NAMES[DNS_IPS.index(route[routeipindex])]
                        if routeipindex!=len(route)-2:
                            translatedstr+=" - "

                    finalstr+=translatedstr+"\n"
                str4save+=finalstr
                
                s.close()
                anssocketlist.remove(s)
            else:
                s.close()
        

print("All targets delievered!")

#write the recieved measurements to the output file
filenum=0
while filenum<=100:
    filename="Measurements_"+str(filenum)+".txt"
    if os.path.isfile(filename):
        filenum+=1
        continue
    else:
        f = open(filename,"w")
        f.write(str4save)
        f.close()

        break

if filenum>100:
    print("Detected 100 Measurement files, please clear some output files and try again!")
else:
    print('\nWriten measurement output to: "'+filename+'"')
exit()

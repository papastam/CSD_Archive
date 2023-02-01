import socket
import sys
import time
import os

print("Starting server on local ip...\n")

#get the local ip from ifconfig command
term=os.popen("ifconfig")
output = term.read().split("\n")
output = output[1].split(" ")
LOCAL_IP = output[9]

#inidialize the rest of the values
TCP_PORT=50000
BUFFER_SIZE=100
REQUESTED_DOMAINS = []
MESSAGE = ''

#create the socket for the incoming request
print("Waiting for new request...\n")
sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
sock.bind((LOCAL_IP,TCP_PORT))
sock.listen(1)

#wait for the request
conn,addr=sock.accept()
while True:
    data=conn.recv(BUFFER_SIZE)

    if data:
        print("Request recieved from ", addr[0])
        reply_ip=addr[0]
        break;

#format the message
datastr=str(data).strip("b'")
targetlist=datastr.split("-")
targetlist.remove("")

#execute the measurements to the targets
print("\nExecuting measurements to targets:",targetlist,"\n")
STAT_REPLY=''
for ip in targetlist:
    STAT_REPLY+=LOCAL_IP+"->"+ip+" / "
    hop_stat = ''

    #ping 10 requests
    term = os.popen("ping -c 10 "+ip)
    output = term.read().split("\n")
    output = output[len(output)-2].split("/")
    STAT_REPLY+=output[4]+" / "
    
    #traceroute
    term = os.popen ("traceroute "+ip)
    output = term.read().split("\n")
    output.remove('')
    numofhops = output[len(output)-1].split(" ")[1]
    STAT_REPLY+= numofhops+" / "

    #create the trace string
    for traceline in output[1:]:
        traceline = traceline.split(" ")

        #a loop to remove the possible * in the traceroute output
        while True:
            try:
                traceline.remove("*")
            except ValueError:
                break;
        
        hopip = traceline[4].strip("()")
        hop_stat += hopip+" - "
    STAT_REPLY += hop_stat + "\n"
    
#Measurement format: " Start hop->End host / ping / num of hops / trace

#create the reply socket and send the reply
reply_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
    reply_socket.connect((reply_ip, TCP_PORT))
    reply_socket.send(STAT_REPLY.encode())
    print("Reply send to ", reply_ip, "\n")
    reply_socket.close()
except ConnectionRefusedError:
    print("Couldn't send message back to ", reply_ip, "\n")
exit()

import csv
import numpy as np
import matplotlib.pyplot as plt
import dc_stat_think as dcst

#open the csv file
file = open('DATASET1.csv')
csvreader=csv.reader(file)

#get the file header
header = []
header = next(csvreader)
ProtocolIndex=header.index('Protocol')
LengthIndex=header.index('Length')

#read and process every row
udplengths=[]
protocolcnt={}
rows = []
for row in csvreader:
    rows.append(row)

    #for the first question, add all udp lengths to udplengths
    if row[ProtocolIndex] == "UDP":
        udplengths.append(int(row[LengthIndex]))

    #for the second question, sum every protocol in the protocolcnt dict
    if row[ProtocolIndex] in protocolcnt:
        protocolcnt[row[ProtocolIndex]]+=1
    else:
        protocolcnt[row[ProtocolIndex]]=1

#sort the udp lengths
udplengths=sorted(udplengths)

#calculate and plot the ecdf function
x, y = dcst.ecdf(udplengths)
plt.plot(x, y*100)
plt.savefig("UDP Length ECDF.png")
plt.clf()

#sort the protocol dictionary by its keys and keep the 5 biggest values
protocolcnt=dict(sorted(protocolcnt.items(), key=lambda item: item[1]))
protocols=list(protocolcnt.keys())[-5:]

#plot the bars of the five most used protocols
plt.bar(np.array(protocols),np.array(list(protocolcnt.values())[-5:]))
plt.savefig('Top-5 Protocols.png')
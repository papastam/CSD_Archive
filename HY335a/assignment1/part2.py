import csv

#open the csv file
file = open('DATASET1.csv')
csvreader=csv.reader(file)

#read the header
header = []
header = next(csvreader)
ProtocolIndex=header.index('Protocol')


tcpcnt=0
lengthsum=0
rows = []
for row in csvreader:
    rows.append(row)
    #for every tcp packet, increment the tcpcnt counter and add its length to the lengthsum list
    if row[4] == "TCP":
        tcpcnt+=1
        lengthsum+=int(row[5])
        print(row)

#calculate and print the average tcp packet length
avglength=lengthsum/tcpcnt
print(lengthsum,"/",tcpcnt,"=",avglength)
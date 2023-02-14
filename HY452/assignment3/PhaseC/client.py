from flask import Flask, request
import requests
import json
import boto3
import random
import ast

#Constants
PUBLIC_DNS_ADDRESS = 'ec2-3-89-8-153.compute-1.amazonaws.com'
ENDPOINT    = 'http://'+PUBLIC_DNS_ADDRESS+':5000/client'
TOPICARN    = 'arn:aws:sns:us-east-1:613787790506:Ads'
SERVERPORT  = 5000

#Game variables

#Scenario selection: 1=Products of same quality, 2=Products with different price
#In the first scenario the price is not sent with the buid, the calculations are the same tho
#scenario        = 1
scenario        = 2

#Flask init
app = Flask(__name__)

#SNS init
sns_client = boto3.client('sns',region_name="us-east-1")
subscribed = 0

#SQS init
sqs             = boto3.resource("sqs",region_name="us-east-1")
clients_queue   = sqs.get_queue_by_name(QueueName='ClientActions')

def print_round_stats(AdID,purchase):
    print("\033[10m - AdID: "+str(adID)+", Purchase: "+str(purchase)+"\033[00m")

def simulate_client(adlist):
    print(" & Received adlist: "+str(adlist))
    client_response = {"Clicked":1}

    #Calculate the sum of all list positions
    listsum=0
    for i in range(len(adlist)):
        listsum+=i+1

    #Calculate the clicked ad
    weightlist = []

    for i in range(len(adlist)):
        weightlist.append((len(adlist)-i)/listsum)
    
    #Chose an ad
    choise = random.choices(adlist, weights=weightlist)[0]
    print(" & Client selected the following ad to click: "+str(choise))
    client_response["AdID"] = choise["AdID"]

    #Calculate the Purchase
    if scenario == 1:
        purchase    = random.randint(0,1)
        client_response["Purchase"] = purchase
    else:
        purchase_probability = float(180-choise["Price"])/float(2)
        purchaselst = [0,1]
        weightlist  = [1-purchase_probability,purchase_probability]

        purchase = random.choices(purchaselst, weights=weightlist)
        client_response["Purchase"] = purchase[0]

    if client_response["Purchase"] == 1:
        print(" & Client procceded to purchase the product!")
    else:
        print(" & Cliend did not purchase the product")

    print_round_stats(client_response["AdID"],client_response["Purchase"])

    #Return the response
    return client_response
    
@app.route('/client', methods = ['GET', 'POST', 'PUT'])
def sns():
    print(" < Recieved a http request at resource /client! Handling...")

    try:
        notification = json.loads(request.data)
    except:
        print(" < Fatal error while parsing request as a json format! Ignoring request...\n")
        return "Fatal error while parsing request as a json format\n"

    #Handle SNS Subscription Confirmation
    if notification["Type"] == 'SubscriptionConfirmation':
        print(" < The request is a Subscription Confirmation, responding...")
        token = notification["Token"]
        response = sns_client.confirm_subscription(
                        TopicArn=TOPICARN,
            Token=token
        )
        subscribed=1

        return 'OK\n'
    #Handle SNS Notifications
    elif notification["Type"] == 'Notification':
        print(" < The request is a Notification, handling...")
        message = ast.literal_eval(notification["Message"])
       
        #Simulate the client
        client_response = simulate_client(message)

        #Send the response back to the queue
        clients_queue.send_message(MessageBody=str(client_response))
        print(" > Sent response to the clients queue: "+str(client_response))
        
    #Handle Unidentified Requests
    else:
        print(notification)

    return 'OK\n'

if __name__ == '__main__':
    print(" > Subscribing to sns")
    response = sns_client.subscribe(
        TopicArn=TOPICARN,
        Protocol='http',
        Endpoint=ENDPOINT,
    )
    print(" > Subscribed to sns and got the following response")
    print(" > "+str(response))
    app.run(
        host = "0.0.0.0",
        port = SERVERPORT,
        debug = True
    )
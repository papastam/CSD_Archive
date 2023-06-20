from flask import Flask, request
import requests
import json
import boto3
import random
import ast

#Constants
PUBLIC_DNS_ADDRESS = 'ec2-3-95-184-65.compute-1.amazonaws.com'
ENDPOINT    = 'http://'+PUBLIC_DNS_ADDRESS+':5000/advertiser'
TOPICARN    = 'arn:aws:sns:us-east-1:613787790506:AdvertiserStats'
SERVERPORT  = 5000

#Game Values
adID                = random.randint(0,999999999)
current_bid         = random.randint(1,100)
current_price       = random.randint(10,100)
total_revenue       = 0
roundcnt            = 0
previus_purchases   = -1
previus_clicks      = -1

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
sqs         = boto3.resource("sqs",region_name="us-east-1")
bids_queue  = sqs.get_queue_by_name(QueueName='BidsQueue')

def print_round_stats(cost,profit,increase,frOm,to):
    print("\033[10m - AdID: "+str(adID)+", Revenue: "+str(total_revenue)+", Cost: "+str(cost)+", Profit"+str(profit)+",Increase"+str(increase)+",from: "+str(frOm)+",to: "+str(to)+"\033[00m")

#access function so the game variables dont go out of range
def chage_value(value,change):
    global current_bid
    global current_price

    if value == "bid":
        if change == "+":
            if current_bid<100:
                current_bid+=1
        elif change == "-":
            if current_bid>1:
                current_bid-=1

    elif value == "price":
        if change == "+":
            if current_price<100:
                current_price+=1
        elif change == "-":
            if current_price>10:
                current_price-=1

    return

#Simple function sending bids to SQS
def send_bid(bid,price):
    global roundcnt
    if scenario == 1:
        message={"AdID":adID,"Bid":bid}
    elif scenario == 2:
        message={"AdID":adID,"Bid":bid,"Price":price}
    bids_queue.send_message(MessageBody=str(message))

    roundcnt+=1
    print(" ^ Sent Bid to SQS: "+str(message))

def calculate_game_variables(message):
    global roundcnt
    global previus_clicks
    global previus_purchases
    global current_bid
    global current_price
    global total_revenue

    strat = ''
    prev_bid = current_bid
    stats = {}
    #Find advertiser's stats
    for i in message:
        if i["AdID"] == adID:
            stats = i

    #If stats not found, report error
    if not stats:
        print(" ! ERROR: My stats not found in input message")
        return

    #If there is no previus knowledge of purchases/clicks
    #This functionality is implemented in order to generate some changes in the ad list in the first round
    if (roundcnt == 1) or (previus_clicks == -1) or ( previus_purchases == -1):
        choise = random.randint(1,5)
        #there is a 20% chance a advertiser decides to change his bid/price without prior rounds knowledge
        if choise == 1:
            choise = random.randing(0,1)
            #50%-50% chance to lower-raise bid/price
            if choise == 0:
                change_value("bid","+")
                change_value("price","+")
                strat = "Increase"
            else:
                change_value("bid","-")
                change_value("price","-")
                strat = "Decrease"
        #80% chance nothing changes in the first round
        else:
            #No change
            pass

    #If the current round is not the first round
    else:
        #Apply strategies as described in the report
        #Bids
        if stats["Clicks"] < previus_clicks:
            change_value("bid","+")
            strat = "Increase"
        else:
            change_value("bid","-")
            strat = "Decrease"

        #Price
        #Calculated only in the second scenario
        if scenario == 2:
            if stats["Cost"]>stats["Purchases"]*stats["Price"]:
                change_value("price","+")
            else:
                change_value("price","-")

    total_revenue+=stats["Price"]*stats["Purchases"]

    #Send the calculated bid
    send_bid(current_bid,current_price)

    print_round_stats(stats["Cost"],stats["Price"]*stats["Purchases"],strat,prev_bid,current_bid)

    #Update Previus round values with current ones
    previus_clicks      = stats["Clicks"]
    previus_purchases   = stats["Purchases"]

    return

@app.route('/advertiser', methods = ['GET', 'POST', 'PUT'])
def sns():
    global subscribed
    print(" < Recieved a http request at resource /advertiser! Handling...")

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
        if subscribed == 1:
            return
        subscribed=1

        #Send the first round bid
        send_bid(current_bid, current_price)
        return 'OK\n'
    #Handle SNS Notifications
    elif notification["Type"] == 'Notification':
        print(" < The request is a Notification, handling...")
        message = ast.literal_eval(notification["Message"])

        #Calculate game variables based on strategies
        calculate_game_variables(message)

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
        ReturnSubscriptionArn=True
    )
    print(" > Subscribed to sns and got the following response")
    print(" > "+str(response))
    app.run(
        host = "0.0.0.0",
        port = SERVERPORT,
        debug = True
    )
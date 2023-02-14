import json
import boto3
import sys

#Game Constants
num_of_ads = 3

dynamodb = boto3.resource("dynamodb")
table = dynamodb.Table("AdServiceDB")

lambda_client = boto3.client('lambda')

debug = 1
def print_debug(message):
    if debug:
        print("DEBUG: "+str(message))

def sort_db(items):
    print_debug("Prioritising the database...")
    debug = 0
    actual_db_size = len(items)
    
    #repeat for the size of the db
    for repeat_cnt in range(actual_db_size):
        #Setup variables
        minbid = sys.maxsize
        minAdId = -1
        remove_index = -1
        
        #Find the AdID with the smaller bid
        for index in range(len(items)):
            if float(items[index]["Bid"]) < float(minbid):
                minbid = items[index]["Bid"]
                minAdId = items[index]["AdID"]
                remove_index = index
        
        #Error case
        if(remove_index < 0) or (minAdId < 0):
            print("ERROR: fatal error after minimum variable calculation, exiting...")
            return
        
        #Update its priority field in the db
        table.update_item(
            Key={
                'AdID': int(minAdId)
            },
            UpdateExpression='SET Priority = :prio',
            ExpressionAttributeValues={
                ':prio': repeat_cnt
            }
        )
        
        #Remove it from the items list
        del items[remove_index]

def lambda_handler(event, context):
    
    dbcontents = table.scan()
    ads_in_db = len(dbcontents["Items"])
    sort_db(dbcontents["Items"])
    
    #-1 because of the quick coordination implementation with the clients_interracted
    if ads_in_db-1 !=num_of_ads:
        print_debug("Currently "+ str(ads_in_db-1) + " ads in the database, waiting for the rest bids...")
        return
    
    print_debug("Triggering PublishList and exiting...")
    response = lambda_client.invoke(
        FunctionName='PublishList',
        InvocationType='Event',
        LogType='None'
    )
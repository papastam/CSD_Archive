import json
import boto3
import ast
from decimal import Decimal

dynamodb = boto3.resource('dynamodb')
table = dynamodb.Table("AdServiceDB")

lambda_client = boto3.client('lambda')

debug = 1
def print_debug(message): #Simple debug function
    if debug:
        print("DEBUG: "+str(message))
    
def lambda_handler(event, context):

    #Default input format
    if ("Records" in event) and ("body" in event["Records"][0]):
        message = ast.literal_eval(event["Records"][0]["body"])
        print_debug("Recieved event with AdID:" + str(message["AdID"])+" and Bid:"+ str(message["Bid"]))
    
    #Test format    
    elif ("AdID" in event) and ("Bid" in event):
        message = event
        print_debug("Recieved event with AdID:" + str(message["AdID"])+" and Bid:"+ str(message["Bid"]))
    
    else:
        print_debug("Recieved event with invalid format, exiting...")
        print_debug(event)
        return
    
    item = {}
    item["AdID"] = int(message["AdID"])
    item["Bid"]  = float(message["Bid"])
    if "Price" in message:
        item["Price"] = float(message["Price"])
    
    response = table.put_item(
        Item = json.loads(json.dumps(item), parse_float=Decimal)
    )
    
    print_debug("Triggering CalculateRevenue and exiting...")
    response = lambda_client.invoke(
        FunctionName='CalculateRevenue',
        InvocationType='Event',
        LogType='None'
    )
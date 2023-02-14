import json
import boto3

dynamodb = boto3.resource("dynamodb")
table = dynamodb.Table("AdServiceDB")

lambda_client = boto3.client('lambda')
    
debug = 1
def print_debug(message): #Simple debug function
    if debug:
        print("DEBUG: "+str(message))

def lambda_handler(event, context):
    dbcontents = table.scan()["Items"]
    
    if ("Records" in event) and ("body" in event["Records"][0]):
        message = event["Records"][0]["body"]
        
    if ("AdID" not in message) or ("Clicked" not in message) or ("Purchase" not in message):
        print("ERROR: Incorrect input event format, exiting...")
        return
    
    message = json.loads(message.replace("'",'"'))
    
    #find ad's previus values
    result = {}
    for i in range(len(dbcontents)):
        if(dbcontents[i]["AdID"] == message["AdID"]):
            result = dbcontents[i]
            
    if not result:
        print("ERROR: AdID nor found in the database!")
        return
        
    #Create clicks and purchases if not in db
    if not "Clicks" in result:
        result["Clicks"]=0
    if not "Purchases" in result:
        result["Purchases"]=0
        
    table.update_item(
        Key={
            'AdID': int(message["AdID"])
        },
        UpdateExpression='SET Clicks = :clicksval, Purchases = :salesval',
        ExpressionAttributeValues={
            ':clicksval': int(result["Clicks"])+1,
            ':salesval' : int(result["Purchases"])+int(message["Purchase"])
        }
    )
    
    #Update clients interracted table entry
    table.update_item(
        Key={
            'AdID': -1
        },
        UpdateExpression='SET Clients_Interracted = :ci',
        ExpressionAttributeValues={
            ':ci': int(dbcontents[0]["Clients_Interracted"])+1,
        }
    )
    
    print_debug("Triggering PublishStats and exiting...")
    response = lambda_client.invoke(
        FunctionName='PublishStats',
        InvocationType='Event',
        LogType='None'
    )
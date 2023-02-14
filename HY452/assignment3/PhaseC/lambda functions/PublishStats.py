import json
import boto3

#Game variables
num_of_clients = 10

dynamodb = boto3.resource("dynamodb")
table = dynamodb.Table("AdServiceDB")

sns_client = boto3.client('sns')

debug = 1
def print_debug(message): #Simple debug function
    if debug:
        print("DEBUG: "+message)

def formatAdList(input):
    adList = []
    
    for item in input:
        new_json={}
        
        for attribute in item:
            new_json[attribute] = float(item[attribute])
            
        adList.append(new_json)
    
    print_debug("Final adlist: "+str(adList))
    return adList

def lambda_handler(event, context):
    print_debug("Recieved trigger, begining execution")
    
    dbcontents = table.scan()["Items"]
    print_debug(str(dbcontents))
    
    #Grhgoro coordination implementation
    #Check if all clients have interracted
    if(dbcontents[0]["Clients_Interracted"] < num_of_clients):
        print_debug(str(dbcontents[0]["Clients_Interracted"])+" Clients_Interracted, waiting for the rest...")
        return

    
    adList = formatAdList(dbcontents)
    
    print_debug("Publishing into AdvertiserStats SNS (Message: "+str(adList)+")")
    
    response = sns_client.publish(
        TopicArn='arn:aws:sns:us-east-1:613787790506:AdvertiserStats',
        Message=str(adList)
    )
    
    #Reset the DynamoDB table
    table.update_item(
        Key={
            'AdID': -1
        },
        UpdateExpression='SET Clients_Interracted = :ci',
        ExpressionAttributeValues={
            ':ci': 0,
        }
    )
    
    #Delete all ads info
    for i in range(len(dbcontents)):
        if dbcontents[i]["AdID"] == -1:
            continue
        table.delete_item(
            Key={
                'AdID': dbcontents[i]["AdID"]
            }
        )
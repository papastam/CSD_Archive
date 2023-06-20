import json
import boto3

dynamodb = boto3.resource("dynamodb")
table = dynamodb.Table("AdServiceDB")

sns_client = boto3.client('sns')

debug = 1
def print_debug(message): #Simple debug function
    if debug:
        print("DEBUG: "+message)

def formatAdList(input):
    adList = []
    print_debug("Formating list:"+str(input))
    
    for item in input:
        new_json={}
        
        for attribute in item:
            print_debug("Handling attribute: "+str(attribute)+"="+str(float(item[attribute])))
            new_json[attribute] = float(item[attribute])
            
        print_debug("Appending item:"+str(new_json))
        adList.append(new_json)
        
        
    def prio_sort(json):
        try:
            # Also convert to int since update_time will be string.  When comparing
            # strings, "10" is smaller than "2".
            return int(json["Priority"])
        except KeyError:
            return 0
            
    adList.sort(key=prio_sort, reverse=True)

        
    print_debug("Final adlist: "+str(adList))
    return adList

def lambda_handler(event, context):
    dbcontents = table.scan() #get all ads
    adList = formatAdList(dbcontents["Items"])
    
    print_debug("Publishing into Ads SNS (Message: "+str(adList)+")")
    
    response = sns_client.publish(
        TopicArn='arn:aws:sns:us-east-1:613787790506:Ads',
        Message=str(adList)
    )
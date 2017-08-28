#!/usr/bin/env python3
import requests
import json

headers = {'Accept':'application/json',
'Accept-Language':'ca-CA',
'client_id':'Hqyble56qaamSD2jzZcbO9BlYEM8zWPlQdNqFk4H'}

def getJSONRaw(url):
    req = requests.get(url,headers=headers)
    return req.text

def getJSONObjectFromRaw(text):
    return json.loads(text)

def getSubjectListFromJSONObject(object):
    return object['results']

def getNextURLFromJSONObject(object):
    return object['next']

def getUndergradSubjectsFromSubjectList(list):
    res = []
    for subject in list:
        if 'GRAU' in subject['plans']:
            res.append(subject)
    return res

def getListOfFIBSubjects():
    url = 'https://api.fib.upc.edu/v2/assignatures/'
    res = []
    while url != None:
        JSONObject = getJSONObjectFromRaw(getJSONRaw(url))
        currentList = getUndergradSubjectsFromSubjectList(
        getSubjectListFromJSONObject(JSONObject))
        url = getNextURLFromJSONObject(JSONObject)
        res += currentList
    return res

def printJSONObjectFromSubjectsList(list):
    res = {'subjects':[]}
    for subject in list:
        res['subjects'].append({'id':subject['id'],'name':subject['nom']})
    print(json.dumps(res))

print('Content-type: application/json\n')
printJSONObjectFromSubjectsList(getListOfFIBSubjects())



















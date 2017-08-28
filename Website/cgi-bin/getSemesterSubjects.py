#!/usr/bin/env python3
import requests
import json
import cgitb
import cgi

headers = {'Accept':'application/json',
'Accept-Language':'ca-CA',
'client_id':'Hqyble56qaamSD2jzZcbO9BlYEM8zWPlQdNqFk4H'}
url = 'https://api.fib.upc.edu/v2/quadrimestres/'

def getSemesterFromURL():
    queryDict = cgi.parse()
    return queryDict['sem'][0]

def getJSONRaw(semester):
    req = requests.get(url + semester + '/assignatures/',headers=headers)
    return req.text

def getSemListFromRaw(text):
    obj = json.loads(text)
    return obj['results']

def printSemSubjectsFromList(list):
    aux = {'subjects':list}
    print(json.dumps(aux))

def printHeaders():
    print('Content-type: application/json\n')

def printHtml():
    printHeaders()
    printSemSubjectsFromList(
    getSemListFromRaw(
    getJSONRaw(getSemesterFromURL())))

printHtml()


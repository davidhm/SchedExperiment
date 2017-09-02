#!/usr/bin/env python3
import requests
import json
import cgi
import sys

headers = {'Accept':'application/json',
'Accept-Language':'ca-CA',
'client_id':'Hqyble56qaamSD2jzZcbO9BlYEM8zWPlQdNqFk4H'}
url = 'https://api.fib.upc.edu/v2/quadrimestres/'

def printQueryStringError():
    print('Content-type: text/html\n')
    print('<html>')
    print('<head>')
    print('<title> Query string error </title>')
    print('</head>')
    print('</body> <h1> Query string error </h1>')
    print('<p> Arguments are invalid. </p>')
    print('</body>')
    print('<html>')
    sys.exit()

def getSemesterFromURL():
    queryDict = cgi.parse()
    if len(queryDict) != 1 or not 'sem' in queryDict or len(queryDict['sem']) != 1:
        printQueryStringError()
    else:
        return queryDict['sem'][0]

def getJSONRaw(semester):
    req = requests.get(url + semester + '/assignatures/',headers=headers)
    return req.text

def getSemListFromRaw(text):
    obj = json.loads(text)
    if 'detail' in obj and obj['detail'] == 'Not found.':
        printQueryStringError()
    return obj['results']

def printSemSubjectsFromList(list):
    aux = {'subjects':list}
    print(json.dumps(aux))

def printHeaders():
    print('Content-type: application/json\n')

def printHtml():
    list = getSemListFromRaw(
    getJSONRaw(getSemesterFromURL()))
    printHeaders()
    printSemSubjectsFromList(list)

printHtml()


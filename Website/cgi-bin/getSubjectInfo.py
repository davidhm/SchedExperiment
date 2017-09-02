#!/usr/bin/env python3
import requests
import json
import cgi
import cgitb
import sys

headers = {'Accept':'application/json',
'Accept-Language':'ca-CA',
'client_id':'Hqyble56qaamSD2jzZcbO9BlYEM8zWPlQdNqFk4H'}

def printQueryStringError():
    print('Content-type: text/html\n')
    print('<html>')
    print('<head>')
    print('<title> Query string error </title>')
    print('</head>')
    print('</body> <h1> Query string error </h1>')
    print('<p> Arguments are invalid.</p>')
    print('</body>')
    print('<html>')
    sys.exit()

def getJSONRaw():
    queryDict = cgi.parse()
    if 'sem' not in queryDict or 'subj' not in queryDict or len(queryDict) != 2:
        printQueryStringError()
    print('Content-type: application/json\n')
    url = 'https://api.fib.upc.edu/v2/quadrimestres/'
    url = url + queryDict['sem'][0] + '/classes/'
    param = {'codi_assig': queryDict['subj'][0]}
    req = requests.get(url,headers=headers,params=param)
    return req.text

def getFinalJSONFromRaw(text):
    res = json.loads(text)
    aux = res['results']
    str = json.dumps({'slots':aux})
    return str

cgitb.enable()
print(getFinalJSONFromRaw(getJSONRaw()))




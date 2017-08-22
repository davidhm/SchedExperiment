#!/usr/bin/env python3
import requests
import json

def getJsonSemestersObject():
    headersRequest = {'Accept':'application/json',
    'client_id':'Hqyble56qaamSD2jzZcbO9BlYEM8zWPlQdNqFk4H'}
    url = 'https://api.fib.upc.edu/v2/quadrimestres/'
    req = requests.get(url,headers=headersRequest)
    return json.loads(req.text)

def printSemestersFromObject(object):
    index = 1
    for sem in object['results']:
        semId = sem['id']
        if sem['actual'] == 'S':
            print('<option value = "',index,'" selected>',semId,'</option>',sep='')
            idActual = semId
        else:
            print('<option value = "',index,'">',semId,'</option>',sep='')
        index = index + 1


def printHtml():
    print('Content-type: text/html\n')
    json = getJsonSemestersObject()
    printSemestersFromObject(json)

printHtml()









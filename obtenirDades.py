import requests
import json

headersRequest = {'Accept':'application/json',
'client_id':'Hqyble56qaamSD2jzZcbO9BlYEM8zWPlQdNqFk4H'}

def getSemesterJSONText():
    url = 'https://api.fib.upc.edu/v2/quadrimestres/'
    req = requests.get(url,headers=headersRequest)
    return req.text

def printSemestersFromObject(jsonObjectSemesters):
    semesterNumber = 1
    for particularSemester in semestersObject['results']:
        print(str(semesterNumber) + ': ' + particularSemester['id'])
        semesterNumber = semesterNumber + 1

def getSemesterSubjectsJSONText(semesterNumber,jsonObjectSemesters):
    url = jsonObjectSemesters['results'][semesterNumber-1]['assignatures']
    req = requests.get(url,headers=headersRequest)
    return req.text

def getDegreeSubjectsSet():
    urlPage1 = 'https://api.fib.upc.edu/v2/assignatures/'
    req = requests.get(urlPage1,headers=headersRequest)
    jsonObject1 = json.loads(req.text)
    subjectsSet = set()
    for subject in jsonObject1['results']:
        if 'GRAU' in subject['plans']:
            subjectsSet.add(subject['id'])
    urlPage2 = 'https://api.fib.upc.edu/v2/assignatures/?page=2'
    req = requests.get(urlPage2,headers=headersRequest)
    jsonObject2 = json.loads(req.text)
    for subject in jsonObject2['results']:
        if 'GRAU' in subject['plans']:
            subjectsSet.add(subject['id'])
    return subjectsSet

def printSemesterSubjectsFromObject(subjectsObject):
    subjects = subjectsObject['results']
    counter = 1
    subjectsInDegree = getDegreeSubjectsSet()
    for subject in subjects:
        if subject in subjectsInDegree:
            print(str(counter) + ': ' + subject)
            counter = counter + 1

semesterObject = json.loads(getSemesterJSONText())
subjectsObject = json.loads(getSemesterSubjectsJSONText(4,semesterObject))
printSemesterSubjectsFromObject(subjectsObject)

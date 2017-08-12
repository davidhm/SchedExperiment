import requests
import json

headersRequest = {'Accept':'application/json',
'client_id':'Hqyble56qaamSD2jzZcbO9BlYEM8zWPlQdNqFk4H'}
subjectQueries = ['G','LP','AS','CCQ','DBD']
semester = '2017Q1'
fileName = 'prologData.pl'

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

def getQueriesList():
    url = ('https://api.fib.upc.edu/v2/quadrimestres/' + semester +
    '/classes/')
    param = ''
    for query in subjectQueries:
        param = param + query + ','
    req = requests.get(url,headers = headersRequest,
    params = {'codi_assig':param})
    return json.loads(req.text)['results']

def getSlotFromHourAndDay(hour,day):
    return int(hour[0:2])-7 + (day-1)*13

def writeCommonPrologPredicates(fileObject,queriesList):
    print('numberOfSubjects({}).'.format(len(subjectQueries)),file=fileObject)
    minSlot = 66
    maxSlot = 0
    minDay = 6
    maxDay = 0
    for entry in queriesList:
        valorSlot = getSlotFromHourAndDay(entry['inici'],
        entry['dia_setmana'])
        if valorSlot < minSlot:
            minSlot = valorSlot
        if valorSlot > maxSlot:
            maxSlot = valorSlot
        if entry['dia_setmana'] < minDay:
            minDay = entry['dia_setmana']
        if entry['dia_setmana'] > maxDay:
            maxDay = entry['dia_setmana']
    print('earliestStartingHour({}).'.format(minSlot),
    'latestStartingHour({}).'.format(maxSlot),
    'earliestDay({}).'.format(minDay),
    'latestDay({}).'.format(maxDay),sep='\n',file=fileObject)

def writeQueryPredicates(fileObject,queriesList):
    subjectGroupSet = set()
    for slot in queriesList:
        subjectIndex = subjectQueries.index(slot['codi_assig']) + 1
        subjectGroup = slot['grup']
        if str(subjectIndex) + subjectGroup not in subjectGroupSet:
            subjectGroupSet.add(str(subjectIndex) + subjectGroup)
            theory = slot['tipus'] == 'T'
            theoryBit = str()
            if theory:
                theoryBit = '1'
            else:
                theoryBit = '0'
            print('group(' + str(subjectIndex) +
            ',' + subjectGroup + ',' + theoryBit + ').'
            ,file=fileObject)
        slotNumber = getSlotFromHourAndDay(slot['inici'],slot['dia_setmana'])
        for i in range(slotNumber,slotNumber+slot['durada']):
            print('class(' + str(i) + ',' +
            str(subjectIndex) + ',' + subjectGroup +
            ').',file=fileObject)



def writePrologPredicates(queriesList):
    with open('./' + fileName,'w') as f:
        writeCommonPrologPredicates(f,queriesList)
        writeQueryPredicates(f,queriesList)








semesters = json.loads(getSemesterJSONText())
subjects = json.loads(getSemesterSubjectsJSONText(4,semesters))
for query in subjectQueries:
    if query not in subjects['results']:
        print('Query:',query,'not in semester')
        quit()
writePrologPredicates(getQueriesList())


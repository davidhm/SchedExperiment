#!/usr/bin/env python3
import requests
import json
import sys
import os
import logging
import subprocess
import bisect
import ast

headers = {'Accept':'application/json',
'Accept-Language':'ca-CA',
'client_id':'Hqyble56qaamSD2jzZcbO9BlYEM8zWPlQdNqFk4H'}

websitePath = '/home/david/Partitions/Almacen3/Documentos/SchedExperiment/Website/'

def setUpLogging():
    logging.basicConfig(filename = websitePath + 'pyLog.txt' ,
    level = logging.DEBUG)

def getJSONRaw():
    numberOfBytes = 0
    try:
        numberOfBytes = int(os.environ['CONTENT_LENGTH'])
    except KeyError:
        logging.exception('Couldn\'t find CONTENT_LENGTH')
        sys.exit(1)
    return sys.stdin.read(numberOfBytes)
    # with open('./input.txt','r') as inputText:
    #     return inputText.read(-1)

def parseJSONToDict(jsonText):
    jsonObject = None
    try:
        jsonObject = json.loads(jsonText)
    except json.JSONDecodeError:
        logging.exception('Received data is not in JSON format')
        sys.exit(1)
    return jsonObject

def getSlotFromHourAndDay(hour,day):
    return int(hour[0:2])-7 + (day-1)*13

def writeGroupPredicates(fileObject,slotsList):
    subjectAndGroupDict = {}
    for slot in slotsList:
        currentSubject = slot['codi_assig']
        if currentSubject not in subjectAndGroupDict:
            subjectAndGroupDict[currentSubject] = set()
        currentGroup = slot['grup'] + slot['tipus']
        if currentGroup not in subjectAndGroupDict[currentSubject]:
            subjectAndGroupDict[currentSubject].add(currentGroup)
    print('numberOfSubjects({}).'.format(len(subjectAndGroupDict)),
    file=fileObject)
    aux = []
    i = 1
    for subject in subjectAndGroupDict:
        aux.append(subject)
        for group in subjectAndGroupDict[subject]:
            groupString = 'group({0},{1},{2}).'
            groupType = ''
            if group[-1] == 'T':
                groupType = '1'
            elif group[-1] == 'L':
                groupType = '0'
            else:
                continue
            print(groupString.format(i,group[:-1],groupType),file=fileObject)
        i = i + 1
    return aux

def writeMaxMinPredicates(fileObject,slotsList):
    minSlot = 66
    maxSlot = 0
    minDay = 6
    maxDay = 0
    for entry in slotsList:
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
    'latestDay({}).'.format(maxDay),
    sep='\n',file=fileObject)

def writeCommonPrologPredicates(fileObject,slotsList):
    writeMaxMinPredicates(fileObject,slotsList)
    return writeGroupPredicates(fileObject,slotsList)

def writeSlotPredicates(fileObject,slotsList,subjectList):
    for slot in slotsList:
        slotValue = getSlotFromHourAndDay(slot['inici'],
        slot['dia_setmana'])
        subj = str(subjectList.index(slot['codi_assig']) + 1)
        group = slot['grup']
        print('class({0},{1},{2}).'.format(slotValue,subj,group),
        file = fileObject)

def writePrologPredicates(slotsList):
    subjectList = []
    with open(websitePath + 'cgi-bin/prologData.pl','w') as f:
        subjectList = writeCommonPrologPredicates(f,slotsList)
        writeSlotPredicates(f,slotsList,subjectList)
    return subjectList

def createPrologSubprocess():
    return subprocess.Popen(['swipl','-q','-s',websitePath + 'cgi-bin/SchedSolver.pl','-g','main'],
    stdout = subprocess.PIPE)

def getScheduleSolution(popenObject):
    out,err = popenObject.communicate()
    return out.decode()

def getSubjectGroupsDict(slotsObject):
    res = {}
    for slot in slotsObject['slots']:
        if slot['codi_assig'] not in res:
            res[slot['codi_assig']] = [[],[]]
        if slot['tipus'] == 'L':
            if slot['grup'] not in res[slot['codi_assig']][1]:
                labList = res[slot['codi_assig']][1]
                group = int(slot['grup'])
                bisect.insort(labList,group)
        else:
            if slot['grup'] not in res[slot['codi_assig']][0]:
                theoryList = res[slot['codi_assig']][0]
                group = int(slot['grup'])
                bisect.insort(theoryList,group)
    return res

def parsePrologSolution(prologSolution):
    return ast.literal_eval(prologSolution)

def prologSolutionToDict(prologSolution,slotsObject,subjectsList):
    subjectGroups = getSubjectGroupsDict(slotsObject)
    solutionList = parsePrologSolution(prologSolution)
    if len(solutionList) > 0:
        i = 1
        for subject in subjectsList:
            theoryList = subjectGroups[subject][0]
            selectedIndex = 2*(i-1)
            selectedGroupIndex = solutionList[selectedIndex]
            selectedTheoryGroup = theoryList[selectedGroupIndex-1]
            subjectGroups[subject][0] = selectedTheoryGroup
            labList = subjectGroups[subject][1]
            selectedIndex = 2*(i-1) + 1
            selectedGroupIndex = solutionList[selectedIndex]
            selectedLabGroup = labList[selectedGroupIndex-1]
            subjectGroups[subject][1] = selectedLabGroup
        return subjectGroups
    else:
        return {'emptyResults':[]}


def printHeaders():
    print('Content-type: application/json\n')

def printSolution(solutionObject):
    printHeaders()
    print(json.dumps(solutionObject))


setUpLogging()
slotsObject = parseJSONToDict(getJSONRaw())
popenObject = createPrologSubprocess()
subjectList = writePrologPredicates(slotsObject['slots'])
scheduleSolution = getScheduleSolution(popenObject)
solutionObject = prologSolutionToDict(scheduleSolution,slotsObject,subjectList)
printSolution(solutionObject)









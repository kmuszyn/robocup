'''
Created on 2010-01-18

Class representing data of a single model in simulation

@author: kamil
'''

import re

class ModelData:
    def __init__(self, filename):
        self.steps = []  # Empty data structure for holding LISTS of VideoDataItems  
                # one list per one time step 
        file = open(filename, 'r')        
        
        stepP = re.compile(r':step[a-z]*')
        aiP = re.compile(r':ai(.)*')
        robotP = re.compile(r':robot(.)*')
        
        dataItem = []
        
        line=file.readline()
        while  line != "":
            print line
            if stepP.match(line):
                if dataItem != None:
                    self.steps.append(dataItem)
                dataItem = ModelDataItem()
            elif aiP.match(line):
                taskName = file.readline()[0:-1]
                dataItem.task = taskName
                taskDesc = file.readline()[0:-1]
                dataItem.taskDesc = taskDesc
                
            elif robotP.match(line):
                pos = file.readline()[0:-1]
                pos = pos.split(' ')
                dataItem.robot['x'] = pos[0]
                dataItem.robot['y'] = pos[1]
                dataItem.robot['rot'] = pos[2]              
                    
            line=file.readline()
                        
        file.close() 

class ModelDataItem:
    
    task = ""
    taskDesc = ""
    robot = dict()
        
    def __init__(self):
        pass
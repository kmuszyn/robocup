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
        rrtP = re.compile(r':rrt(.)*')
        
        dataItem = ModelDataItem()
        
        line=file.readline()
        while  line != "":
            if stepP.match(line):                
                if dataItem.task != "":        
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
            elif rrtP.match(line):
                line = line.split(' ')
                rrtSize = int(line[1])
                for i in range(0, rrtSize):
                    line = file.readline()
                    line = line.split(' ')
                    pos = RRTPos()
                    pos.x = float(line[0])
                    pos.y = float(line[1])
                 
                    dataItem.rrt.append(pos)
                    
            line=file.readline()
                        
        file.close()


class ModelDataItem:
        
    def __init__(self):
        self.task = ""
        self.taskDesc = ""
        self.robot = dict()
        self.rrt = []
        
class RRTPos:
    def __init__(self):
        x = 0.0
        y = 0.0        
'''
Created on 2010-01-24

@author: kamil
'''

import re

"""---------------------------------------------------------------------------------"""
class Config:
    """
    Class holds info about last used videodata file and possible robot file names
    extracted from videodata
    """
    
    videoDataFileName = ''
    robotNames = []
    configFile = None
    def __init__(self):
        pass
        
    def load(self, filename):    
        self.configFile = filename 
        try:
            file = open(self.configFile, 'r')
            if file!= None:
                self.videoDataFileName = file.readline()
                print 'Config, read file',self.videoDataFileName             
                file.close()            
        except IOError, x:
            pass     
        
    def save(self):
        if self.videoDataFileName != None:
            file = open(self.configFile, 'w')
            file.write(self.videoDataFileName)
            file.close()
            print 'Saved videoData file:', self.videoDataFileName
            
    def disp(self):
        print self.videoDataFileName
        print self.robotNames
        
    def videoDataFileNameOK(self):
        return self.videoDataFileName != None and len(self.videoDataFileName) > 0
        

"""---------------------------------------------------------------------------------"""
    
class VideoData:
    """ Class holds video data read from file, allows easy access to selected time step """    
    
    def __init__(self):
        self.steps = []  # Empty data structure for holding LISTS of VideoDataItems  
                # one list per one time step
        self.robotNames = []
                
    def load(self, videoDataFileName): 
        file = open(videoDataFileName, 'r')        
        #re patterns
        pStep = re.compile(r':step[a-z]*')
        tmpList = []      
        
        stepNr = None             
        
        robots = file.readline()
        robots = robots[0:-2]
        robots = robots.split(' ')
        self.robotNames = robots
                
        for line in file:    
            result = pStep.match(line)
            if result:
                """saving read step and clearing tmpList for a new step data"""
                if stepNr != None:
                    """
                    if steps nr are not in order, add empty missing steps
                    added because steps may not start from 0, but 1 or greater nr, depends
                    on when was the writing function called in robocup_mgr_client
                    steps numbers must be correct in order to synchronize videodata steps
                    with robot data steps
                    """
                    if len(self.steps) < stepNr:
                        print 'adding empty steps', stepNr                
                        while(len(self.steps) < stepNr):
                            self.steps.append([])  
                    
                    self.steps.append(tmpList)
                    
                tmpList = []
                line = line.split(' ')
                stepNr = int(line[1])
            else:
                line = line[0:-1] #trim \n sign
                line = line.split(' ')
                #print line, line[0]
                tmpItem = VideoDataItem()
                tmpItem.x = float(line[0])
                tmpItem.y = float(line[1])
                tmpItem.rot = float(line[2])
                tmpItem.radius = float(line[3])
                tmpItem.team = float(line[4])
                tmpList.append(tmpItem)
                    
        file.close() 
        
    def length(self):
        return len(self.steps)
        
class VideoDataItem:
    ''' Class represents videoData item '''
    x = 0
    y = 0
    rot = 0
    radius = 0
    team = 0
    
"""---------------------------------------------------------------------------------"""
class ModelData:
    def __init__(self, filename):
        self.steps = []  # Empty data structure for holding LISTS of VideoDataItems  
                # one list per one time step 
        file = open(filename, 'r')        
        
        stepP = re.compile(r':step[a-z]*')
        aiP = re.compile(r':ai(.)*')
        robotP = re.compile(r':robot(\w)(.)*')
        rrtP = re.compile(r':rrt(\w)(.)*')
        rrtP = re.compile(r':rrtresult(\w)(.)*')
        
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
                for i in range(rrtSize):
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
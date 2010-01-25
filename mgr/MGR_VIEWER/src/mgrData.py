'''
Created on 2010-01-24

@author: kamil
'''

import re

"""---------------------------------------------------------------------------------"""
class Config:
    videoDataFile = None
    modelNames = []
    def __init__(self):
        try:
            file = open('mgrViewerConfig', 'r')
            if file!= None:
                self.videoDataFile = file.readline()
                print 'Config, read file',self.videoDataFile             
                file.close()            
        except IOError, x:
            pass
        
    
    def save(self):
        if self.videoDataFile != None:
            file = open('mgrViewerConfig', 'w')
            file.write(self.videoDataFile)
            file.close()
            print 'Saved videoData file:', self.videoDataFile
            
    def disp(self):
        print self.videoDataFile
        print self.modelNames
        
    def video_data_OK(self):
        return self.videoDataFile != None and len(self.videoDataFile) > 0
        

"""---------------------------------------------------------------------------------"""
    
class VideoData:
    ''' Class holds video data read from file, allows easy access to selected time step '''    
    
    def __init__(self, config):
        self.steps = []  # Empty data structure for holding LISTS of VideoDataItems  
                # one list per one time step 
        file = open(config.videoDataFile, 'r')        
        #re patterns
        pStep = re.compile(r':step[a-z]*')
        tmpList = []           
        
        models = file.readline()
        models = models[0:-2]
        models = models.split(' ')
        config.modelNames = models
                
        for line in file:            
            result = pStep.match(line)
            if result:
                #print ':step'
                if len(tmpList) > 0:
                    self.steps.append(tmpList)
                tmpList = []
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
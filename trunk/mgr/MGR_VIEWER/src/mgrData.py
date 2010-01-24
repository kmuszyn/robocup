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
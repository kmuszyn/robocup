'''
Created on 2010-01-10

@author: kamil
'''

import re
from Config import Config

class VideoData:
    ''' Class holds video data read from file, allows easy access to selected time step '''    
    
    def __init__(self, fileName, config):
        self.steps = []  # Empty data structure for holding LISTS of VideoDataItems  
                # one list per one time step 
        file = open(fileName, 'r')        
        #re patterns
        pStep = re.compile(r':step[a-z]*')
        tmpList = []           
        
        models = file.readline()
        models = models[0:-2]
        models = models.split(' ')
        for m in models:
            config.modelFiles.append(m)
        
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

          
        
        
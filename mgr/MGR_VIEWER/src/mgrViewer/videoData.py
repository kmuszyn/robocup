'''
Created on 2010-01-10

@author: kamil
'''

import re

class VideoData:
    ''' Class holds video data read from file, allows easy access to selected time step '''
    
    steps = []  # Empty data structure for holding LISTS of VideoDataItems  
                # one list per one time step 
    
    def __init__(self, fileName):
        file = open(fileName, 'r')        
        #re patterns
        pStep = re.compile(r':step[a-z]*')
        tmpList = []           
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
                tmpItem.x = line[0]
                tmpItem.y = line[1]
                tmpItem.rot = line[2]
                tmpItem.radius = line[3]
                tmpList.append(tmpItem)
                    
        file.close() 
        
class VideoDataItem:
    ''' Class represents videoData item '''
    x = 0
    y = 0
    rot = 0
    radius = 0

          
        
        
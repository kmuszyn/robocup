'''
Created on 2010-01-17

@author: kamil
'''

class Config:
    videoDataFile = None
    modelFiles = []
    def __init__(self):
        try:
            file = open('mgrViewerConfig', 'r')
            if file!= None:
                self.videoDataFile = file.readline()             
                file.close()            
        except IOError, x:
            pass
        
    
    def save(self):
        if self.videoDataFile != None:
            file = open('mgrViewerConfig', 'w')
            file.write(self.videoDataFile)
            file.close()
            
    def disp(self):
        print self.videoDataFile
        print self.modelFiles
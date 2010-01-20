'''
Created on 2010-01-18

File containing all data objects.
Allows GUI and data separation

@author: kamil
'''
from Config import Config
from VideoData import VideoData
from ModelData import ModelData
import os

class SimData:    
    def __init__(self):
        '''config gen'''
        self.config = Config()        
        
    def loadVideoData(self, filename):
        if filename!= None:
            self.config.videoDataFile = filename
            self.videoData = VideoData(filename, self.config)   
            
            if len(self.config.modelFiles) > 0:
                self.loadModelsData()
                
    def videoDataSize(self):
        return len(self.videoData.steps)
    
    def getVideoData(self, stepNr):
        return self.videoData.steps[stepNr]
 
    def loadModelsData(self):
        self.modelData = dict()
        dir = os.path.dirname(str(self.config.videoDataFile))
        for model in self.config.modelFiles:
            filename =  dir +'/'+ model+'.txt'
            
            if os.path.isfile(filename) == True:
                self.modelData[model] = ModelData(filename)            
        
    def modelsDataLoaded(self):
        return len(self.modelData)> 0
 
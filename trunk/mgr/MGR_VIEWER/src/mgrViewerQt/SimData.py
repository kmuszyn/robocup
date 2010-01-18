'''
Created on 2010-01-18

File containing all data objects.
Allows GUI and data separation

@author: kamil
'''
from Config import Config
from VideoData import VideoData

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
        pass
        #dir = os.path.dirname(self.config.videoDataFile)
        #self.container.drawingArea.models = []
        #for model in self.config.modelFiles:
        #    filename =  dir +'/'+ model+'.txt'
        ##    md = ModelData(filename)
         #   if md != None:
         #       self.container.drawingArea.models.append(md)
               # to jest syf, bo tez menu musi miec do tego dostep!
            
 
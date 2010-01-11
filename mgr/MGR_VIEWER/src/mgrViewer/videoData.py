'''
Created on 2010-01-10

@author: kamil
'''

class VideoData:
    ''' Class holds video data read from file, allows easy access to selected time step '''
    def __init__(self, fileName):
        file = open(fileName, 'r')   
        
        for line in file:
            print line,
        
        file.close() 
        
        
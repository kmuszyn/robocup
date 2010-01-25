'''
Created on 2010-01-24

@author: kamil
'''
from PyQt4 import QtGui, QtCore
from mgrUI import DrawingArea, MgrMenu
from mgrData import Config, VideoData, ModelData
import sys
import os

class MainWin(QtGui.QMainWindow):
    def __init__(self):
        QtGui.QMainWindow.__init__(self)
        self.setWindowTitle('MGR VIEWER 2.0')
        self.setGeometry(10,10,840,840)
        
        self.addScroll()
        self.populateScroll()
        
        self.bindActions()
        
        self.createMenu()
        
        self.initVideoData()        

    def addScroll(self):
        self.scroll = QtGui.QScrollArea(self)
        self.setCentralWidget(self.scroll)
        
    def populateScroll(self):
        container = QtGui.QWidget()
    
        self.drawingArea = DrawingArea(self)
        self.mgrMenu = MgrMenu(self)
        
        hbox = QtGui.QHBoxLayout()
        hbox.addWidget(self.drawingArea)        
        hbox.addWidget(self.mgrMenu)
        container.setLayout(hbox)
        
        self.scroll.setWidget(container)
        
    def createMenu(self):
        """Creates top menu with file option"""
        
        self.statusBar().showMessage('Select file with videoData')
        
        exit = QtGui.QAction('Exit', self)    
        self.connect(exit, QtCore.SIGNAL('triggered()'), QtCore.SLOT('close()'))

        videoData = QtGui.QAction('Load VideoData', self)
        self.connect(videoData, QtCore.SIGNAL('triggered()'), self.videoDataDialog)
        
        menubar = self.menuBar()
        file = menubar.addMenu('&File')
        
        file.addAction(videoData)
        file.addAction(exit)

    def initVideoData(self):        
        self.config = Config()
        if self.config.video_data_OK():
            self.loadVideoData()
        
    def loadVideoData(self):
        print 'Trying to load data from:', self.config.videoDataFile
        self.videoData = VideoData(self.config)
        
        if self.videoData :
            self.mgrMenu.setVideoDataLength(len(self.videoData.steps)-1)
            self.mgrMenu.setVideoDataEnabled(True)
            self.setVideoData(0)
            
            if len(self.config.modelNames) > 0:
                self.loadModelsData()
                self.setRobotData(0)
            
        else:
            self.mgrMenu.setVideoDataEnabled(True)
        
    def videoDataDialog(self):
        tmp = QtGui.QFileDialog.getOpenFileName(self, 'Open file','.')
        if tmp:
            self.config.videoDataFile = tmp    
            self.loadVideoData()
        
    def loadModelsData(self):
        self.modelData = dict()
        dir = os.path.dirname(str(self.config.videoDataFile))
        for model in self.config.modelNames:
            filename =  dir +'/'+ model+'.txt'
            
            if os.path.isfile(filename) == True:
                self.modelData[model] = ModelData(filename)
        
        self.mgrMenu.setRobotDataEnabled(True)        
        self.mgrMenu.addModels(self.config.modelNames)       
             
        
    def closeEvent(self, event):
        self.config.disp()
        self.config.save()
        
    def bindActions(self):                
        self.connect(self.mgrMenu.slider, QtCore.SIGNAL('valueChanged(int)'), self.setVideoData)
        self.connect(self.mgrMenu.slider, QtCore.SIGNAL('valueChanged(int)'), self.setRobotData)
        self.connect(self.mgrMenu.robotCombo, QtCore.SIGNAL('currentIndexChanged(int)'), self.switchRobotData)
        
    def setVideoData(self, val):
        self.drawingArea.setVideoData(self.videoData.steps[val])
        
    def setRobotData(self, val):        
        model = str(self.mgrMenu.robotCombo.currentText())
        self.mgrMenu.setRobotData(self.modelData[model].steps[val])
        self.drawingArea.setRRT(self.modelData[model].steps[val].rrt)
        
    def switchRobotData(self, val):
        self.setRobotData(self.mgrMenu.slider.value())

if __name__ == '__main__':
    print 'Start'
    app = QtGui.QApplication(sys.argv)
    mainWin = MainWin()
    mainWin.show()
    sys.exit(app.exec_())
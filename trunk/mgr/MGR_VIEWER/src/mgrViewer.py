'''
Created on 2010-01-24

@author: kamil
'''
from PyQt4 import QtGui, QtCore
from mgrUI import DrawingArea, DrawingMenu
from mgrData import Config, VideoData, ModelData
import sys
import os

class MainWin(QtGui.QMainWindow):
    def __init__(self):
        """ Creates main app win and tries to load videodata from last used file """
        QtGui.QMainWindow.__init__(self)
        
        """UI part"""
        self.setWindowTitle('MGR VIEWER 2.0')
        self.setGeometry(10,10,840,840)
        
        self.createContainer()
        self.createTopMenu()
                
        """data init part"""
        self.config = Config()
        self.config.load('mgrViewerConfig')
        if self.config.videoDataFileNameOK():
            self.loadVideoData(self.config.videoDataFileName)
        
    def createContainer(self):        
        """
        Creates main container for window content. Populates it with widgets.
        Container is placed in scroll to make it possible to resize window with no clipping.
        """
        
        scroll = QtGui.QScrollArea(self)
        self.setCentralWidget(scroll)
        
        container = QtGui.QWidget()
    
        self.drawingArea = DrawingArea(self)
        self.drawingMenu = DrawingMenu(self)
        
        hbox = QtGui.QHBoxLayout()
        hbox.addWidget(self.drawingArea)        
        hbox.addWidget(self.drawingMenu)
        container.setLayout(hbox)
        
        scroll.setWidget(container)
        
        self.bindActions()
        
    def createTopMenu(self):
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
        if self.config.video_data_OK():
            self.loadVideoData()
        
    def loadVideoData(self, videoDataFileName):    
        try:    
            self.videoData = VideoData()
            self.videoData.load(videoDataFileName)
            
            self.drawingMenu.enableVideoData(self.videoData.length())
            
            return
            
            if self.videoData :
                self.drawingMenu.setVideoDataLength(len(self.videoData.steps)-1)
                self.drawingMenu.setVideoDataEnabled(True)
                self.setVideoData(0)
                
                if len(self.config.robotNames) > 0:
                    self.loadModelsData()
                    self.setRobotData(0)
                
            else:
                self.drawingMenu.setVideoDataEnabled(True)
        except BaseException as e:
            self.displayErrorMsg('Error while reading videoData: ' + str(e))
        
    def videoDataDialog(self):
        tmp = QtGui.QFileDialog.getOpenFileName(self, 'Open file','.')
        if tmp:
            self.config.videoDataFileName = tmp    
            self.loadVideoData(self.config.videoDataFileName)
        
    def loadModelsData(self):
        self.modelData = dict()
        dir = os.path.dirname(str(self.config.videoDataFileName))
        for model in self.config.robotNames:
            filename =  dir +'/'+ model+'.txt'
            
            if os.path.isfile(filename) == True:
                self.modelData[model] = ModelData(filename)
        
        self.drawingMenu.setRobotDataEnabled(True)        
        self.drawingMenu.addModels(self.config.robotNames)       
             
        
    def closeEvent(self, event):
        self.config.disp()
        self.config.save()
        
    def bindActions(self):                
        self.connect(self.drawingMenu.slider, QtCore.SIGNAL('valueChanged(int)'), self.setVideoData)
        self.connect(self.drawingMenu.slider, QtCore.SIGNAL('valueChanged(int)'), self.setRobotData)
        self.connect(self.drawingMenu.robotCombo, QtCore.SIGNAL('currentIndexChanged(int)'), self.switchRobotData)
        
    def setVideoData(self, val):
        self.drawingArea.setVideoData(self.videoData.steps[val])
        
    def setRobotData(self, val):        
        model = str(self.drawingMenu.robotCombo.currentText())
        if len(self.modelData[model].steps) > 0 :
            self.drawingMenu.setRobotData(self.modelData[model].steps[val])
            self.drawingArea.setRRT(self.modelData[model].steps[val].rrt)
        
    def switchRobotData(self, val):
        self.setRobotData(self.drawingMenu.slider.value())
        
    def displayErrorMsg(self, msg):
        QtGui.QMessageBox.warning(self, 'Error', msg , QtGui.QMessageBox.Ok)

if __name__ == '__main__':
    print 'Start'
    app = QtGui.QApplication(sys.argv)
    mainWin = MainWin()
    mainWin.show()
    sys.exit(app.exec_())
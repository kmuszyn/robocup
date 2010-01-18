'''
Created on 2010-01-14

@author: kamil
'''

from PyQt4 import QtGui, QtCore
from VideoData import VideoData
from MainMenu import MainMenu
from DrawingArea import DrawingArea
from Config import Config
import os
from SimData import SimData

class MainWin(QtGui.QMainWindow):
    def __init__(self):
        QtGui.QMainWindow.__init__(self)      
        self.setWindowTitle('MGR VIEWER 1.0')
        self.center()
                       
        '''adding main container'''
        self.container = Container(self)            
        self.setCentralWidget(self.container)
        self.adjustSize()
        
        '''creating top menu'''
        self.statusBar().showMessage('Select file with videoData')
        
        exit = QtGui.QAction('Exit', self)    
        self.connect(exit, QtCore.SIGNAL('triggered()'), QtCore.SLOT('close()'))

        videoData = QtGui.QAction('Load VideoData', self)
        self.connect(videoData, QtCore.SIGNAL('triggered()'), self.loadVideoDataDialog)
        
        menubar = self.menuBar()
        file = menubar.addMenu('&File')
        
        file.addAction(videoData)
        file.addAction(exit)
        
        self.simData = SimData()
        
        '''binding actions'''
        self.bindActions()
        
        '''pre loading video data from last file'''
        
        if self.simData.config.videoDataFile != None:
            self.loadVideoData(self.simData.config.videoDataFile)    
            
                      
                        
    def center(self):
        screen = QtGui.QDesktopWidget().screenGeometry()
        size = self.geometry()
        self.move((screen.width()-size.width())/2, (screen.height()-size.height())/2)
        
    def closeEvent(self, event):
        self.simData.config.disp()
        self.simData.config.save()
        event.accept()
       # reply = QtGui.QMessageBox.question(self, 'Message', 'Are you sure?', QtGui.QMessageBox.No, 
       #                                    QtGui.QMessageBox.Yes)
      #  if reply == QtGui.QMessageBox.Yes:
      #      event.accept()
      #  else:
      #      event.ignore()
            
    def loadVideoDataDialog(self):
        print 'Loading videoData...'    
        filename = QtGui.QFileDialog.getOpenFileName(self, 'Open file', 
                                                     '/home/kamil/workspace/robocup_mgr_client/Debug')
        self.loadVideoData(filename)
                
    def loadVideoData(self, filename): 
        self.simData.loadVideoData(filename)    
        stepsCount = self.simData.videoDataSize()
        self.statusBar().showMessage('Loaded %(steps)03d steps' 
                                         % {'steps' : stepsCount})               
        self.container.mainMenu.enableVideoData(stepsCount)
        self.container.drawingArea.vd = self.simData.getVideoData(0)
        
    def bindActions(self):
        '''main menu slider connection'''
        self.connect(self.container.mainMenu.slider, QtCore.SIGNAL('valueChanged(int)'), self.sliderAction)
        
    def sliderAction(self,value):
        self.container.mainMenu.changeSliderValue(value)
        self.container.drawingArea.vd = self.simData.getVideoData(value)
        self.container.drawingArea.repaint()
            

class Container(QtGui.QWidget):
    def __init__(self, parent = None):
        QtGui.QWidget.__init__(self, parent)                
        self.drawingArea = DrawingArea(self)
        self.mainMenu = MainMenu(self)
        
        hbox = QtGui.QHBoxLayout()    
        hbox.addWidget(self.drawingArea)
        hbox.addWidget(self.mainMenu)
        self.setLayout(hbox)
            
    
            
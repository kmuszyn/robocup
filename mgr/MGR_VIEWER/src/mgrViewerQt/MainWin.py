'''
Created on 2010-01-14

@author: kamil
'''

from PyQt4 import QtGui, QtCore
from VideoData import VideoData
from MainMenu import MainMenu
from DrawingArea import DrawingArea
from Config import Config

class MainWin(QtGui.QMainWindow):
    def __init__(self):
        QtGui.QMainWindow.__init__(self)      
        self.setWindowTitle('Test QT')
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
        
        '''config gen'''
        self.config = Config()
        self.loadVideoData(self.config.videoDataFile)           
                        
    def center(self):
        screen = QtGui.QDesktopWidget().screenGeometry()
        size = self.geometry()
        self.move((screen.width()-size.width())/2, (screen.height()-size.height())/2)
        
    def closeEvent(self, event):
        self.config.disp()
        self.config.save()
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
        if filename!= None:
            self.config.videoDataFile = filename
            self.container.drawingArea.setVideoData(VideoData(filename, self.config))   
            self.statusBar().showMessage('Loaded %(steps)03d steps' 
                                         % {'steps':len(self.container.drawingArea.vd.steps)}) 
              
            self.container.mainMenu.enableVideoData(len(self.container.drawingArea.vd.steps)-1)        

class Container(QtGui.QWidget):
    def __init__(self, parent = None):
        QtGui.QWidget.__init__(self, parent)                
        self.drawingArea = DrawingArea(self)
        self.mainMenu = MainMenu(self)
        
        hbox = QtGui.QHBoxLayout()    
        hbox.addWidget(self.drawingArea)
        hbox.addWidget(self.mainMenu)
        self.setLayout(hbox)
            
        '''main menu slider connection'''
        self.connect(self.mainMenu.slider, QtCore.SIGNAL('valueChanged(int)'), self.sliderAction)
        
    def sliderAction(self,value):
        self.mainMenu.changeSliderValue(value)
        self.drawingArea.setTimeStep(value)    
            
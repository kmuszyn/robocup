'''
Created on 2010-01-14

@author: kamil
'''

from PyQt4 import QtGui, QtCore
from videoData import VideoData

class MainWin(QtGui.QMainWindow):
    def __init__(self):
        QtGui.QMainWindow.__init__(self)
        self.resize(400,300)
        self.setWindowTitle('Test QT')
        self.center()
        
        self.statusBar().showMessage('Select file with videoData')
        
        exit = QtGui.QAction('Exit', self)    
        self.connect(exit, QtCore.SIGNAL('triggered()'), QtCore.SLOT('close()'))

        videoData = QtGui.QAction('Load VideoData', self)
        self.connect(videoData, QtCore.SIGNAL('triggered()'), self.loadVideoData)
        
        menubar = self.menuBar()
        file = menubar.addMenu('&File')
        
        file.addAction(videoData)
        file.addAction(exit)
        
                        
    def center(self):
        screen = QtGui.QDesktopWidget().screenGeometry()
        size = self.geometry()
        self.move((screen.width()-size.width())/2, (screen.height()-size.height())/2)
        
    def closeEvent(self, event):
        reply = QtGui.QMessageBox.question(self, 'Message', 'Are you sure?', QtGui.QMessageBox.No, 
                                           QtGui.QMessageBox.Yes)
        if reply == QtGui.QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()
            
    def loadVideoData(self):
        print 'Loading videoData...'    
        filename = QtGui.QFileDialog.getOpenFileName(self, 'Open file', '/home/kamil/workspace/robocup_mgr_client/Debug')
        self.vd = VideoData(filename)   
        self.statusBar().showMessage('Loaded %(steps)03d steps' % {'steps':len(self.vd.steps)})     
        
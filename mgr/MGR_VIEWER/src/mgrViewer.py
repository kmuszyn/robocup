'''
Created on 2010-01-24

@author: kamil
'''
from PyQt4 import QtGui, QtCore
from mgrUI import DrawingArea, MgrMenu
from mgrData import Config, VideoData
import sys

class MainWin(QtGui.QMainWindow):
    def __init__(self):
        QtGui.QMainWindow.__init__(self)
        self.setWindowTitle('MGR VIEWER 2.0')
        self.setGeometry(10,10,840,840)
        
        self.add_scroll()
        self.populate_scroll()
        
        self.bind_actions()
        
        self.create_menu()
        
        self.init_video_data()        

    def add_scroll(self):
        self.scroll = QtGui.QScrollArea(self)
        self.setCentralWidget(self.scroll)
        
    def populate_scroll(self):
        container = QtGui.QWidget()
    
        self.drawingArea = DrawingArea(self)
        self.mgrMenu = MgrMenu(self)
        
        hbox = QtGui.QHBoxLayout()
        hbox.addWidget(self.drawingArea)        
        hbox.addWidget(self.mgrMenu)
        container.setLayout(hbox)
        
        self.scroll.setWidget(container)
        
    def create_menu(self):
        """Creates top menu with file option"""
        
        self.statusBar().showMessage('Select file with videoData')
        
        exit = QtGui.QAction('Exit', self)    
        self.connect(exit, QtCore.SIGNAL('triggered()'), QtCore.SLOT('close()'))

        videoData = QtGui.QAction('Load VideoData', self)
        self.connect(videoData, QtCore.SIGNAL('triggered()'), self.video_data_dialog)
        
        menubar = self.menuBar()
        file = menubar.addMenu('&File')
        
        file.addAction(videoData)
        file.addAction(exit)

    def init_video_data(self):        
        self.config = Config()
        if self.config.video_data_OK():
            self.load_video_data()
        
    def load_video_data(self):
        print 'Trying to load data from:', self.config.videoDataFile
        self.videoData = VideoData(self.config)
        
    def video_data_dialog(self):
        self.config.videoDataFile = QtGui.QFileDialog.getOpenFileName(self, 'Open file','.')
        
    def closeEvent(self, event):
        self.config.disp()
        self.config.save()
        
    def bind_actions(self):                
        pass
        

if __name__ == '__main__':
    print 'Start'
    app = QtGui.QApplication(sys.argv)
    mainWin = MainWin()
    mainWin.show()
    sys.exit(app.exec_())
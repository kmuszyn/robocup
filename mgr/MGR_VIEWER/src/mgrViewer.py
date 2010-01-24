'''
Created on 2010-01-24

@author: kamil
'''
from PyQt4 import QtGui, QtCore
from mgrUI import DrawingArea, MgrMenu
import sys

class MainWin(QtGui.QMainWindow):
    def __init__(self):
        QtGui.QMainWindow.__init__(self)
        self.setWindowTitle('MGR VIEWER 2.0')
        self.setGeometry(10,10,840,800)
        
        self.add_scroll()
        self.populate_scroll()
        
        self.bind_actions()

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
        
    def bind_actions(self):                
        pass
        

if __name__ == '__main__':
    print 'Start'
    app = QtGui.QApplication(sys.argv)
    mainWin = MainWin()
    mainWin.show()
    sys.exit(app.exec_())
'''
Created on 2010-01-17

@author: kamil
'''
from PyQt4 import QtGui, QtCore

class DrawingArea(QtGui.QWidget):
    
    timeStep = 0;
    vd = None; #video Data
    
    def __init__(self, parent = None):
        QtGui.QWidget.__init__(self, parent)
        self.setFixedSize(QtCore.QSize(540,740))
        
    def paintEvent(self, event):
        p = QtGui.QPainter()
        p.begin(self)        
        if self.vd != None:
            self.paintVideoData()
        p.end()
        
    def setTimeStep(self, ts):
        self.timeStep = ts
        
    def paintVideoDatA(self):
        
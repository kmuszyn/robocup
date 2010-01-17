'''
Created on 2010-01-17

@author: kamil
'''
from PyQt4 import QtGui, QtCore

class DrawingArea(QtGui.QWidget):
    
    timeStep = 0;
    vd = None; #video Data
    MARGIN = 10;
    FIELD_WIDTH = 540
    FIELD_HEIGHT = 740
    
    def __init__(self, parent = None):
        QtGui.QWidget.__init__(self, parent)
        self.setFixedSize(QtCore.QSize(self.FIELD_WIDTH + 2 * self.MARGIN,self.FIELD_HEIGHT + 2 * self.MARGIN))
        
    def paintEvent(self, event):
        p = QtGui.QPainter()
        p.begin(self)    
        self.paintField(p)            
        if self.vd != None:
            self.paintVideoData(p)
        p.end()
        
    def setVideoData(self, data):
        self.vd = data;
        if len(self.vd.steps)>0:
            self.setTimeStep(0)
        
        
    def setTimeStep(self, ts):
        self.timeStep = ts
        self.repaint()
        
    def paintVideoData(self, p):
        tmp = self.vd.steps[self.timeStep]
        
        for i in tmp:
            #print i.x, i.y, i.radius
            #print i.x * 100, i.y * 100, int(round(i.radius * 200, 0))
            x = int(round(i.x * 100,0)) + self.MARGIN
            y = self.FIELD_HEIGHT - int(round(i.y * 100,0)) + self.MARGIN
            d = int(round(i.radius * 100, 0)) 
            
            p.setBrush(QtGui.QColor(200,10,10))
            p.drawEllipse(QtCore.QPointF(x,y), d, d)
            
    def paintField(self,p):
        p.setBrush(QtGui.QColor(28,140,28))
        p.drawRect(self.MARGIN, self.MARGIN, self.FIELD_WIDTH, self.FIELD_HEIGHT)          
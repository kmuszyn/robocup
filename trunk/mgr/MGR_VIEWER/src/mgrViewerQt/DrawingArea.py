'''
Created on 2010-01-17

@author: kamil
'''
from PyQt4 import QtGui, QtCore

class DrawingArea(QtGui.QWidget):
    
    vd = None; #video Data
    models = []
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
            self.paintRRT(p)
        p.end()
        
    def setVideoData(self, data):
        self.vd = data;
        if len(self.vd.steps)>0:
            self.setTimeStep(0)
        
        
    def paintVideoData(self, p):                
        for i in self.vd:
            #print i.x, i.y, i.radius
            #print i.x * 100, i.y * 100, int(round(i.radius * 200, 0))
            x = int(round(i.x * 100,0)) + self.MARGIN
            y = self.FIELD_HEIGHT - int(round(i.y * 100,0)) + self.MARGIN
            d = int(round(i.radius * 100, 0))             
            
            color = QtGui.QColor(250,110,30) #orange            
            
            if i.team == 1:
                color = QtGui.QColor(200,10,10)
                
            if i.team == 2:
                color = QtGui.QColor(20,30,190)
            
            p.setBrush(color)
            p.drawEllipse(QtCore.QPointF(x,y), d, d)
    
    def paintRRT(self,p):
        menu = self.parentWidget().mainMenu
        
        if menu.hideRRT.isChecked():
            return
        
        rrt = menu.getRRT()
        if len(rrt) > 0:
            for pos in rrt:
                
                x = int(round(pos.x * 100,0)) + self.MARGIN
                y = self.FIELD_HEIGHT - int(round(pos.y * 100,0)) + self.MARGIN
                
                pen = QtGui.QPen()
                pen.setColor(QtCore.Qt.black)
                pen.setWidth(2)
                p.setPen(pen)
                p.drawPoint(x,y)
            
    def paintField(self,p):
        p.setBrush(QtGui.QColor(28,140,28))
        p.drawRect(self.MARGIN, self.MARGIN, self.FIELD_WIDTH, self.FIELD_HEIGHT)          
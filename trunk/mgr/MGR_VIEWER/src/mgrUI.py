'''
Created on 2010-01-24

@author: kamil
'''

from PyQt4 import QtGui, QtCore

class DrawingArea(QtGui.QWidget):
    
    MARGIN = 10;
    FIELD_WIDTH = 540
    FIELD_HEIGHT = 740
    
    data = []
    rrt = []
    
    def __init__(self, parent = None):
        QtGui.QWidget.__init__(self, parent)
        self.setFixedSize(
                QtCore.QSize(self.FIELD_WIDTH + 2 * self.MARGIN,
                             self.FIELD_HEIGHT + 2 * self.MARGIN))        
        
    def paintEvent(self, event):
        p = QtGui.QPainter()
        p.begin(self)    
        self.paintField(p)
        if len(self.data) > 0 : self.paintData(p)
        if len(self.rrt) > 0 : self.paintRRT(p)
                           
        p.end()
            
    def paintField(self,p):
        p.setBrush(QtGui.QColor(28,140,28))
        p.drawRect(self.MARGIN, self.MARGIN, self.FIELD_WIDTH, self.FIELD_HEIGHT)
        
    def paintData(self,p):
        for i in self.data:
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
            
    def paintRRT(self, p):        
        for pos in self.rrt:
                
            x = int(round(pos.x * 100, 0)) + self.MARGIN
            y = self.FIELD_HEIGHT - int(round(pos.y * 100, 0)) + self.MARGIN
                
            pen = QtGui.QPen()
            pen.setColor(QtCore.Qt.black)
            pen.setWidth(2)
            p.setPen(pen)
            p.drawPoint(x, y)
                
    def setVideoData(self, videoData):
        self.data = videoData;
        self.repaint()
        
    def setRRT(self, rrtData):        
        self.rrt = rrtData
        self.repaint()
        
        
        
        
        
class DrawingMenu(QtGui.QWidget):
        
    def __init__(self, parent = None):
        QtGui.QWidget.__init__(self, parent)
        self.setMinimumWidth(160)
        self.vbox = QtGui.QVBoxLayout()
        self.setLayout(self.vbox)
        
        self.buildStepMenu()
        self.buildRobotMenu()
        self.bind_actions()      
        
        self.setVideoDataEnabled(False)  
        self.setRobotDataEnabled(False)
    
    def buildStepMenu(self):           
        self.stepVal = QtGui.QLabel()
        self.stepVal.setText('Current step: 0')
        self.stepVal.setEnabled(False)
        
        self.vbox.addWidget(self.stepVal)
        
        self.slider = QtGui.QSlider(QtCore.Qt.Horizontal)
        self.slider.setFocusPolicy(QtCore.Qt.NoFocus)        
        self.vbox.addWidget(self.slider)
        
        
        self.prev = QtGui.QPushButton('<<')
        self.next = QtGui.QPushButton('>>')
        hbox1 = QtGui.QHBoxLayout()
        hbox1.addWidget(self.prev)
        hbox1.addWidget(self.next)
        self.vbox.addLayout(hbox1)
        
    def buildRobotMenu(self):
        self.vbox.addStretch(1)
        
        self.robotCombo = QtGui.QComboBox(self)
        self.vbox.addWidget(self.robotCombo)
        
        t = QtGui.QLabel('Task:', self)
        self.task = QtGui.QLabel('', self)        
        hbox = QtGui.QHBoxLayout()
        hbox.addWidget(t)
        hbox.addWidget(self.task)
        self.vbox.addLayout(hbox)
        
        desc = QtGui.QLabel('Details:', self)
        self.taskDesc = QtGui.QLabel('', self)        
        hbox = QtGui.QHBoxLayout()
        hbox.addWidget(desc)
        hbox.addWidget(self.taskDesc)
        self.vbox.addLayout(hbox)
        
        p = QtGui.QLabel('Robot pos.:', self)
        self.robotPos = QtGui.QLabel('', self)        
        hbox = QtGui.QHBoxLayout()
        hbox.addWidget(p)
        hbox.addWidget(self.robotPos)
        self.vbox.addLayout(hbox)
        
        
        
        
        
        
    def bind_actions(self):
        self.connect(self.slider, QtCore.SIGNAL('valueChanged(int)'), 
                     self.set_step_val)
        self.connect(self.prev, QtCore.SIGNAL('clicked()'), self.slider, QtCore.SLOT('subtractStep()'))
        self.connect(self.next, QtCore.SIGNAL('clicked()'), self.slider, QtCore.SLOT('addStep()'))  
                
    def set_step_val(self, value):        
        self.stepVal.setText('Current step: %(val)5d' % {'val':value})
    
    def setVideoDataEnabled(self, enabled):
        self.slider.setEnabled(enabled)
        self.stepVal.setEnabled(enabled)
        self.prev.setEnabled(enabled)
        self.next.setEnabled(enabled)
        
    def setRobotDataEnabled(self, enabled):
        self.robotCombo.setEnabled(enabled)
        self.task.setEnabled(enabled)
        self.taskDesc.setEnabled(enabled)
        self.robotPos.setEnabled(enabled)
            
    def setRobotData(self, data):
        
        if data == None : return
        
        self.task.setText(data.task)
        self.taskDesc.setText(data.taskDesc)
        print data.robot
        pos = '%(x)2.2f %(y)2.2f %(rot)3.2f' % {'x'   : float(data.robot['x']), 
                                                          'y'   : float(data.robot['y']), 
                                                          'rot' : float(data.robot['rot'])}
        self.robotPos.setText(pos)
        
    def enableVideoData(self, length):
        """Enables video data and sets slider value to proper val"""
        self.setVideoDataEnabled(True)        
        self.slider.setMaximum(length - 1)
        
    def enableRobotData(self, robots):
        self.setRobotDataEnabled(True)
        self.robotCombo.clear()
        for i in robots:
            self.robotCombo.addItem(i)
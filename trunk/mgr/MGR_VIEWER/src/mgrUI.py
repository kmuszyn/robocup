'''
Created on 2010-01-24

@author: kamil
'''

from PyQt4 import QtGui, QtCore

class DrawingArea(QtGui.QWidget):
    
    MARGIN = 10;
    FIELD_WIDTH = 540
    FIELD_HEIGHT = 740
    
    step = []
    
    def __init__(self, parent = None):
        QtGui.QWidget.__init__(self, parent)
        self.setFixedSize(
                QtCore.QSize(self.FIELD_WIDTH + 2 * self.MARGIN,
                             self.FIELD_HEIGHT + 2 * self.MARGIN))
        
    def paintEvent(self, event):
        p = QtGui.QPainter()
        p.begin(self)    
        self.paintField(p)                   
        p.end()
            
    def paintField(self,p):
        p.setBrush(QtGui.QColor(28,140,28))
        p.drawRect(self.MARGIN, self.MARGIN, self.FIELD_WIDTH, self.FIELD_HEIGHT)
        
class MgrMenu(QtGui.QWidget):
    def __init__(self, parent = None):
        QtGui.QWidget.__init__(self, parent)
        self.setMinimumWidth(160)
        self.vbox = QtGui.QVBoxLayout()
        self.setLayout(self.vbox)
        
        self.build_step_menu()
        self.bind_actions()        
    
    def build_step_menu(self):           
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
        
    def bind_actions(self):
        self.connect(self.slider, QtCore.SIGNAL('valueChanged(int)'), 
                     self.set_step_val)
        self.connect(self.prev, QtCore.SIGNAL('clicked()'), self.slider, QtCore.SLOT('subtractStep()'))
        self.connect(self.next, QtCore.SIGNAL('clicked()'), self.slider, QtCore.SLOT('addStep()'))  
                
    def set_step_val(self, value):        
        self.stepVal.setText('Current step: %(val)5d' % {'val':value})
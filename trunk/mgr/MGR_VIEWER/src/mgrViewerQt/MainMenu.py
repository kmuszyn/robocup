'''
Created on 2010-01-17

@author: kamil
'''
from PyQt4 import QtGui, QtCore

class MainMenu(QtGui.QWidget):
    def __init__(self, parent = None):
        QtGui.QWidget.__init__(self,parent)
        
        
        '''slider for browsing steps'''
        sliderLabel = QtGui.QLabel('Time step selection');
        self.sliderValue = QtGui.QLabel('')        
        
        self.slider = QtGui.QSlider(QtCore.Qt.Horizontal, self)
        self.slider.setFocusPolicy(QtCore.Qt.NoFocus)
        self.slider.setEnabled(False)                    
        
        #self.slider.setTickPosition(QtGui.QSlider.TicksRight)
      #  self.slider.setMinimum(0)
       # self.slider.setMaximum(200)
       
        '''some labels'''
        tasklabel = QtGui.QLabel('Task: goTo')
        infoLabel = QtGui.QLabel('(2,2), rot 0')
       
        '''combo box for robot files'''
        
        combo = QtGui.QComboBox(self)
        combo.addItem('Test1')
        combo.addItem('Test2')
        combo.addItem('Test3')
        
        '''check box'''
        cb = QtGui.QCheckBox('Hide RRT')
        cb.setFocusPolicy(QtCore.Qt.NoFocus)  
        
        cb2 = QtGui.QCheckBox('Hide Speed')
        cb2.setFocusPolicy(QtCore.Qt.NoFocus)
        
        '''layout'''
        vbox = QtGui.QVBoxLayout()        
        vbox.addWidget(sliderLabel)
        vbox.addWidget(self.slider)
        vbox.addWidget(self.sliderValue)
        vbox.addStretch(1)
        vbox.addWidget(combo)     
        vbox.addWidget(tasklabel)
        vbox.addWidget(infoLabel)
        vbox.addWidget(cb)
        vbox.addWidget(cb2)      
        self.setLayout(vbox)
        
    def enableVideoData(self, maxStepTime):
        self.slider.setEnabled(True)
        self.slider.setValue(0)
        self.changeSliderValue(0)   
        self.slider.setMaximum(maxStepTime)
        
    def changeSliderValue(self, value):
        if self.slider.isEnabled():
            self.sliderValue.setText('Current: %(val)5d' % {'val':value})
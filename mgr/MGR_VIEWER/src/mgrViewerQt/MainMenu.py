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
        
        '''layout'''
        vbox = QtGui.QVBoxLayout()        
        vbox.addWidget(sliderLabel)
        vbox.addWidget(self.sliderValue)
        vbox.addWidget(self.slider)
        self.setLayout(vbox)
        
    def enableVideoData(self, maxStepTime):
        self.slider.setEnabled(True)
        self.slider.setValue(0)
        self.changeSliderValue(0)   
        self.slider.setMaximum(maxStepTime)
        
    def changeSliderValue(self, value):
        if self.slider.isEnabled():
            self.sliderValue.setText('Current: %(val)5d' % {'val':value})
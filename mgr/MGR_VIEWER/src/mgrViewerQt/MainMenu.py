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
       
        
       
        '''combo box for robot files'''
                        
        self.combo = QtGui.QComboBox(self)
        
        ''' position, rotation'''
        self.position = QtGui.QLabel("Pos:")
        self.rotation = QtGui.QLabel("Rot: ")
        
        '''AI labels'''
        self.taskName = QtGui.QLabel('Task:')
        self.taskDesc = QtGui.QLabel('Details:')
        
        
        '''check box'''
        #cb = QtGui.QCheckBox('Hide RRT')
        #cb.setFocusPolicy(QtCore.Qt.NoFocus)  
        
       # cb2 = QtGui.QCheckBox('Hide Speed')
       # cb2.setFocusPolicy(QtCore.Qt.NoFocus)
        
        '''layout'''
        vbox = QtGui.QVBoxLayout()        
        vbox.addWidget(sliderLabel)
        vbox.addWidget(self.slider)
        vbox.addWidget(self.sliderValue)
        vbox.addStretch(1)
        vbox.addWidget(self.combo)     
        vbox.addWidget(self.position)
        vbox.addWidget(self.rotation)
        vbox.addWidget(self.taskName)
        vbox.addWidget(self.taskDesc)      
        self.setLayout(vbox)
        
        self.enableModelData(False)
        
    def enableVideoData(self, maxStepTime):
        self.slider.setEnabled(True)
        self.slider.setValue(0)
        self.changeSliderValue(0)   
        self.slider.setMaximum(maxStepTime-1)
        
    def enableModelData(self, enabled):
        self.combo.setEnabled(enabled)
        self.position.setEnabled(enabled)
        self.rotation.setEnabled(enabled)
        self.taskName.setEnabled(enabled)
        self.taskDesc.setEnabled(enabled)
        
    def initModelList(self, items):
        self.combo.clear()
        for i in items:
            self.combo.addItem(i)
            
    def setModelData(self, data):
        self.modelData = data
        
    def dispModelData(self, model):
        print self.modelData
        data = self.modelData[str(model)]
        print data
        self.position = 'Pos:', data.robot['x'], data.robot['y']
        self.rotation = 'Rot:', data.robot['rot']
        
        
    def changeSliderValue(self, value):
        if self.slider.isEnabled():
            self.sliderValue.setText('Current: %(val)5d' % {'val':value})
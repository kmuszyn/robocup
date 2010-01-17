'''
Created on 2010-01-17

@author: kamil
'''
from PyQt4 import QtGui, QtCore

class MainMenu(QtGui.QWidget):
    def __init__(self, parent = None):
        QtGui.QWidget.__init__(self,parent)
        
        '''slider for browsing steps'''
        self.slider = QtGui.QSlider(QtCore.Qt.Horizontal, self)
        self.slider.setFocusPolicy(QtCore.Qt.NoFocus)
        
        '''layout'''
        vbox = QtGui.QVBoxLayout()
        vbox.addWidget(self.slider)
        
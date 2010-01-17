'''
Created on 2010-01-17

@author: kamil
'''
from PyQt4 import QtGui, QtCore

class DrawingArea(QtGui.QWidget):
    def __init__(self, parent = None):
        QtGui.QWidget.__init__(self, parent)
        self.resize(540, 740)
        
    def paintEvent(self, event):
        paint = QtGui.QPainter()
        paint.begin(self)
        paint.setPen(QtGui.QColor(168, 34, 3))
        paint.setFont(QtGui.QFont('Decorative', 10))
        paint.drawText(event.rect(), QtCore.Qt.AlignCenter, 'Abc')
        paint.end()
        
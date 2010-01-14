'''
Created on 2010-01-14

@author: kamil
'''

from PyQt4 import QtGui, QtCore

class MainWin(QtGui.QMainWindow):
    def __init__(self):
        QtGui.QMainWindow.__init__(self)
        self.resize(400,300)
        self.setWindowTitle('Test QT')
        self.center()
        
        self.statusBar().showMessage('Select file with videoData')
        
        exit = QtGui.QAction('Exit', self)
        self.connect(exit, QtCore.SIGNAL('triggered()'), QtCore.SLOT('close()'))
        
        menubar = self.menuBar()
        file = menubar.addMenu('&File')
        file.addAction(exit)
        
                        
    def center(self):
        screen = QtGui.QDesktopWidget().screenGeometry()
        size = self.geometry()
        self.move((screen.width()-size.width())/2, (screen.height()-size.height())/2)
        
    def closeEvent(self, event):
        reply = QtGui.QMessageBox.question(self, 'Message', 'Are you sure?', QtGui.QMessageBox.No, 
                                           QtGui.QMessageBox.Yes)
        if reply == QtGui.QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()
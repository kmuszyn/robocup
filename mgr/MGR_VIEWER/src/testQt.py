from PyQt4 import QtGui, QtCore
import sys

class MainWin(QtGui.QMainWindow):
    def __init__(self):
        QtGui.QMainWindow.__init__(self)
        self.resize(400,300)
        self.setWindowTitle('Test QT')
        self.center()
        
        quit = QtGui.QPushButton('Close', self)
        quit.setGeometry(10, 40, 60, 30)
        
        self.connect(quit,QtCore.SIGNAL('clicked()'), QtGui.qApp, QtCore.SLOT('quit()'))
        
        self.statusBar().showMessage('Ready')
        
        exit = QtGui.QAction('Exit', self)
        self.connect(exit, QtCore.SIGNAL('triggered()'), QtCore.SLOT('close()'))
        
        menubar = self.menuBar()
        file = menubar.addMenu('&File')
        file.addAction(exit)
        
        self.toolbar = self.addToolBar('Exit')
        self.toolbar.addAction(exit)
        
        textEdit = QtGui.QTextEdit()
        self.setCentralWidget(textEdit)
        
    def center(self):
        screen = QtGui.QDesktopWidget().screenGeometry()
        size = self.geometry()
        self.move((screen.width()-size.width())/2, (screen.height()-size.height())/2)
        
    def closeEvent(self, event):
        reply = QtGui.QMessageBox.question(self, 'Message', 'Sure?', QtGui.QMessageBox.No, 
                                           QtGui.QMessageBox.Yes)
        if reply == QtGui.QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()

if __name__== '__main__':
    print 'qt test start'
    app = QtGui.QApplication(sys.argv)
    
    w = MainWin()
    w.show()
        
    sys.exit(app.exec_())
    
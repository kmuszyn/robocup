from PyQt4 import QtGui
from mgrViewerQt import MainWin
import sys

if __name__ == '__main__':
    print 'qt test start'
    app = QtGui.QApplication(sys.argv)
    
    w = MainWin.MainWin()
    w.show()
        
    sys.exit(app.exec_())
    
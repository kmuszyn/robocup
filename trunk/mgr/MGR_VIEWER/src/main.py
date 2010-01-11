import pygtk
import gtk
from mgrViewer.videoData import VideoData
from mgrViewer.mgrUI import MgrUI 

class MainWindow:
    def main(self):
        gtk.main()
        
    def hello(self, widget, data=None):
        print 'Hello world'
        
    def delete_event(self, widget, event, data=None):
        print 'Delete event'
        gtk.main_quit()
        return False
        
    def destroy_event(self, widget, data=None):
        print 'Destroy event'
        gtk.main_quit()

    def __init__(self):
        #main window settings
        self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
        self.window.set_border_width(20)
        self.window.connect("delete_event", self.delete_event)
        self.window.connect("destroy_event", self.destroy_event)
        self.window.show()
        
        self.mainBox = gtk.HBox(False,0)
        self.mainBox.show()
        self.window.add(self.mainBox)
        
        
        self.button = gtk.Button("Hello world")
        self.button.connect("clicked", self.hello, None)
        self.button.connect_object("clicked", gtk.Widget.destroy, self.window)
        self.button.show()
        
        self.button2 = gtk.Button("Hello world")        
        self.button2.show()
        
        self.mainBox.pack_start(self.button, True, True, 0)
        self.mainBox.pack_start(self.button2, True, True, 0)
if __name__=="__main__":
    #main routine start
    print 'Start'
    #w = MainWindow()
    #w.main()
    ui = MgrUI()
    vd = VideoData('/home/kamil/workspace/robocup_mgr_client/Debug/videoServer.txt')
    
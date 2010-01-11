'''
Created on 2010-01-10

@author: kamil
'''
import gtk
import pygtk

class MgrUI:
    '''Class responsible for showing user interface'''
    #events
    def delete_event(self, widget, event, data=None):
        print 'Exit'
        gtk.main_quit()
        return False   
    
    def create_main_window(self):
        self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
        self.window.set_border_width(20)
        self.window.connect('delete_event', self.delete_event)
        self.window.show()
                   
        self.mainBox = gtk.HBox(False,0)
        self.mainBox.show()
        self.window.add(self.mainBox)
        
    def create_drawning_area(self):
        self.drawing_area = gtk.DrawingArea()
        self.drawing_area.set_size_request(300, 200)
        self.drawing_area.show()
        self.mainBox.pack_start(self.drawing_area, True, True, 0)
        
    def create_top_menu(self):
        menu_bar = gtk.MenuBar()
        gtk.Container.add(menu_bar)
        
    def create_menu(self):
        label = gtk.Label('Step: ')
        label.show()
        self.mainBox.pack_start(label, True, True, 0)
        
    def __init__(self):
        self.create_main_window()
        self.create_drawning_area()
        self.create_top_menu()
        self.create_menu()
        gtk.main()
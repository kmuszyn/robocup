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
        self.window.set_border_width(0)
        self.window.set_default_size(300,200)
        self.window.set_title('Mgr Viewer 1.0')
        self.window.connect('delete_event', self.delete_event)
        self.window.show()
        
                   
        self.winBox = gtk.VBox(False,0)
        self.winBox.show()
        self.window.add(self.winBox)        
        self.create_top_menu()
        
    def create_top_menu(self):
        menu_item = gtk.MenuItem("File")
        menu_item.show()
        menu_bar = gtk.MenuBar()
        menu_bar.show()
        menu_bar.append(menu_item)
        self.winBox.pack_start(menu_bar, False, False, 0)
        
        
    def create_drawning_area(self):        
        self.mainBox = gtk.HBox(False,0)
        self.mainBox.show()
        self.winBox.pack_start(self.mainBox)                
        
        self.drawing_area = gtk.DrawingArea()
        self.drawing_area.set_size_request(300, 200)
        self.drawing_area.modify_bg(gtk.STATE_NORMAL, gtk.gdk.color_parse("white"))
        self.drawing_area.show()
        self.mainBox.pack_start(self.drawing_area, True, True, 0)
        
    
        
    def create_menu(self):
        self.menuBox = gtk.VBox(False,0)
        self.menuBox.show()
        self.mainBox.pack_start(self.menuBox)
              
        label = gtk.Label('Step: ')
        label.show()        
        self.menuBox.pack_start(label, True, True, 0)
        
    def __init__(self):
        self.create_main_window()
        self.create_drawning_area()        
        self.create_menu()
        gtk.main()
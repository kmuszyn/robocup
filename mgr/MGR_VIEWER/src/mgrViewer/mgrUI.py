'''
Created on 2010-01-10

@author: kamil
'''
import gtk
import pygtk
from mgrViewer.videoData import VideoData

class MgrUI:
    '''Class responsible for showing user interface'''
    #events
    def delete_event(self, widget, event, data=None):
        print 'Exit'
        gtk.main_quit()
        return False   
    
    def quit_event(self, action):
        print 'Exit'
        gtk.main_quit()
        
    def load_vd_event(self, action):
        print 'Load VideoData'
        chooser = gtk.FileChooserDialog(title=None,action=gtk.FILE_CHOOSER_ACTION_OPEN,
                                  buttons=(gtk.STOCK_CANCEL,gtk.RESPONSE_CANCEL,gtk.STOCK_OPEN,gtk.RESPONSE_OK))
        
        filter = gtk.FileFilter()
        filter.add_pattern("*.txt")
        filter.set_name("txt files")
        chooser.add_filter(filter)
        chooser.set_current_folder('/home/kamil/workspace/robocup_mgr_client/Debug')        
        
        response = chooser.run()
        if response == gtk.RESPONSE_OK:
            self.vd = []
            print chooser.get_filename()
            self.vd = VideoData(chooser.get_filename())
            print 'Loaded',len(self.vd.steps),'steps'
            self.curr_step.set_sensitive(True)            
            self.curr_step.set_range(0,len(self.vd.steps) - 1)
            self.draw_step()
            
        chooser.destroy()
        
    def draw_step(self, action = None):
        tmp = self.vd.steps[int(self.curr_step.get_value())]
        drawable = self.drawing_area.window
        gc = drawable.new_gc(foreground=None, background=None, font=None, 
                     function=-1, fill=-1, tile=None,
                     stipple=None, clip_mask=None, subwindow_mode=-1,
                     ts_x_origin=-1, ts_y_origin=-1, clip_x_origin=-1,
                     clip_y_origin=-1, graphics_exposures=-1,
                     line_width=-1, line_style=-1, cap_style=-1,
                     join_style=-1)
        
        for i in tmp:
            print i.x, i.y, i.radius
            print i.x * 100, i.y * 100, int(round(i.radius * 200, 0))
            x = int(round(i.x * 100,0))
            y = int(round(i.y * 100,0))
            d = int(round(i.radius * 200, 0))
            drawable.draw_arc(gc, False, x, y, d, d , 0, 360*64)
        
    
    def create_main_window(self):
        self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
        self.window.set_border_width(0)
        self.window.set_default_size(1024,-1)
        self.window.set_title('Mgr Viewer 1.0')
        self.window.connect('delete_event', self.delete_event)
        self.window.show()
        
                   
        self.winBox = gtk.VBox(False,0)
        self.winBox.show()
        self.window.add(self.winBox)        
        self.create_top_menu()
        
    def create_top_menu(self):       
        uimanager = gtk.UIManager()
        accelgroup = uimanager.get_accel_group()
        self.window.add_accel_group(accelgroup)
        
        actiongroup = gtk.ActionGroup('mgrUI')       
        actiongroup.add_actions([('Quit',None,'_Quit','<control>q',None, self.quit_event),
                                ('File',None,'_File', '<control>f'),
                                ('LoadVideoData',None,'Load _VideoData', '<control>v', None, self.load_vd_event)])
        uimanager.insert_action_group(actiongroup,0)
        
        ui = '''
        <ui>
            <menubar name = "MenuBar">
                <menu action="File">
                    <menuitem action="LoadVideoData" />
                    <menuitem action="Quit"/>                    
                </menu>                
            </menubar>
        </ui>
        '''
        
        uimanager.add_ui_from_string(ui)
        self.winBox.pack_start(uimanager.get_widget('/MenuBar'), False)
        
        self.window.show_all()
        
    def create_drawning_area(self):        
        self.mainBox = gtk.HBox(False,0)
        self.mainBox.show()
        self.winBox.pack_start(self.mainBox)                
        
        self.drawing_area = gtk.DrawingArea()
        self.drawing_area.set_size_request(540, 740)
        self.drawing_area.modify_bg(gtk.STATE_NORMAL, gtk.gdk.color_parse("white"))
        self.drawing_area.show()
        self.mainBox.pack_start(self.drawing_area, True, True, 0)
        
    
        
    def create_menu(self):
        self.menuBox = gtk.VBox(False,0)
        self.menuBox.show()
        self.mainBox.pack_start(self.menuBox)
              
        label = gtk.Label('Step: ')
        label.show()        
        self.menuBox.pack_start(label,False)
        
        self.curr_step = gtk.HScale()
        self.curr_step.set_draw_value(True)
        self.curr_step.set_digits(0)
        self.curr_step.set_value_pos(gtk.POS_RIGHT)
        self.curr_step.show()        
        self.curr_step.set_sensitive(False)
        self.curr_step.connect('value_changed', self.draw_step) 
        
        self.menuBox.pack_start(self.curr_step,False)
        
    def __init__(self):
        self.create_main_window()
        self.create_drawning_area()        
        self.create_menu()
        gtk.main()
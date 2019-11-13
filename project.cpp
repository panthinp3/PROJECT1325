
#include "project.h"
#include <gtkmm.h>

using namespace std;
using namespace Gtk;

main_window::main_window()
{
    set_title("User Login");
    set_border_width(30);
    resize(450,600);
    set_position(Gtk::WIN_POS_CENTER_ALWAYS);
    box.set_spacing(10);
    
    l3.set_markup("<span style=\"italic\">SPLIT!</span>");
    box.pack_start(l3);
    
    gif_i.set("src/money.gif");
    box.pack_start(gif_i);
    
    l1.set_markup("<big>Enter Name:</big>");
    box.pack_start(l1);
    
    e1.set_placeholder_text("eg: Pramit");
    e1.set_max_length(15);
    box.pack_start(e1);
    
    l2.set_markup("<big>Enter Password:</big>");
    box.pack_start(l2);
    
    e2.set_placeholder_text("***********");
    e2.set_visibility(FALSE);
    e2.set_max_length(20);
    box.pack_start(e2);
    
    checkbutton.set_label("Visible");
    box.pack_start(checkbutton);
    checkbutton.signal_toggled().connect(sigc::mem_fun(*this,&main_window::toggle_checkbox));
    checkbutton.set_active(true);
    
    b1.add_pixlabel("src/login.png","Login",0.5,0.5);
    b1.signal_clicked().connect(sigc::mem_fun(*this, &main_window::login_click));
    box.pack_start(b1);
    
    b2.add_pixlabel("src/signup.png","Sign Up",0.5,0.5);
    b2.signal_clicked().connect(sigc::mem_fun(*this, &main_window::signup_click));
    box.pack_start(b2);
    
    b3.add_pixlabel("src/close.png","Close",0.5,0.5);
    b3.signal_clicked().connect(sigc::mem_fun(*this, &main_window::close_click));
    box.pack_start(b3);
    
    box.show_all();
    add(box);
}

void main_window::login_click(){}
void main_window::signup_click(){}
void main_window::close_click(){}

main_window::~main_window(){}

void main_window::toggle_checkbox()
{
    e2.set_visibility(checkbutton.get_active());
}

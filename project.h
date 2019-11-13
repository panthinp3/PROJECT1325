#ifndef PROJECT_HEAD
#define PROJECT_HEAD

#include "gtkmm.h"

using namespace std;
using namespace Gtk;


class main_window: public Window{
public:
    main_window();
    virtual ~main_window();
protected:
    Button b1,b2,b3;  //b1=login, b2=signup, b3=close
    Entry e1,e2;
    Label l1,l2,l3;      //enter name and pwd and SPLIT!
    Image gif_i;        //gif file
    VBox box;
    CheckButton checkbutton;
    
    
    //signal handlers
    void login_click();
    void signup_click();
    void close_click();
    void toggle_checkbox();
};





#endif

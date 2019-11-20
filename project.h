#ifndef PROJECT_HEAD
#define PROJECT_HEAD

#include "gtkmm.h"
#include <string.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>


using namespace std;
using namespace Gtk;


extern string file_person;
extern string file_details;

class person{
    string pwd;
public:
    string name;
    string grp_name;
    int b;   //b=1 means he/she has a group
    float tot_exp_grp;
    float tot_exp_mem;
    float tot_owe;
    
    string get_pwd();
    void set_pwd(string new_pwd);
    virtual ~person();
};

class details{
public:
    string name;
    string vendor;
    float expense;
    virtual ~details();
};


class group{
public:
    string name;
    float tot_exp;  //may not be needed
    vector <person> members;
    vector <details> details_list;
    
    group();
    void update_person(string file_person);
    void update_details(string file_details);
    void sign_up();
    void split_calc();
    void add_expense(string vendor, float amt);
    virtual ~group();
};


class main_window: public Window{
public:
    main_window();
    group g;
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

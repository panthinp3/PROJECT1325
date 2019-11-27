#ifndef PROJECT_HEAD
#define PROJECT_HEAD

#include "gtkmm.h"
#include <string.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <map>


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

class signup_window: public Window{

protected:
	vector <person>* members;
	Button signup_button, close_button;
	Entry username_entry, pass_entry, repass_entry;
	Label username_label, pass_label, repass_label;
	VBox box;
	CheckButton checkbutton;

	void signup_click();
	void close_click();
	void toggle_checkbox();
public:
    signup_window(vector <person>* m);
    virtual ~signup_window();

};

class split_window:public Window{
public:
  split_window(vector <person>* m,string username, vector<details>*ptr);
  virtual ~split_window();
    //group g;
    
protected:
  string user_name;
  vector <person>* members;
    vector <details>* d;
  Label label1,label2,label3;
  Image gif_i;
  Button button1,button2,button3,button4;
  VBox vbox;
  HBox hbox1,hbox2,hbox3;

  void add_expense();
  void pay();
  void show_details();
  void log_out();
};

class pay_window:public Window{
    std::vector<Gtk::RadioButton*> all_buttons; 
public:
    pay_window( vector <person*> membersof_thisgroup,string username,std::map<std::string,int> owe_info);
    
    void make_buttons(std::map<std::string,int> owe_info);
protected:
    vector <person*> members;
    void on_button_clicked();
    Gtk::VBox box1, box2, box3;
    Gtk::Separator line;
    Gtk::Button Close,pay;
};


class new_group_window:public Window{
public:
  new_group_window(vector <person>* m, string gname, int memnum, string name);
  virtual ~new_group_window();

  void add_clicked();
  void cancel_clicked();

protected:
  string creator_name, group_name;
  vector <person>* members;
  vector <string> entry_list;
  Image gif_m;
  Label label1;
  vector <shared_ptr<Entry>> entries;
  Button button1, button2;
  VBox vbox;

};

#endif

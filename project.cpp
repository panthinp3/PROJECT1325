
#include "project.h"
#include <gtkmm.h>

using namespace std;
using namespace Gtk;


string file_person="registered_members.txt";
string file_details="details.txt";

group::group()
{
    string line;
    string temp;
    ifstream inFile;
    inFile.open(file_person);
    if(!inFile.is_open())
    {
        cout<<"Could't open member file. exiting..."<<endl;
        exit(1);
    }
    while(!inFile.eof())
    {
        person p;
        getline(inFile,line);
        stringstream ss(line);
        getline(ss, p.name, ',');
        getline(ss, temp, ',');
        p.set_pwd(temp);
        getline(ss, temp, ',');
        p.b=stoi(temp);
        getline(ss, p.grp_name, ',');
        getline(ss, temp, ',');
        p.tot_exp_grp=stof(temp);
        getline(ss, temp, ',');
        p.tot_exp_mem=stof(temp);
        getline(ss, temp);
        p.tot_owe=stof(temp);
        members.push_back(p);
    }
    inFile.close();
    
    ifstream inFile2;
    inFile2.open(file_details);
    if(!inFile2.is_open())
    {
        cout<<"Could't open details file. exiting..."<<endl;
        exit(1);
    }
    while(!inFile2.eof())
    {
        details d;
        getline(inFile2,line);
        stringstream ss(line);
        getline(ss,d.name,',');
        getline(ss,d.vendor,',');
        getline(ss,temp);
        d.expense=stof(temp);
        details_list.push_back(d);
    }
    inFile2.close();
    cout<<"this: "<<members[0].name<<endl;
    cout<<"this: "<<details_list[0].vendor<<endl;
}


string person::get_pwd()
{
    return pwd;
}

void person::set_pwd(string new_pwd)
{
    pwd=new_pwd;
}


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


void main_window::toggle_checkbox()
{
    e2.set_visibility(checkbutton.get_active());
}

main_window::~main_window(){}
group::~group(){}
details::~details(){}
person::~person(){}




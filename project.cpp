
#include "project.h"
#include <gtkmm.h>

using namespace std;
using namespace Gtk;


string file_person="src/registered_members.txt";
string file_details="src/details.txt";

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

signup_window::signup_window(vector <person> &members){
    set_title("User Sign Up");
    set_border_width(30);
    resize(400,600);
    set_position(Gtk::WIN_POS_CENTER_ALWAYS);
    box.set_spacing(10);

    username_label.set_markup("<big>Enter name:</big>");
    box.pack_start(username_label);

    username_entry.set_placeholder_text("eg: Donald Trump");
    username_entry.set_max_length(15);
    username_entry.select_region(0, username_entry.get_text_length());
    box.pack_start(username_entry);

    pass_label.set_markup("<big>Enter your new password:</big>");
    box.pack_start(pass_label);

    pass_entry.set_placeholder_text("***********");
    pass_entry.set_visibility(FALSE);
    pass_entry.set_max_length(20);
    pass_entry.select_region(0, pass_entry.get_text_length());
    box.pack_start(pass_entry);

    repass_label.set_markup("<big>Re-enter your new password:</big>");
    box.pack_start(repass_label);


    repass_entry.set_placeholder_text("***********");
    repass_entry.set_visibility(FALSE);
    repass_entry.set_max_length(20);
    repass_entry.select_region(0, repass_entry.get_text_length());
    box.pack_start(repass_entry);

    checkbutton.set_label("Visible");
    box.pack_start(checkbutton);
    checkbutton.signal_toggled().connect(sigc::mem_fun(*this,&signup_window::toggle_checkbox));
    checkbutton.set_active(false);

    signup_button.add_pixlabel("src/signup.png","Sign Up",0.5,0.5);
    signup_button.signal_clicked().connect(sigc::mem_fun(*this, &signup_window::signup_click));
    box.pack_start(signup_button);
    
    close_button.add_pixlabel("src/close.png","Close",0.5,0.5);
    close_button.signal_clicked().connect(sigc::mem_fun(*this, &signup_window::close_click));
    box.pack_start(close_button);
    
    box.show_all();
    add(box);

}


signup_window::~signup_window(){}


void signup_window::toggle_checkbox(){
    pass_entry.set_visibility(checkbutton.get_active());
    repass_entry.set_visibility(checkbutton.get_active());
}
    
void signup_window::signup_click(){
    string username, pass, repass;

    username = username_entry.get_text();
    pass = pass_entry.get_text();
    repass = repass_entry.get_text();

    if(pass==repass){
        person p;
        p.name = username;
        p.set_pwd(pass);
        p.b = 0;
        p.tot_exp_grp = 0.0;
        p.tot_exp_mem = 0.0;
        p.tot_owe = 0.0;

        members.push_back(p);   
    }
    else{
        MessageDialog dialog(*this, "Passwords doesn't match! Enter Again.", false, Gtk::MESSAGE_INFO);
        dialog.run();
    }
}

void signup_window::close_click(){
    hide();
}



void main_window::login_click(){}

void main_window::signup_click(){
    signup_window window(members);
    Main::run(window);
}

void main_window::close_click()
{
    ofstream members_update;
    ofstream details_list_update;
    
    members_update.open(file_person);
    if (!members_update.is_open())
    {
        stringstream message;
        message << "Unable to open file \""<<file_person<<"\"";
        Gtk::MessageDialog d(*this, message.str(),false,Gtk::MESSAGE_INFO);
        d.run();
        std::exit(1);
    }
    
    string comma = ",";
    
    for(int i=0;i<g.members.size();i++)    //fix this once group object is created
    {
        members_update<<g.members[i].name<<comma<<g.members[i].get_pwd()<<comma<<g.members[i].b<<comma<<g.members[i].grp_name<<comma<<g.members[i].tot_exp_grp<<comma<<g.members[i].tot_exp_mem<<comma<<g.members[i].tot_owe<<endl;
    }
    
    details_list_update.open(file_details);     //fix this once group object is created
    if (!details_list_update.is_open())
    {
        stringstream message;
        message << "Unable to open file \""<<file_details<<"\"";
        Gtk::MessageDialog d(*this, message.str(),false,Gtk::MESSAGE_INFO);
        d.run();
        std::exit(1);
    }
    
    for(int i=0;i<g.details_list.size();i++)
    {
        details_list_update<<g.details_list[i].name<<comma<<g.details_list[i].vendor<<comma<<g.details_list[i].expense<<endl;
    }
    
    std::cout<<"Everything updated closing file"<<endl;        //delete if not wanted
    members_update.close();
    details_list_update.close();
    
    hide();
}


void main_window::toggle_checkbox()
{
    e2.set_visibility(checkbutton.get_active());
}

main_window::~main_window(){}
group::~group(){}
details::~details(){}
person::~person(){}




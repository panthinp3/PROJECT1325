
#include "project.h"
#include <gtkmm.h>
#include <map>

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
        if(p.name!="")
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
        if(d.name!="")
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

signup_window::signup_window(vector <person>* m){
    
    members=m;
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
        p.grp_name="*";
        p.tot_exp_grp = 0.0;
        p.tot_exp_mem = 0.0;
        p.tot_owe = 0.0;
        members->push_back(p);
        hide();
        MessageDialog dialog(*this,username + " signed up successfully", false, Gtk::MESSAGE_INFO);
        
        dialog.run();
        
        //cout<<"vector: "<<members[0].name<<endl;
    }
    else{
        MessageDialog dialog(*this, "Passwords doesn't match! Enter Again.", false, Gtk::MESSAGE_INFO);
        dialog.run();
    }
}

void signup_window::close_click(){
    hide();
}



//void main_window::login_click(){}

void main_window::signup_click(){
    signup_window window(&(g.members));
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





//nabin
void main_window::login_click()
{
  //bool ans=false;
  int check;
  string name=e1.get_text();
  //transform(name.begin(),name.end(),name.begin(),::tolower);
  string password=e2.get_text();

    for(int i=0; i<g.members.size();i++)
    {
      cout<<g.members[i].name<<endl;
      if(name=="" && password=="")
      {
        check=3;
        break;
      }

      if(name==g.members[i].name && password==g.members[i].get_pwd() && g.members[i].b==1)
      {
        check=1;
        break;
      }
      else if(name==g.members[i].name && password==g.members[i].get_pwd()&& g.members[i].b==0)
      {
        check=2;
        break;
      }
      else
      {
        check=3;
      }
    }

    if(check==1)
    {
        //hide();
        split_window sp(&(g.members),name, &g.details_list);
        Gtk::Main::run(sp);
    }
    else if(check==2)
    {
      MessageDialog di(*this, "You do not have a group. Please create a new one!.",false,MESSAGE_INFO);
        di.run();
        di.hide();  
        Window x;
        Dialog *dialog = new Dialog();
        dialog->set_transient_for(x);
        dialog->set_title("Create New Group");
        dialog->set_size_request(400,200);
        dialog->set_border_width(10);

        Label *label1 = new Label("Enter group name:");
        dialog->get_content_area()->pack_start(*label1);
        label1->show();

        Entry *entry1 = new Entry();
        entry1->set_placeholder_text("eg: Apartment 134");
        entry1->set_max_length(20);
        entry1->show();
        dialog->get_content_area()->pack_start(*entry1);


        Label *label2 = new Label("Enter number of members:");
        dialog->get_content_area()->pack_start(*label2);
        label2->show();

        Entry *entry2 = new Entry();
        entry2->set_placeholder_text("eg: 5 ");
        entry2->set_max_length(3);
        entry2->show();
        dialog->get_content_area()->pack_start(*entry2);

        dialog->add_button("Ok", 0);
        dialog->add_button("Cancel", 1);

        int result = dialog->run();

        if(result == 0){
            string gname = entry1->get_text();
            int memnum = stoi(entry2->get_text());
            
            new_group_window w(&(g.members), gname, memnum, name);
            Gtk::Main::run(w);
        }

        dialog->close();

        delete dialog;
        delete label1;
        delete entry1;
        delete label2;
        delete entry2;
    }
    else if(check==3)
    {
      MessageDialog dialog(*this, "User not found. Please try again.",false,MESSAGE_WARNING);
      dialog.run();
      dialog.hide();
      //main_window m1;
      //Gtk::Main::run(m1);
    }
}


split_window::split_window(vector <person>* m,string username, vector<details>*ptr)
{
  //hide();
    
    user_name=username;
    members=m;
    d=ptr;
  set_title("Split App");
  set_border_width(10);
  resize(450,600);
  set_position(Gtk::WIN_POS_CENTER_ALWAYS);
  label3.set_markup("<span style=\"italic\">SPLIT!</span>");
  vbox.pack_start(label3);

  gif_i.set("src/money.gif");
  vbox.pack_start(gif_i);
  label1.set_markup("\n\n<big>Total expenses of the group: $</big>\n\n");
  hbox1.pack_start(label1);

  label2.set_markup("\n\n<big>You owe: $</big>\n\n");
  hbox1.pack_start(label2);

  vbox.pack_start(hbox1);

  button1.add_pixlabel("src/plus.png","Add new expense",0.5,0.5);
  button1.signal_clicked().connect(sigc::mem_fun(*this, &split_window::add_expense));
  vbox.pack_start(button1);

  button2.add_pixlabel("src/pay.png","Pay",0.5,0.5);
  button2.signal_clicked().connect(sigc::mem_fun(*this,&split_window::pay));
  vbox.pack_start(button2);

  button3.add_pixlabel("src/details.jpg","Show Details",0.5,0.5);
  button3.signal_clicked().connect(sigc::mem_fun(*this, &split_window::show_details));
  vbox.pack_start(button3);

  button4.add_pixlabel("src/out.jpeg","Logout",0.5,0.5);
  button4.signal_clicked().connect(sigc::mem_fun(*this, &split_window::log_out));
  vbox.pack_start(button4);

  vbox.show_all();
  add(vbox);
}

void split_window::add_expense()
{
    Window w;
    Dialog* dialog= new Dialog();
    dialog->set_transient_for(w);
    dialog->set_title("Expense Details");
    dialog->resize(200,200);
    Label* label = new Gtk::Label("Enter vendor's name: ");
    dialog->get_vbox()->pack_start(*label);
    label->show();
    Entry* entry = new Entry();
    dialog->get_vbox()->pack_start(*entry);
    entry->show();
    Label* label2 = new Gtk::Label("Enter amount spent: ");
    dialog->get_vbox()->pack_start(*label2);
    label2->show();
    Entry* entry2 = new Entry();
    dialog->get_vbox()->pack_start(*entry2);
    entry2->show();
    dialog->add_button("Ok",1);
    dialog->add_button("Cancel",0);
    
    int result=dialog->run();
    if(result==0)
    {
        delete(dialog);
    }
    else
    {
        details temp;
        temp.name=user_name;
        temp.vendor=entry->get_text();
        temp.expense=stof(entry2->get_text());
        d->push_back(temp);
        
        int i;
        for(i=0; i<(*members).size(); i++)
        {
            if(members->at(i).name == user_name)
            {
                members->at(i).tot_exp_mem += stof(entry2->get_text());
            }
             members->at(i).tot_exp_grp += stof(entry2->get_text());
        }
        delete (dialog);
    }
}
void split_window::pay()
{
    string group_name;
    int index;
    for(int i=0;i<members->size();i++)
    {
        if(members->at(i).name==user_name)
        {
            group_name=members->at(i).grp_name;
            index=i;
        }
    }
    
    vector <person*> membersof_thisgroup;       //holds the members of a certain group name
    person* p;
    
    for(int i=0;i<members->size();i++)
    {
        if(members->at(i).grp_name==group_name)
        {
            p=&members->at(i);
            membersof_thisgroup.push_back(p);
        }
    }
    
    std::map<std::string,int> owe_info; //hold name and how much you owe them("+" means somebody owes you)
    //"-" mean you owe them
    
    float user_exp;
    for(int i=0;i<membersof_thisgroup.size();i++)
    {
        if(membersof_thisgroup[i]->name==user_name)
        {
            user_exp = membersof_thisgroup[i]->tot_exp_mem;
            break;
        }
    }
    
    int group_size = membersof_thisgroup.size();
    
    for(int i=0;i<membersof_thisgroup.size();i++)
    {
        float owe_amt;
        if(membersof_thisgroup[i]->name!=user_name)
        {
            owe_amt = (user_exp-membersof_thisgroup[i]->tot_exp_mem)/group_size;
            members->at(index).tot_owe+=owe_amt;
            owe_info.insert({membersof_thisgroup[i]->name,owe_amt});
        }
    }
    
    pay_window a(membersof_thisgroup,user_name,owe_info);
    Gtk::Main::run(a);
    
}

void split_window::show_details()
{
    Window w;
    Dialog *dialog =new Dialog;
    dialog->set_transient_for(w);
    dialog->set_border_width(50);
    dialog->set_size_request(150,150);
    dialog->set_title("Details");

    for(int i=0;i<(*d).size();i++)
    {
        float f=d->at(i).expense;
        string paid=to_string(f);
        //string paid=to_string(g.details_list[i].expense);
        Label *label1=new Label(d->at(i).name+" paid $"+paid+" at "+d->at(i).vendor);
        dialog->get_content_area()->pack_start(*label1);
        label1->show();
    }

    dialog->add_button("OK",0);
    int i=dialog->run();
    if(i==0)
    {
        dialog->close();
    }
}

void split_window::log_out()
{
  hide();
  //main_window m1;
  //Gtk::Main::run(m1);
}
split_window::~split_window(){}

void pay_window::make_buttons(std::map<std::string,int> owe_info)
{
    
    
    for(std::map<std::string, int>::iterator itr = owe_info.begin(); itr != owe_info.end(); itr++)
    {
        stringstream ss;
        
        if(itr->second>0)
        {
            ss<<itr->first<<" owes you $"<<itr->second;
            
        }
        if(itr->second<=0)
        {
            ss<<"You owe "<<itr->first<< "$"<<-itr->second;
            
        }
        string output;
        output = ss.str();
        
        //cout<<output<<endl;
        
        Gtk::RadioButton* b=new Gtk::RadioButton(output);
        all_buttons.push_back(b);
        
    }
    
    
        Gtk::RadioButton* b=new Gtk::RadioButton();
        all_buttons.push_back(b);
}

pay_window::pay_window( vector <person*> membersof_thisgroup,string username,std::map<std::string,int> owe_info):Close("close"),pay("Pay")
{
    members= membersof_thisgroup;
    set_title("Pay");
    set_border_width(0);
    make_buttons(owe_info);
    cout<<"hello frm the other side"<<endl;
    
    for(int i=1;i<members.size();i++)
    {
        all_buttons[i]->join_group(*all_buttons[0]);
    }
    
    add(box1);
    box1.pack_start(box2);
    box1.pack_start(line);
    box1.pack_start(box3);
    
    for (int i=0;i<members.size();i++)
    {
        box2.pack_start(*all_buttons[i]);
    }
    box3.pack_start(pay);
    box3.pack_start(Close);
    
    Close.set_can_default();
    Close.grab_default();
    
    Close.signal_clicked().connect(sigc::mem_fun(*this, &pay_window::close));
    
    show_all_children();
}

new_group_window::new_group_window(vector <person>* m, string gname, int memnum, string name)
{   group_name = gname;
    creator_name = name;
    members = m;
    set_title("New Group Information");
    set_size_request(400, memnum*50+150);
    set_border_width(10);
    add(vbox);

    label1.set_text("Enter group members name:");
    vbox.pack_start(label1);

    for (int i = 0; i < memnum; i++){
        shared_ptr<Entry> e = make_shared<Entry>();
        e->set_placeholder_text("eg: Ben");
        entries.push_back(e);
    }

    for(int i = 0; i < entries.size(); i++){
        vbox.pack_start(*entries.at(i));
    }

    button1.add_label("Add");
    button1.signal_clicked().connect(sigc::mem_fun(*this, &new_group_window::add_clicked));
    vbox.pack_start(button1);

    button2.add_label("Cancel");
    button2.signal_clicked().connect(sigc::mem_fun(*this, &new_group_window::cancel_clicked));
    vbox.pack_start(button2);

    vbox.show_all();    
}

new_group_window::~new_group_window(){

}

void new_group_window::add_clicked(){
    bool valid = true;
    bool found = false;

    

    for(int i = 0; i < entries.size(); i++){
        entry_list.push_back(entries.at(i)->get_text());
        if(entry_list.at(i) == creator_name){
            entry_list.clear();
            valid = false;
            MessageDialog d1(*this, "Creator of the group cannot be added to a group!",false,MESSAGE_WARNING);
            d1.run();
            break;
        }
    }


    if(valid){
        for(int i = 0; i < entry_list.size(); i++){
        found = false;
            for(int j = 0; j < members->size(); j++){
                if(entry_list.at(i) == members->at(j).name){
                    found = true;
                    break;
                }

            }
            if(!found){
                entry_list.clear();
                MessageDialog d(*this, "Non registered members cannot be added to a group!",false,MESSAGE_WARNING);
                d.run();
                break;
            }
        
        }

        if(found){

            for(int i = 0; i < members->size(); i++){
                if (members->at(i).name == creator_name){
                    members->at(i).b = 1;
                    members->at(i).grp_name = group_name;
                    break;
                }
            }



            for(int i = 0; i < entry_list.size(); i++){
                for(int j = 0; j < members->size(); j++){
                    if(entry_list.at(i) == members->at(j).name){
                        members->at(j).b = 1;
                        members->at(j).grp_name = group_name;
                        break;
                    }
                }
            }
            MessageDialog d2(*this, "Members added to the group!",false,MESSAGE_INFO);
            d2.run();
            hide();
        }       

    }

}

void new_group_window::cancel_clicked(){
    hide();
}

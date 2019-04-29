
#include "connection.h"
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include "misc.h"
Connection::Connection(){
    // I'm already done! 
    set_connection();
}


Connection::~Connection(){
    delete birthdate;
    delete email;
    delete phone;

    /*while(!myfriends.empty())
    {
        delete myfriends.back();
        myfriends.pop_back();
    } */
    // TODO: Complete me!
}


Connection::Connection(string fname, string lname, \
        string bdate, string email, string phone){
    

    this->f_name = fname;
    this->l_name = lname;
    this->birthdate = new Date(bdate);
    
    string email_type = email.substr(1, email.find(')')-1);
    string email_formatted = email.substr(email.find(' ')+1);

    string phone_type = phone.substr(1, phone.find(')')-1);
    string phone_formatted = phone.substr(phone.find(' ')+1);

    this -> email = new Email(email_type, email_formatted);
    this -> phone = new Phone(phone_type, phone_formatted);
    // TODO: Complete this method!
    // phone and email strings are in full version
}


Connection::Connection(string filename){
    set_connection(filename);
    // TODO: Complete this method!
}


void Connection::set_connection(){
    // prompts for the information of the user
    // first/last name can have spaces!
    // date format must be "M/D/YYYY"
    // We are sure user enters info in correct format.
    // TODO: complete this method!
    string temp;
    string type_email;
    string type_phone;
    string e_address;
    string p_num;
    
    cout << "First Name: ";
    std::getline (std::cin, f_name);
    //cin >> f_name;
	
    cout << "Last Name: ";
    std::getline (std::cin, l_name);
    //cin >> l_name;
    // code here

    cout << "Birthdate (M/D/YYYY): ";
    std::getline (std::cin, temp);
    //cin >> temp;// code here
    birthdate = new Date(temp); 

    cout << "Type of email address: ";
    std::getline (std::cin, type_email);
    //cin >> type_email;// code here
    
    cout << "Email address: ";
    std::getline (std::cin, e_address);
    //cin >> e_address;// code here

    email = new Email(type_email, e_address);

    cout << "Type of phone number: ";
    // code here
    cin >> type_phone;
    
    cout << "Phone number: ";
    cin >> p_num;

    phone = new Phone(type_phone, p_num);
    // code here
    // code here
}


void Connection::set_connection(string filename){
    
    ifstream infile; 
    string fname_temp;
    infile.open(filename.c_str()); 
    getline(infile, this->l_name, ',');
    getline(infile, f_name);
    
    this->f_name = f_name.substr(1);
    //infile >> f_name;
    
    //cout<< l_name <<endl;
    //cout<< f_name << endl;
    
    string temp_bdate;
    getline(infile, temp_bdate);
    birthdate = new Date(temp_bdate);


    string email_full; 
    getline(infile, email_full); //read in full email and split

    string email_type = email_full.substr(1, email_full.find(')')-1);
    string email_formatted = email_full.substr(email_full.find(' ') +1);

    //cout << email_type <<endl;
    //cout << email_formatted << endl;

    email = new Email(email_type, email_formatted);

    string phone_full;
     getline(infile, phone_full);//continue here!

     string phone_type = phone_full.substr(1, phone_full.find(')')-1);
     string phone_formatted = phone_full.substr(phone_full.find(' ')+1);

     phone = new Phone(phone_type, phone_formatted);
    // TODO: Complete this method!
    // Look at connection_template files as examples.     
    // Phone number in files can have '-' or not.
}


bool Connection::operator==(const Connection& rhs){
    if (f_name == rhs.f_name && l_name == rhs.l_name)
        return true;
    else
        return false;
    // TODO: Complete this method!
    // Note: Difference to Lab is that from now on the combination of fname-lname is unique for any connection
}


bool Connection::operator!=(const Connection& rhs){ 
    return !(*this == rhs);
    // TODO: Complete this method!
}


void Connection::print_connection(){
    // Already implemented for you! Do not change!
	cout << l_name <<", " << f_name << endl;
	birthdate->print_date("Month D, YYYY");
    email->print();
    phone->print();


    for (int i =0; i < myfriends.size(); i++) {
        string fname = myfriends[i] -> f_name;
        string lname = myfriends[i] -> l_name;
        cout << codeName(fname, lname) << endl;

    }



}

void Connection::makeFriend(Connection* newFriend) {


myfriends.push_back(newFriend);
//string fname = newFriend -> f_name;
//string lname = newFriend -> l_name;
//string code = codeName(fname, lname);
//mycodes.push_back(code);    


} 


void Connection::write_connection(ofstream& fileName) {


    fileName << l_name << ", " << f_name << endl;
    fileName << birthdate -> get_date() << endl;
    fileName << email -> get_contact() << endl;
    fileName << phone -> get_contact() <<endl; 
    

    for (int i =0; i < myfriends.size(); i++) {
        string fname = myfriends[i] -> f_name;
        string lname = myfriends[i] -> l_name;
        fileName << codeName(fname, lname) << endl;

    }

    fileName << "------------------" << endl;
}
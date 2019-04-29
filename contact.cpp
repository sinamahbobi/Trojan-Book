
#include "contact.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream> 
#include <algorithm>
// TODO: Add needed libraries! Done
using namespace std;

Email::Email(string type, string email_addr){
    // TODO: Complete me!
    this -> type = type;
    this -> email_addr = email_addr;
}


void Email::set_contact(){
    // TODO: Do not change the prompts!
	
    cout << "Enter the type of email address: ";
    string type;
    cin >> type;
    this -> type = type;
    // some code here Done
    cout << "Enter email address: ";
    string email_addr;
    cin >> email_addr;
    this -> email_addr = email_addr;
    // some code here Done
}


string Email::get_contact(string style){
    // Note: We have default argument in declaration and not in definition!
    if (style=="full")
	    return "(" + type + ") " + email_addr;
    else 
        return email_addr;
}


void Email::print(){
    // Note: get_contact is called with default argument
	cout << get_contact() << endl;
}


Phone::Phone(string type, string phone_num){
    // TODO: It is possible that num includes "-" or not, manage it!
    // TODO: Complete this method!
    // Note: We don't want to use C++11! stol is not valid!
    // The code has been covered in the discussion session

    //Done
    this -> type = type;
    phone_num.erase(remove(phone_num.begin(), phone_num.end(), '-'), phone_num.end());
    stringstream phone;
    long int num;
    phone << phone_num;
    phone >> num;
    this -> phone_num = num;
    //cout << phone_num <<endl;
}


void Phone::set_contact(){
    // TODO: Complete this method
    // Use the same prompts as given!
	cout <<"Enter the type of phone number: ";
    string type;
    cin >> type;
    this -> type = type;
	cout << "Enter the phone number: ";
    string phone_num;
    cin >> phone_num;
    
    phone_num.erase(remove(phone_num.begin(), phone_num.end(), '-'), phone_num.end());
    stringstream phone;
    long int num;
    phone << phone_num;
    phone >> num;
    this -> phone_num = num;

}


string Phone::get_contact(string style){
    // TODO: Complete this method, get hint from Email 
    // The code has been covered in discussion session 
    stringstream num;
    num << phone_num;
    string phone = num.str();

    string phoneNum = phone.substr(0,3) + "-" + phone.substr(3,3) + "-" + phone.substr(6);
    

    //cout << x1;
   

    //cout<<x1 << " " << x2 << " " << x3;
    if (style=="full")
        return "(" + type + ") " + phoneNum;
    else 
        return phoneNum;
     
}


void Phone::print(){
    // Note: get_contact is called with default argument
	cout << get_contact() << endl;
}



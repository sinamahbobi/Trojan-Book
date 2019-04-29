
#include "network.h"
#include <limits>
#include "misc.h"
#include <fstream>
#include <dirent.h>


Network::Network(){
    head = NULL;
    tail = NULL;
    count = 0;
}


Network::Network(string fileName){
    // TODO: complete this method!
    head = NULL;
    tail = NULL;
    count = 0;
    loadDB(fileName.c_str());
    // Implement it in one single line!
    // You may need to implement the load method before this!

}

Network::~Network(){
    Connection* ptr = head;
    while(head != NULL){
        ptr = head->next;
        delete head;
        head = ptr; 
        }
    // Copy from lab5 
}


void Network::push_front(Connection* newEntry){
    // Adds a new Connection (newEntry) to the front of LL
    // TA completed me in lab5 and since then I've not been changed! 
    newEntry->prev = NULL;
    newEntry->next = head;

    if (head != NULL)
        head->prev = newEntry;
    else
        tail = newEntry;
    
    head = newEntry;
    count++;
}


void Network::push_back(Connection* newEntry){
    
    newEntry -> next = NULL;
    newEntry-> prev = tail;

    if(tail != NULL)
        tail -> next = newEntry;
    else
        head = newEntry;

tail = newEntry;
count++;
    // Adds a new Connection (newEntry) to the back of LL
    // Copy from your lab5
}


Connection* Network::search(Connection* searchEntry){
    Connection *temp = head;
    while (temp->next != NULL){
        if ( temp ->f_name == searchEntry->f_name && temp->l_name == searchEntry->l_name) 
            return temp;
    
    temp = temp -> next;
    }
    
    if ( temp ->f_name == searchEntry->f_name && temp->l_name == searchEntry->l_name )
        return temp;
    else 
        return NULL;
    // Searches the Network for searchEntry
    // if found, returns a pointer to it, else returns NULL
    // Copy from lab5 
}


Connection* Network::search(string fname, string lname){
   
    
    Connection *temp = head;
    while (temp->next != NULL){
        if ( temp ->f_name == fname && temp->l_name == lname) 
            return temp;
    
    temp = temp -> next;
    }
    
    if ( temp ->f_name == fname && temp->l_name == lname )
        return temp;
    else 
        return NULL;
    // New == for Connection, only based on fname and lname
    // if found, returns a pointer to it, else returns NULL
    // TODO: Complete this method
    // Note: two ways to implement this, 1st making a new Connection with fname and lname and and using search(Connection*), 2nd using fname and lname directly. 
}


void Network::printDB(){
    // Leave me alone! I know how to print! 
    // Note: Notice that we don't need to update this even after adding to Connection attributes
    // This is a feature of OOP, classes are supposed to take care of themselves!
    cout << "Number of connections: " << count << endl;
    cout << "------------------------------" << endl;
    Connection* ptr = head;
    while(ptr != NULL){
        ptr->print_connection();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}


void Network::saveDB(string filename){
    
    ofstream *outfile = new ofstream(filename.c_str());
    //outfile -> open(filename.c_str());
    Connection * ptr = head;

    while(ptr != NULL) {
    
    ptr -> write_connection(*outfile);
    ptr = ptr -> next;
    
    }

    outfile -> close();
    // Saves the netwrok in file <filename>
    // Note: The format of the output file is very abstract, just raw data
    // Look at studentDB.txt as a template
    // TODO: Update this method with new requirements
    // Note: notice the intentional flaw in this code, as compared to the note mentioned in printDB, now the one who is responsible for implementing Network should be aware of implementation of Connection, not good! You will fix this in PA2. 
}


void Network::loadDB(string filename){
    

    Connection* ptr = head;
    
    while(head != NULL){
        ptr = head->next;
        delete head;
        head = ptr;
        count--;
    }
    head = NULL;
    tail = NULL;
    ifstream infile;
    infile.open(filename.c_str());
    string buff, fname, lname, bdate, email, phone;
    while(getline(infile, buff)){
        lname = buff.substr(0, buff.find(','));
        fname = buff.substr(buff.find(',')+2);
        getline(infile, bdate);
        getline(infile, email);
        getline(infile, phone);
        Connection* newEntry = new Connection(fname, lname, bdate, email, phone);
            
            while(getline(infile, buff)) {
                    //cout <<buff2 <<endl;
                    if(buff.substr(0,1) == "-"){
                       break;
                       
                       //cout <<buff2[0];
                       //break; 
                    }
                    
                    else {    //cout<<"test \n";
                        newEntry -> mycodes.push_back(buff);
                        //for (int i = 0; i < newEntry->mycodes.size(); i++) {
                            //cout <<i;
                            //cout << newEntry -> mycodes[i] <<endl;
                        //}
                        
                    }
                    



            }
            
        //getline(infile,buff);
        //cout<<phone << endl;
        //cout<<"test \n";
        //newEntry -> print_connection();
        this->push_back(newEntry);
        

    // Loads the netwrok from file <filename>
    // The format of the input file is similar to saveDB
    // Look at network studentDB.txt as a template
    // Phone number can be with dashes or without them
    // TODO: Now you will notice you need to go back and make a new constructor to the Connection class,  
    // Connection::Connection(fname, lname, bdate, email, phone)
    // TODO: Update this method with new requirements 
}

ptr = head;
Connection * temp;
    while (ptr != NULL){
        int sizeVec = ptr->mycodes.size();
            for (int i = 0; i < sizeVec ; i++) { //need run another while loop iterating through network
                //string checkCode = ptr -> mycodes[i];
                temp = search(ptr->mycodes[i]);
                //cout << ptr -> mycodes[i] << endl;
                if (temp != NULL) {
                    ptr -> myfriends.push_back(temp);
                }
            }


            ptr = ptr -> next;
    }


}
bool Network::remove(string fname, string lname){
    string bdate = "4/20/1969";
    string email = "(USC-email) yeet@yote.edu";
    string phone = "(Cell) 4206969420";
    Connection* ptr = new Connection(fname, lname , bdate, email, phone);
    
    Connection* searchptr = search(ptr);
    delete ptr;
    
    if (count == 1) {

        head = NULL;
        tail = NULL;
        count--;
        
       

    }

    if(searchptr == NULL) {
        //delete searchptr; //checks if connection exists
        return false;
         } 
    else if (searchptr -> prev == NULL && searchptr -> next != NULL) { //checks if connection is head

    head = searchptr -> next;
    head -> prev = NULL;
    searchptr -> next = NULL;
    count--;
    //delete searchptr;
    return true;
    }
    else if (searchptr -> next == NULL && searchptr -> prev != NULL) { //checks if connection is tail

        tail  = searchptr -> prev;
        tail -> next = NULL;
        searchptr -> prev = NULL;
        count--;
        //delete searchptr;
        return true; }
    else if (searchptr -> next != NULL && searchptr -> prev != NULL) { //checks if connection is neither head nor tail
        searchptr -> prev -> next = searchptr -> next;
        searchptr -> next -> prev = searchptr -> prev;
        searchptr -> next = NULL;
        searchptr -> prev = NULL;
        count --;
        //delete searchptr;
        return true;
    }
    // We modified the definition of == for Connection in Connection definition itself, 
    // So we should not be worried about changes we made in Connection to modify this method!
    // Copy from lab5
Connection * ptr1 = head;
    while (ptr1 != NULL) {
        int size = ptr1 -> myfriends.size();
            string code = codeName(fname, lname);
           if(search(code)) {
            for (int i = 0; i <size; i++) {
                ptr1 -> mycodes.erase(ptr1->mycodes.begin() + i);
                ptr1 -> myfriends.erase(ptr1->myfriends.begin() + i);
            }
        }

    }
    delete ptr1;
    delete searchptr;
}


void Network::sendEmail(string addr, string subject, string content, string attachment =""){
     addr = "\"" + addr + "\"";
    content = "\"" + content + "\"";
    subject = "\"" + subject + "\"";
    attachment = "\"" + attachment + "\"";
    string cmd;
    //cmd = "echo " + content + " | mailx -s " + subject + " " + addr;
    
        cmd = "echo " + content + " | mailx -s " + subject + " -a " + attachment + " " + addr;
    

    cout << cmd << endl;
    system(cmd.c_str());

    // Sending a command looks like:
    // echo "content" | mailx -s "subject" -a "attachment" addr;
    // TODO: Search how you can run a unix command in C++
    // TODO: You need to add double quotation character (") to both sides of strings for this command. Adding other characters (like ? in code below) should be easy, but double quotation says: I'm a character but not a typical character! 
    // string new_str = '?' + old_str + '?'
    // TODO: Complete this method
    // Sending a command looks like:
    
    
}

Connection* Network::search(string code) {

    Connection* temp = head;
    while (temp != NULL) {

        string fname = temp ->f_name;
        string lname = temp -> l_name;
        string check = codeName(fname, lname);
            if (check == code) {
                return temp;
            }
    
            temp = temp -> next;
    }




}


void Network::showMenu() {
    // TODO: Complete this method!
    // All the prompts are given to you, 
    // You should add code before, between and after prompts!
    Network myNetwork;
    int opt;
    while(1) {
        cout << "\033[2J\033[1;1H";
        printMe("banner"); // from misc library

        cout << "Select from below: \n";
        cout << "1. Save network database \n";
        cout << "2. Load network database \n";
        cout << "3. Add a new connection \n";
        cout << "4. Remove a connection \n";
        cout << "5. Search \n";
        cout << "6. Send an email \n";
        cout << "7. Send an iMessage \n";
        cout << "8. Print database \n";
        cout << "9. Connect \n";
        cout << "\nSelect an option ... ";
        
        if (cin >> opt) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Wrong option! " << endl;
            return;
        }
        
        // You may need these variables! Add more if you want!
        string fname, lname, fileName, bdate;
        cout << "\033[2J\033[1;1H";

        if (opt==1){
            // TODO: Complete me!
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            cin >> fileName;
            cout << "Network saved in " << fileName << endl;
            myNetwork.saveDB(fileName);
        }
        else if (opt==2){
            // TODO: Complete me!
            cout << "Loading network database \n";
             DIR *dir;
            struct dirent *ent;
            char targetFolderAddr[] = "./";
            string fileArray[420];
            int filecount = 0;
            
                if ((dir = opendir ("./")) != NULL) {
       
                while ((ent = readdir (dir)) != NULL) {
                   string name = ent -> d_name;
                    if (name.length() >2 && name.substr(name.length()-2) == "db") {
                        cout << name << endl;
                        fileArray[filecount] = name;
                        filecount++;
            
            }
          
            }
            closedir (dir);
            }


            // TODO: print all the files in this same directory that have ".db" format
            int flag =0;// Take a look into sample_files.cpp 
            cout << "Enter the name of the load file: "; 
            cin >> fileName;
                for (int i = 0; i < filecount ; i++) {
                if(fileName == fileArray[i] ) {
                    flag =1;
                    break;
                
                }
               
            }   

            // If file with name FILENAME does not exist: 
            if (flag ==1  ) {
                myNetwork.loadDB(fileName); 
                cout << "Network loaded from " << fileName << " with " << myNetwork.count << " connections \n";
                
            }
            else {
                cout << "File " << fileName <<" does not exist!" << endl;
            }
        }
        else if (opt == 3){
            // TODO: Complete me!
            // TODO: use push_front, and not push_back 
            // Add a new Connection ONLY if it does not exists!
            cout << "Adding a new connection \n";
            Connection* c1 = new Connection();
            //cout << "garbage";
            Connection *temp = myNetwork.search(c1);
            if (temp == NULL) {

                myNetwork.push_front(c1);
                cout << "Connection added! \n"; 
            }
            else {
                cout << "This connection already exists! \n";
            }
        }
        else if (opt == 4){
            // TODO: Complete me!
            cout << "Removing a connection \n";
            cout << "First name: ";
            std::getline (std::cin, fname);
            cout << "Last name: ";
            std::getline (std::cin, lname);

            Connection *temp = myNetwork.search(fname,lname);
            if(temp != NULL) {
                cout << "Remove Successful! \n";
                myNetwork.remove(fname,lname);
                 
                
            }
            else {

                cout << "Connection not found! \n"; 
            }
            // if found, cout << "Remove Successful! \n";
            // if not found: cout << "Connection not found! \n";
        }
        else if (opt==5){
            // TODO: Complete me!
            cout << "Searching: \n";
            cout << "First Name: ";
            std::getline (std::cin, fname);
            cout << "Last Name: ";
            std::getline (std::cin, lname);
            // if found: print connection
            // if not, cout << "Not found! \n";
            Connection *temp = myNetwork.search(fname, lname);  
            if(temp != NULL) {
                
                //cout <<temp;
                temp -> print_connection(); 
            }
            else {
                cout << "Not found! \n";
            }
        }
        else if (opt==6){
            // Note: Completed!
            cout << "Sending email to: \n";
            cout << "First Name: ";
            std::getline (std::cin, fname);
            cout << "Last Name: ";
            std::getline (std::cin, lname);
            Connection* ptr = myNetwork.search(fname, lname);
            if (ptr ){
                string subject, content, attachment;
                cout << "Sending email to: \n";
                ptr->print_connection();
                cout << "Subject: ";
                std::getline (std::cin, subject);
                cout << "Content: ";
                std::getline (std::cin, content);
                cout << "Attachment: ";
                std::getline (std::cin, attachment);
                string addr = ptr->email->get_contact("1");
                sendEmail(addr, subject, content, attachment);
            }
            else 
                cout << "Contact not found! \n";
        }
        else if (opt==7){
            cout << "Option currently not available\n";
        }
        else if (opt==8){
            // TODO: Complete me!
            cout << "Network Database: \n";
            myNetwork.printDB();
            
        }
        else if (opt == 9) {
            
            cout << "Make friends: \n"; 
            cout << "Connection 1 \n";
            cout << "First Name: ";
            std::getline (std::cin, fname);
            cout << "Last Name: ";
            std::getline (std::cin, lname);
            Connection *temp = myNetwork.search(fname, lname);  
            
            if(temp == NULL) {
                
                cout << "Connection 1 not found! \n";
                //break;//return;//cout <<temp;
                
            }

            string fname2, lname2;
            cout << "Connection 2 \n";
            cout << "First Name: ";
            std::getline (std::cin, fname2);
            cout << "Last Name: ";
            std::getline (std::cin, lname2);
            Connection *temp1 = myNetwork.search(fname2, lname2);  

            
            
            
            if(temp1 == NULL) {
                
                cout << "Connection 2 not found! \n";
                //break;//return;//cout <<temp;
                
            }

            if (temp != NULL && temp1 != NULL) {
                temp -> makeFriend(temp1);
                temp1 -> makeFriend(temp);
                cout << "Connection made!";
                //temp -> myfriends[0] -> print_connection();
            }
            
        }
        else
            cout << "Nothing matched!\n";
        
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        std::getline (std::cin, temp);
        cout << "\033[2J\033[1;1H";
    }
}





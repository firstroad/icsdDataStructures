#include <iostream>     
#include <fstream>      
#define N 29            
using namespace std;

class user {    
    private:
        string username;    
        string password;    
        user *next;         
    public:
        user(string username, string password, user *next){ 
            this->username=username;    
            this->password=password;    
            this->next=next;    
        }
        string getUser(){ return username; }    
        void setUser( string username ){ this->username=username; }
        string getPass(){ return password; }
        void setPass(string password){ this->password=password; }
        user *getNext(){ return next; }
        void setNext(user *next){ this->next=next; }
};

void InitializeHashTable(user *[]);     
int GetKey(string );                    
int Hash(string );                      
void insert(user *[], string, string);  
string search(user *[], string);        
void print(user *[]);                   

int main() {
    user * hashTable[N]={NULL};         
    InitializeHashTable(hashTable);
    char choice;    
    do{
        string username;    
        string password;
        cout << "Enter Login Name: ";   
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;
        if(search(hashTable,username)=="") cout << "Unknown User Name" << endl; 
        else if(search(hashTable,username)==password) cout << "Authentication Successful" << endl;  
        else cout << "Authentication Fail" << endl;
        cout << "Do you want to continue (y/n) ? "; 
        cin >> choice;
        while(choice!='y' && choice!='n'){  
            cout << "Wrong input. Do you want to continue (y/n) ? " << endl;
            cin >> choice;
        }
    }while(choice=='y');    
    print(hashTable);
    return 0;
}

void InitializeHashTable(user *hashTable[]){    
    ifstream file ("passwords.dat");            
    if (file.is_open()) {                       
        string username,password;               
        while( !file.eof() ){                   
            file >> username >> password;       
            insert(hashTable,username,password);
        }
        file.close();   
    }
    else cout << "Unable to open the file\n";   
}
int GetKey(string username){    
    int sum = 0;                
    for(int i=0;i<username.length();i++)    
        sum+=(int)username[i];              
    return sum; 
}
int Hash(string username){  
    return GetKey(username)%N;  
}
void insert(user *hashTable[], string username, string pass){   
    user *tmp = new user(username, pass, hashTable[Hash(username)]);    
    hashTable[Hash(username)]=tmp; 
}
string search(user *hashTable[], string username){  
    int index = Hash(username); 
    user *tmp = hashTable[index];    
    while(tmp!=NULL){           
        if(tmp->getUser()==username){   
            return tmp->getPass();      
            break;                      
        }
        tmp=tmp->getNext();             
    }
    return "";  
}
void print(user *hashTable[]) {     
    for(int i=0;i<N;i++){       
        cout << i << ". ";      
        user *tmp=hashTable[i]; 
        while(tmp!=NULL){       
            cout << tmp->getUser() << " " << tmp->getPass() << "\t";    
            tmp=tmp->getNext(); 
        }
        cout << endl;   
    }
}

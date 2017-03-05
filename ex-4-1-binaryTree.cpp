using namespace std;

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>  
#include <time.h>

class lNode{    
private:
    int line;   
    lNode *next;
public:
    int getLine(){return line;}
    lNode *getNext(){return next;}
    void setNext(lNode *next){ this->next=next; }
    lNode(int line){    
        this->line=line;
        next=NULL;
    }
};

class wNode{    
private:
    string word;    
    wNode* left;    
    wNode* right;   
    lNode* head;    
public:
    string getWord(){return word;}      
    wNode *getLeft(){return left;}
    void setLeft(wNode *left){this->left=left;}
    wNode *getRight(){return right;}
    void setRight(wNode *right){this->right=right;}
    wNode(string word, int lineNum){    
        this->word=word;
        left=NULL;
        right=NULL;
        head=new lNode(lineNum);
    }
    wNode(string word, wNode *left, int lineNum){   
        this->word=word;
        this->left=left;
        right=NULL;
        head=new lNode(lineNum);
    }
    wNode(string word, int lineNum, wNode *right){     
        this->word=word;
        left=NULL;
        this->right=right;
        head=new lNode(lineNum);
    }
    wNode(string word, wNode *left, int lineNum, wNode *right){ 
        this->word=word;
        this->left=left;
        this->right=right;
        head=new lNode(lineNum);
    }
    void display(){         
        cout << word << ':';
        lNode *temp=head;
        do{
            cout << ' ' << temp->getLine();
            if(temp->getNext()!=NULL) cout << ',';
            temp=temp->getNext();
        }while(temp!=NULL);
        cout << endl;
    }
    int getTimes(){     
        lNode *temp=head;
        int times=0;
        do{
            times++;
            temp=temp->getNext();
        }while(temp!=NULL);
        return times;
    }
    void addPos(int lineNum){   
        lNode *temp = head;
        while(temp->getNext()!=NULL)    
            temp=temp->getNext();
        if(temp->getLine()==lineNum) return; 
        temp->setNext(new lNode(lineNum));  
    }
};

string convert(string);
void displayAll(wNode *);
bool addLeft(wNode *,string, int);
bool addRight(wNode *,string,int);
bool add(wNode *,string,int);
wNode *fnd(wNode *, string);
void del(wNode **, string , int &, int &);
void displayStats(wNode *, int ,int ,int );
void exportToFile(wNode *, int ,int ,int);

int main() {
    string path;
    int textWords=0, indexWords=0;
    wNode *root=NULL;

    cout << "Insert relative file path:";
    cin >> path;
    ifstream myfile(path.c_str()); 
    if(myfile.is_open()) { 
        clock_t start = clock();
        string lineString; 
        int lineNum=0; 
        while ( getline(myfile,lineString) ) { 
            istringstream lineStream(lineString); 
            lineNum++;  
            string word;
            while (lineStream >> word){ 
                textWords++;    
                word=convert(word); 
                if(textWords==1) { 
                    root = new wNode(word,lineNum);
                    indexWords++;
                }
                else if(add(root, word, lineNum)==true) indexWords++; 
            }
        }
        myfile.close(); 
        double elapsed= ((double)(clock() - start))/CLOCKS_PER_SEC; 

        int choice=0;   
        while(choice!=3){ 
            if(choice==0) 
                displayStats(root,textWords,indexWords,elapsed);
            else if(choice==1){ 
                cout << "Insert word: ";
                string word;
                cin >> word;
                cout << "Insert line number: ";
                int lineNum;
                cin >> lineNum;
                textWords++;
                word=convert(word);
                if(textWords==1) {
                    root = new wNode(word,lineNum);
                    indexWords++;
                }
                else if(add(root, word, lineNum)==true) indexWords++;
            }
            else if(choice==2){ 
                cout << "Insert word: ";
                string word;
                cin >> word;
                word=convert(word);
                del(&root,word,textWords,indexWords);
            }
            else cout << "Wrong input" << endl; 
            cout << "0. Show stats" << endl << "1. Insert word" << endl << "2. Delete word" << endl << "3. Exit" << endl;
            cout << "Insert the number of your choice: ";
            cin >> choice;
        }
        exportToFile(root,textWords,indexWords,elapsed); 
    }
    else
        cout << "Can't process file!" << endl; 
}

string convert(string word){    
    for(int i = 0; i < word.size(); i++)    
        word.at(i) = toupper(word.at(i));
    if(!isalpha(word.at(word.size()-1)))    
        word=word.substr(0,word.size()-1);  
    return word;
};

void displayAll(wNode *root){   
    if(root==NULL) { cout << "The index is empty!" << endl; return; }
    while(root->getLeft()!=NULL)
        root=root->getLeft();
    while(root!=NULL){
        root->display();
        root=root->getRight();
    }
}

bool addLeft(wNode *root, string word, int lineNum){    
    while(root->getLeft()!=NULL && root->getWord()>word) 
        root=root->getLeft();
    if(root->getWord()==word){  
        root->addPos(lineNum);  
        return false;
    }
    else if(root->getWord()<word){  
        root->setRight(new wNode(word, root, lineNum, root->getRight()));   
        root->getRight()->getRight()->setLeft(root->getRight());            
    }
    else root->setLeft(new wNode(word,lineNum,root));   
    return true;
}

bool addRight(wNode *root, string word, int lineNum) {      
    while(root->getRight()!=NULL && root->getWord()<word)
        root=root->getRight();
    if(root->getWord()==word){
        root->addPos(lineNum);
        return false;
    }
    else if(root->getWord()>word){
        root->setLeft(new wNode(word,root->getLeft(),lineNum,root));
        root->getLeft()->getLeft()->setRight(root->getLeft());
    }
    else root->setRight(new wNode(word,root,lineNum));
    return true;
}

bool add(wNode *root, string word, int lineNum) {   
    if(word>root->getWord()){                       
        if(addRight(root,word,lineNum)==false)
            return false;
    }
    else if(word<root->getWord()){
        if(addLeft(root,word,lineNum)==false)
            return false;
    }
    else if(word==root->getWord()){ 
        root->addPos(lineNum);
        return false;
    }
    return true;
}

wNode *fnd(wNode *root, string word){ 
    if(root!=NULL){                 
        if(word==root->getWord())   
            return root;            
        else if(word<root->getWord() && root->getLeft()!=NULL){ 
            if(root->getWord()>word) return NULL;   
            else return fnd(root->getLeft(),word);  
        }
        else if(root->getRight()!=NULL)         
            return fnd(root->getRight(),word);
    }
    return NULL;
}

void del(wNode **root, string word, int &textWords, int &indexWords) { 
    wNode *tmp=*root;
    if(*root==NULL) { cout << "Can't delete because empty!" << endl; return; } 
    else if (tmp->getWord()==word) {    
        textWords-=tmp->getTimes();     
        if(tmp->getRight()!=NULL)       
            *root=tmp->getRight();
        else if(tmp->getLeft()!=NULL)   
            *root=tmp->getLeft();
        else { *root=NULL; return; }    
        tmp->getLeft()->setRight(tmp->getRight());  
        tmp->getRight()->setLeft(tmp->getLeft());   
    }
    else {              
        wNode *del=NULL;    
        del=fnd(*root,word);
        if(del!=NULL){  
            textWords-=del->getTimes(); 
            if(del->getLeft()!=NULL)    
                del->getLeft()->setRight(del->getRight());  
            if(del->getRight()!=NULL)       
                del->getRight()->setLeft(del->getLeft());
        }
        else { cout << "Den vrethike h leksh" << endl; return; } 
    }
    cout << "Diagrafike epituxws" << endl; 
    indexWords--;   
}

void displayStats(wNode *root, int textWords,int indexWords,int elapsed){ 
    cout << "Word Index:\n--------------------------------------------------\n";
    displayAll(root);
    cout << "Number of text words: " << textWords << endl;
    cout << "Number of index words: " << indexWords << endl;
    cout << "Time elapsed to create binary tree: " << elapsed << " sec." << endl;
}

void exportToFile(wNode *root, int textWords,int indexWords,int elapsed){ 
    ofstream out("index_bst.txt");  
    streambuf *coutbuf = std::cout.rdbuf();
    cout.rdbuf(out.rdbuf());
    displayStats(root,textWords,indexWords,elapsed);
    cout.rdbuf(coutbuf);
}

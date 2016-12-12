#include <iostream>
#include <limits>

using namespace std;

class book {
    private:
        string title;
        string author;
        string type;
        string description;
        float fame;
        book *prev;
        book *next;

    public:
        book(string title, string author, string type, string description){
            this->title=title;
            this->author=author;
            this->type=type;
            this->description=description;
            next=NULL;
            prev=NULL;
            fame=0;
        }
        string getTitle() { return title; }
        float getFame() { return fame; }
        book *getPrev() { return prev; }
        void setPrev(book *prev) { this->prev=prev; }
        book *getNext() { return next; }
        void setNext(book *next) { this->next=next; }
        void display() {
            cout << "Title: " << title << endl;
            cout << "Author: " << author << endl;
            cout << "Genre: " << type << endl;
            cout << "Description: " << description << endl;
            fame+=0.5;
        }
};

void addBook(book **, book **,string,string,string,string);
void searchBook(book **, book **,string);
void deleteBook(book **, book **,string);
int countBook(book *);
void maxRateBook(book *);
void minRateBook(book *,book *);
void allBooks(book *);

int main(){
    book *head = NULL;
    book *tail = NULL;

    string title;
    string author;
    string type;
    string description;

    int choice=0;

    while(choice!=8) {
        cout << "1. Insert book" << endl;
        cout << "2. Search book" << endl;
        cout << "3. Delete book" << endl;
        cout << "4. Show number of books" << endl;
        cout << "5. Book with highest popularity" << endl;
        cout << "6. Book with lowest popularity" << endl;
        cout << "7. Show all books" << endl;
        cout << "8. Exit" << endl;
        cin >> choice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');


        if (choice == 1) {
            cout << "Insert title: ";
            getline(cin,title);
            cout << "Insert author: ";
            getline(cin,author);
            cout << "Insert genre: ";
            getline(cin,type);
            cout << "Insert description: ";
            getline(cin,description);
            addBook(&head,&tail, title, author, type, description);
        }

        else if (choice==2) {
            cout << "Insert the title of the book you want to search: ";
            getline(cin,title);
            searchBook(&head, &tail, title);
        }
        else if (choice==3) {
            cout << "Insert the title of the book you want to delete: ";
            getline(cin,title);
            deleteBook(&head, &tail, title);
        }
        else if (choice==4)
            cout << "The number of the books is: " << countBook(head) << endl;
        else if (choice==5)
            maxRateBook(head);
        else if(choice==6)
            minRateBook(head,tail);
        else if(choice==7) {
            cout << "Books: " << endl;
            allBooks(head);
        }
        cout<<endl;
     }

     return 0;
 }

void addBook(book **head, book **tail, string title, string author, string type, string description) {
    book *cur = new book(title,author,type,description);
    book *tmp = *head;
    if((*head)==NULL) {
        *head=cur;
        *tail=cur;
    }
    else {
        while(tmp!=NULL && tmp->getTitle()!=title) tmp=tmp->getNext();
        if(tmp!=NULL) cout << "Book exists" << endl;
        else {
            cur->setPrev(*tail);
            (*tail)->setNext(cur);
            *tail=cur;
            while(cur->getPrev()!=NULL && cur->getPrev()->getFame()==0 && cur->getPrev()->getTitle()>title) {
                if(cur->getNext()==NULL) *tail=cur->getPrev();
                else cur->getNext()->setPrev(cur->getPrev());
                cur->getPrev()->setNext(cur->getNext());
                if(cur->getPrev()->getPrev()==NULL) {
                        cur->getPrev()->setPrev (cur);
                        cur->setNext(cur->getPrev());
                        cur->setPrev(NULL);
                        (*head)=cur;
                }
                else {
                    cur->setNext(cur->getPrev());
                    cur->setPrev(cur->getPrev()->getPrev());
                    cur->getPrev()->setNext(cur);
                    cur->getNext()->setPrev(cur);
                }
            }
        }
    }
}

void searchBook(book **head, book **tail, string title) {
    book *tmp = *head;
    while(tmp!=NULL && tmp->getTitle()!=title) tmp=tmp->getNext();
    if(tmp==NULL) cout<<"Book doesn't exist!"<<endl;
    else {
        tmp->display();
        if(tmp->getPrev()!=NULL){

            while(tmp->getPrev()!=NULL && (tmp->getPrev()->getFame()<tmp->getFame() || (tmp->getPrev()->getFame()==tmp->getFame() && tmp->getPrev()->getTitle()>tmp->getTitle()))){
                if(tmp->getNext()==NULL) *tail=tmp->getPrev();
                else tmp->getNext()->setPrev(tmp->getPrev());
                tmp->getPrev()->setNext(tmp->getNext());
                if(tmp->getPrev()->getPrev()==NULL) {
                    tmp->getPrev()->setPrev(tmp);
                    tmp->setNext(tmp->getPrev());
                    tmp->setPrev(NULL);
                    (*head)=tmp;
                }
                else {
                    tmp->setNext(tmp->getPrev());
                    tmp->setPrev(tmp->getPrev()->getPrev());
                    tmp->getPrev()->setNext(tmp);
                    tmp->getNext()->setPrev(tmp);
                }
            }
        }
    }
}

void deleteBook(book **head, book **tail, string title){
    book *tmp=*head;
    while(tmp!=NULL && tmp->getTitle()!=title) tmp=tmp->getNext();
    if(tmp==NULL) cout<<"Book doesn't exist!"<<endl;
    else if(tmp->getPrev()==NULL && tmp->getNext()==NULL){
        (*head)=NULL;
        (*tail)=NULL;
    }
    else if(tmp->getPrev()==NULL){
        (*head)=tmp->getNext();
        (*head)->setPrev(NULL);
    }
    else if(tmp->getNext()==NULL){
        (*tail)=tmp->getPrev();
        (*tail)->setNext(NULL);
    }
    else {
        tmp->getPrev()->setNext(tmp->getNext());
        tmp->getNext()->setPrev(tmp->getPrev());
    }
}

int countBook(book *head){
    int counter=0;
    while(head!=NULL) {
        counter++;
        head=head->getNext();
    }
    return counter;
}

void maxRateBook(book *head) {
    if(head==NULL) cout << "There are no books!" << endl;
    else {
        float rate=head->getFame();
        while(head!=NULL) {
            if(head->getFame()==rate) cout << "+"  << head->getTitle() << " " <<head->getFame() << endl;
            head=head->getNext();
        }
    }
}

void minRateBook(book *head, book *tail) {
    if(head==NULL) cout << "There are no books!" << endl;
    else {
        float rate=tail->getFame();
        while(head!=NULL) {
            if(head->getFame()==rate) cout << "+"  << head->getTitle() << " " <<head->getFame() << endl;
            head=head->getNext();
        }
    }
}

void allBooks(book *head) {
    if(head==NULL) cout << "There are no books!" << endl;
    else {
        while(head!=NULL) {
            cout << "+"  << head->getTitle() << " " << head->getFame() << endl;
            head=head->getNext();
        }
    }
}

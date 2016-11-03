#include <iostream>
#include <stdlib.h>

//TO DO
//1-poses kai pou free malloc
//2-head akrivhs ulopoihsh

using namespace std;

class node {
    private:
        int number;
        node *next;
    public:
        node(){ next=NULL;}
        int getNum(){return this->number;}
        void setNum(int num){number=num;}
        node *getNext(){return this->next;}
        void setNext(node *next){this->next=next;}
};

class nodeD {
    protected:
        int number;
        nodeD *next;
        nodeD *prev;
    public:
        nodeD(){ next=NULL; prev=NULL; }
        int getNum(){return this->number;}
        void setNum(int num){number=num;}
        nodeD *getNext(){ return this->next;}
        void setNext(nodeD *next){this->next=next;}
        nodeD *getPrev(){ return this->prev; }
        void setPrev(nodeD *prev){ this->prev=prev; }
};

void addNodeSingle(node *, int, int);
void addDescending(node *, int);
int countList(node *);
void displayList(node *);
void deleteLast(node *);
void deleteNode(node *, int);
node * appendLists(node *, node *);
void addNodeDouble(nodeD *, nodeD *, int, int);
void ReversedisplayList(nodeD *, nodeD *);
void swapElements1(node *);
void swapElements2(node *, node *);
void swapElements3(node *);

//NA DIAGRAFEI
void displayListD(nodeD *);

int main(){
    node *head1 = new node();
    node *head2 = new node();
    node *head3 = new node();

    addNodeSingle(head1,3,0);
    addNodeSingle(head1,5,0);
    addNodeSingle(head1,7,0);
    addNodeSingle(head1,9,0);
    addNodeSingle(head1,1,1);
    displayList(head1);
    addDescending(head1,2);
    displayList(head1);
    addDescending(head1,10);
    displayList(head1);
    cout << countList(head1) << endl;
    displayList(head1);
    deleteLast(head1);
    displayList(head1);
    addDescending(head1,10);
    addNodeSingle(head1,2,1);
    displayList(head1);
    deleteNode(head1,10);
    displayList(head1);

    addNodeSingle(head2,3,0);
    addNodeSingle(head2,5,0);
    addNodeSingle(head2,7,0);
    addNodeSingle(head2,9,0);
    addNodeSingle(head2,1,1);
    addDescending(head2,2);
    displayList(head2);

    head3 = appendLists(head1,head2);
    displayList(head3);

    swapElements1(head3);
    displayList(head3);

    cout << endl;

    nodeD *head = new nodeD();
    nodeD *tail = new nodeD();
    addNodeDouble(head,tail,5,0);
    displayListD(head);
    addNodeDouble(head,tail,4,0);
    displayListD(head);
    addNodeDouble(head,tail,6,1);
    displayListD(head);
    ReversedisplayList(head, tail);

    free(head1);
    free(head2);
    free(head3);

    return 0;
}

void addNodeSingle(node *head, int num, int thesi) {
    if(head->getNext()==NULL){
        node *tmp = new node();
        tmp->setNum(num);
        tmp->setNext(NULL);
        head->setNext(tmp);
    }
    else if(head->getNext()!=NULL){
        node *tmp = new node();
        if(thesi==0){
            tmp->setNum(num);
            tmp->setNext(head->getNext());
            head->setNext(tmp);
        }
        else if(thesi==1){
            while(head->getNext()!=NULL){
                head=head->getNext();
            }
            tmp->setNum(num);
            tmp->setNext(NULL);
            head->setNext(tmp);
        }
    }
}

void addDescending(node *head, int num) {
    if(head->getNext()==NULL){
        node *tmp = new node();
        tmp->setNum(num);
        head->setNext(tmp);
    }
    else if(head->getNext()!=NULL){
        head=head->getNext();
        while(head->getNum()>num && head->getNext()!=NULL) {
            head=head->getNext();
        }
        node *tmp = new node();
        if(head->getNum()<=num) {
            tmp->setNum(head->getNum());
            tmp->setNext(head->getNext());
            head->setNum(num);
            head->setNext(tmp);
        }
        else {
            tmp->setNum(num);
            head->setNext(tmp);
            tmp->setNext(NULL);
        }
    }
}

void displayList(node * head) {
    while(head->getNext()!=NULL) {
        head=head->getNext();
        cout << head->getNum();
    }
    cout << endl;
}

int countList(node * head) {
    int counter=0;
    while(head->getNext()!=NULL) {
        counter++;
        head=head->getNext();
    }
    return counter;
}

void deleteLast(node * head) {
    while(head->getNext()->getNext()!=NULL) {
        head=head->getNext();
    }
    free(head->getNext());
    head->setNext(NULL);
}

//NA VALOUME FREE
void deleteNode(node * head, int num) {
    while(head->getNext()!=NULL) {
        if(head->getNext()->getNum()==num)
            if(head->getNext()->getNext()==NULL){
                head->setNext(NULL);
                break;
            }
            else head->setNext(head->getNext()->getNext());
        else head=head->getNext();
    }
}

node * appendLists(node * head1, node * head2) {
    node *tmp = new node();
    int head1length = countList(head1);
    int head2length = countList(head2);
    int length = head1length + head2length;
    int temp[length];
    for(int i=0;i<head1length;i++) {
        head1=head1->getNext();
        temp[i]=head1->getNum();
    }
    for(int i=head1length;i<length;i++) {
        head2=head2->getNext();
        temp[i]=head2->getNum();
    }
    for(int i=0;i<length;i++) {
        addDescending(tmp,temp[i]);
    }
    return tmp;
}

void addNodeDouble(nodeD *head, nodeD *tail, int num, int thesi) {
    if(head->getNext()==NULL){
        nodeD *tmp = new nodeD();
        tmp->setNum(num);
        tmp->setNext(NULL);
        tmp->setPrev(head);
        head->setNext(tmp);
    }
    else if(head->getNext()!=NULL){
        nodeD *tmp = new nodeD();
        if(thesi==0){
            tmp->setNum(num);
            tmp->setNext(head->getNext());
            head->getNext()->setPrev(tmp);
            tmp->setPrev(head);
            head->setNext(tmp);
        }
        else if(thesi==1){
            while(head->getNext()!=NULL){
                head=head->getNext();
            }
            tmp->setNum(num);
            tmp->setNext(NULL);
            tmp->setPrev(head);
            head->setNext(tmp);
            tail->setPrev(tmp);
        }
    }
}

void swapElements1(node * head) {
    node *tmp = new node();
    tmp->setNext(head->getNext());
    while(tmp->getNext()!=NULL) {
        tmp=tmp->getNext();
    }
    int temp=tmp->getNum();
    tmp->setNum(head->getNext()->getNum());
    head->getNext()->setNum(temp);
}

void ReversedisplayList(nodeD *head, nodeD *tail) {
    while(tail->getPrev()!=NULL) {
        tail=tail->getPrev();
        cout << tail->getNum();
    }
    cout << endl;
}

//NA DIAGRAFEI
void displayListD(nodeD * head) {
    while(head->getNext()!=NULL) {
        head=head->getNext();
        cout << head->getNum();
    }
    cout << endl;
}

#include <iostream>
#include <stdlib.h>

using namespace std;

class node {
    protected:
        int number;
        node *next;
    public:
        node(){ next=NULL; }
        int getNum(){ return number; }
        void setNum(int num){ number=num; }
        node *getNext(){ return next; }
        void setNext(node *next){ this->next=next; }
};

class nodeD : public node {
    protected:
        nodeD *next;
        nodeD *prev;
    public:
        nodeD(){ next=NULL; prev=NULL; }
        nodeD *getNext(){ return next; }
        void setNext(nodeD *next){ this->next=next; }
        nodeD *getPrev(){ return prev; }
        void setPrev(nodeD *prev){ this->prev=prev; }
};

void addNodeSingle(node **, int, int);
void addDescending(node **, int);
int countList(node *);
void displayList(node *);
void deleteLast(node **);
void deleteNode(node **, int);
node *appendLists(node *, node *);
void addNodeDouble(nodeD **, nodeD **, int, int);
void ReversedisplayList(nodeD *);
void swapElements1(node *);
void swapElements2(nodeD *, nodeD *);
void swapElements3(node *);

void displayListD(nodeD *);
void displayListC(node *);


int main(){
    node *head1 = NULL;
    node *head2 = NULL;
    node *head3 = NULL;

    cout << "Dimiourgia aplis sindedemenis listas meso tis addNodeSingle..." << endl;
    addNodeSingle(&head1,3,0);
    addNodeSingle(&head1,5,0);
    addNodeSingle(&head1,7,0);
    addNodeSingle(&head1,9,0);
    addNodeSingle(&head1,1,1);
    cout << "Emfanisi tis listas meso tis displayList: " <<  endl;
    displayList(head1);

    cout << "Prosthiki neou komvou me timi 2 kai taksinomisi se fthinousa seira meso tis addDescending..." << endl;
    addDescending(&head1,2);
    cout << "Emfanisi tis listas meso tis displayList: " << endl;
    displayList(head1);
    cout << "Prosthiki neou komvou me timi 10 kai taksinomisi se fthinousa seira meso tis addDescending..." << endl;
    addDescending(&head1,10);
    cout << "Emfanisi tis listas meso tis displayList: " << endl;
    displayList(head1);

    cout << "Emfanisi tou plithous ton stoixeion tis parapano listas meso tis countList: " << countList(head1) << endl;

    cout << "Diagrafi tou teleutaiou komvou tis listas meso tis deleteLast..." << endl;
    deleteLast(&head1);
    cout << "Emfanisi tis listas meso tis displayList: " << endl;
    displayList(head1);

    cout << "Diagrafi tou komvou pou periexei ti timi 10 meso tis deleteNode..." << endl;
    deleteNode(&head1,10);
    cout << "Emfanisi tis listas meso tis displayList: " << endl;
    displayList(head1);

    cout << "Dimiourgia deuteris aplis sindedemenis listas meso tis addNodeSingle..." << endl;
    addNodeSingle(&head2,4,0);
    addNodeSingle(&head2,6,0);
    addNodeSingle(&head2,7,0);
    addNodeSingle(&head2,8,0);
    addNodeSingle(&head2,1,1);
    addDescending(&head2,2);
    cout << "Emfanisi tis deuteris listas meso tis displayList: " << endl;
    displayList(head2);

    cout << "Dimiourgia tritis  aplis sindedemenis listas pou periexei tous komvous ton dio proigoumenon liston, taksinomimenous kata fthinousa seira meso tis appendLists..." << endl;
    head3 = appendLists(head1,head2);
    cout << "Emfanisi tis tritis listas meso tis displayList: " << endl;
    displayList(head3);

    nodeD *head = NULL;
    nodeD *tail = NULL;

    cout << "Dimiourgia diplis sindedemenis lista meso tis addNodeDouble..." << endl;
    addNodeDouble(&head,&tail,5,0);
    addNodeDouble(&head,&tail,6,0);
    addNodeDouble(&head,&tail,7,0);
    addNodeDouble(&head,&tail,4,0);
    addNodeDouble(&head,&tail,6,1);
    cout << "Emfanisi tis listas meso tis displayListD: " << endl;
    displayListD(head);

    cout << "Emfanisi ton dedomenon tis diplis sindedemenis listas me anapodi seira meso tis ReversediplayList: " << endl;
    ReversedisplayList(tail);

    cout << "Antistrofi protou me teleutaiou stoixeiou tis tritis aplis sindedemenis listas meso tis swapElements1..." << endl;
    swapElements1(head3);
    cout << "Emfanisi tis listas meso tis displayList: " << endl;
    displayList(head3);

    cout << "Antistrofi protou me teleutaiou stoixeiou tis diplis sindedemenis listas swapElements2..." << endl;
    swapElements2(head,tail);
    cout << "Emfanisi tis listas meso tis displayListD: " << endl;
    displayListD(head);

    cout << "Dimiourgia mias aplis sindedemenis kiklikis listas..." << endl;
    node *headC = NULL;


    node *tmp1 = new node();
    headC=tmp1;
    tmp1->setNum(2);
    tmp1->setNext(headC);
    node *tmp2 = new node();
    tmp1->setNext(tmp2);
    tmp2->setNum(3);
    tmp2->setNext(headC);
    node *tmp3 = new node();
    tmp2->setNext(tmp3);
    tmp3->setNum(4);
    tmp3->setNext(headC);
    cout << "Emfanisi tis listas meso tis displayListC: " << endl;
    displayListC(headC);

    cout << "Antistrofi protou me teleutaiou stoixeiou tis aplis sindedemenis kiklikis listas meso tis swapElements3..." << endl;
    swapElements3(headC);
    cout << "Emfanisi tis listas meso tis displayListC: " << endl;
    displayListC(headC);

    free(head);
    free(head1);
    free(head2);
    free(head3);
    free(headC);
    free(tail);

    return 0;
}

void addNodeSingle(node **head, int num, int thesi) {
    node *tmp = new node();
    tmp->setNum(num);
    if(*head==NULL){
        *head=tmp;
    }
    else if(head!=NULL){
        if(thesi==0){
            tmp->setNext(*head);
            *head=tmp;
        }
        else if(thesi==1){
            node *tmp2 = *head;
            while(tmp2->getNext()!=NULL){
                tmp2=tmp2->getNext();
            }
            tmp2->setNext(tmp);
        }
    }
}

void addDescending(node **head, int num) {
    node *tmp = new node();
    if(*head==NULL){
        tmp->setNum(num);
        *head=tmp;
    }
    else if(head!=NULL){
        node *tmp2 = *head;
        while(tmp2->getNum()>num && tmp2->getNext()!=NULL) {
            tmp2=tmp2->getNext();
        }
        if(tmp2->getNum()<=num) {
            tmp->setNum(tmp2->getNum());
            tmp->setNext(tmp2->getNext());
            tmp2->setNum(num);
            tmp2->setNext(tmp);
        }
        else {
            tmp->setNum(num);
            tmp2->setNext(tmp);
        }
    }
}

int countList(node *head) {
    int counter=0;
    while(head!=NULL) {
        counter++;
        head=head->getNext();
    }
    return counter;
}

void displayList(node *head) {
    if(head==NULL) cout << "The list is empty!";
    while(head!=NULL){
        cout << head->getNum();
        head=head->getNext();
    }
    cout << endl;
}

void deleteLast(node **head) {
    if(head==NULL) cout << "Can't delete because empty!";
    else if ((*head)->getNext()==NULL) *head=NULL;
    else {
        node *tmp = *head;
        while(tmp->getNext()->getNext()!=NULL) {
            tmp=tmp->getNext();
        }
        free(tmp->getNext());
        tmp->setNext(NULL);
    }
}

void deleteNode(node **head, int num) {
    node *tmp=*head;
    if(head==NULL) cout << "Can't delete because empty!";
    else if (tmp->getNext()!=NULL && tmp->getNum()==num) *head=tmp->getNext();
    else {
        while(tmp->getNext()!=NULL) {
            if(tmp->getNext()->getNum()==num)
                if(tmp->getNext()->getNext()==NULL){
                    free(tmp->getNext());
                    tmp->setNext(NULL);
                    break;
                }
                else tmp->setNext(tmp->getNext()->getNext());
            else tmp=tmp->getNext();
        }
    }
}

node *appendLists(node *head1, node *head2) {
    node *tmp = NULL;
    int head1length = countList(head1);
    int head2length = countList(head2);
    for(int i=0;i<head1length;i++) {
        addDescending(&tmp,head1->getNum());
        head1=head1->getNext();
    }
    for(int i=0;i<head2length;i++) {
        addDescending(&tmp,head2->getNum());
        head2=head2->getNext();
    }
    return tmp;
}

void addNodeDouble(nodeD **headD, nodeD **tail, int num, int thesi) {
    nodeD *tmp = new nodeD();
    tmp->setNum(num);
    if(*headD==NULL){
        *headD=tmp;
        *tail=tmp;

    }
    else if(headD!=NULL){
        if(thesi==0){
            tmp->setNext(*headD);
            (*headD)->setPrev(tmp);
            *headD=tmp;
        }
        else if(thesi==1){
            (*tail)->setNext(tmp);
            tmp->setPrev(*tail);
            *tail=tmp;
        }
    }
}

void ReversedisplayList(nodeD *tail) {
    if(tail==NULL) cout << "The list is empty!";
    while(tail!=NULL) {
        cout << tail->getNum();
        tail=tail->getPrev();
    }
    cout << endl;
}

void swapElements1(node *head) {
    if(head==NULL) {cout << "The list is empty!"<<endl; return;}
    node *tmp = head;
    while(tmp->getNext()!=NULL) {
        tmp=tmp->getNext();
    }
    int temp=tmp->getNum();
    tmp->setNum(head->getNum());
    head->setNum(temp);
}

void swapElements2(nodeD *head, nodeD *tail) {
    int temp=head->getNum();
    head->setNum(tail->getNum());
    tail->setNum(temp);
}

void swapElements3(node *head) {
    node * tmp = head;
    while(tmp->getNext()!=head) {
        tmp=tmp->getNext();
    }
    int temp=head->getNum();
    head->setNum(tmp->getNum());
    tmp->setNum(temp);
}

void displayListD(nodeD *headD) {
    if(headD==NULL) cout << "The list is empty!";
    while(headD!=NULL){
        cout << headD->getNum();
        headD=headD->getNext();
    }
    cout << endl;
}

void displayListC(node *head) {
    if(head==NULL) cout << "The list is empty!";
    node *tmp = head;
    do {
        cout << tmp->getNum();
        tmp=tmp->getNext();
    }while(tmp!=head);
    cout << endl;
}

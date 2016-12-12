#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<string.h>

using namespace std;

void enque(int *, int, int*, int, int);
void deque(int *, int  *, int, int);

int main() {
    int front=0;
    int rear=0;
    int N;
    cout << "Insert the size of the stack: ";
    cin >> N;
    while(N>=160 || N<=0 || isalpha(N)!=0){
        cin.clear();
        while (cin.get() != '\n')
        {
            continue;
        }
        cout << "Wrong input, insert again: ";
        cin >> N;
    }
    int stack[++N];

    for(int i=0;i<N-1;i++){
        int tmp;
        cout << "Insert element " << i+1 << ": ";
        cin >> tmp;
        if(tmp>0)
            enque(stack,front,&rear,N,tmp);
        else if(tmp<0 && abs(tmp)==stack[front+1])

            deque(stack,&front,rear,N);
        else {
            rear=1;
            break;
        }
    }
    if(front==rear)
        cout<<"It is a stack"<<endl;
    else
        cout << "It is not a stack"<<endl;

    return 0;
}

void enque(int *stack, int front, int *rear, int nMax, int x) {
    if(front==((*rear)+1)%nMax){
        cout << "Can't enque" << endl;
        return;
    }
    *rear=(*rear+1)%nMax;
    stack[(*rear)]=x;
}

void deque(int *stack, int *front, int rear, int nMax){
    if((*front)==rear)
        cout << "Can't deque" << endl;
    *front=(*front+1)%nMax;
}

#include <iostream>     
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define PARENT(i) ((i-1) / 2)

using namespace std;

int * createTable(int &);       
void createHeap(int * , int );
void insertheap(int *, int &, int );
void displayHeap(int *, int);
void displayTreeHeap(int *, int);
void heapSort(int *, int);
void fixheap(int *, int , int );

int main() {        
    int N;      
    int *A;
    int random=0;
    int choice=0;
    while(true) {       
        cout << "1. Create Table.\n";
        cout << "2. Create heap from table.\n";
        cout << "3. New item in heap.\n";
        cout << "4. Show heap as table.\n";
        cout << "5. Show heap as tree.\n";
        cout << "6. Sort and show table.\n";
        cout << "7. Exit.\n";
        cin >> choice;      

        if(choice==1)       
            A=createTable(N);
        else if(choice==2)      
            createHeap(A,N);
        else if(choice==3) {        
            int num;
            cout << "Insert number to insert in heap: ";
            cin >> num;
            insertheap(A,N,num);
        }
        else if(choice==4)      
            displayHeap(A,N);
        else if(choice==5)      
            displayTreeHeap(A,N);
        else if(choice==6)      
            heapSort(A,N);
        else if(choice==7)      
            break;
    }
    return 0;       
}       
int * createTable(int &N) {     
    N=20;
    int * A = new int[N+1];
    srand(time(NULL));
    for(int i=1; i<=N; i++)
        A[i]=(rand()%100)+1;
    return A;
}
void createHeap(int * A, int N) {       
    for(int i=1; i<=N; i++)
        while(i>1 && A[i]<A[i/2]){      
            int temp = A[i];
            A[i] = A[i/2];
            A[i/2]=temp;
            i/=2;
        }
}
void insertheap(int * A, int &N, int num){      
    N++;
    int *tmp = A;
    A = new int[N+1];       
    A=tmp;
    A[N]=num;
    int i=N;
    while(i>1 && A[i]<A[i/2]){      
        int temp = A[i];
        A[i] = A[i/2];
        A[i/2]=temp;
        i/=2;
    }
}
void displayHeap(int * A, int N) {      
    for (int i=1;i<=N;i++)
        cout << A[i] << " ";
    cout << endl;
}
void displayTreeHeap(int * A, int N) {      
    int width=N*4;      
    int position[N-1];      
    int i, j, k, pos, x=1, level=0;     
    for(i=0,j=1; i<N; i++,j++) {        
        pos = position[PARENT(i)] + (i%2?-1:1)*(width/(pow(2,level+1))+1);
        for (k=1; k<pos-x; k++) {
                if(i==0 || i%2) cout<< " ";     
                else cout<<"-";
        }
        cout << A[i+1];     
        position[i] = x = pos+1;        
        if (j==pow(2,level)) {      
            cout << endl;
            level++;
            x = 1;
            j = 0;
        }
    }
    cout << endl;
}
void heapSort(int * A, int N) {     
    for (int i=N/2-1;i>0;i--)       
        fixheap(A,N,i);
    for (int i=N;i>0;i--) {
        swap(A[i], A[1]);
        fixheap(A,i,1);
    }
    displayHeap(A,N);
}
void fixheap(int * A, int N, int i) {
    int largest=i;
    int left=2*i;
    int right=2*i+1;
    if(left<N && A[left]>A[largest] && left!=0)
        largest=left;
    if(right<N && A[right]>A[largest])
        largest = right;
    if(largest!=i) {
        swap(A[i],A[largest]);
        fixheap(A,N,largest);
    }
}

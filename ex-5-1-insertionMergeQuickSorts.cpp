#include<iostream>      
#include<stdlib.h>
#include<time.h>

using namespace std;

void insertionSort(int,unsigned long long int,double);     
void mergeStart(int,int,double);
void mergeSort(int *,int,int,int&);
void merge(int *,int,int,int,int&);
void quickStart(int,int,double);
void quickSort(int *,int,int,int&);
int partition (int *,int,int,int&);
void swap(int *,int *);

int main() {      
    srand(time(NULL));
    int choice=0,N=0;       
    int l=0,r=0;
    unsigned long long int MA_sigkriseon=0;
    double MX_taksinomisis=0;
    while(choice!=4) {      
        cout << "1.<<Insertion Sort>>\n";
        cout << "2.<<Merge Sort>>\n";
        cout << "3.<<Quick Sort>>\n";
        cout << "4.Exit\n\n";
        cout << "Insert choice: ";   
        cin >> choice;

        while(choice>4 || choice<1) {   
            cout << "Wrong input. Insert again: ";
            cin >> choice;
        }
        if(choice==4)       
            return 0;
        cout << "Insert array size: ";        
        cin >> N;
        if(choice==1)       
            insertionSort(N,MA_sigkriseon,MX_taksinomisis);     
        else if(choice==2)
            mergeStart(N,MA_sigkriseon,MX_taksinomisis);        
        else if(choice==3)
            quickStart(N,MA_sigkriseon,MX_taksinomisis);        
        cout << endl;
    }
    return 0;       
}       

void insertionSort(int N, unsigned long long int MA_sigkriseon, double MX_taksinomisis) {      
    clock_t start, end;     
    double elapsed;
    start=clock();      
    for(int i=0;i<100;i++){     
        int *p,temp=0,k;        
        p=(int*)malloc(N*sizeof(int));      
        for(int j=0;j<N;j++)     
            p[j]=rand()%50000+1;
        for(int j=1;j<N;j++){       
            int timhEisagwghs=p[j]; 
            int kenh=j; 
            while(kenh>0 && timhEisagwghs > p[kenh-1]){ 
                MA_sigkriseon++;    
                p[kenh]= p[kenh - 1];   
                kenh=kenh - 1;          
            }
            p[kenh]=timhEisagwghs;  
            MA_sigkriseon++;    
        }
        free(p);    
    }
    MA_sigkriseon/=100; 
    end=clock();    
    elapsed=((double)(end-start))/CLOCKS_PER_SEC; 
    MX_taksinomisis=elapsed/100;    
    cout << "Average comparisons: " << MA_sigkriseon << endl;
    cout << "Average comparison time: " << MX_taksinomisis << " sec" << endl;
}

void mergeStart(int N, int MA_sigkriseon, double MX_taksinomisis) {
    clock_t start, end;     
    double elapsed;
    start=clock();      
    int l=0,r=N-1;  
    for(int i=0;i<100;i++){ 
        int *p,temp=0,k;    
        p=(int*)malloc(N*sizeof(int));  
        for(int j=0;j<N;j++)    
            p[j]=rand()%50000+1;
        mergeSort(p,l,r,MA_sigkriseon); 
        free(p);
    }
    MA_sigkriseon/=100; 
    end=clock();    
    elapsed=((double)(end-start))/CLOCKS_PER_SEC; 
    MX_taksinomisis=elapsed/100;    
    cout << "Average comparisons: " << MA_sigkriseon << endl;
    cout << "Average comparison time: " << MX_taksinomisis << " sec" << endl;
}

void mergeSort(int *p, int l, int r, int &MA_sigkriseon) {
    if(l<r) {   
        int m=l+(r-l)/2;    
        mergeSort(p,l,m,MA_sigkriseon); 
        mergeSort(p,m+1,r,MA_sigkriseon); 
        merge(p,l,m,r,MA_sigkriseon);   
    }
    MA_sigkriseon++;
}

void merge(int *p,int l,int m,int r,int &MA_sigkriseon) {
    int nL=m-l+1;   
    int nR=r-m; 
    int L[nL],R[nR];    
    for(int i=0;i<nL;i++)   
        L[i]=p[l+i];
    for(int j=0;j<nR;j++)
        R[j]=p[m+1+j];
    int iL=0,iR=0,i=l; 
    while(iL<nL && iR<nR) {   
        if(L[iL]>=R[iR]) { 
            p[i]=L[iL];  
            iL++;    
        }
        else {
            p[i]=R[iR];  
            iR++;    
        }
        i++;    
        MA_sigkriseon++;
    }
    while(iL<nL) {   
        p[i]=L[iL];  
        iL++;
        i++;
    }
    while(iR<nR) {   
        p[i]=R[iR];
        iR++;
        i++;
    }
}

void quickStart(int N, int MA_sigkriseon, double MX_taksinomisis) {     
    clock_t start, end;     
    double elapsed;
    start=clock();      
    int l=0,r=N-1;      
    for(int i=0;i<100;i++) {        
        int *p;     
        p=(int*)malloc(N*sizeof(int));      
        for(int j=0;j<N;j++)        
            p[j]=rand()%50000+1;
        quickSort(p,l,r,MA_sigkriseon);     
        free(p);        
    }
    MA_sigkriseon/=100; 
    end=clock();    
    elapsed=((double)(end-start))/CLOCKS_PER_SEC; 
    MX_taksinomisis=elapsed/100;    
    cout << "Average comparisons: " << MA_sigkriseon << endl;
    cout << "Average comparison time: " << MX_taksinomisis << " sec" << endl;
}

void quickSort(int *p,int left,int right,int &MA_sigkriseon) {      
    if (left<right) {
        int pi=partition(p,left,right,MA_sigkriseon);   
        quickSort(p,left,pi-1,MA_sigkriseon);   
        quickSort(p,pi+1,right,MA_sigkriseon);  
    }
}

int partition (int *p,int left,int right,int &MA_sigkriseon) {
    int pivot=p[right];    
    int i=(left-1);  
    for(int j=left;j<=right-1;j++) {    
        if(p[j]>=pivot) {   
            i++;    
            swap(&p[i],&p[j]);  
        }
        MA_sigkriseon++;    
    }
    swap(&p[i+1],&p[right]);    
    return (i+1);       
}

void swap(int* a,int* b) {  
    int t=*a;
    *a=*b;
    *b=t;
}

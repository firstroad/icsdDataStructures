
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void serial(int,int&,double&,float&);
void binary(int,int&,double&,float&);

int main(){
    int choice=0, N=0;
    do{
        cout << "1. Serial Search \n2. Binary search \n\nChoose the search what search you want: ";
        cin >> choice;
    }while(choice!=1 && choice!=2);
    srand(time(NULL));
    cout << "Input table size: ";
    cin >> N;
    int averageCompares=0;
    double averageTime=0;
    float searchPercent=0;

    clock_t start, end;
    double elapsed;
    start = clock();

    if(choice==1)
        serial(N,averageCompares,averageTime,searchPercent);
    else if(choice==2)
        binary(N,averageCompares,averageTime,searchPercent);

    averageCompares/=1000;
    searchPercent=(searchPercent/1000)*100;
    end = clock();
    elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    averageTime = elapsed/1000;
    cout.precision(8);
    cout << "For N = " << N << endl;
    cout << "Average compares: " << averageCompares << endl;
    cout << "Average search time: " << fixed << averageTime << endl;
    cout << "Success searches percent: " << searchPercent << endl;
}

void serial(int N, int &averageCompares, double &averageTime, float &searchPercent){
    for(int i=0;i<1000;i++){
        int *p;
        p=(int*)malloc(N*sizeof(int));
        for(int j=0;j<N;j++)
            p[j]=rand()%30000+1;
        int r=rand()%30000+1;
        for(int j=0;j<N;j++)
        {
            if(r==p[j])
            {
                searchPercent++;
                averageCompares+=j;
                break;
            }
            else if (j==N-1)
            {
                averageCompares+=N;
            }
        }
        free(p);
    }
}

void binary(int N, int &averageCompares, double &averageTime, float &searchPercent){
    for(int i=0;i<1000;i++){
        int *p;
        p=(int*)malloc(N*sizeof(int));
        p[0]=1+rand()%3;
        for(int j=1;j<N;j++)
        {
            int temp=j-1;
            p[j]=p[temp]+1+rand()%3;
        }
        int r=rand()%p[N]+p[0];
        int low=0, high=N-1, middle=(low+high)/2;
        int counter=0;

        while(low<=high)
        {
            counter++;
            if(r==p[middle])
            {
                searchPercent++;
                break;
            }
            else if(p[middle]>r)
                high=middle-1;
            else if(p[middle]<r)
                low=middle+1;
            middle=(low+high)/2;
        }
        averageCompares+=counter;
        free(p);
    }
}

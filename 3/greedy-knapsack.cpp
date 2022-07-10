#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

void sort(int*& vett, int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n-1; j++){
            if(vett[j]<=vett[j+1])
                swap(vett[j],vett[j+1]);
        }
    }
}

void knapsack(int* vett, int n, int p){
    int sum = 0;
    sort(vett, n);

    for(int i=0; i<p; i++)
        sum += vett[i];

    out << sum << endl;
}

int main(){
    int n, p;
    for(int i=0; i<100; i++){
        in >> n; in >> p;
        int* vett = new int[n];
        for(int j=0; j<n; j++)
            in >> vett[j];
        knapsack(vett, n, p);
    }
    return 0;
}
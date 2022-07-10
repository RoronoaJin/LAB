#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

int getMax(int* vett, int n){
    int max = vett[1];

    for(int i=2; i<=n; i++){
        if(vett[i]>max)
            max = vett[i];
    }
    return max;
}

int getMin(int* vett, int n){
    int min = vett[1];

    for(int i=2; i<=n; i++){
        if(vett[i]<min)
            min = vett[i];
    }
    return min;
}

void countingsort(int* vett, int n){
    int max = getMax(vett, n);
    int min = getMin(vett, n);
    int k = max - min +1;
    int C[k+1];

    for(int i=0; i<=k; i++)
        C[i] = 0;
    for(int i=1; i<=n; i++)
        C[vett[i]-min+1]++;
    for(int i=2; i<=k; i++)
        C[i] = C[i] + C[i-1];

    for(int i=0; i<=k-1; i++)
        out << C[i] << " ";

    int* B = new int[n+1];
    for(int i=n; i>0; i--){
        B[C[vett[i]-min+1]] = vett[i];
        C[vett[i]-min+1]--;
    }

    for(int i=1; i<=n; i++)
        out << B[i] << " ";
    out << endl;
}

int main(){
    int n;
    for(int i=0; i<100; i++){
        in >> n;
        int* vett = new int[n+1];

        for(int j=1; j<=n; j++)
            in >> vett[j];
        countingsort(vett, n);
    }
    return 0;
}
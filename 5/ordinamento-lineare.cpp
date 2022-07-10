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

template <class H>
void countingsort(H* A, int n){
    int* vett = new int[n+1];

    for(int i=1; i<=n; i++)
        vett[i] = int(A[i]);

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

    H* B = new H[n+1];
    for(int i=n; i>0; i--){
        B[C[vett[i]-min+1]] = vett[i];
        C[vett[i]-min+1]--;
    }

    for(int i=1; i<=n; i++)
        out << B[i] << " ";
    out << endl;
}

void countingsortD(double* A, int n){
    int* vett = new int[n+1];

    for(int i=1; i<=n; i++)
        vett[i] = int(A[i]*10);

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

    double* B = new double[n+1];
    for(int i=n; i>0; i--){
        B[C[vett[i]-min+1]] = double(vett[i]/10.0);
        C[vett[i]-min+1]--;
    }

    for(int i=1; i<=n; i++)
        out << B[i] << " ";
    out << endl;
}

int main(){
    string type; int n;
    for(int i=0; i<100; i++){
        in >> type; in >> n;
        if(type=="int" || type=="bool"){
            int* vett = new int[n+1];

            for(int j=1; j<=n; j++)
                in >> vett[j];
            countingsort<int>(vett, n);
        }
        else if(type=="double"){
            double* vett = new double[n+1];

            for(int j=1; j<=n; j++)
                in >> vett[j];
            countingsortD(vett, n);
        }
        else if(type=="char"){
            char* vett = new char[n+1];

            for(int j=1; j<=n; j++)
                in >> vett[j];
            countingsort<char>(vett, n);
        }
    }
    return 0;
}
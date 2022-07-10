#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

template <class H>
class Coppia{
    public:
        H val1, val2;

        Coppia(H x, H y){
            val1 = x;
            val2 = y;
        }
        void print(){
            out << "(" << val1 << " " << val2 << ") ";
        }
};

int getMax(Coppia<int>** vett, int n){
    int max = vett[1]->val1;

    for(int i=2; i<=n; i++){
        if(vett[i]->val1>max)
            max = vett[i]->val1;
    }
    return max;
}

int getMin(Coppia<int>** vett, int n){
    int min = vett[1]->val1;

    for(int i=2; i<=n; i++){
        if(vett[i]->val1<min)
            min = vett[i]->val1;
    }
    return min;
}

void countingsort(Coppia<double>** A, int n){
    Coppia<int>** vett = new Coppia<int>*[n+1];

    for(int i=1; i<=n; i++)
        vett[i] = new Coppia<int>(int(A[i]->val1*10),int(A[i]->val2*10));

    int max = getMax(vett, n);
    int min = getMin(vett, n);
    int k = max - min +1;
    int C[k+1];

    for(int i=0; i<=k; i++)
        C[i] = 0;
    for(int i=1; i<=n; i++)
        C[vett[i]->val1-min+1]++;
    for(int i=2; i<=k; i++) 
        C[i] = C[i] + C[i-1];

    for(int i=0; i<=k-1; i++)
        out << C[i] << " ";
    
    Coppia<double>** B = new Coppia<double>*[n+1];
    for(int i=n; i>0; i--){
        B[C[vett[i]->val1-min+1]] = new Coppia<double>(double(vett[i]->val1/10.0),double(vett[i]->val2/10.0));
        C[vett[i]->val1-min+1]--;
    }

    for(int i=1; i<=n; i++)
        B[i]->print();
    out << endl;
}

int main(){
    int n;
    for(int i=0; i<100; i++){
        in >> n;
        Coppia<double>** vett = new Coppia<double>*[n+1];
        char tmp; double x, y;

        for(int j=1; j<=n; j++){
            in >> tmp;
            in >> x; in >> y;
            in >> tmp;
            vett[j] = new Coppia<double>(x, y);
        }
        countingsort(vett, n);
    }
    return 0;
}
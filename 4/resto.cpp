#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

void resto(int* vett, int n, int r){
    int C[r+1];
    C[0] = 0;

    for(int i=1; i<r+1; i++)
        C[i] = INT_MAX;
    for(int i=1; i<r+1; i++){
        for(int j=0; j<n; j++){
            if(vett[j]<=i){
                int sub = C[i-vett[j]];
                if(sub!=INT_MAX && sub+1<C[i])
                    C[i] = sub+1;
            }
        }
    }
    out << C[r] << endl;
}  

int main(){
    int r, n;
    for(int i=0; i<100; i++){
        in >> r; in >> n;
        int* vett = new int[n];

        for(int j=0; j<n; j++)
            in >> vett[j];
        resto(vett, n, r);
    }
    return 0;
}
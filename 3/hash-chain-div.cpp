#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

template <class H>
void Hash(H* vett, int n, int m){
    int k[m];

    for(int i=0; i<m; i++)
        k[i] = 0;
    for(int i=0; i<n; i++){
        int j = int(vett[i])%m;
        k[j]++;
    }
    for(int i=0; i<m; i++)
        out << k[i] << " ";
    out << endl;
}

template <class H>
void metodo(int n, int m){
    H* vett = new H[n];

    for(int i=0; i<n; i++)
        in >> vett[i];
    Hash(vett, n, m);
}

int main(){
    string type; int m, n;
    for(int i=0; i<100; i++){
        in >> type; in >> m; in >> n;
        if(type=="int" || type=="bool")
            metodo<int>(n,m);
        else if(type=="double")
            metodo<double>(n,m);
        else if(type=="char")
            metodo<char>(n,m);
    }
    return 0;
}
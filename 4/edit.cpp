#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

int min(int a, int b, int c){
    return min(min(a,b),c);
}

void edit(string x, string y, int n, int m){
    int M[n+1][m+1];

    for(int i=0; i<n+1; i++)
        M[i][0] = i;
    for(int i=1; i<m+1; i++)
        M[0][i] = i;
    for(int i=1; i<n+1; i++){
        for(int j=1; j<m+1; j++){
            if(x[i-1]==y[j-1])
                M[i][j] = M[i-1][j-1];
            else
                M[i][j] = 1 + min(M[i-1][j-1],M[i-1][j],M[i][j-1]);
        }
    }
    out << M[n][m] << endl;
}

int main(){
    int n, m;
    string x, y;
    for(int i=0; i<100; i++){
        in >> n; in >> m;
        in >> x; in >> y;
        edit(x,y,n,m);
    }
    return 0;
}
#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

void print_lcs(int** M, string x, string y, int n, int m){
    int i = n, j = m;
    int index = M[n][m];
    char o[index+1];
    o[index] = '\0';

    while(i>0 && j>0){
        if(x[i-1]==y[j-1]){
            o[index-1] = x[i-1];
            index--;
            i--;
            j--;
        }
        else{
            if(M[i][j-1]>=M[i-1][j])
                j--;
            else
                i--;
        }
    }
    out << o << endl;
}

void lcs(string x, string y, int n, int m){
    int** M = new int*[n+1];

    for(int i=0; i<n+1; i++)
        M[i] = new int[m+1];
    for(int i=0; i<n+1; i++)
        M[i][0] = 0;
    for(int i=1; i<m+1; i++)
        M[0][i] = 0;
    for(int i=1; i<n+1; i++){
        for(int j=1; j<m+1; j++){
            if(x[i-1]==y[j-1])
                M[i][j] = 1 + M[i-1][j-1];
            else
                M[i][j] = max(M[i-1][j],M[i][j-1]);
        }
    }
    print_lcs(M,x,y,n,m);
}

int main(){
    int n, m;
    string x, y;
    for(int i=0; i<100; i++){
        in >> n; in >> m;
        in >> x; in >> y;
        lcs(x,y,n,m);
    }
    return 0;
}
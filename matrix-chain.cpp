#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

int matrix(int* p, int n){
    int M[n][n];

    for(int i=1; i<n; i++)
        M[i][i] = 0;
    for(int l=2; l<n; l++){
        for(int i=1; i<n-l+1; i++){
            int j = i+l-1;
            M[i][j] = INT_MAX;
            for(int k=i; k<=j-1; k++){
                int q = M[i][k]+M[k+1][j]+p[i-1]*p[k]*p[j];
                if(q<M[i][j])
                    M[i][j] = q;
            }
        }
    }
    return M[1][n-1];
}

int main(){
    int n;
    for(int i=0; i<100; i++){
        in >> n;
        int* p = new int[n+1];
        int r, c;
        for(int j=0; j<n; j++){
            char tmp; in >> tmp;
            in >> r;
            in >> tmp;
            in >> c;
            in >> tmp;
            p[j] = r;
        }
        p[n] = c;
        out << matrix(p,n+1) << endl;
    }
    return 0;
}
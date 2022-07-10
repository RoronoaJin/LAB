#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

class Edge{
    public:
        int start, finish, peso;

        Edge(int s, int f, int p){
            start = s;
            finish = f;
            peso = p;
        }
};

template <class H>
class Grafo{
    private:
        int len, n, m;
        Edge** M;
        H* K;

        int findIndex(H val){
            for(int i=0; i<n; i++){
                if(K[i]==val)
                    return i;
            }
            return -1;
        }
    public:
        Grafo(){
            len = 1000;
            n = 0;
            m = 0;
            M = new Edge*[len];
            for(int i=0; i<len; i++)    
                M[i] = NULL;
            K = new H[len];
            for(int i=0; i<len; i++)
                K[i] = -1;
        } 
        void addNode(H val){
            K[n] = val;
            n++;
        }
        void addEdge(H s, H f, int p){
            int i = findIndex(s);
            int j = findIndex(f);
            M[m] = new Edge(i,j,p);
            m++;
        }
        void BellmanFord(H s, H f){
            int start = findIndex(s);
            int end = findIndex(f);
            int dist[n];

            for(int i=0; i<n; i++)  
                dist[i] = INT_MAX;
            dist[start] = 0;

            for(int i=0; i<n-1; i++){
                for(int j=0; j<m; j++){
                    if(M[j]!=NULL){
                        int u = M[j]->start;
                        int v = M[j]->finish;
                        int w = M[j]->peso;
                        if(dist[u]!=INT_MAX && dist[u]+w<dist[v])
                            dist[v] = dist[u]+w;
                    }
                }
            }
            for(int i=0; i<m; i++){
                if(M[i]!=NULL){
                    int u = M[i]->start;
                    int v = M[i]->finish;
                    int w = M[i]->peso;
                    if(dist[u]!=INT_MAX && dist[u]+w<dist[v]){
                        out << "undef." << endl;
                        return;
                    }
                }
            }
            if(dist[end]!=INT_MAX) 
                out << dist[end] << endl;
            else
                out << "inf." << endl;
        }
};

template <class H>
void metodo(int n, int m){
    Grafo<H>* g = new Grafo<H>();
    char tmp; H val1, val2; int p;

    for(int i=0; i<n; i++){
        in >> val1;
        g->addNode(val1);
    }
    for(int i=0; i<m; i++){
        in >> tmp;
        in >> val1; in >> val2; in >> p;
        in >> tmp;
        g->addEdge(val1, val2, p);
    }
    H s, f;
    in >> s; in >> f;
    g->BellmanFord(s,f);
}

int main(){
    int n, m;
    string type;
    for(int i=0; i<100; i++){
        in >> n; in >> m;
        in >> type;
        if(type=="int")
            metodo<int>(n,m);
        else if(type=="double")
            metodo<double>(n,m);
    }
    return 0;
}
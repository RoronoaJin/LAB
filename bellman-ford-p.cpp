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

class Grafo{
    private:
        int len, n, m;
        Edge** M;
    public:
        Grafo(int _n){
            len = 1000;
            n = _n;
            m = 0;
            M = new Edge*[len];
            for(int i=0; i<len; i++)
                M[i] = NULL;
        }
        void addEdge(int s, int f, int p){
            M[m] = new Edge(s,f,p);
            m++;
        }
        void BellmanFord(int s, int f, int k){
            int dist[n];

            for(int i=0; i<n; i++)
                dist[i] = INT_MAX;
            dist[s] = 0;

            for(int i=0; i<k; i++){
                for(int j=0; j<m; j++){
                    int u = M[j]->start;
                    int v = M[j]->finish;
                    int w = M[j]->peso;
                    if(dist[u]!=INT_MAX && dist[u]+w<dist[v])
                        dist[v] = dist[u]+w;
                }
            }
            if(dist[f]!=INT_MAX)
                out << dist[f] << endl;
            else
                out << "inf." << endl;
        }
};

int main(){
    int n, m, k;
    for(int i=0; i<100; i++){
        in >> n; in >> m; in >> k;
        Grafo* g = new Grafo(n);
        char tmp; int s, f, p;

        for(int i=0; i<m; i++){
            in >> tmp; 
            in >> s; in >> f; in >> p;
            in >> tmp;
            g->addEdge(s,f,p);
        }
        in >> s; in >> f;
        g->BellmanFord(s,f,k);
    }
    return 0;
}
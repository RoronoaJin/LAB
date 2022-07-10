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
            for(int i=0; i<n; i++)
                if(K[i]==val)
                    return i;
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
        int getMin(int* dist, bool* p){
            int min = INT_MAX;
            int index;

            for(int i=0; i<n; i++){
                if(dist[i]<min && p[i]==false){
                    min = dist[i];
                    index = i;
                }
            }
            return index;
        }
        void Dijkstra(H s, H f){
            int start = findIndex(s);
            int end = findIndex(f);
            int* dist = new int[n];
            bool* processed = new bool[n];

            for(int i=0; i<n; i++){
                dist[i] = INT_MAX;
                processed[i] = false;
            }
            dist[start] = 0;

            for(int i=0; i<n; i++){
                int u = getMin(dist, processed);
                processed[u] = true;
                for(int j=0; j<m; j++){
                    if(M[j]->start==u){
                        int v = M[j]->finish; 
                        int w = M[j]->peso;
                        if(dist[u]+w<dist[v])
                            dist[v]=dist[u]+w;
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
    g->Dijkstra(s,f);
}

int main(){
    int n, m;
    string type;
    for(int i=0; i<100; i++){
        in >> n; in >> m; in >> type;
        if(type=="int")
            metodo<int>(n,m);
        else if(type=="double")
            metodo<double>(n,m);
    }
    return 0;
}
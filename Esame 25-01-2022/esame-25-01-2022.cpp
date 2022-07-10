#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

template <class H>
class Heap{
    private:
        H* vett;
        int heapsize;
        bool heap;
    
        int parent(int i){
            return (int)(i/2);
        }
        int left(int i){
            return 2*i;
        }
        int right(int i){
            return 2*i+1;
        }
    public:
        Heap(){
            vett = new H[100];
            heapsize=0;
            heap = false;
        }
        void enqueue(H val){
            heapsize++;
            vett[heapsize] = val;
            int i = heapsize;
            while(i>1 && vett[parent(i)]>vett[i]){
                swap(vett[parent(i)],vett[i]);
                i = parent(i);
            }
        }
        void modifyKey(int i, H val){
            vett[i] = val;
            for(int j=1; j<heapsize; j++)
                Heapify(j);
        }
        void Heapify(int i){
            int l = left(i);
            int r = right(i);
            int min = i;

            if(l<=heapsize && vett[l]<vett[min])
                min = l;
            if(r<=heapsize && vett[r]<vett[min])
                min = r;
            if(min!=i){
                heap = true;
                swap(vett[i],vett[min]);
                Heapify(min);
            }
        }
        bool isHeap(){
            for(int i=heapsize/2; i>=1; i--){
                Heapify(i);
            }
            if(heap==true)
                return false;
            else
                return true;
        }
        void print(){
            for(int i=1; i<=heapsize; i++){
                out << vett[i] << " ";
            }
            out << endl;
        }
};

int main(){

    for(int i=0; i<3; i++){
        string type; int n; int m;
        in >> type; in >> n; in >> m;
        if(type=="int"){
            Heap<int>* h = new Heap<int>();
            for(int j=0; j<n; j++){
                int val;
                in >> val;
                h->enqueue(val);
            }
            for(int j=0; j<m; j++){
                char tmp; int x, y;
                in >> tmp;
                in >> x;
                in >> y;
                in >> tmp;
                h->modifyKey(x,y);
            }
            h->print();
        }
        else if(type=="double"){
            Heap<double>* h = new Heap<double>();
            for(int j=0; j<n; j++){
                double val;
                in >> val;
                h->enqueue(val);
            }
            for(int j=0; j<m; j++){
                char tmp; int x; double y;
                in >> tmp;
                in >> x;
                in >> y;
                in >> tmp;
                h->modifyKey(x,y);
            }
            h->print();
        }
    }
    return 0;
}
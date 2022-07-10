#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

template <class H>
class Heap{
    private:
        int heapsize;
        H* vett;

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
            heapsize = 0;
        }
        void Heapify(int i){
            int l = left(i);
            int r = right(i);
            int max = i;
            if(l<=heapsize && vett[l]>vett[max])
                max = l;
            if(r<=heapsize && vett[r]>vett[max])
                max = r;
            if(max!=i){
                swap(vett[i],vett[max]);
                Heapify(max);
            }
        }
        void BuildHeap(H* arr, int n){
            heapsize = n;
            vett = arr;
            for(int i=heapsize/2; i>0; i--)
                Heapify(i);
        }
        void print(){
            for(int i=1; i<=heapsize; i++)
                out << vett[i] << " ";
            out << endl;
        }
};

template <class H>
void metodo(int n){
    Heap<H>* h = new Heap<H>();
    H* vett = new H[n+1];

    for(int i=1; i<=n; i++)
        in >> vett[i];
    h->BuildHeap(vett, n);
    h->print();
}

int main(){
    string type; int n;
    for(int i=0; i<100; i++){
        in >> type; in >> n;
        if(type=="int" || type=="bool")
            metodo<int>(n);
        else if(type=="double")
            metodo<double>(n);
        else if(type=="char")
            metodo<char>(n);
    }
    return 0;
}
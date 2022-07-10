#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

template <class H>
class Coppia{
    public:
        H val1, val2;

        Coppia(H x, H y){
            val1 = x;
            val2 = y;
        }
        bool confronto(Coppia* a, Coppia* b){
            if(a->val1>b->val1)
                return true;
            else if(a->val1==b->val1 && a->val2>b->val2)
                return true;
            return false;
        }
        void print(){
            out << "(" << val1 << " " << val2 << ") ";
        }
};  

template <class H>
class Heap{
    private:
        int heapsize, count, old_length;
        Coppia<H>** vett;

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
            count = 0;
            old_length = 0;
        }
        void Heapify(int i){
            if(heapsize>=1)
                count++;
            int l = left(i);
            int r = right(i);
            int max = i;
            if(l<=heapsize && vett[i]->confronto(vett[l],vett[max]))
                max = l;
            if(r<=heapsize && vett[i]->confronto(vett[r],vett[max]))
                max = r;
            if(max!=i){
                swap(vett[i],vett[max]);
                Heapify(max);
            }
        }
        void BuildHeap(Coppia<H>** arr, int n){
            heapsize = n;
            vett = arr;
            for(int i=heapsize/2; i>0; i--)
                Heapify(i);
        }
        void extract(){
            swap(vett[1],vett[heapsize]);
            heapsize--;
            Heapify(1);
        }
        void Heapsort(Coppia<H>** arr, int n){
            BuildHeap(arr, n);
            old_length = heapsize;
            for(int i=n; i>1; i--)
                extract();
        }
        void print(){
            for(int i=1; i<=old_length; i++)
                vett[i]->print();
            out << endl;
        }
        int getCount(){
            return count;
        }
};

template <class H>
void metodo(int n){
    Heap<H>* h = new Heap<H>();
    Coppia<H>** vett = new Coppia<H>*[n+1];
    char tmp; H val1, val2;

    for(int i=1; i<=n; i++){
        in >> tmp;
        in >> val1; in >> val2;
        in >> tmp;
        vett[i] = new Coppia<H>(val1, val2);
    }
    h->Heapsort(vett, n);
    out << h->getCount() << " ";
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
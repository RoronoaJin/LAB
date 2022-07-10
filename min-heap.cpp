#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

template <class H>
class Heap{
    private:
        int heapsize, count, max;
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
        Heap(int n){
            heapsize = 0;
            max = n;
            count = 0;
            vett = new H[max];
        }
        void Heapify(int i){
            if(heapsize>=1)
                count++;
            int l = left(i);
            int r = right(i);
            int min = i;
            if(l<=heapsize && vett[l]<vett[min])
                min = l;
            if(r<=heapsize && vett[r]<vett[min])
                min = r;
            if(min!=i){
                swap(vett[i],vett[min]);
                Heapify(min);
            }
        }
        void enqueue(H val){
            heapsize++;
            vett[heapsize] = val;
            int i = heapsize;
            while(i>1 && vett[parent(i)]>vett[i]){
                swap(vett[i],vett[parent(i)]);
                i = parent(i);
            }
        }
        void extract(){
            swap(vett[1],vett[heapsize]);
            heapsize--;
            Heapify(1);
        }
        void print(){
            for(int i=1; i<=heapsize; i++)
                out << vett[i] << " ";
            out << endl;
        }
        int getCount(){
            return count;
        }
};  

template <class H>
void metodo(int n){
    Heap<H>* h = new Heap<H>(n+1);
    H val; char tmp;

    for(int i=0; i<n; i++){
        in >> tmp; 
        in >> tmp;
        if(tmp!=':'){
            for(int j=0; j<5; j++)
                in >> tmp;
            h->extract();
        }
        else{
            in >> val;
            h->enqueue(val);
        }
    }
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
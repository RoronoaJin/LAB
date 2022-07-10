#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

class Activity{
    public:
        int start, finish;

        Activity(int s, int f){
            start = s;
            finish = f;
        }
        int getProfit(){
            return finish - start;
        }
};

void sort(Activity** vett, int n){
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(vett[i]->finish>vett[j]->finish)
                swap(vett[i],vett[j]);
            else if(vett[i]->finish==vett[j]->finish && vett[i]->start < vett[j]->start)
                swap(vett[i],vett[j]);
        }
    }
}

int nonConflict(Activity** vett, int i){
    for(int j=i-1; j>=0; j--){
        if(vett[j]->finish<=vett[i]->start)
            return j;
    }
    return -1;
}

void select(Activity** vett, int n){
    sort(vett, n);
    int table[n];
    table[0] = vett[0]->getProfit();

    for(int i=1; i<n; i++){
        int prof = vett[i]->getProfit();
        int l = nonConflict(vett, i);
        if(l!=-1)
            prof+=table[l];
        if(prof>table[i-1])
            table[i] = prof;
        else
            table[i] = table[i-1];
    }
    out << table[n-1] << endl;
}

int main(){
    int n;
    for(int i=0; i<100; i++){
        in >> n;
        Activity** vett = new Activity*[n];
        char tmp; int s, f;

        for(int j=0; j<n; j++){
            in >> tmp;
            in >> s; in >> f;
            in >> tmp;
            vett[j] = new Activity(s,f);
        }
        select(vett, n);
    }
    return 0;
}
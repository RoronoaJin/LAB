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
};

void sort(Activity** vett, int n){
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(vett[i]->finish>vett[j]->finish)
                swap(vett[i],vett[j]);
        }
    }
}

void select(Activity** vett, int n){
    sort(vett, n);
    int sum = 1;
    int k = 0;
    
    for(int i=1; i<n; i++){
        if(vett[i]->start>=vett[k]->finish){
            sum++;
            k = i;
        }
    }
    out << sum << endl;
}

int main(){
    int n;
    for(int i=0; i<100; i++){
        in >> n;
        Activity** vett = new Activity*[n];
        char tmp; int s, f;

        for(int i=0; i<n; i++){
            in >> tmp;
            in >> s; in >> f;
            in >> tmp;
            vett[i] = new Activity(s,f);
        }
        select(vett, n);
    }
    return 0;
}
#include <iostream>
#include <fstream>

#define B 0 
#define R 1

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

template <class H>
class Nodo{
    public:
        H elemento;
        Nodo<H>* padre;
        Nodo<H>* dx;
        Nodo<H>* sx;
        bool colore;

        Nodo(H ele){
            elemento = ele;
            padre = NULL;
            dx = NULL;
            sx = NULL;
            colore = R;
        }
};

template <class H>
class Tree{
    public:
        Nodo<H>* radice;

        Tree(){
            radice = NULL;
        }
        void left_rot(Nodo<H>* x){
            if(x!=NULL){
                Nodo<H>* y = x->dx;
                if(y!=NULL){
                    x->dx = y->sx;
                    if(y->sx!=NULL)
                        y->sx->padre = x;
                    y->padre = x->padre;
                    if(x->padre==NULL)
                        radice = y;
                    else if(x==x->padre->sx)
                        x->padre->sx = y;
                    else
                        x->padre->dx = y;
                    y->sx = x;
                    x->padre = y;
                }
            }
        }
        void right_rot(Nodo<H>* x){
            if(x!=NULL){
                Nodo<H>* y = x->sx;
                if(y!=NULL){
                    x->sx = y->dx;
                    if(y->dx!=NULL)
                        y->dx->padre = x;
                    y->padre = x->padre;
                    if(x->padre==NULL)
                        radice = y;
                    else if(x==x->padre->dx)
                        x->padre->dx = y;
                    else
                        x->padre->sx = y;
                    y->dx = x;
                    x->padre = y;
                }
            }
        }
        void insertFix(Nodo<H>* x){
            while(x!=radice && x->padre->colore==R){
                if(x->padre==x->padre->padre->sx){
                    Nodo<H>* zio = x->padre->padre->dx;
                    if(zio!=NULL && zio->colore==R){
                        x->padre->colore = B;
                        zio->colore = B;
                        x->padre->padre->colore = R;
                        x = x->padre->padre;
                    }
                    else{
                        if(x==x->padre->dx){
                            x = x->padre;
                            left_rot(x);
                        }
                        x->padre->colore = B;
                        x->padre->padre->colore = R;
                        right_rot(x->padre->padre);
                        break;
                    }
                }
                else{
                    Nodo<H>* zio = x->padre->padre->sx;
                    if(zio!=NULL && zio->colore==R){
                        x->padre->colore = B;
                        zio->colore = B;
                        x->padre->padre->colore = R;
                        x = x->padre->padre;
                    }
                    else{
                        if(x==x->padre->sx){
                            x = x->padre;
                            right_rot(x);
                        }
                        x->padre->colore = B;
                        x->padre->padre->colore = R;
                        left_rot(x->padre->padre);
                        break;
                    }
                }
            }
            radice->colore = B;
        }
        void insert(H val){
            Nodo<H>* nuovo = new Nodo<H>(val);

            if(radice==NULL)
                radice = nuovo;
            else{
                Nodo<H>* iter = radice;
                Nodo<H>* tmp = NULL;

                while(iter!=NULL){
                    tmp = iter;

                    if(val>iter->elemento)
                        iter = iter->dx;
                    else
                        iter = iter->sx;
                }
                nuovo->padre = tmp;
                if(val>tmp->elemento)
                    tmp->dx = nuovo;
                else
                    tmp->sx = nuovo;
            }
            insertFix(nuovo);
        }
        int altezza(Nodo<H>* x){
            if(x==NULL)
                return 0;
            else{
                int s, d;
                s = altezza(x->sx);
                d = altezza(x->dx);
                if(s>d)
                    return 1+s;
                else
                    return 1+d;
            }
        }
};  

template <class H>
void metodo(int n){
    Tree<H>* t = new Tree<H>();
    H val;

    for(int i=0; i<n; i++){
        in >> val;
        t->insert(val);
    }
    out << t->altezza(t->radice) << endl;
}

int main(){
    string type; int n;
    for(int i=0; i<100; i++){
        in >> type; in >> n;
        if(type=="int")
            metodo<int>(n);
        else if(type=="double")
            metodo<double>(n);
    }
    return 0;
}
#include <iostream>
#include <fstream>

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

        Nodo(H ele){
            elemento = ele;
            padre = NULL;
            dx = NULL;
            sx = NULL;
        }
};

template <class H>
class Tree{
    private:
        Nodo<H>* radice;
    public:
        Tree(){
            radice = NULL;
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
        }
        Nodo<H>* cerca(H val){
            Nodo<H>* iter = radice;

            while(iter!=NULL && iter->elemento!=val){
                if(val>iter->elemento)
                    iter = iter->dx;
                else
                    iter = iter->sx;
            }
            return iter;
        }
        Nodo<H>* minimo(Nodo<H>* x){
            Nodo<H>* iter = x;

            while(iter->sx!=NULL)
                iter = iter->sx;
            return iter;
        }
        void Trapianta(Nodo<H>* x, Nodo<H>* y){
            if(x->padre==NULL)
                radice = y;
            else if(x==x->padre->dx)
                x->padre->dx = y;
            else
                x->padre->sx = y;
            if(y!=NULL)
                y->padre = x->padre;
        }
        void Cancella(H val){
            Nodo<H>* iter = cerca(val);
            if(iter!=NULL){
                if(iter->sx==NULL)
                    Trapianta(iter,iter->dx);
                else if(iter->dx==NULL)
                    Trapianta(iter,iter->sx);
                else{
                    Nodo<H>* y = minimo(iter->dx);
                    if(y->padre!=iter){
                        Trapianta(y,y->dx);
                        y->dx = iter->dx;
                        y->dx->padre = y;
                    }
                    Trapianta(iter,y);
                    y->sx = iter->sx;
                    y->sx->padre = y;
                }
            }
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
        void rotate(string type, H val){
            Nodo<H>* x = cerca(val);
            if(type=="left")
                left_rot(x);
            else
                right_rot(x);
        }
        void inorder(Nodo<H>* x){
            if(x!=NULL){
                inorder(x->sx);
                out << x->elemento << " ";
                inorder(x->dx);
            }
        }
        void preorder(Nodo<H>* x){
            if(x!=NULL){
                out << x->elemento << " ";
                preorder(x->sx);
                preorder(x->dx);
            }
        }
        void postorder(Nodo<H>* x){
            if(x!=NULL){
                postorder(x->sx);
                postorder(x->dx);
                out << x->elemento << " ";
            }
        }
        void print(string visita){
            if(visita=="inorder")
                inorder(radice);
            else if(visita=="preorder")
                preorder(radice);
            else if(visita=="postorder")
                postorder(radice);
            out << endl;
        }
};

template <class H>
void metodo(int n, string visita){
    Tree<H>* t = new Tree<H>();
    char tmp; H val;

    for(int i=0; i<n; i++){
        in >> tmp;
        if(tmp=='i'){
            while(tmp!=':')
                in >> tmp;
            in >> val;
            t->insert(val);
        }
        else if(tmp=='c'){
            while(tmp!=':')
                in >> tmp;
            in >> val;
            t->Cancella(val);
        }
        else if(tmp=='l'){
            while(tmp!=':')
                in >> tmp;
            in >> val;
            t->rotate("left",val);
        }
        else if(tmp=='r'){
            while(tmp!=':')
                in >> tmp;
            in >> val;
            t->rotate("right",val);
        }
    }
    t->print(visita);
}

int main(){
    string type; int n, m; string visita;
    for(int i=0; i<100; i++){
        in >> type; in >> n; in >> m; in >> visita;
        if(type=="int")
            metodo<int>(n+m,visita);
        else if(type=="double")
            metodo<double>(n+m,visita);
    }
    return 0;
}
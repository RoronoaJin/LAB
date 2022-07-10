#include <iostream>
#include <cstdlib>
#include <typeinfo>
#include <cmath>
#include <string>

using namespace std;

class A
{
	private:
		double *vec;
		short len;
		
	public:
		A(short w, double a, double b)
		{
			vec = new double [w];
			double MIN = a;
			double MAX = b;
			for(int i=0; i<w; i++)
			{
				vec[i]=a + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX/b+a));
			}
			len=w;
		}
		
		short getLen()
		{
			return len;
		}
		
		virtual double foo(short a)=0;
		
		virtual ostream &put(ostream &os)
		{
			os << " " << typeid(*this).name() << ": " << "vec=[ ";
			for(int i=0; i<len; i++)
			{
				os << vec[i] << " ";
			}
			return os << "]";
		}
		
	protected:
		double get(short i)
		{
			return vec[i%len];
		}
};

ostream &operator << (ostream &left, A &obj)
{
	return obj.put(left);
}

class B: public A
{
	private:
		int p;
		
	public:
		B(short m, short x, short y): A(m,x,y)
		{
			p=(int)rand()%((100*y)+(10*x));
		}
		
		double foo(short a)
		{
			return (double)log(prod(a, a/2));
		}
		
		ostream &put(ostream &os)
		{
			A::put(os);
			return os << ", p=" << p << ", foo(3)=" << this->foo(3);
		}
		
	protected:
		double prod(short s, double v)
		{
			double somma=0;
			
			for(int i=s; i<getLen(); i++)
			{
				somma+=get(i);
			}
			return (double)v*somma;
		}
};

template <class T>
class C: public A
{
	private:
		T y;
		
	public:
		C(short n, double x, double y): A(n,x,y)
		{
			if(typeid(y)==typeid(short))
			{
				y=n;
			}
			else
			{
				y=log(1+pow(cos(n), 2));
			}
		}
		
		double foo(short r)
		{
			return g(r);
		}
		
		double g(double k)
		{
			return (2*y)*(k+1);  
		}
		
		ostream &put(ostream &os)
		{
			A::put(os);
			return os << ", y=" << y << ", foo(3)=" << this->foo(3);
		}
	
};

int main()
{
	srand(111222333);
	const int DIM=50;
	A *vett[DIM];

      for(int i=0; i<DIM; i++) {
	short n=5+rand()%5;
	switch(rand()%3) {
	  case 0: 
	    vett[i]= new B(n, rand()%5 + 1, rand()%10 + 5);
	    break;
	  case 1:
	    vett[i]= new C<double>(n, rand()%5 + 1, rand()%10 + 5);
	    break;
	  case 2: 
	    vett[i]= new C<short>(n, rand()%5 + 1, rand()%10 + 5);
	}
    }
    
    cout << "PUNTO 1" << endl;
    for(int i=0; i<DIM; i++)
    {
    	cout << i << ") " << *vett[i] << endl;
	}
	
	
	cout << endl;
	cout << "PUNTO 2" << endl;
	
	int MAX=vett[0]->foo(3);
	float media;
	int somma=0;
 
    for (int i=0; i<DIM; i++)
    {
        if (vett[i]->foo(3)>MAX)
        {
            MAX=vett[i]->foo(3);
        }
		if(typeid(*vett[i])==typeid(C<double>))
		{
		somma=somma+((C<double>*)vett[i])->g(0.5);
		}
	}
	media=(float)somma/DIM;

    cout << "Max=" << MAX << " Avg=" << media << endl;
}









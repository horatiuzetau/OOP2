#include <iostream>

using namespace std;

int i;

class Complex{
    float re, im;
public:
//---------------------CONSTRUCTORI
    Complex();
    Complex(float);
    Complex(float, float);
    Complex(const Complex&);
//---------------------DESTRUCTOR
//---------------------SUPRAINCARCAREA DE OPERATORI
    Complex& operator=(const Complex&);
    Complex operator+(const Complex&);
    Complex operator-(const Complex&);
//---------------------CIN SI COUT
    friend istream& operator>>(istream&, Complex&);
    friend ostream& operator<<(ostream&, Complex&);
};
//---------------------CONSTRUCTORI
Complex::Complex(){
    re = im = 0;
}
Complex::Complex(float x){
    re = x;
    im = 0;
}
Complex::Complex(float x, float y){
    re = x;
    im = y;
}
Complex::Complex(const Complex& x){
    this->re = x.re;
    this->im = x.im;
}
//---------------------SUPRAINCARCAREA DE OPERATORI
Complex Complex::operator+(const Complex& x){
    Complex rezultat;
    rezultat.re = this->re + x.re;
    rezultat.im = this->im + x.im;

    return rezultat;
}
Complex Complex::operator-(const Complex& x){
    Complex rezultat;
    rezultat.re = this->re - x.re;
    rezultat.im = this->im - x.im;

    return rezultat;
}
Complex& Complex::operator=(const Complex& x){
    this->im = x.im;
    this->re = x.re;
}
//---------------------CIN SI COUT
istream& operator>>(istream& in, Complex& x){
    cout << "Introduceti partea reala: ";
    in >> x.re;
    cout << "Introduceti partea imaginara: ";
    in >> x.im;

    return in;
}
ostream& operator<<(ostream& out, Complex& x){
    if(x.re !=0 )
        out << x.re << " ";
    if(x.im != 0)
        out << " + (" <<  x.im << ")i";
    if(x.im != 0 || x.re != 0)
        out << endl;
    return out;
}

class Vector{
protected:
    int dim;
    Complex *v;
public:
//---------------------CONSTRUCTORI
    Vector();
    Vector(int);
    Vector(int, Complex*);
    Vector(const Vector&);

//---------------------DESTRUCTOR
    virtual ~Vector() = 0;
//---------------------FUNCTII
    virtual void push(const Complex&);
    void resize(int);
//---------------------SUPRAINCARCAREA DE OPERATORI
    friend istream& operator>>(istream&,Vector&);
    friend ostream& operator<<(ostream&, Vector&);
};
//---------------------CONSTRUCTORI
Vector::Vector(){
    dim = 0;
    v = nullptr;
}
Vector::Vector(int x){
    dim = x;
    v = nullptr;
}
Vector::Vector(int x, Complex* c){
    dim = x;
    try{
        v = c;
    }catch(bad_alloc& ba){
        cout << "Allocation failure!\n";
        exit(EXIT_FAILURE);
    }
}
Vector::Vector(const Vector& x){
    this->dim = x.dim;
    try{
        this->v = new Complex[this->dim];
    }catch(bad_alloc &ba){
        cout << "Allocation failure!\n";
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < x.dim; i++)
        this->v[i] = x.v[i];

}

//---------------------DESRUCTOR
Vector::~Vector(){
    delete[] v;
}
//---------------------FUNCTII
void Vector::resize(int a){
    Complex * aux;
    aux = new Complex[this->dim];
    for(i = 0; i < this->dim; i++)
        aux[i] = this->v[i];

    this->dim += a;
    this->v = new Complex[this->dim];

    for(i = 0; i < this->dim - a; i++){
        this->v[i] = aux[i];
    }
}
//Aici push baga un element in vector (la coada)
void Vector::push(const Complex& x){
    this->resize(1);
    this->v[this->dim - 1] = x;
}
//---------------------SUPRAINCARCAREA DE OPERATORI
istream& operator>>(istream& in, Vector& x){
    if(x.dim != 0) {
        cout << "La citire, vectorul se rescrie. Sunteti de acord?(1/0) : ";
        int k;
        cin >> k;
        if (!k)
            return in;
    }
    //SE RESCRIE VECTORUL
    cout << "Introduceti dimensiunea: ";
    cin >> x.dim;

    x.v = new Complex[x.dim];
    for(i = 0; i < x.dim; i++)
        cin >> x.v[i];

    return in;
}
ostream& operator<<(ostream& out, Vector& x){
    for(i = 0; i < x.dim; i++)
        out << x.v[i];

    return out;
}

class Stiva : public Vector{
public:
    void push(const Complex&) override;
    //In caz de se face cea de-a doua metoda(dubla mostenire), se va pune virtual
    //in fata la pop si empty de aici
    void pop();
    int empty();
};
//Aici push baga un element in stiva in fata
void Stiva::push(const Complex& x){
    this->resize(1);
    for(i = this->dim-1; i > 0; i--)
        this->v[i] = this->v[i-1];
    this->v[0] = x;
}

//Aici pop scoate elementul din fata si il si afiseaza, nu il returneaza, e doar o chestiune minora
void Stiva::pop(){
    cout << this->v[0];
    for(i = 0; i < this->dim; i++)
        this->v[i] = this->v[i+1];
    this->resize(-1);
}

int Stiva::empty(){
    return !dim;
}


//---------------------------METODA DE COADA CU O MOSTENIRE


class Coada : public Vector{
public:
    void pop() ;
    int empty();
};
//Aici push baga un element in coada in spate, ca la vector, deci nu mai facem push

//Aici pop scoate elementul din fata(CA LA STIVA) si il si afiseaza, nu il returneaza, e doar o chestiune minora
//Am observat ca am combinata stiva cu vectorul, oarecum, si mi-a reultat coada
void Coada::pop(){
    cout << this->v[0];
    for(i = 0; i < this->dim; i++)
        this->v[i] = this->v[i+1];
    this->resize(-1);
}

int Coada::empty(){
    return !dim;
}


int main() {
    Coada x;
    cin >> x;
    Complex b(3, 5);
    x.push(b);
    cout << x << endl;
    x.pop();
    cout << endl << x;
    if(x.empty())
        cout << "bos";

    return 0;
}

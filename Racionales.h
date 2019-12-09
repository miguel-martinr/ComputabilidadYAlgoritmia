#include<cassert>
#include<iostream>



class rational_t {
 public:
  rational_t(int num=0, int den=1) {
	assert(den != 0); 
	 num_ = num, den_ = den; }
  ~rational_t(){}

  void set_num(int num) { num_ = num; }
  int get_num() { return num_; }


  void set_den(int den) {
   assert(den!=0);
   den_ = den;
  }
 
  int get_den() { return den_; }



  void read(std::istream& source);
  void read(void);
  void print(std::ostream& out);

  void add(rational_t A, rational_t B);
  void sub(rational_t A, rational_t B);
  void mul(rational_t A, rational_t B);
  void div(rational_t A, rational_t B); 
  char comp(rational_t A);

 private:

  int num_;
  int den_;

  int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
  }
};

// Lee un rational_t desde un istream, su uso es preferible para ficheros de texto.
void rational_t::read(std::istream& source) {
  int aux;
  source>>aux;
  set_num(aux);
  source.seekg(1,std::ios::cur);
  source>>aux;
  set_den(aux);
}


// Lee un rational_t desde teclado.
void rational_t::read(void) {
  int aux;  
  std::cin>>aux;
  set_num(aux);
  getchar();
  std::cin>>aux;
  set_den(aux);
}


// Imprime un rational_t ya sea en un fichero o en pantalla. 
void rational_t::print(std::ostream& out=std::cout) {
  if (get_den() == 1) {
    out<<get_num();
  } else if(get_num() == 0) {
    out<<0;
  } else if (get_num() == get_den()) {
    out<<1;
  } else {
    int mcd = gcd(get_num(), get_den());
    if ((get_den() / mcd) == 1) {
      out<<get_num()/mcd;
    } else {	
      out<<get_num()/mcd<<" / "<<get_den()/mcd;
    }
  }
}
    


// Suma dos rational_t y su resultado se guarda en el objeto invocante.
void rational_t::add(rational_t A, rational_t B) {
  if (A.get_den()==B.get_den()) {
    set_num(A.get_num()+B.get_num());
    set_den(A.get_den());
  } else {
    set_num(A.get_num()*B.get_den() + A.get_den()*B.get_num());
    set_den(A.get_den()*B.get_den());
  }
}


// Resta dos rational_t y su resultado se guarda en el objeto invocante.
void rational_t::sub(rational_t A, rational_t B) {
  if (A.get_den()==B.get_den()) {
    set_num(A.get_num()-B.get_num());
    set_den(A.get_den());
  } else {
    set_num(A.get_num()*B.get_den() - A.get_den()*B.get_num());
    set_den(A.get_den()*B.get_den());
  }
}


// Multiplica dos rational_t y su resultado se guarda en el objeto invocante.
void rational_t::mul(rational_t A, rational_t B) {
  set_num(A.get_num()*B.get_num());
  set_den(A.get_den()*B.get_den());
}

// Divide dos rational_t y su resultado se guarda en el objeto invocante.
void rational_t::div(rational_t A, rational_t B) {
  //if equal -> 1
  set_num(A.get_num()*B.get_den());
  set_den(A.get_den()*B.get_num());
}


// Compara al objeto invocante con el que se le pasa como parámetro. Devuelve <,> o =.
char rational_t::comp(rational_t A) {
  double val, valA;
  val = (double) get_num()/(double) get_den();
  valA = (double) A.get_num()/(double) A.get_den();
  if(val < valA)
    return '<';
    else if (val > valA)
    return '>';
    else
    return '=';
}

// SOBRECARGA DE OPERADORES

// Impresión (<<)
std::ostream& operator<<(std::ostream& out, rational_t A) {
  A.print(out);
  return out;
}

// Suma (+)
rational_t operator+(rational_t A, rational_t B) {
  rational_t C;
  C.add(A, B);
  return C;
}

// Resta (-)
rational_t operator-(rational_t A, rational_t B) {
  rational_t C;
  C.sub(A, B);
  return C;
}

// Multiplicación (*)
rational_t operator*(rational_t A, rational_t B) {
  rational_t C;
  C.mul(A, B);
  return C;
}

// División (/)
rational_t operator/(rational_t  A, rational_t B) {
  rational_t C;
  C.div(A, B);
  return C;
}


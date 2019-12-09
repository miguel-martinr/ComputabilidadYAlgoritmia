#include "Racionales.h"

#include <iostream>
#include <cassert>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// IMPRIMIR OPERACIONES EN FICHERO
// Se le pasa el fichero ya abierto.
// NO! cierra el fichero
void print_op(ofstream& file_out, rational_t rat1, rational_t rat2) {
  assert(file_out.is_open());
  file_out<<rat1<<" + "<<rat2<<" = "<<rat1 + rat2<<endl;
  file_out<<rat1<<" - "<<rat2<<" = "<<rat1 - rat2<<endl;
  file_out<<rat1<<" * "<<rat2<<" = "<<rat1 * rat2<<endl;
  file_out<<rat1<<" / "<<rat2<<" = "<<rat1 / rat2<<endl;
  file_out<<rat1<<" "<<rat1.comp(rat2)<<" "<<rat2<<endl;
}


// IMPRIMIR OPERACIONES POR PANTALLA
void  print_op(ostream& out, rational_t rat1, rational_t rat2) {
  out<<rat1<<" + "<<rat2<<" = "<<rat1 + rat2<<endl;
  out<<rat1<<" - "<<rat2<<" = "<<rat1 - rat2<<endl;
  out<<rat1<<" * "<<rat2<<" = "<<rat1 * rat2<<endl;
  out<<rat1<<" / "<<rat2<<" = "<<rat1 / rat2<<endl;
  out<<rat1<<" "<<rat1.comp(rat2)<<" "<<rat2<<endl;
}


// IMPRIMIR DE FICHERO A FICHERO
// Se le pasain los ficheros de entrada y salida ya  abiertos.
// NO! cierra los ficheros.
void print_ff(ifstream& file_in, ofstream& file_out) {
  assert(file_in.is_open() && file_out.is_open());
  while(file_in.peek() != EOF && file_in.peek() != '\n') {
    rational_t rat1, rat2;
    rat1.read(file_in);
    rat2.read(file_in);
    print_op(file_out, rat1, rat2);
    file_out<<endl;
    file_in.seekg(1, ios::cur);    // Adelantar el cursor un espacio para saltar el \n
  }
}


// IMPRIMIR DE FICHERO A PANTALLA (-fp)
// Se le pasa el fichero de entrada ya abierto.
// NO! cierra el fichero.
void print_fp(ifstream& file_in) {
  assert(file_in.is_open());
  while(file_in.peek() != EOF && file_in.peek() != '\n') {
    rational_t rat1, rat2;
    rat1.read(file_in);
    rat2.read(file_in);
    print_op(cout, rat1, rat2);
    cout<<endl;
    file_in.seekg(1, ios::cur);
  }
}







int main(int argc, char *argv[]){

  if(argc==1) {

    //Instrucciones para pasar parámetros
    system("clear");
    char aux;
    ifstream file_inst;
    file_inst.open("instrucciones.txt");
    if(!file_inst.is_open()) {
      cout<<"No se encontro el fichero de instrucciones."<<endl<<endl;
    } else {
      file_inst.get(aux);
      while(!file_inst.eof()) {
        file_inst.get(aux);
	cout<<aux;
      }
      file_inst.close();
    }
  } else {
      string argv_1=argv[1];    // Conversion de *char[] a string para hacer posible
			        // las comparaciones en los if posteriores.

     
       if (argv_1=="-pp") {
	//DE PANTALLA A PANTALLA
    	int num_pares;
    	rational_t rat_v[50];
    	cout<<"\nNumero de pares de numeros racionales: ";cin>>num_pares;
    	for(int i=0, j=0; i<num_pares; i++, j+=2) {
    	  rat_v[j].read();
    	  rat_v[j+1].read();
    	}
    	cout<<endl;
    	for(int i=0, j=0; i<num_pares; i++, j+=2) {
    	  cout<<endl;
    	  print_op(cout, rat_v[j], rat_v[j+1]);
    	}
       } else if (argc==3) {

      string argv_1 = argv[1];

     
      if(argv_1== "-fp") {
	//DE FICHERO A PANTALLA
	ifstream file_in;
	file_in.open(argv[2]);
	if (!file_in.is_open()) {
	  cout<<"Error apertura de fichero.\n";
	} else {
	  print_fp(file_in);
	  file_in.close();
        }
      } else if (argv_1=="-pf") {


        //DE PANTALLA A FICHERO
        ofstream file_out;
	file_out.open(argv[2]);
	if (!file_out.is_open()) {
	  cout<<"Error apertura de fichero.\n";
	} else {
	  int num_pares;
	  rational_t rat1, rat2;
	  cout<<"\nNumero de pares de numeros racionales: ";cin>>num_pares;
	  for (int i=0; i<num_pares; i++) {
	    rat1.read();
	    getchar();
	    rat2.read();
	    print_op(file_out, rat1, rat2);
	    file_out<<endl;
	  }
	  file_out.close();
        }
      } else {


	//(DEFECTO) DE FICHERO A FICHERO
	ifstream file_in;
	ofstream file_out;
	file_in.open(argv[1]);
	file_out.open(argv[2]);
	if(!(file_in.is_open() && file_out.is_open()))
	  cout<<"Error apertura de fichero.\n";
	else
	print_ff(file_in, file_out);
	file_in.close();
	file_out.close();
        }
      }
    }
  return 0;
}

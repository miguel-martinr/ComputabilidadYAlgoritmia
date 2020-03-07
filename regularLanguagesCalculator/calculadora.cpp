// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia (CyA)
// Curso: 2º
// Práctica 3 CyA - Calculadora para lenguajes formales
// Autor: Miguel alejandro Martín Reyes
// Correo: alu0101209777@ull.edu.es
// Fecha: 6/10/2019
// Archivo calculadora.h: Contiene la implementación de la clase "calculadora".
// Esta
//                        clase se construye a partir de dos strings (nombres de
//                        ficheros de entrada y salida) y  un int (código de
//                        operación). Tomando los lenguajes del fichero de
//                        entrada como operandos, se encarga de imprimir en el
//                        fichero de salida los resultados. Para más información
//                        véase Enunciado de la práctica.
// Referencias:
//                    Enunciado de la práctica:
//                    https://campusvirtual.ull.es/1920/pluginfile.php/159482/mod_assign/introattachment/0/CYA_1920_Practica_3.pdf?forcedownload=0
// Historial de revisiones
//                    6/10/2019 - Creación (primera versión) del código

#include "calculadora.h"

#include <fstream>
#include <iostream>
#include <stack>

using namespace std;

calculadora::calculadora(string file_in, string file_out, int code) {
  file_in_ = file_in;
  file_out_ = file_out;
  code_ = code;
}

int calculadora::start(int pot) {
  ifstream file_in;
  ofstream file_out;
  file_in.open(file_in_);
  file_out.open(file_out_);

  string line;
  stack<string> linestack;  // Pila para verificar que hay dos operandos.
  lenguaje l1, l2;

  // Comprobación de apertura ficheros E/S
  if (!file_in.is_open() || !file_out.is_open()) {
    cout << "Error al cargar fichero." << endl;
    return 1;
  }

  switch (code_) {
    case 1: {  // CONCATENACIÓN
     // while (!file_in.eof()) {
       // getline(file_in, line);
       // if (line.size() != 0) {
        //  linestack.push(line);
       // }
        /*if (linestack.size() == 2) {
          l2.reset(linestack.top());
          linestack.pop();
          l1.reset(linestack.top());
          linestack.pop();
          file_out << l1.conc(l2).write() << endl;
        }*/
     // }
        operate_conc(file_in, file_out, pot);
      break;
    }

    case 2: {  // UNIÓN
      while (!file_in.eof()) {
        getline(file_in, line);
        if (line.size() != 0) {
          linestack.push(line);
        }
        if (linestack.size() == 2) {
          l2.reset(linestack.top());
          linestack.pop();
          l1.reset(linestack.top());
          linestack.pop();
          file_out << l1.Union(l2).write() << endl;
        }
      }
      break;
    }

    case 3: {  // INTERSECCIÓN
      while (!file_in.eof()) {
        getline(file_in, line);
        if (line.size() != 0) {
          linestack.push(line);
        }
        if (linestack.size() == 2) {
          l2.reset(linestack.top());
          linestack.pop();
          l1.reset(linestack.top());
          linestack.pop();
          file_out << l1.intersec(l2).write() << endl;
        }
      }
      break;
    }

    case 4: {  // DIFERENCIA
      while (!file_in.eof()) {
        getline(file_in, line);
        if (line.size() != 0) {
          linestack.push(line);
        }
        if (linestack.size() == 2) {
          l2.reset(linestack.top());
          linestack.pop();
          l1.reset(linestack.top());
          linestack.pop();
          file_out << l1.dif(l2).write() << endl;
        }
      }
      break;
    }

    case 5: {  // SUBLENGUAJE
      while (!file_in.eof()) {
        getline(file_in, line);
        if (line.size() != 0) {
          linestack.push(line);
        }
        if (linestack.size() == 2) {
          l2.reset(linestack.top());
          linestack.pop();
          l1.reset(linestack.top());
          linestack.pop();
          file_out << (l1.subde(l2) ? "TRUE" : "FALSE") << endl;
        }
      }
      break;
    }

    case 6: {  // IGUALDAD
      while (!file_in.eof()) {
        getline(file_in, line);
        if (line.size() != 0) {
          linestack.push(line);
        }
        if (linestack.size() == 2) {
          l2.reset(linestack.top());
          linestack.pop();
          l1.reset(linestack.top());
          linestack.pop();
          file_out << (l1.iguala(l2) ? "TRUE" : "FALSE") << endl;
        }
      }
      break;
    }

    case 7: {  // INVERSA
      while (!file_in.eof()) {
        getline(file_in, line);
        if (line.size() != 0) {
          l1.reset(line);
          file_out << l1.inv().write() << endl;
        }
      }
      break;
    }

    case 8: {  // POTENCIA
      while (!file_in.eof()) {
        getline(file_in, line);
        if (line.size() != 0) {
          l1.reset(line);
          file_out << l1.pot(pot).write() << endl;
        }
      }
      break;
    }

    case 9: {  // CIERRE POSITIVO
      while (!file_in.eof()) {
        getline(file_in, line);
        if (line.size() != 0) {
          l1.reset(line);
          file_out << l1.positive().write() << endl;
        }
      }
      break;
    }

    case 10: {  // CIERRE DE KLEENE
      while (!file_in.eof()) {
        getline(file_in, line);
        if (line.size() != 0) {
          l1.reset(line);
          file_out << l1.kleene().write() << endl;
        }
      }
      break;
    }

    default: { cout << "Codigo desconocido." << endl; }
  }
  file_in.close();
  file_out.close();
  return 0;
}

void calculadora::operate_conc(ifstream& file_in, ofstream& file_out, int size) {
      	lenguaje aux;
  string str;
  stack<lenguaje> stackaux;
  while (!file_in.eof()) {
    for (int i= 0; i<size; i++) {
      getline(file_in, str);
      aux.reset(str);
      stackaux.push(aux);
    }
  
    if (stackaux.size() == size) {
      lenguaje legvec[size];
      for (int i=size-1; i >= 0; i--) {
        legvec[i]=stackaux.top();
        stackaux.pop();
      }
      lenguaje lout=legvec[0];
      for (int i=1; i < size-1; i++) {
        lout = lout.conc(legvec[i]);
      }
      file_out<<lout.write()<<endl;
    }
  }
}

// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia (CyA)
// Curso: 2º
// Práctica 3 CyA - Calculadora para lenguajes formales
// Autor: Miguel alejandro Martín Reyes
// Correo: alu0101209777@ull.edu.es
// Fecha: 6/10/2019
// Archivo mainl.cpp: programa cliente. Contiene la función main del proyecto
//                    que usa las clases lenguaje y calculadora que realizan el
//                    trabajo de leer el fichero de entrada identificando
//                    patrones en el texto que dan lugar al fichero de salida.
// Referencias:
//                    Enunciado de la práctica:
//                    https://campusvirtual.ull.es/1920/pluginfile.php/159482/mod_assign/introattachment/0/CYA_1920_Practica_3.pdf?forcedownload=0
// Historial de revisiones
//                    6/10/2019 - Creación (primera versión) del código

#include "../include/calculadora.h"

#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
  if (argc == 2 || argc == 3) {
    cout << "Número inesperado de argumentos." << endl;
    return 1;
  }
  if (argc == 1) {
    ifstream inst("cfg/instrucciones.txt", ios::in);
    if (!inst.is_open()) {
      cout << "Error al cargar instrucciones." << endl;
      return 2;
    }
    char aux;
    while (!inst.eof()) {
      inst.get(aux);
      cout << aux;
    }
    return 0;
  }
  int code = atoi(argv[3]);
  calculadora calc1(argv[1], argv[2], code);
  if (argc >= 5) {
    int pot = atoi(argv[4]);
    calc1.start(pot);
  } else {
    calc1.start();
  }

  return 0;
}

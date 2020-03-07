// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia (CyA)
// Curso: 2º
// Práctica 3 CyA - Calculadora para lenguajes formales
// Autor: Miguel alejandro Martín Reyes
// Correo: alu0101209777@ull.edu.es
// Fecha: 6/10/2019
// Archivo calculadora.h: Contiene la definición de la clase "calculadora". Esta
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

#include "lenguaje.h"
#include <fstream>
class calculadora {
 public:
  calculadora(string file_name, string file_out, int code);
  ~calculadora() {}

  int start(int pot = 1);  // Se encarga de realizar las operaciones según el código.
                     // pot es la hipotética potencia a la que se debe elevar el
                     // lenguaje (en caso de que el código sea 8).

	  void operate_conc(ifstream& file_in, ofstream& file_out, int size);

 private:
  int code_;
  string file_in_;
  string file_out_;
};

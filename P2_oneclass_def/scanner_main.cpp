/************************************************************************************************
 * Programador: Miguel Alejandro Martín Reyes
 * El siguiente código hace uso de la clase scanner (analizador léxico) para analizar todos los lexemas
 * de un fichero de entrada e imprimir los resultados obtenidos en un fichero de salida.
 * Fecha:
 * 
 * 
 * 
 * *********************************************************************************************/




#include "scanner.h"

//#include <iomanip>
#include <fstream>
#include <stack>

int main(int argc, char* argv[]) {


  ifstream file_in;
  // Verificar correcto numero de argumentos 
  if(argc == 2 || argc > 3) {
    cout << "Numero inesperado de argumentos.\n";
    return 0;
  }

  // Mostrar instrucciones en caso de no recibir solo 1 argumento
  if (argc == 1) {
    system("clear");
    file_in.open("scanner_cfg/instrucciones.txt");
    if (!file_in.is_open()) {
      cout << "Error al cargar fichero de instrucciones\n";
      return 1;
    } else {
      char aux;
      file_in.get(aux);
      while (!file_in.eof()) {
        cout << aux;
        file_in.get(aux);
      }
      file_in.close();
    }
  
    return 1;
  }


  // En caso de recibir dos argumentos (entrada.txt salida.txt)
  ofstream file_out;
  file_in.open(argv[1]);
  file_out.open(argv[2]);
  if (!file_in.is_open() || !file_out.is_open()) {
    cout << "Error al cargar ficheros.\n";
    return 1;
  } else {

    // MODIFICACION
    stack<string> parenta, parentc, corcha, corchc;

    scanner syntan;  // objeto scanner syntan (Syntax Analyzer)
    string str;
    char aux;  // Variable auxiliar para facilitar lectura de file_in
    do {
      file_in >> str;

      // MODIFICACION
      if (str == "(")
        parenta.push(str);
      if (str == ")") {
        if (parenta.empty()) {
          cout<<"Error parent\n";
	  return 1;
	}
	parenta.pop();
      }

      if (str == "{")
        corcha.push(str);
      if (str == "}") { 
        if (corcha.empty()) {
          cout<<"Error corch\n";
	  return 1;
	}
	corcha.pop();
      }



      file_out << syntan.analyze(str) << endl;
      file_in.get(aux);
    } while (file_in.peek() != EOF);
    file_in.close();
    file_out.close();

   //MODIFICACION
   if (!parenta.empty() || !corcha.empty())
     cout<<"Error parentesis o corchetes.\n";  

  
  }

	return 0;
}

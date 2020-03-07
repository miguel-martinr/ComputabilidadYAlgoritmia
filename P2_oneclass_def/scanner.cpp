/************************************************************************************************
 * Programador: Miguel Alejandro Martín Reyes
 * El siguiente código constituye la implementación de la clase scanner.h (analizador léxico).
 * 
 * Fecha:
 * 
 * 
 * 
 * *********************************************************************************************/




#include "scanner.h"

#include <fstream>
#include <cctype>

// El constructor abre los ficheros donde se encuentran los elementos
// de los contenedores e inicializa los mismos insertando cada elemento
// en el contenedor que corresponde. Todos los elementos formados por letras
// se pasan "estandarizados" (en mayúsculas) al contenedor .
scanner::scanner(void) {
string cont_names[3] = {"scanner_cfg/operadores.txt", "scanner_cfg/signpunt.txt", "scanner_cfg/palabesp.txt"};
  ifstream file_in;
  for (int i=0; i < NUM_CONT; i++) {
    file_in.open(cont_names[i]);
    if (!file_in.is_open()) {
      cout<<"Error al cargar fichero "<<cont_names[i]<<endl;
    } else {
      char ch_aux;                          // ch_aux : Variable auxiliar para facilitar lectura de fichero.
      file_in.get(ch_aux);             
      while (file_in.peek() != EOF) {
        file_in.seekg(-1, ios::cur);   
        string str;
        file_in>>str;
        if (str != "\n" && str != " ")
          cont_[i].insert(standarize(str)); // insertar en contenedor elemento ESTANDARIZADO.
        file_in.get(ch_aux);
      }
      file_in.close();
    }
  }
}

// Analiza str y devuelve el string final (token + str o STR)
string scanner::analyze(string str) {

  string str_out;
  bool floag;
  if (check_num(str, str_out)) {
    return str_out;  // INT o FLOT
  } else {
    if (check_cont(standarize(str), str_out)) {  // NOTA: Es importante pasar str estandarizada a check_cont
      return str_out;  // STR
    } else {
        if (check_pal(str, str_out))
         return str_out;  // PAL
    }
  }
  return token[3] + " " + str;  // DESCONOCIDA
}


// Verifica si str es un número válido y si es flotante o entero.
bool scanner::check_num(string str, string& str_out) {
  str_out.clear();
  int comma = 0;                            // Cuenta cuantas comas o puntos tiene str
  const char* ptr = str.c_str();
  for (int i=0; i < str.size(); i++) {
    if (!(isdigit(ptr[i]) || ptr[i] == '.' || ptr[i] == ',') || comma > 1)
      return false;
    (ptr[i] == ',' || ptr[i] == '.') ? comma++ : comma = comma;
  }
  if (comma == 1)                           // Si es número y tiene 1 punto o coma entonces es flotante
   str_out = token[5] + " " + str;
   else
   str_out = token[4] + " " + str;
  
  return true;
  
}


// Verifica si str coincide con algun elemento de los contenedores.
bool scanner::check_cont(string str, string& str_out) {
  str_out.clear(); 
  for (int i = 0; i < NUM_CONT; i++) {
    if (cont_[i].find(str) != cont_[i].end()) {
      if (i == 2)                          // Si se trata del contendor 2 es una 
                                           // palabra especial, por lo que a str_out
                                           // se le asigna la palabra estandarizada.
        str_out = standarize(str);
      else 
        str_out = token[i] + " " + str;
      return true;
    }
  }
  return false;
}


// Verifica si str se trata de una  palabra no especial
bool scanner::check_pal(string str, string& str_out) {
  str_out.clear();
  const char* ptr = str.c_str();
  if (!isalpha(ptr[0]))
    return false;
  for (int i=0; i < str.size(); i++) {
    if (!isalpha(ptr[i]) && !isdigit(ptr[i]))
      return false;
  }
  str_out = token[2] + " " + str;
  return true;
}






// Devuelve una versión estandarizada de  str cambiando toda letra minúscula a mayúscula.
string scanner::standarize(string str) {
  char str_aux[str.size() + 1];
  str.copy(str_aux, str.size());
  for (int i=0; i < str.size(); i++) {
    if (str_aux[i] > 96 && str_aux[i] < 123)
      str_aux[i] -= 32;
  }
  string str_out = "";
  for (int i=0; i < str.size(); i++)
    str_out += str_aux[i];
  return str_out; 
}

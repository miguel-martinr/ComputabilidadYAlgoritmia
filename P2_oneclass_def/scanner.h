/************************************************************************************************
 * Programador: Miguel Alejandro Martín Reyes
 * El siguiente código constituye la definición de la clase scanner.h (analizador léxico).
 * Su método principal (analyze()) analiza un lexema de tipo string y devuelve otro objeto
 * de tipo string indicando el token que le corresponde.
 * 
 * Fecha:
 * 
 * 
 * 
 * *********************************************************************************************/




#include <iostream>
#include <string>
#include <unordered_set>

#define NUM_CONT 3  // Número de contenedores.

using namespace std;

class scanner {

 public:
   scanner(void);
   ~scanner(void){}
   
   string analyze(string str);  // Analiza str y retorna la cadena final: token + lexema
                                // o LEXEMA según sea el caso.



 private:

   // Vector de contenedores. 
   unordered_set<string> cont_[NUM_CONT]; // 0: operadores, 1: signpunt, 
                                          // 2:palabesp

   string token[6] = {"OP", "SIG", "PAL", "DESCONOCIDA", "INT", "FLOT" };
                    // 0      1      2          3          4       5             

   // En los tres primeros métodos a continuación: en caso de retornar true, la
   // cadena str_out contendrá la cadena final, es decir, token + lexema o LEXEMA, 
   // según sea el caso.

   bool check_num(string str, string& str_out);  // Verifica si str es un número 
                                                 // válido y si es int o float.

   bool check_cont(string str, string& str_out); // Verifica si str coincide con
                                                 // algún elemento de los conetenedores.

   bool check_pal(string str, string& str_out);  // Verifica si str es una palabra 
                                                 // no especial.

   string standarize(string str);                // "Estandariza" str poniendo toda letra
                                                 // minúscula a mayúscula. De este modo el
                                                 // programa main no diferencia entre
                                                 // minúsculas y mayúsculas.
};

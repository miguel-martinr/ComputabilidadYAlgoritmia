// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia (CyA)
// Curso: 2º
// Práctica 3 CyA - Calculadora para lenguajes formales
// Autor: Miguel alejandro Martín Reyes
// Correo: alu0101209777@ull.edu.es
// Fecha: 6/10/2019
// Archivo lenguaje.h:  Contiene la definición de la clase "lenguaje". Estos
//                      objetos se construyen a partir de un objeto string
//                      debidamente formateado: una llave "{" para indicar el
//                      incio del lenguaje, y una llave "}" para indicar el
//                      final. Las cadenas que forman el lenguaje deben estar
//                      separadas por comas.
//
// Notas:
//   Caracteres no permitidos como cadenas comunes: {, }, .
//   Lenguaje vacío: {}
//   Cadena vacía: &
// Referencias:
//                    Enunciado de la práctica:
//                    https://campusvirtual.ull.es/1920/pluginfile.php/159482/mod_assign/introattachment/0/CYA_1920_Practica_3.pdf?forcedownload=0
// Historial de revisiones
//                    6/10/2019 - Creación (primera versión) del código

#include <set>
#include <string>

using namespace std;

class lenguaje {
 public:
  lenguaje(void) {
    set_inf(false);
  }  // Por defecto los lenguajes no son infinitos.

  lenguaje(
      string dirty_line);  // dirty_line : string formateado (ej: {a, b, c})
  ~lenguaje(void) {}

  set<string>& get_set(void) {
    return set_;
  }  // Retorna el set_. Es útil para acceder al mismo y hacer comparaciones
     // desde objetos externos.

  bool empty(void) { return set_.empty(); }  // Verifica si es lenguaje vacío.
  bool onlyepsilon(
      void);  // Verifica si el lenguaje solo contiene la cadena vacía.
  string write(
      void);  // Retorna un string formateado del lenguaje (ej: {a, b, c})
  void reset(string dirty_line);     // Construye de nuevo el objeto a partir de
                                     // dirty_line
  void clear(void) { reset("{}"); }  // Convierte al lenguaje en lenguaje vacío.

  lenguaje conc(lenguaje l1);   // Retorna el lenguaje resultante de la
                                // concatenación de lenguaje_invocante * l1
  lenguaje Union(lenguaje l1);  // Retorna el lenguaje resultante de la unión de
                                // lenguaje_invocante U l1
  lenguaje intersec(lenguaje l1);  // Retorna el lenguaje resultante de la
                                   // intersección de lenguaje_invocante ∩ l1
  lenguaje dif(lenguaje l1);       // Retorna el lenguaje resultante de la
                                   // diferencite entre lenguaje_invocante - l1
  bool subde(lenguaje l1);  // Retorna true si el lenguaje invocante está
                            // contenido en l1
  bool iguala(
      lenguaje l1);  // Retorna true si el lenguaje invocante y l1 son iguales.

  lenguaje pot(int n);  // Retorna el lenguaje resultante de elevar el lenguaje
                        // resultante a la n
  lenguaje kleene(void);  // Retorna al menos las 10 primeras cadenas del cierre
                          // de kleene del lenguaje invocante.
  lenguaje positive(void);  // Retorna al menos las 10 primeras cadenas del
                            // cierre positivo del lenguaje invocante.
  lenguaje inv(void);       // Retorna la inversa del lenguaje invocante.

 private:
  lenguaje potpot(lenguaje& l1, int& n);  // Método recursivo interno utilizado
                                          // por pot para calcular la potencia.
  bool is_inf(void) {
    return inf_;
  }  // Retorna true si el lenguaje invocante se toma como infinito.
  void set_inf(bool inf) {
    inf_ = inf;
  }           // Permite setear el inf_ del lenguaje.
  bool inf_;  // Permite saber si se toma el lenguaje como infinito o finito.
              // (Útil para el método write).
  string str_inv(string str);  // Retorna la inversa de str.
  set<string> set_;            // Conjunto de cadenas del lenguaje.
};
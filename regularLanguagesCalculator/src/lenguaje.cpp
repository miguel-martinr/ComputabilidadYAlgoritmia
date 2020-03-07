// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia (CyA)
// Curso: 2º
// Práctica 3 CyA - Calculadora para lenguajes formales
// Autor: Miguel alejandro Martín Reyes
// Correo: alu0101209777@ull.edu.es
// Fecha: 6/10/2019
// Archivo lenguaje.cpp: Contiene la implementación de la clase "lenguaje".
//
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

#include "../include/lenguaje.h"

#include <cassert>
#include <iostream>
#include <iterator>

// Constructor a partir de string dirty_line formateada. Recorre dirty_line char
// a char.
lenguaje::lenguaje(string dirty_line) {
  set_inf(false);
  string clean;
  const char* ptr = dirty_line.c_str();
  for (int i = 0; i < dirty_line.size(); i++) {
    if (ptr[i] != ' ' && ptr[i] != '\n' && ptr[i] != '{' && ptr[i] != '.') {
      if (ptr[i] == ',' || ptr[i] == '}') {
        if (!clean.empty()) {
          set_.insert(clean);
          clean.clear();
        }
      } else {
        clean += ptr[i];
      }
    }
  }
}

// ONLYEPSILON
bool lenguaje::onlyepsilon(void) {
  if ((set_.find("&") != set_.end()) && set_.size() == 1) return true;
  return false;
}

// WRITE
string lenguaje::write(void) {
  string str_out;
  set<string>::iterator itr;
  for (itr = set_.begin(); itr != set_.end(); ++itr) {
    if (itr == --set_.end()) {
      if (is_inf())  // Si el lenguaje es infinito se añaden tres puntos al
                     // final (sin añadirlos al set).
        str_out += *itr + ", ...";
      else
        str_out += *itr;
    } else {
      str_out += *itr + ", ";
    }
  }
  return "{" + str_out + "}";
}

// RESET
void lenguaje::reset(string dirty_line) {
  lenguaje aux(dirty_line);
  *this = aux;
}

// CONCATENACIÓN
lenguaje lenguaje::conc(lenguaje l1) {
  if (this->onlyepsilon()) return l1;
  if (l1.onlyepsilon()) return (*this);
  lenguaje lout;
  if (empty() || l1.empty()) return lout;
  set<string>::iterator itr1, itr2;
  for (itr1 = set_.begin(); itr1 != set_.end(); ++itr1) {
    for (itr2 = l1.get_set().begin(); itr2 != l1.get_set().end(); ++itr2) {
      if (*itr1 == "&")
        lout.get_set().insert(*itr2);
      else if (*itr2 == "&")
        lout.get_set().insert(*itr1);
      else
        lout.get_set().insert(*itr1 + *itr2);
    }
  }
  return lout;
}

// UNIÓN
lenguaje lenguaje::Union(lenguaje l1) {
  lenguaje lout;
  set<string> set_vect[2] = {get_set(), l1.get_set()};
  set<string>::iterator itr;
  for (int i = 0; i < 2; i++) {
    for (itr = set_vect[i].begin(); itr != set_vect[i].end(); ++itr) {
      lout.get_set().insert(*itr);
    }
  }

  return lout;
}

// INTERSECCIÓN
lenguaje lenguaje::intersec(lenguaje l1) {
  lenguaje lout;
  set<string>::iterator itr;
  for (itr = get_set().begin(); itr != get_set().end(); ++itr) {
    if (l1.get_set().find(*itr) != l1.get_set().end())
      lout.get_set().insert(*itr);
  }
  return lout;
}

// DIFERENCIA
lenguaje lenguaje::dif(lenguaje l1) {
  lenguaje lout;
  set<string>::iterator itr;
  for (itr = get_set().begin(); itr != get_set().end(); ++itr) {
    if (l1.get_set().find(*itr) == l1.get_set().end())
      lout.get_set().insert(*itr);
  }
  return lout;
}

// SUBLENGUAJE
bool lenguaje::subde(lenguaje l1) {
  set<string>::iterator itr;
  for (itr = get_set().begin(); itr != get_set().end(); ++itr)
    if (l1.get_set().find(*itr) == l1.get_set().end()) return false;

  return true;
}

// IGUALDAD
bool lenguaje::iguala(lenguaje l1) {
  if (subde(l1) && l1.subde(*this)) return true;

  return false;
}

// INVERSA DE LENGUAJE
lenguaje lenguaje::inv(void) {
  lenguaje lout;
  set<string>::iterator itr;
  for (itr = get_set().begin(); itr != get_set().end(); ++itr)
    lout.get_set().insert(str_inv(*itr));
  return lout;
}

// INVERSA DE CADENA
string lenguaje::str_inv(string str) {
  int n = str.size();
  for (int i = 0; i < n / 2; i++) swap(str[i], str[n - i - 1]);
  return str;
}

// POTENCIA
lenguaje lenguaje::pot(int n) {
  lenguaje lout = *this;
  return potpot(lout, n);
}

// POTENCIA RECURSIVA (SUBMÉTODO DE POT)
lenguaje lenguaje::potpot(lenguaje& l1, int& n) {
  if (n == 0) {
    lenguaje lepsi("{&}");
    return lepsi;
  }
  return l1.conc(l1.potpot(l1, --n));
}

// CIERRE DE KLEENE
lenguaje lenguaje::kleene(void) {
  lenguaje lout;
  int j;
  j = (set_.size() == 1 ? 10 : 4);
  for (int i = 0; i < j; i++) {
    lout = lout.Union(pot(i));
  }
  lout.set_inf(true);
  return lout;
}

// CIERRE POSITIVO
lenguaje lenguaje::positive(void) {
  lenguaje lout;
  int j;
  j = (set_.size() == 1 ? 11 : 4);
  for (int i = 1; i < j; i++) {
    lout = lout.Union(pot(i));
  }
  lout.set_inf(true);
  return lout;
}

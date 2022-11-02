#ifndef TIPOS_H
#define TIPOS_H

#include <cstdlib>
#include <cassert>
#include <iostream>
#include <set>
#include <tuple>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "string_map.h"

using namespace std;

using Nat = unsigned int;

using Coordenada = pair<Nat, Nat>;

using Color = string;

template<typename T>
using conjunto = list<T>;   // En los lugares donde utilizabamos un conjunto, por pre condición no había elementos repetidos.
// Por esa razon y por algunos problemas con el uso de set realizamos este renombre.

template<typename T>
using trie = string_map<T>;

enum Direccion {
    ARRIBA, ABAJO, IZQUIERDA, DERECHA
};

enum TipoCasillero {
    PISO, RAMPA, ELEVACION
};

#endif // TIPOS_H

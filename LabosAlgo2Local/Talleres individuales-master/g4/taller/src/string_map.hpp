template<typename T>
string_map<T>::string_map():raiz(nullptr), _size(0) {}

template<typename T>
string_map<T>::string_map(const string_map<T> &aCopiar)
        : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template<typename T>
string_map<T> &string_map<T>::operator=(const string_map<T> &d) {
    eliminarNodo(this->raiz);
    if (d.raiz != nullptr) {
        agregarNodo(this->raiz, d.raiz);
    }
    this->_size = d._size;
}

template<typename T>
void string_map<T>::agregarNodo(Nodo *&actual, Nodo *copia) { //Al hacer *& la raiz de mi instancia queda apuntada.
    if (copia != nullptr) {
        if (actual == nullptr) {
            Nodo *n = new Nodo();
            actual = n;
        }
    }
    if (copia->definicion != nullptr) {
        T *t = new T(*copia->definicion);
        actual->definicion = t;
    }
    int i = 0;
    while (i < copia->siguientes.size()) {
        if (copia->siguientes[i] != nullptr) {
            agregarNodo(actual->siguientes[i], copia->siguientes[i]);
        }
        i++;
    }
}

template<typename T>
void string_map<T>::insert(const pair<string, T> &value_type) {
    int i = 0;
    int codAscii = value_type.first[i];
    if (raiz == nullptr) {
        Nodo *nuevo = new Nodo();
        raiz = nuevo;
    }
    Nodo *actual = raiz;
    while (i < value_type.first.size()) {
        if (actual->siguientes[codAscii] == nullptr) {
            Nodo *nuevo = new Nodo();
            actual->siguientes[codAscii] = nuevo;
            actual = nuevo;
        } else {
            actual = actual->siguientes[codAscii];
        }
        i++;
        codAscii = value_type.first[i];
    }
    if (i == value_type.first.size()) {
        if (actual->definicion != nullptr) {
            delete actual->definicion;
        }
        actual->definicion = new T(value_type.second);
        _size++;
    }

}

template<typename T>
string_map<T>::~string_map() {
    if (raiz != nullptr) {
        int i = 0;
        while (i < raiz->siguientes.size()) {
            if (raiz->siguientes[i] != nullptr) {
                eliminarNodo(raiz->siguientes[i]);
            }
            i++;
        }
        if (raiz->definicion != nullptr) {
            delete raiz->definicion;
        }
        raiz->siguientes.clear();
        _size = 0;
    }
    delete raiz;
    _size = 0;
}

template<typename T>
void string_map<T>::eliminarNodo(Nodo *&n) {
    int i = 0;
    if (n != nullptr) {
        while (i < n->siguientes.size()) {
            if (n->siguientes[i] != nullptr) {
                eliminarNodo(n->siguientes[i]);
            }
            i++;
        }
        if (n->definicion != nullptr) {
            delete n->definicion;
            n->definicion = nullptr;
            _size--;
        }
    }
    /*  if (n != nullptr && n->definicion != nullptr) {
          delete n->definicion;
          n->definicion = nullptr;
          _size--;
      }*/
    delete n;
    n = nullptr;
}

template<typename T>
int string_map<T>::count(const string &clave) const {
    int res = 0;
    if (raiz != nullptr) {
        Nodo *actual = raiz;
        int i = 0;
        int codAscii = clave[i];
        while (actual != nullptr && i < clave.size()) {
            actual = actual->siguientes[codAscii];
            i++;
            codAscii = clave[i];
        }
        if (actual != nullptr) {
            if (actual->definicion != nullptr && i == clave.size()) {
                res = 1;
            }
        }

    }
    return res;
}

template<typename T>
const T &string_map<T>::at(const string &clave) const {
    Nodo *actual = raiz;
    int i = 0;
    int codAscii = clave[i];
    while (i < clave.size()) {
        actual = actual->siguientes[codAscii];
        i++;
        codAscii = clave[i];
    }
    return *actual->definicion;
}

template<typename T>
T &string_map<T>::at(const string &clave) {
    Nodo *actual = raiz;
    int i = 0;
    int codAscii = clave[i];
    while (i < clave.size()) {
        actual = actual->siguientes[codAscii];
        i++;
        codAscii = clave[i];
    }
    return *actual->definicion;
}

template<typename T>
void string_map<T>::erase(const string &clave) {
    eraseAux(raiz, clave, 0);
}

template<typename T>
void string_map<T>::eraseAux(Nodo *n, string clave, int s) {
// Busco el nodo a borrar y el ultimo nodo que es util. Es decir , el tiene una una definicion distinta de null.
    Nodo *ultNodoUtil = raiz;
    Nodo *actual = raiz;
    int i = 0;
    int codAscii = clave[i];
    while (i < clave.size()) {
        if (actual != nullptr && actual->definicion != nullptr || tieneHijos(actual)) {
            ultNodoUtil = actual;
        }
        actual = actual->siguientes[codAscii];
        i++;
        codAscii = clave[i];
    }
// Dos casos de borrado :
    //el nodo que contiene la clave a borrar tiene hijos y por lo tanto no lo borro
    if (tieneHijos(actual)) {
        delete actual->definicion;
        actual->definicion = nullptr;
        _size--;
    } else { // El nodo no tiene hijos y entonces tengo que borrar todo el camino inutil entre ultNodoUtil y actual.
        i = 0;
        while (i < ultNodoUtil->siguientes.size()) {
            if (ultNodoUtil->siguientes[i] != nullptr) {
                eliminarNodo(ultNodoUtil->siguientes[i]);
            }
            i++;
        }
    }
}

template<typename T>
bool string_map<T>::tieneHijos(Nodo *n) {
    int i = 0;
    bool res = false;
    while (i < n->siguientes.size()) {
        if (n->siguientes[i] != nullptr) {
            res = true;
        }
        i++;
    }
    return res;
}

template<typename T>
int string_map<T>::size() const {
    return _size;
}

template<typename T>
bool string_map<T>::empty() const {
    return _size == 0;
}

template<typename T>
T &string_map<T>::operator[](const string &clave) {
    // COMPLETAR
}

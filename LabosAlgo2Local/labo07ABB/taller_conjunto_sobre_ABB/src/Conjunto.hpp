#include "Conjunto.h"


template<class T>
Conjunto<T>::Conjunto(): _raiz(nullptr), _longitud(0) {}

template<class T>
Conjunto<T>::~Conjunto() {
    destruir(_raiz);
}

template<class T>
bool Conjunto<T>::pertenece(const T &clave) const {
    return perteneceAux(clave, _raiz);
}

template<class T>
bool Conjunto<T>::perteneceAux(const T &clave, Nodo *elem) const {
    bool res = false;
    while (elem != nullptr && elem->valor != clave) {
        if (clave > elem->valor) {
            elem = elem->der;
        } else {
            elem = elem->izq;
        }
    }

    if (elem != nullptr) {
        res = true;
    }
    return res;
}


template<class T>
void Conjunto<T>::insertar(const T &clave) {
    insertarAux(clave, _raiz);
}

template<class T>
void Conjunto<T>::insertarAux(const T &clave,
                              Nodo *&elem) { // Lo paso por referencia , asi puedo insertar y que se modifique.
    if (elem == nullptr) {
        elem = new Nodo(clave);
        _longitud++;
    } else if (elem->valor == clave) {
        //No hago nada , ya que la clave está en mi conjunto.
    } else if (clave < elem->valor) {
        insertarAux(clave, elem->izq);
    } else if (elem->valor < clave) {
        insertarAux(clave, elem->der);
    }
}

template<class T>
void Conjunto<T>::remover(const T &clave) {
    removerAux(clave, _raiz);
}

template<class T>
void Conjunto<T>::removerAux(const T &clave, Nodo *&elem) {
    if (elem->valor == clave) {
        if (elem->der == nullptr && elem->izq == nullptr) { // Caso 1: Es una hoja
            delete (elem);
            elem = nullptr; // Sin esto su padre queda apuntando a cualquier lado.
            _longitud--;
        } else if (elem->der == nullptr && elem->izq != nullptr) { // Caso 2: Un solo hijo izq
            Nodo * temp = elem->izq;
            delete (elem);
            elem = temp;
            //elem->izq = nullptr;
            _longitud--;
        } else if (elem->der != nullptr && elem->izq == nullptr) { // Caso 2: Un solo hijo der
            Nodo * temp = elem->der;
            delete (elem);
            elem = temp;
            _longitud--;
        } else { // Caso 3: tiene dos hijos.
            T sucesorInmed = siguiente(elem->valor);
            removerAux(sucesorInmed,elem);
            elem->valor = sucesorInmed;
        }
    } else if (clave < elem->valor) {
        removerAux(clave, elem->izq);
    } else if (elem->valor < clave) {
        removerAux(clave, elem->der);
    }
}

// PRE: Se asume que el elemento recibido
// se encuentra en el conjunto y existe un elemento siguiente.

template<class T>
const T &Conjunto<T>::siguiente(const T &clave) {
    return sucesorAux(clave);
}

template<class T>
const T &Conjunto<T>::sucesorAux(const T &clave) const { //Idea del Cormen
    Nodo *elem = _raiz;
    while (elem->valor != clave) {
        if (clave > elem->valor) {
            elem = elem->der;
        } else {
            elem = elem->izq;
        }
    }
    // ver tema return.
    if (elem->der != nullptr) { // Caso 1 : existe un subarbol derecho
        return treeMinimum(elem->der);
    } else { // Caso 2 : NO existe un subarbol derecho
        Nodo *predecesor = _raiz;
        Nodo *sucesor = nullptr;
        while (predecesor != elem) {
            if (elem->valor < predecesor->valor) {
                sucesor = predecesor;
                predecesor = predecesor->izq;
            } else {
                predecesor = predecesor->der;
            }
        }
        return sucesor->valor;
    }
}

template<class T>
const T &Conjunto<T>::minimo() const {
    Nodo *nodoTemp = _raiz;
    while (nodoTemp->izq != nullptr) {
        nodoTemp = nodoTemp->izq;
    }
    return nodoTemp->valor;
}

template<class T>
const T &Conjunto<T>::maximo() const {
    Nodo *nodoTemp = _raiz;
    while (nodoTemp->der != nullptr) {
        nodoTemp = nodoTemp->der;
    }
    return nodoTemp->valor;
}

template<class T>
unsigned int Conjunto<T>::cardinal() const {
    return _longitud;
}

template<class T>
void Conjunto<T>::mostrar(std::ostream &) const {
// Es opcional , pero hacerlo.
}

template<class T>
void Conjunto<T>::destruir(Nodo *n) {
    if (n != nullptr) {
        destruir(n->izq);
        destruir(n->der);
        delete (n);
    }
}

template<class T>
//Idea del cormen
const T &Conjunto<T>::treeMinimum(Nodo *x) const {
    while (x->izq != nullptr) {
        x = x->izq;
    }
    return x->valor;
}

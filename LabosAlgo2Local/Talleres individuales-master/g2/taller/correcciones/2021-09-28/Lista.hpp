#include "Lista.h"

Lista::Lista() : _longitud(0), _primero(nullptr), _ultimo(nullptr) {}

Lista::Lista(const Lista &l) : Lista() {
    *this = l;
}

Lista::~Lista() {
    Nodo *temp = _primero;
    while (temp != nullptr) {
        temp = temp->_siguiente;
        delete (_primero);
        _primero = temp;
    }
}

Lista &Lista::operator=(const Lista &aCopiar) {
    while (_primero != nullptr) {
        eliminar(0);
    }
    Nodo *temp = aCopiar._primero;
    while (temp != nullptr) {
        agregarAtras(temp->valor);
        temp = temp->_siguiente;
    }
    return *this;
}

void Lista::agregarAdelante(const int &elem) {
    Nodo *nuevo = new Nodo(elem);
    nuevo->_siguiente = _primero;
    if (_primero != nullptr) {
        _primero->_anterior = nuevo;
    }
    _primero = nuevo;
    _longitud++;
}

void Lista::agregarAtras(const int &elem) {
    Nodo *nuevo = new Nodo(elem);
    Nodo *temp = _primero;
    if (_primero == nullptr) {
        _primero = nuevo;
    } else {
        while (temp->_siguiente != nullptr) {
            temp = temp->_siguiente;
        }
        temp->_siguiente = nuevo;
        nuevo->_anterior = temp;
    }
    _longitud++;
}

void Lista::eliminar(Nat i) {
    Nodo *temp = _primero;
    int cont = 0;
    while (cont < longitud() && cont != i && temp != nullptr) {
        temp = temp->_siguiente;
        cont++;
    }
    if (temp->_anterior == nullptr) { //Eliminar el primer nodo
        _primero = temp->_siguiente;
        if (temp->_siguiente != nullptr) {
            temp->_siguiente->_anterior = nullptr;
        }
    } else if (temp->_siguiente == nullptr) { //Eliminar el ultimo nodo
        _ultimo = temp->_anterior;
        if (temp->_anterior != nullptr) {
            temp->_anterior->_siguiente = nullptr;
        }
    } else { // cualquier caso donde no es ni primer nodo , ni ultimo nodo
        temp->_siguiente->_anterior = temp->_anterior;
        temp->_anterior->_siguiente = temp->_siguiente;
    }
    delete (temp);
    _longitud--;
}

int Lista::longitud() const {
    return _longitud;
}

const int &Lista::iesimo(Nat i) const {
    Nodo *temp = _primero;
    int pos = 0;
    bool encontre = false;
    while (pos < longitud() && !encontre) {
        if (pos == i) {
            encontre = true;
        } else {
            temp = temp->_siguiente;
        }
        pos++;
    }
    return temp->valor;
}

int &Lista::iesimo(Nat i) {
    Nodo *temp = _primero;
    int pos = 0;
    bool encontre = false;
    while (pos < longitud() && !encontre) {
        if (pos == i) {
            encontre = true;
        } else {
            temp = temp->_siguiente;
        }
        pos++;
    }
    return temp->valor;
}

//Aca no aclara el formato para imprimir por consola, así que va a tener el siguiente formato : [1,2,3,4]
void Lista::mostrar(ostream &o) {
    o << "[";
    Nodo *temp = _primero;
    while (temp != nullptr) {
        if (temp->_siguiente != nullptr) {
            o << temp->valor << ",";
        }
        temp = temp->_siguiente;
    }
    o << "]";
}

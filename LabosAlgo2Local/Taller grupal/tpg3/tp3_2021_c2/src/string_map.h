#ifndef STRING_MAP_H
#define STRING_MAP_H

#include <string>

using namespace std;

template<typename T>
class string_map {
public:

    string_map();

    string_map(const string_map<T> &aCopiar);

    string_map &operator=(const string_map &d);

    ~string_map();

    pair<T *, string> insert(const pair<string, T> &);

    int count(const string &key) const;

    const T &at(const string &key) const;

    T &at(const string &key);

    void erase(const string &key);

    int size() const;

    bool empty() const;

    const set<string> devolverConjClaves() const;

private:

    struct Nodo {
        vector<Nodo *> siguientes;
        T *definicion;

        Nodo() : siguientes(256, nullptr),
                 definicion(nullptr) {}

        Nodo(T *def) : siguientes(256, nullptr),
                       definicion(def) {}
    };

    void eliminarNodo(Nodo *&n);

    void agregarNodo(Nodo *&actual, Nodo *copia);

    bool tieneHijos(Nodo *n);

    void eraseAux(Nodo *n, string clave, int s);

    set<string> _conjClaves; // Al diseño del string_map del taller 4 se le agregó un set que contiene el conj de claves total.
    Nodo *raiz;
    int _size;
};

#include "string_map.hpp"

#endif //STRING_MAP_H_

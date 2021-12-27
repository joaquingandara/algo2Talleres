
template<class T>
ColaPrior<T>::ColaPrior():_heap(), _longitud(0) {}

template<class T>
int ColaPrior<T>::tam() const {
    return _longitud;
}

template<class T>
void ColaPrior<T>::encolar(const T &elem) {
    _longitud++;
    _heap.push_back(elem);
    siftUp(_longitud -
           1);// Porque si el elemento lo agregue al final entonces la longitud menos 1 es la pos de ese elemento.
}

//Precondición: debe haber al menos un elemento en la cola.
template<class T>
const T &ColaPrior<T>::proximo() const {
    return _heap[0];
}

template<class T>
void ColaPrior<T>::desencolar() {
    swap(_heap[0], _heap[_longitud - 1]);
    _heap.pop_back();
    _longitud--;
    siftDown(0);
}

template<class T>
ColaPrior<T>::ColaPrior(const vector<T> &elems) {
    for (int i = 0; i < elems.size(); ++i) {
        encolar(elems[i]);
        _longitud++;
    }
}

//Funciones auxiliares
template<class T>
int ColaPrior<T>::hijoIzq(int i) {
    return ((2 * i) + 1);
    f
}

template<class T>
int ColaPrior<T>::hijoDER(int i) {
    return ((2 * i) + 2);
}

template<class T>
int ColaPrior<T>::padre(int i) {
    return ((i - 1) / 2);
}

template<class T>
void ColaPrior<T>::siftUp(int i) {
    while (i > 0 && i < _longitud &&  _heap[i] > _heap[padre(i)]) {
        swap(_heap[padre(i)], _heap[i]); // es parte de c++ el swap este.
        i = padre(i);
    }
};

template<class T>
void ColaPrior<T>::siftDown(int i) {

    // Ver si el max es hijo der o izq
    int maximoI = i;
    int izq = hijoIzq(i);
    if (izq < _longitud && _heap[izq] > _heap[maximoI]) {
        maximoI = izq;
    }
    int der = hijoDER(i);
    if (der < _longitud && _heap[der] > _heap[maximoI]) {
        maximoI = der;
    }

    // swap y recursion
    if (i != maximoI) {    //Por si el maximo es el indice que le pase.
        swap(_heap[i], _heap[maximoI]);
        siftDown(maximoI);
    }
};

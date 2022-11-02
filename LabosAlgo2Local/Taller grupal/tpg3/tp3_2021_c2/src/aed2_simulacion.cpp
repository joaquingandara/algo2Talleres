#include "aed2_simulacion.h"

aed2_Simulacion::aed2_Simulacion(const aed2_Mapa &mapa, const map<Color, Coordenada> &objetos, Coordenada inicio)
        : _simulacion(mapa.mapa(), inicio, objetos) {}

void aed2_Simulacion::mover(Direccion d) {
    _simulacion.mover(d);
}

void aed2_Simulacion::agregarObjetivo(Objetivo o) {
    _simulacion.agObjetivo(o);
}

const aed2_Mapa aed2_Simulacion::mapa() const {
    return aed2_Mapa(_simulacion.devolverMapa());
}

const map<Color, Coordenada> &aed2_Simulacion::posObjetos() const {
    return _simulacion.devolverPosObjetos();
};

Coordenada aed2_Simulacion::posAgente() const {
    return _simulacion.posicionAgente();
}

const list<Objetivo> &aed2_Simulacion::objetivosDisponibles() const {
    return _simulacion.objetivosDisponibles();
}

Nat aed2_Simulacion::movimientos() const {
    return _simulacion.cantMovimientos();
}

Nat aed2_Simulacion::objetivosResueltos() const {
    return _simulacion.objetivosCompletados();
}

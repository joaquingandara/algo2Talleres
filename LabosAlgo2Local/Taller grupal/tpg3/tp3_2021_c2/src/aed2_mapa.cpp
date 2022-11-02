#include "aed2_mapa.h"

aed2_Mapa::aed2_Mapa() {
    _mapa = Mapa();
};

aed2_Mapa::aed2_Mapa(Nat ancho, Nat alto, set<Coordenada> elevaciones, map<Color, Coordenada> receptaculos) :
        _mapa(ancho, alto, receptaculos), _receptaculos(receptaculos) {
    for (Coordenada coord: elevaciones) {
        _mapa.agregarPared(coord);
    }
};

void aed2_Mapa::agregarRampa(Coordenada c) {
    _mapa.agregarRampa(c);
}

Nat const aed2_Mapa::ancho() {
    return _mapa.devolverAncho();
}

Nat const aed2_Mapa::alto() {
    return _mapa.devolverAlto();
}

TipoCasillero aed2_Mapa::tipoCasillero(Coordenada c) const {
    return _mapa.devolverTipoCasillero(c);
}

const map<Color, Coordenada> &aed2_Mapa::receptaculos() const {
    return _receptaculos;
}

Coordenada aed2_Mapa::receptaculo(Color color) {
    return _mapa.devolverPosPorColor(color);
}

aed2_Mapa::aed2_Mapa(Mapa m) {
    _mapa = m;
    _receptaculos = map<Color, Coordenada>();
    for (const Color clave: m.devolverConjClaves()) {
        Coordenada c = m.devolverPosPorColor(clave);
        _receptaculos.insert(make_pair(clave, c));
    }
}

Mapa aed2_Mapa::mapa() const {
    return _mapa;
}
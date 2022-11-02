#include "Mapa.h"
#include "stdlib.h"

Mapa::Mapa() {};

Mapa::Mapa(Nat ancho, Nat alto, map<Color, Coordenada> receptaculos) {
    _alto = alto;
    _ancho = ancho;
    _receptaculos = trie<Coordenada>();
    _mapa = vector<vector<TipoCasillero>>(alto, vector<TipoCasillero>(ancho, PISO));
    _coloresPosiciones = vector<vector<Color>>(alto, vector<Color>(ancho, ""));
    for (const auto &receptaculo: receptaculos) {
        _receptaculos.insert(receptaculo);
        _coloresPosiciones[receptaculo.second.first][receptaculo.second.second] = receptaculo.first;
    }
}

void Mapa::agregarPared(Coordenada c) {
    _mapa[c.first][c.second] = ELEVACION;
}

void Mapa::agregarRampa(Coordenada c) {
    _mapa[c.first][c.second] = RAMPA;
}

bool Mapa::esPared(Coordenada c) {
    return _mapa[c.first][c.second] == ELEVACION;
}

bool Mapa::esRampa(Coordenada c) {
    return _mapa[c.first][c.second] == RAMPA;
}

bool Mapa::esPiso(Coordenada c) {
    return _mapa[c.first][c.second] == PISO;
}

bool Mapa::enRango(Coordenada c) {
    return _alto > c.first && _ancho > c.second;
}

int Mapa::dist(Coordenada a, Coordenada b) {
    int d1 = a.first - b.first;
    int d2 = a.second - b.second;
    return abs(d1) + abs(d2);
}

Color Mapa::devolverColorPorPos(Coordenada pos) {
    return _coloresPosiciones[pos.first][pos.second];
}

Coordenada Mapa::devolverPosPorColor(Color c) const {
    return _receptaculos.at(c);
}

Nat const Mapa::devolverAlto() const {
    return _alto;
};

Nat const Mapa::devolverAncho() const {
    return _ancho;
};

TipoCasillero Mapa::devolverTipoCasillero(Coordenada coordenada) const {
    return _mapa[coordenada.first][coordenada.second];
}

const set<string> Mapa::devolverConjClaves() {
    return _receptaculos.devolverConjClaves();
}


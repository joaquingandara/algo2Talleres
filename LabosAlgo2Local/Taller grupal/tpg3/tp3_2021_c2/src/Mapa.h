#ifndef MAPA_H
#define MAPA_H

#include "Tipos.h"

class Mapa {
public:

    Mapa();

    Mapa(Nat ancho, Nat alto, map<Color, Coordenada> receptaculos);

    void agregarRampa(Coordenada c);

    void agregarPared(Coordenada c);

    bool esPared(Coordenada c);

    bool esRampa(Coordenada c);

    bool esPiso(Coordenada c);

    bool enRango(Coordenada c);

    int dist(Coordenada a, Coordenada b);

    Color devolverColorPorPos(Coordenada pos);

    Coordenada devolverPosPorColor(Color c) const;

    Nat const devolverAlto() const;

    Nat const devolverAncho() const;

    TipoCasillero devolverTipoCasillero(Coordenada c) const;

    const set<string> devolverConjClaves();

private:
    int _alto;
    int _ancho;
    vector<vector<TipoCasillero>> _mapa;
    vector<vector<Color>> _coloresPosiciones;
    trie<Coordenada> _receptaculos;
};

#endif //MAPA_H

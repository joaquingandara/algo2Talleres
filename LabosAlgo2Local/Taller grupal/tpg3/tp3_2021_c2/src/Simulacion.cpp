#include "Simulacion.h"

Simulacion::Simulacion() {}

Simulacion::Simulacion(Mapa m, Coordenada c, map<Color, Coordenada> objetos) : _mapa(m) {
    _posicionAgente = c;
    _cantMovimientos = 0;
    _objetivosRealizados = 0;
    _matrizPosiciones = vector<vector<pair<pair<map<Color, Coordenada>::iterator, trie<conjunto<Objetivo>::iterator>> *, string>>>(
            m.devolverAlto(),
            vector<pair<pair<map<Color, Coordenada>::iterator, trie<conjunto<Objetivo>::iterator>> *, string>>(
                    m.devolverAncho(),
                    make_pair(nullptr, "")));
    for (const pair<Color, Coordenada> objeto: objetos) {
        trie<conjunto<Objetivo>::iterator> trieObjetivos;
        map<Color, Coordenada>::iterator itPosObjeto = _posObjetos.insert(make_pair(objeto.first, objeto.second)).first;
        pair<pair<map<Color, Coordenada>::iterator, trie<conjunto<Objetivo>::iterator>> *, string> itObjeto = _coloresObjetos.insert(
                make_pair(objeto.first, make_pair(itPosObjeto, trieObjetivos)));
        _matrizPosiciones[objeto.second.first][objeto.second.second] = itObjeto;
    }
}

void Simulacion::mover(Direccion dir) {
    if (estaDentroDelMapa(dir)) {
        _cantMovimientos++;
    }
    bool sePuedeMover = hayMovimiento(_posicionAgente, dir);
    if (sePuedeMover) {
        Coordenada siguientePos = siguientePosicion(_posicionAgente, dir);
        pair<pair<map<Color, Coordenada>::iterator, trie<conjunto<Objetivo>::iterator>> *, string> itObjeto = _matrizPosiciones[siguientePos.first][siguientePos.second];
        bool hayObjeto = false;

        if (itObjeto.first != nullptr) {
            hayObjeto = true;
        }
        Coordenada sigDeSigPos = siguientePosicion(siguientePos, dir);
        bool existeSiguientePosicion = hayMovimiento(siguientePos, dir);
        bool haySiguienteObjeto = false;

        if (existeSiguientePosicion) {
            if (_matrizPosiciones[sigDeSigPos.first][sigDeSigPos.second].first != nullptr) {
                haySiguienteObjeto = true;
            }
        }
        if (!hayObjeto) {
            _posicionAgente = siguientePos;
        } else if (!haySiguienteObjeto) {
            if (existeSiguientePosicion) {
                pair<map<Color, Coordenada>::iterator, string_map<conjunto<Objetivo>::iterator>> def = _coloresObjetos.at(
                        itObjeto.second);
                map<Color, Coordenada>::iterator itAPosObjeto = def.first;
                Coordenada posicionObjeto = _coloresObjetos.at(itObjeto.second).first->second;
                Coordenada nuevaPosicionDelObjeto = siguientePosicion(posicionObjeto, dir);
                trie<conjunto<Objetivo>::iterator> &trieReceptaculos = _coloresObjetos.at(itObjeto.second).second;
                _posObjetos.erase(itAPosObjeto);
                map<Color, Coordenada>::iterator itNuevaPosicionDelObjeto = _posObjetos.insert(_posObjetos.end(),
                                                                                               make_pair(
                                                                                                       itObjeto.second,
                                                                                                       nuevaPosicionDelObjeto));
                itObjeto = _coloresObjetos.insert(
                        make_pair(itObjeto.second, make_pair(itNuevaPosicionDelObjeto, trieReceptaculos)));
                _posicionAgente = siguientePos;
                _matrizPosiciones[siguientePos.first][siguientePos.second] = make_pair(nullptr, "");
                _matrizPosiciones[sigDeSigPos.first][sigDeSigPos.second] = itObjeto;
                Color colorPiso = _mapa.devolverColorPorPos(sigDeSigPos);
                if (itObjeto.first->second.count(colorPiso) == 1) {
                    auto itObjetivo = itObjeto.first->second.at(colorPiso);
                    if (realizado(*itObjetivo)) {
                        _objetivosDisponibles.erase(itObjetivo);
                        _objetivosRealizados++;
                        trie<conjunto<Objetivo>::iterator> &trieReceptaculos = _coloresObjetos.at(
                                itObjeto.second).second;
                        trieReceptaculos.erase(colorPiso);
                    }
                }
            }
        }
    }
}

void Simulacion::agObjetivo(Objetivo o) {
    if (realizado(o)) {
        _objetivosRealizados++;
    } else {
        set<string> claves = _coloresObjetos.devolverConjClaves();
        Color colorObj = o.objeto();
        Color colorReceptaculo = o.receptaculo();
        for (string clave: claves) {
            if (clave == colorObj) {
                conjunto<Objetivo>::iterator it = _objetivosDisponibles.insert(_objetivosDisponibles.end(), o);
                pair<map<Color, Coordenada>::iterator, trie<conjunto<Objetivo>::iterator>> &def = _coloresObjetos.at(
                        colorObj);
                def.second.insert(make_pair(colorReceptaculo, it));
                Coordenada posObj = posObjeto(colorObj);
                pair<pair<map<Color, Coordenada>::iterator, trie<conjunto<Objetivo>::iterator>> *, string> itObjeto = _coloresObjetos.insert(
                        make_pair(colorObj, (posObj, def)));
                _matrizPosiciones[posObj.first][posObj.second] = itObjeto;
            }
        }
    }
}

bool Simulacion::hayMovimiento(Coordenada pos, Direccion dir) {
    bool res = false;
    Coordenada sigPos = siguientePosicion(pos, dir);
    if (_mapa.enRango(sigPos)) {
        res = true;
        if (!(_mapa.esRampa(pos)) && _mapa.esPared(sigPos)) {
            res = false;
        }
    }
    return res;
}

Coordenada Simulacion::siguientePosicion(Coordenada c, Direccion d) {
    Coordenada res = c;
    switch (d) {
        case ARRIBA:
            res.second++;
            break;

        case ABAJO:
            res.second--;
            break;

        case IZQUIERDA:
            res.first--;
            break;

        case DERECHA:
            res.first++;
            break;
    }
    return res;
}

conjunto<Objetivo> Simulacion::filtrarRealizados(conjunto<Objetivo> objetivos) {
    conjunto<Objetivo>::iterator it = objetivos.begin();
    while (it != objetivos.end()) {
        if (realizado(*it)) {
            objetivos.erase(it);
        }
        advance(it, 1);
    }
    return objetivos;
}

bool Simulacion::hayObjeto(Coordenada pos) {
    bool res = false;
    if (_matrizPosiciones[pos.first][pos.second].first != nullptr) {
        res = true;
    }
    return res;

}

bool Simulacion::hayAlgunObjeto(Coordenada c, set<Color> colores) {
    bool res = false;
    for (const Color &color: colores) {
        if (posObjeto(color) == c) {
            res = true;
            break;
        }
    }
    return res;
}

Coordenada Simulacion::posObjeto(Color c) const {
    return _coloresObjetos.at(c).first->second;
}

Nat Simulacion::cantMovimientos() const {
    return _cantMovimientos;
}

Nat Simulacion::objetivosCompletados() const {
    return _objetivosRealizados;
}

Coordenada Simulacion::posicionAgente() const {
    return _posicionAgente;
}

const conjunto<Objetivo> &Simulacion::objetivosDisponibles() const {
    return _objetivosDisponibles;
}

bool Simulacion::realizado(Objetivo o) const {
    return _mapa.devolverPosPorColor(o.receptaculo()) == posObjeto(o.objeto());
}

const Mapa Simulacion::devolverMapa() const {
    return this->_mapa;
}

const map<Color, Coordenada> &Simulacion::devolverPosObjetos() const {
    return _posObjetos;
}

bool Simulacion::estaDentroDelMapa(Direccion dir) {
    Coordenada sigPos = siguientePosicion(_posicionAgente, dir);
    return _mapa.enRango(sigPos);
}
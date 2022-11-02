#ifndef SIMULACION_H
#define SIMULACION_H

#include "Mapa.h"
#include "Objetivo.h"
#include "Tipos.h"

class Simulacion {
public:

    Simulacion();

    Simulacion(Mapa m, Coordenada c, map<Color, Coordenada> objetos);

    void mover(Direccion dir);

    void agObjetivo(Objetivo o);

    bool hayMovimiento(Coordenada pos, Direccion dir);

    Coordenada siguientePosicion(Coordenada c, Direccion d);

    conjunto<Objetivo> filtrarRealizados(conjunto<Objetivo> objetivos);

    bool hayObjeto(Coordenada pos);

    bool hayAlgunObjeto(Coordenada c, set<Color> colores);

    Coordenada posObjeto(Color c) const;

    Nat cantMovimientos() const;

    Nat objetivosCompletados() const;

    Coordenada posicionAgente() const;

    const conjunto<Objetivo> &objetivosDisponibles() const;

    bool realizado(Objetivo o) const;

    const Mapa devolverMapa() const;

    const map<Color, Coordenada> &devolverPosObjetos() const;

    bool estaDentroDelMapa(Direccion dir);

private:
    Mapa _mapa;
    Coordenada _posicionAgente;
    Nat _cantMovimientos;
    Nat _objetivosRealizados;
    string_map<pair<map<Color, Coordenada>::iterator, string_map<conjunto<Objetivo>::iterator>>> _coloresObjetos;
    vector<vector<pair<pair<map<Color, Coordenada>::iterator, trie<conjunto<Objetivo>::iterator>> *, string>>> _matrizPosiciones;
    conjunto<Objetivo> _objetivosDisponibles;
    map<Color, Coordenada> _posObjetos;
};
/*  Cambios respecto a la estructura del TP2:
     *  _coloresObjetos originalmente en el tp2 de diseño era un diccTrie(colorObjeto,<posicion, diccTrie(colorCasillero,itObjetivo)>).
        Para cumplir las complejidades cambiamos el primer elemento del par por un iterador a la coordenada en el map _posObjetos.
        De esta forma podemos mantener actualizado el _posObjetos con la complejidad pedida.
     *  _matrizPosiciones que originalmente era un vector<vector<itColoresObjetos>>, fue cambiado para que cada posicion contenga un par
        cuyo primer elemento apunte al significado de _coloresObjetos que corresponda con el objeto que esta ubicado en la segunda posicion del par.
     * _posObjetos no pertenecía a la estructura del tp2. Se lo agregó para poder devolver un map<Color,Coordenada> por referencia , en la funcion posObjetos dada por la catedra.
 */

#endif //SIMULACION_H


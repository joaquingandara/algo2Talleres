#include "Objetivo.h"

Objetivo::Objetivo() {
}

bool Objetivo::operator<(const Objetivo &o) {
    if (this->_colorObjeto != o._colorObjeto || this->_colorDestino != o._colorDestino) {
        return true;
    }
    return false;

}

Objetivo::Objetivo(const Color &objeto, const Color &receptaculo) {
    _colorObjeto = objeto;
    _colorDestino = receptaculo;
}

const Color &Objetivo::objeto() const {
    return _colorObjeto;
}

const Color &Objetivo::receptaculo() const {
    return _colorDestino;
}
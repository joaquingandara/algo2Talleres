#ifndef OBJETIVO_H
#define OBJETIVO_H

#include "Tipos.h"

class Objetivo {
public:

    Objetivo();

    Objetivo(const Color &objeto, const Color &receptaculo);

    const Color &objeto() const;

    const Color &receptaculo() const;

    bool operator<(const Objetivo &o);

private:

    Color _colorObjeto;
    Color _colorDestino;
};

#endif

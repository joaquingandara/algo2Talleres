
#ifndef SOLUCION_PERIODO_H
#define SOLUCION_PERIODO_H

using namespace std;

class Periodo {
public:
    Periodo(int anios, int meses, int dias);

    int anios() const;

    int meses() const;

    int dias() const;

private:
    int anios_;
    int meses_;
    int dias_;
};

#endif //SOLUCION_PERIODO_H

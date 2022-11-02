#include <iostream>
#include <list>

using namespace std;

using uint = unsigned int;

// Pre: 0 <= mes < 12
uint dias_en_mes(uint mes) {
    uint dias[] = {
        // ene, feb, mar, abr, may, jun
        31, 28, 31, 30, 31, 30,
        // jul, ago, sep, oct, nov, dic
        31, 31, 30, 31, 30, 31
    };
    return dias[mes - 1];
}

// Ejercicio 7, 8, 9 y 10

// Clase Fecha
class Fecha {
    public:
        Fecha(uint mes,uint dia);
        uint mes();
        uint dia();

        bool operator==(Fecha o);
        void incrementar_dia();
    private:
        uint mes_;
        uint dia_;
};
Fecha::Fecha(uint mes, uint dia): mes_(mes),dia_(dia) {};

uint Fecha::mes() {
    return mes_;
}
uint Fecha::dia(){
    return dia_;
}
ostream& operator<<(ostream& os,Fecha f){
    os << f.dia()<<"/" << f.mes();
    return os;
}

bool Fecha::operator==(Fecha o) {
    bool igual_dia = this->dia() == o.dia();
    bool igual_mes = this->mes() == o.mes();
    return (igual_dia && igual_mes);
}

void Fecha::incrementar_dia() {
    if(dia_ >= dias_en_mes(mes_)){
        dia_= 1;
        mes_= mes_ +1;
    }else if(dia_ >= dias_en_mes(mes_) && mes_==12){ // Preguntar si es necesario el caso cuando se pasa de un año a otro.
        dia_= 1;
        mes_=1;
    }else{
        dia_++;
    }
}

// Ejercicio 11, 12

// Clase Horario

class Horario {
    public:
        Horario(uint hora,uint min);
        uint hora();
        uint min();
        bool operator==(Horario h);
        bool operator<(Horario h);
    private:
        uint hora_;
        uint min_;
};

Horario::Horario(uint hora, uint min): hora_(hora),min_(min) {};
uint Horario::hora() {
    return hora_;
}
uint  Horario::min() {
    return min_;
}

ostream& operator<<(ostream& os,Horario h){
    os << h.hora() << ":" << h.min();
    return os;
}

bool Horario::operator==(Horario h) { //
    bool igual_hora = this->hora() == h.hora();
    bool igual_min = this->min() == h.min();
    return (igual_hora && igual_min);
}
bool Horario::operator<(Horario h) {
    bool res= false;
    if(h.hora()==hora_){
        res= h.min() > min_;
    }else{
        res= h.hora() > hora_;
    }
    return res;
}

// Ejercicio 13

// Clase Recordatorio

class Recordatorio {
    public:
        Recordatorio(Fecha f,Horario h, string m);
        Fecha fecha ();
        Horario horario();
        string mensaje();
    private:
        Fecha f_;
        Horario h_;
        string m_;
};

Recordatorio::Recordatorio(Fecha f, Horario h, string m):
        f_(f), h_(h),m_(m){};

Fecha Recordatorio::fecha() {
    return f_;
}
Horario Recordatorio::horario() {
    return h_;
}
string Recordatorio::mensaje() {
    return m_;
}

ostream& operator<<(ostream& os,Recordatorio r){
    os << r.mensaje() << " @ " << r.fecha() << " " << r.horario();
    return os;
}

// Ejercicio 14

// Clase Agenda

class Agenda {
    public:
        Agenda(Fecha fecha_inicial);
        void agregar_recordatorio(Recordatorio rec);
        void incrementar_dia();
        list<Recordatorio> recordatorios_de_hoy();
        Fecha hoy();

    private:
        Fecha fecha_inicial_;
        list <Recordatorio> list_recordatorios_;
};

Agenda::Agenda(Fecha fecha_inicial): fecha_inicial_(fecha_inicial) {};

list<Recordatorio> Agenda::recordatorios_de_hoy() {
    vector<Recordatorio> v_recordatorios_de_hoy;

    for (Recordatorio r: list_recordatorios_) {
        if(r.fecha()==fecha_inicial_){
            v_recordatorios_de_hoy.push_back(r);
        }
    }

    list<Recordatorio> l_recordatorios_de_hoy;
    for (int i = 0; i < v_recordatorios_de_hoy.size(); ++i) {
        for (int j = 0; j < v_recordatorios_de_hoy.size()-1 ; ++j) {
            if(v_recordatorios_de_hoy[j+1].horario()<v_recordatorios_de_hoy[j].horario()){
                Recordatorio temp = v_recordatorios_de_hoy[j+1];
                v_recordatorios_de_hoy[j+1] = v_recordatorios_de_hoy[j];
                v_recordatorios_de_hoy[j]= temp;
            }
        }

    }
    for (int i = 0; i < v_recordatorios_de_hoy.size(); ++i) {
        l_recordatorios_de_hoy.push_back(v_recordatorios_de_hoy[i]);
    }
    return l_recordatorios_de_hoy;
}

void Agenda::agregar_recordatorio(Recordatorio rec) {
    list_recordatorios_.push_back(rec);
}
void Agenda::incrementar_dia() {
    fecha_inicial_.incrementar_dia();
}
Fecha Agenda::hoy() {
    return fecha_inicial_;
}

ostream& operator<<(ostream& os,Agenda ag){
    os << ag.hoy() << "\n" << "=====" <<"\n";
    for (Recordatorio r: ag.recordatorios_de_hoy()) {
        os << r << "\n";
    }
    return os;
}
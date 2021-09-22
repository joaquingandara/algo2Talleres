#include "SistemaDeMensajes.h"

SistemaDeMensajes::SistemaDeMensajes() : _conns() {};

void SistemaDeMensajes::registrarJugador(int id, string ip) {
    if (_conns[id] != nullptr) {
        delete _conns[id];
    }
    _conns[id] = new ConexionJugador(ip);
}

bool SistemaDeMensajes::registrado(int id) const {
    bool res = false;
    if (_conns[id] != nullptr) {
        res = true;
    }
    return res;
}

void SistemaDeMensajes::enviarMensaje(int id, string mensaje) {
    if (registrado(id)) {
        _conns[id]->enviarMensaje(mensaje);
    }
}

string SistemaDeMensajes::ipJugador(int id) const {
    string res = "";
    if (registrado(id)) {
        res = _conns[id]->ip();
    }
    return res;
}

SistemaDeMensajes::~SistemaDeMensajes() {
    delete _conns[0];
    delete _conns[1];
    delete _conns[2];
    delete _conns[3];
    for (int i = 0; i < _proxys.size(); ++i) {
        delete _proxys[i];
    }
}

void SistemaDeMensajes::desregistrarJugador(int id) {
    if (registrado(id)) {
        delete _conns[id];
    }
    _conns[id] = nullptr;
}

Proxy* SistemaDeMensajes::obtenerProxy(int id){
    Proxy *p = new Proxy(&_conns[id]);
    _proxys.push_back(p);
    return p;
}
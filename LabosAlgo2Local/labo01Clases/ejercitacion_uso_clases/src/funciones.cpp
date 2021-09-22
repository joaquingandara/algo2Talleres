#include <vector>
#include "algobot.h"

using namespace std;

// Ejercicio 1
vector<int> quitar_repetidos(vector<int> s) {
    vector <int> sinRepetidos;
    for (int i = 0; i < s.size(); ++i) {
        bool pertenece=false;
        for (int j = 0; j < sinRepetidos.size()&&!pertenece; ++j) {
            if(s[i]==sinRepetidos[j]){
                pertenece=true;
            }
        }
        if(!pertenece){
            sinRepetidos.push_back(s[i]);
        }
    }
    return sinRepetidos;
}

// Ejercicio 2
vector<int> quitar_repetidos_v2(vector<int> s) {
    set<int> setA;
    vector<int>res;
    for (int i = 0; i < s.size(); ++i) {
        if(setA.count(s[i])==0){
            setA.insert(s[i]);
            res.push_back(s[i]);
        }
    }
    return res;
}

// Ejercicio 3
bool mismos_elementos(vector<int> a, vector<int> b) {
    bool iguales=true;
    for (int i = 0; i < a.size()&&iguales; ++i) {
        iguales=false;
        for (int j = 0; j < b.size(); ++j) {
            if(a[i]==b[j]){
                iguales=true;
            }
        }
    }
    return iguales;
}

// Ejercicio 4
bool mismos_elementos_v2(vector<int> a, vector<int> b) {
    set <int> set_a;
    for (int i = 0; i < a.size(); ++i) {
        set_a.insert(a[i]);
    }
    set<int> set_b;
    for (int i = 0; i < b.size()  ; ++i) {
        if(set_a.count(b[i])>=1){
            set_b.insert(b[i]);
        }
    }
    return set_a==set_b;
}

// Ejercicio 5
map<int, int> contar_apariciones(vector<int> s) {
    map <int,int> m;
    for (int i = 0; i < s.size(); ++i) {
        m[s[i]]++;
    }
    return m;
}

// Ejercicio 6
vector<int> filtrar_repetidos(vector<int> s) {
    vector <int> res;

    for (int i = 0; i < s.size(); ++i) {
        bool rep=false;
        for (int j = 0; j < s.size()&&!rep; ++j) {
            if(s[i]==s[j] && i!=j){
                rep=true;
            }
        }
        if(!rep){
            res.push_back(s[i]);
        }
    }
    return res;
}

// Ejercicio 7
set<int> interseccion(set<int> a, set<int> b) {
    set <int> res;
    for (int x: a) {
       if(b.count(x)==1){
           res.insert(x);
       }
    }

    return res;
}

// Ejercicio 8
// Pre: Sin repetidos: (∀ i, j : nat) (i, j < long(s) ⇒ s[i] = s[j] ⇐⇒ i = j)}
map<int, set<int>> agrupar_por_unidades(vector<int> s) {
    map <int,set<int>> res;
    for (int i = 0; i < s.size(); ++i) {
        res[s[i]%10].insert(s[i]); // Al pedir el modulo 10 de un numero te da el ultimo digito.
    }
    return res;
}

// Ejercicio 9
vector<char> traducir(vector<pair<char, char>> tr, vector<char> str) {
    vector <char> res=str;
    for (int i = 0; i < res.size() ; ++i) { // Entiendo que el solo se tiene que traducir una vez.
        for (int j = 0; j < tr.size(); ++j) {
            if(tr[j].first==res[i] ){
                res[i]=tr[j].second;
                break;
            }
        }

    }
    return res;
}

// Ejercicio 10
bool integrantes_repetidos(vector<Mail> s) {
    bool res=false;
    for (int i = 0; i < s.size()&&!res; ++i) {
        set<LU> set_LU1 = s[i].libretas();
        for (int j = i+1; j < s.size()&&!res; ++j) {
            set<LU> set_LU2 = s[j].libretas();
            for (LU lib: set_LU1) {
                if(set_LU2.count(lib)==1 && set_LU1!=set_LU2){ // Si una persona esta en mas de un grupo
                    res=true;
                    break;
                }
            }
        }
    }

    return res;
}

// Ejercicio 11
map<set<LU>, Mail> entregas_finales(vector<Mail> s) {
    map <set <LU> , Mail> final;
    for (int i = 0; i < s.size() ; ++i) {
        final[s[i].libretas()]=s[i];
    }
    for (int i = 0; i < s.size(); ++i) {
        for (int j = 0; j < s.size(); ++j) {
            if(s[i].fecha()>s[j].fecha() && s[i].adjunto()){
                final[s[i].libretas()]=s[i];
            }
        }
    }

    return final;
}

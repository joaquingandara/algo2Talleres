#include "gtest-1.8.1/gtest.h"
#include "../src/Libreta.h"
#include "../src/Truco.h"
#include <map>
#include <cmath>

using namespace std;

// Ejercicio 4
TEST(Aritmetica, suma) {
    int resultado = 15 + 7;
    int esperado = 22;
    EXPECT_EQ(resultado, esperado);
}

// Ejercicio 5
TEST(Aritmetica, potencia) {
    float resultado = pow(10, 2);
    float esperado = 100;
    EXPECT_EQ(resultado, esperado);
}

// Ejercicios 6
TEST(Aritmetica, potencia_general) {
    for (int i = -5; i < 5; ++i) {
        EXPECT_EQ(pow(i, 2), i * i);
    }
}

//Ejercicio 7
TEST(Diccionario, obtener) {
    map<int, int> resultado = {{2, 3}};
    EXPECT_EQ(resultado.at(2), 3);
}

//Ejercicio 8
TEST(Diccionario, definir) { //Se fija la cantidad de apariciones
    map<int, int> resultado;
    EXPECT_EQ(resultado.count(2), 0);
    resultado.insert(make_pair(2, 3));
    EXPECT_EQ(resultado.count(2), 1);
}

//Ejercicio 9
TEST(Truco, inicio) {
    Truco t;
    EXPECT_EQ(t.puntaje_j1(), 0);
    EXPECT_EQ(t.puntaje_j2(), 0);
}

//Ejercicio 10
TEST(Truco, buenas) {
    Truco t;

    EXPECT_FALSE(t.buenas(1));
    for (int i = 0; i < 15; ++i) {
        t.sumar_punto(1);
    }
    EXPECT_FALSE(t.buenas(1));
    t.sumar_punto(1);
    EXPECT_TRUE(t.buenas(1));
    t.sumar_punto(1);
    t.sumar_punto(1);
    EXPECT_TRUE(t.buenas(1));
}

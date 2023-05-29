#pragma once
#include "Nodos.h"
#include <iostream>
#include <vector>
using namespace std;

class Heap {
private:
    vector<int> posiciones;
public:
    vector<Nodo*> heap;
    Heap(){}
    void agregar(Nodo* valor);
    void subir(int valor);
    Nodo* extraer_min();

    void actualizar();
    void comparador_heap(int indice);

    void huffman();

    void imprimir();
    void recorridoEnOrden(Nodo* nodo);

    void asignar();
    void asignar_recorrido(Nodo* nodo, string recorrido);

    string encriptar(string texto, vector<Nodo*> vector);
};
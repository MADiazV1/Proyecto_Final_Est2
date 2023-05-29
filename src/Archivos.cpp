#include "Archivos.h"

void Archivo::crear_archivo_bin(string frasesSpan, string file){
    ofstream archivo(file, ios::binary);
    if(!archivo.is_open()){
        return;
    }
    for(char caracter : frasesSpan){
        if(caracter == '0'){
            char byte = 0;
            archivo.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
        }else if(caracter == '1'){
            char byte = 1;
            archivo.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
        }
    }
    archivo.close();
}

string Archivo::leer_documento(string archivoBin) {
    ifstream archivo(archivoBin, ios::binary);
    if (!archivo.is_open()) {
        return "";
    }
    string cadena;
    char byte;
    while (archivo.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
        if (byte == 0) {
            cadena += '0';
        } else if (byte == 1) {
            cadena += '1';
        }
    }
    archivo.close();
    return cadena;
}

string Archivo::desencriptar(string texto, Heap arbol){
    string nuevoTexto;
    Nodo* nodo = arbol.heap[0];
    for(char str : texto){
        if(str == '1'){
            nodo = nodo->izq;
        }else{
            nodo = nodo->der;
        }
        if(!nodo->huff){
            if(nodo->get_letra() != '&'){
                nuevoTexto += nodo->get_letra();
                nodo = arbol.heap[0];
            }else{
                nuevoTexto += "\n";
                nodo = arbol.heap[0];
            }
        }
    }
    return nuevoTexto;
}

void Archivo::crear_archivo_txt(string texto, string file){
    ofstream archivo(file, ios::binary);
    if(archivo.is_open()){
        archivo.write(texto.c_str(), texto.length());
        archivo.close();
        cout << "Archivo creado" << endl;
        cout << "/---------------------------------------------------------------------------------------------/" << endl;
    }else{
        cout << "No se pudo crear el archivo." << endl;
        cout << "/---------------------------------------------------------------------------------------------/" << endl;
    }
}
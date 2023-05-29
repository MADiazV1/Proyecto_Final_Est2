#include "Archivos.h"
#include <string>
#include <cstdlib>
#include <random>

vector<string> creacion_lista_frases(int repeticiones){
    vector<string> palabras = { "corre", "comprar", "quiero", "saludar", "el", "la", "los", "las", "un", "una", "unos", "unas", "gato", "perro", "casa", "coche", "arbol", "sol", "salta", "come", "duerme", "baila", "ama", "feliz", "triste", "grande", "pequenno", "feo", "estadio", "casa", "lunes", "martes", "miercoles", "jueves", "viernes", "sabado", "domingo", "festivo", "futbol", "baloncesto", "hockey", "familia", "registrar", "serio", "duro", "tener", "mucho", "oferta", "increible", "descuentos", "edificio", "pesos", "soledad", "nosotros", "ellos", "barato"};

    vector<string> frases;
    srand(time(NULL));
    random_device random;
    for(int i=0; i<repeticiones; i++){
        string frase = "";
        uniform_int_distribution<int> randFrase(5,10);
        for(int i=0; i<randFrase(random); i++){
            uniform_int_distribution<int> p(0,palabras.size()-1);
            frase += palabras[p(random)] + " ";
        }
        frases.push_back(frase);
    }
    return frases;
}

const int num = 101;
bool buscador(const string& texto, const string& patron){
    int tamannoPatron = patron.length();
    int tamannoTexto = texto.length();
    int hashTexto = 0;
    int hastPatron = 0;
    int h = 1;
    int cantidad = 256;
    for(int i=0; i<tamannoPatron-1; i++){
        h = (h * cantidad) % num;
    } 
    for(int i=0; i<tamannoPatron; i++){
        hastPatron = (cantidad * hastPatron + patron[i]) % num;
        hashTexto = (cantidad * hashTexto + texto[i]) % num;
    }
    for(int i=0; i<=tamannoTexto-tamannoPatron; i++){
        if(hastPatron == hashTexto){
            bool coincidencia = true;
            for(int j=0; j<tamannoPatron; j++){
                if(texto[i+j] != patron[j]){
                    coincidencia = false;
                    break;
                }
            }
            if(coincidencia){
                return true;
            }
        }
        if(i < tamannoTexto - tamannoPatron){
            hashTexto = (cantidad * (hashTexto - texto[i] * h)+ texto[i+tamannoPatron]) % num;
            if(hashTexto < 0){
                hashTexto = (hashTexto + num);
            }
        }
    }
    return false;
}

vector<string> frasesSpan(vector<string> frases){
    vector<string> span;
    vector<string> palabrasSpan = { "comprar","registrar","festivo","oferta","descuentos","pesos","barato"};
    int i=0;
    for(string frase : frases){
        for(string pSpan : palabrasSpan){
            bool es_span = buscador(frase, pSpan);
            if(es_span){
                frase += "&";
                span.push_back(frase);
                break;
            }
        }
        i++;
    }
    return span;
}

vector<string> eliminar_span(vector<string> frases){
    vector<string> noSpan;
    vector<string> palabrasSpan = { "comprar","registrar","festivo","oferta","descuentos","pesos","barato"};
    for(string frase : frases){
        bool tf = true;
        for(string pSpan : palabrasSpan){
            bool es_span = buscador(frase, pSpan);
            if(es_span){ 
                tf = false;               
                break;
            }
        }
        if(tf){
            frase += "&";
            noSpan.push_back(frase);
        }
    }
    return noSpan;
}

int main(){
    Nodo nodo;
    Heap miHeap;
    Archivo archivo;

    srand(time(NULL));
    random_device random;
    uniform_int_distribution<int> cantidad(30,50);
    
    string alfabetoHuffman = "abcdefghijklmnopqrstuvwxyz &";

    vector<Nodo*> alfabeto = nodo.vector_nodo_letras(alfabetoHuffman);
    vector<string> frases = creacion_lista_frases(cantidad(random));

    vector<string> span = frasesSpan(frases);
    vector<string> Nfrases = eliminar_span(frases);
    for(Nodo* item : alfabeto){
        miHeap.agregar(item);
    }

    miHeap.huffman();
    // miHeap.imprimir();

    string noSpanBin = "";
    for(string item : Nfrases){
        noSpanBin += miHeap.encriptar(item, alfabeto);
    }
    archivo.crear_archivo_bin(noSpanBin, "NoSpanBin");
    string docNoSpan = archivo.leer_documento("../dist/NoSpanBin");
    archivo.crear_archivo_txt(archivo.desencriptar(docNoSpan, miHeap), "NoSpan.txt");

    string spanBin = "";
    for(string item : span){
        spanBin += miHeap.encriptar(item, alfabeto);
    }
    archivo.crear_archivo_bin(spanBin, "SpanBin");
    string docSpan = archivo.leer_documento("../dist/SpanBin");
    archivo.crear_archivo_txt(archivo.desencriptar(docSpan, miHeap), "Span.txt");


    return 0;
}
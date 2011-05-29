#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;
#include <sstream>
#include "Lexico.h"
#include "Gramatica.h"
#include "Entrega3.h"

int main()
{
    Lexico lexico("archivo.txt");
    lexico.generarTokens();
    //lexico.printTokens();
    Gramatica gramatica(lexico);
    //cout<<"String import: "<<gramatica.string_import<<endl;
    //cout<<"String parse_code: "<<gramatica.string_parser_code<<endl;
    //cout<<"String class: "<<gramatica.string_class<<endl;
    //gramatica.printTerminales();
    //gramatica.printNoTerminales();
    //gramatica.printProducciones();
    Entrega2 entrega2(gramatica);
    //entrega2.printProduccionesProcesadas();
    //entrega2.funcion_misterio();
    //cout<<entrega2.compararListaProducciones(entrega2.nodos[0],entrega2.nodos[0]);
    Tabla tabla(entrega2.lista_nodos,gramatica.terminales,gramatica.no_terminales,gramatica.lista_producciones);
    vector<string> tokens;
    tokens.push_back("a");
    tokens.push_back("x");
    tokens.push_back("b");
    if(tabla.verificarTokens(tokens))
        cout<<"input correcto";
    else
        cout<<"input incorrecto";
    return 0;
}

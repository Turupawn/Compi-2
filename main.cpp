#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;
#include <sstream>
#include "Lexico.h"
#include "Gramatica.h"
#include "Entrega2.h"

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
    Misterio misterio(gramatica);
    //misterio.printProduccionesProcesadas();
    //misterio.funcion_misterio();
    misterio.funcionMisterio();
    //cout<<misterio.compararListaProducciones(misterio.nodos[0],misterio.nodos[0]);
    return 0;
}

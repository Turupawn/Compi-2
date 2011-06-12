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
    cout<<"----Iniciando MiCup----"<<endl;
    cout<<"Leyendo desde el archivo gramatica"<<endl;
    Lexico lexico("gramatica");
    lexico.generarTokens();
    //lexico.printTokens();
    Gramatica gramatica(lexico);
    //cout<<"String import: "<<gramatica.string_import<<endl;
    //cout<<"String parse_code: "<<gramatica.string_parser_code<<endl;
    //cout<<"String class: "<<gramatica.string_class<<endl;
    //gramatica.printTerminales();
    //gramatica.printNoTerminales();
    //gramatica.printProducciones();
    cout<<endl<<"Generando nodos:"<<endl;
    Entrega2 entrega2(gramatica);
    //entrega2.printProduccionesProcesadas();
    //entrega2.funcion_misterio();
    //cout<<entrega2.compararListaProducciones(entrega2.nodos[0],entrega2.nodos[0]);
    cout<<endl<<"Generando tabla:"<<endl;
    Tabla tabla(entrega2.lista_nodos,gramatica.terminales,gramatica.no_terminales,gramatica.lista_producciones);
    tabla.print();
    tabla.escribirParser();
    cout<<endl<<"Escribiendo en el archivo MiParser.java"<<endl;
    cout<<"Procedimiento terminado con exito"<<endl;


cout<<"      ___                       ___           ___           ___   "<<endl;
cout<<"     /__/\\        ___          /  /\\         /__/\\         /  /\\  "<<endl;
cout<<"    |  |::\\      /  /\\        /  /:/         \\  \\:\\       /  /::\\ "<<endl;
cout<<"    |  |:|:\\    /  /:/       /  /:/           \\  \\:\\     /  /:/\\:\\ "<<endl;
cout<<"  __|__|:|\\:\\  /__/::\\      /  /:/  ___   ___  \\  \\:\\   /  /:/~/:/"<<endl;
cout<<" /__/::::| \\:\\ \\__\\/\\:\\__  /__/:/  /  /\\ /__/\\  \\__\\:\\ /__/:/ /:/ "<<endl;
cout<<" \\  \\:\\~~\\__\\/    \\  \\:\\/\\ \\  \\:\\ /  /:/ \\  \\:\\ /  /:/ \\  \\:\\/:/  "<<endl;
cout<<"  \\  \\:\\           \\__\\::/  \\  \\:\\  /:/   \\  \\:\\  /:/   \\  \\::/   "<<endl;
cout<<"   \\  \\:\\          /__/:/    \\  \\:\\/:/     \\  \\:\\/:/     \\  \\:\\   "<<endl;
cout<<"    \\  \\:\\         \\__\\/      \\  \\::/       \\  \\::/       \\  \\:\\  "<<endl;
cout<<"     \\__\\/                     \\__\\/         \\__\\/         \\__\\/  2.0"<<endl;

/*

cout<<" .-.-. .-.-. .-.-. .-.-. .-.-."<<endl;
cout<<"( M .'( i .'( C .'( U .'( P .'"<<endl;
cout<<" `.(   `.(   `.(   `.(   `.(  "<<endl;

cout<<" _  _  __  ___  _  _  ____  ";
cout<<"( \/ )(  )/ __)/ )( \(  _ \ ";
cout<<"/ \/ \ )(( (__ ) \/ ( ) __/ ";
cout<<"\_)(_/(__)\___)\____/(__)  ";

*/


    return 0;
}

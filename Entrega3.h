#include "Entrega2.h"
class ElementoPila
{
    //string
};
class FilaTerminal
{
public:
    string terminal;
    string tipo;
    int nodo;
    FilaTerminal(string terminal,string tipo,int nodo)
    {
        this->terminal=terminal;
        this->tipo=tipo;
        this->nodo=nodo;
    }
};
class FilaNoTerminal
{
public:
    string no_terminal;
    int nodo;
    FilaNoTerminal(string no_terminal,int nodo)
    {
        this->no_terminal=no_terminal;
        this->nodo=nodo;
    }
};
class Fila
{
public:
    vector<FilaTerminal> terminales;
    vector<FilaNoTerminal> no_terminales;
};
class Tabla
{
public:
    //dados
    vector<Nodo> lista_nodos;
    vector<Produccion> lista_producciones;
    //dar
    vector<Fila> filas;
    Tabla(vector<Nodo> lista_nodos,vector<Terminal> terminales,vector<NoTerminal> no_terminales,vector<Produccion>lista_producciones)
    {
        this->lista_producciones=lista_producciones;
        this->lista_nodos=lista_nodos;
        terminales.push_back(Terminal("$"));
        for(int i=0;i<lista_nodos.size();i++)
        {
            filas.push_back(Fila());
            for(int j=0;j<lista_nodos[i].producciones.size();j++)
            {
                Produccion p_actual=lista_nodos[i].producciones[j];
                if(p_actual.posicion<p_actual.simbolos.size())
                {
                    if(compararCadenas(p_actual.getSimboloActual().tipo,"terminal"))//agregacion
                    {
                        bool existe=false;
                        for(int k=0;k<filas[i].terminales.size();k++)
                            if(compararCadenas(p_actual.getSimboloActual().nombre,filas[i].terminales[k].terminal))
                                existe=true;
                        if(!existe)
                            filas[i].terminales.push_back(FilaTerminal(p_actual.getSimboloActual().nombre,"d",getNumeroNodo(p_actual)));
                    }
                    if(compararCadenas(p_actual.getSimboloActual().tipo,"no terminal"))//agregacion
                        filas[i].no_terminales.push_back(FilaNoTerminal(p_actual.getSimboloActual().nombre,getNumeroNodo(p_actual)));
                }else
                {
                    if(p_actual.nombre[0]=='p')//agregacion
                        filas[i].terminales.push_back(FilaTerminal("$","a",-1));
                    else
                        for(int k=0;k<p_actual.set_no_terminales.size();k++)//agregacion
                            filas[i].terminales.push_back(FilaTerminal(p_actual.set_no_terminales[k],"r",getNumeroProduccion(p_actual)));
                }
            }
        }

        cout<<endl<<endl<<endl;
        for(int i=0;i<filas.size();i++)
        {
            cout<<i<<":";
            for(int j=0;j<filas[i].terminales.size();j++)
            {
                cout<<" "<<filas[i].terminales[j].terminal<<filas[i].terminales[j].tipo<<filas[i].terminales[j].nodo<<",";
            }
            cout<<"  |  ";
            for(int j=0;j<filas[i].no_terminales.size();j++)
            {
                cout<<" "<<filas[i].no_terminales[j].no_terminal<<filas[i].no_terminales[j].nodo<<",";
            }
            cout<<endl;
        }
    }
    int getNumeroNodo(Produccion produccion)
    {
        produccion.posicion++;
        for(int i=0;i<lista_nodos.size();i++)
            if(lista_nodos[i].producciones[0].compararProduccion(produccion))//!!!!
                return i;
        return -1;
    }
    int getNumeroProduccion(Produccion produccion)
    {
        for(int i=0;i<lista_producciones.size();i++)
            if(lista_producciones[i].compararProduccionSimple(produccion))
                return i;
        return -1;
    }

    bool verificarTokens(vector<string> cadena)
    {
        int fila_actual=0;
        int pos_actual=0;
        for(int i=0;i<filas[fila_actual].terminales.size();i++)
            if(compararCadenas(filas[fila_actual].terminales[i].terminal,cadena[pos_actual]))
                cout<<filas[fila_actual].terminales[i].terminal<<filas[fila_actual].terminales[i].tipo<<filas[fila_actual].terminales[i].nodo;
        return false;
    }
};

#include "Entrega2.h"
#include <stdlib.h>
#include <iostream>
#include <string>
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

bool filaTerminalContieneNombre(Fila fila,string nombre)
{
    bool existe=false;
    for(int k=0;k<fila.terminales.size();k++)
        if(compararCadenas(nombre,fila.terminales[k].terminal))
            return true;
    return false;
}

bool filaNoTerminalContieneNombre(Fila fila,string nombre)
{
    bool existe=false;
    for(int k=0;k<fila.no_terminales.size();k++)
        if(compararCadenas(nombre,fila.no_terminales[k].no_terminal))
            return true;
    return false;
}

class Tabla
{
public:
    //dados
    vector<Nodo> lista_nodos;
    vector<Produccion> lista_producciones;
    vector<Terminal> terminales;
    vector<NoTerminal> no_terminales;
    Gramatica gramatica;
    //dar
    vector<Fila> filas;
    Tabla(vector<Nodo> lista_nodos,vector<Terminal> terminales,vector<NoTerminal> no_terminales,vector<Produccion>lista_producciones,Gramatica gramatica)
    {
        this->gramatica=gramatica;
        this->lista_producciones=lista_producciones;
        this->terminales=terminales;
        this->no_terminales=no_terminales;
        this->lista_producciones.insert(this->lista_producciones.begin(),Produccion("prima_"+this->lista_producciones[0].nombre,this->lista_producciones[0].tipo));
        this->lista_producciones[0].simbolos.push_back(Simbolo("no terminal",this->lista_producciones[1].nombre));
        this->lista_nodos=lista_nodos;
        terminales.push_back(Terminal("$"));
        for(int i=0;i<lista_nodos.size();i++)//for each nodo
        {
            filas.push_back(Fila());//agrego una fila
            //Ciclo de agregaciones de desplazares
            for(int j=0;j<lista_nodos[i].producciones.size();j++)//for each produccion del nodo actual
            {
                Produccion p_actual=lista_nodos[i].producciones[j];
                if(p_actual.posicion<p_actual.simbolos.size())//si no estoy al final la produccion
                {
                    if(compararCadenas(p_actual.getSimboloActual().tipo,"terminal"))//agregacion
                        if(!filaTerminalContieneNombre(filas[i],p_actual.getSimboloActual().nombre))
                            filas[i].terminales.push_back(FilaTerminal(p_actual.getSimboloActual().nombre,"d",getNumeroNodo(p_actual)));
                    if(compararCadenas(p_actual.getSimboloActual().tipo,"no terminal"))//agregacion
                        if(!filaNoTerminalContieneNombre(filas[i],p_actual.getSimboloActual().nombre))
                            filas[i].no_terminales.push_back(FilaNoTerminal(p_actual.getSimboloActual().nombre,getNumeroNodo(p_actual)));
                }
            }
            //Ciclo de agregaciones de reducires y aceptares
            for(int j=0;j<lista_nodos[i].producciones.size();j++)//for each produccion del nodo actual
            {
                Produccion p_actual=lista_nodos[i].producciones[j];
                if(p_actual.posicion==p_actual.simbolos.size())//si estoy al final la produccion
                {
                    if(p_actual.nombre[0]=='p'&&p_actual.nombre[1]=='r'&&p_actual.nombre[2]=='i'&&p_actual.nombre[3]=='m'&&p_actual.nombre[4]=='a'&&p_actual.nombre[5]=='_')//agregacion
                        filas[i].terminales.push_back(FilaTerminal("$","a",-1));
                    else
                        for(int k=0;k<p_actual.set_no_terminales.size();k++)//agregacion
                            if(!filaTerminalContieneNombre(filas[i],p_actual.set_no_terminales[k]))
                                filas[i].terminales.push_back(FilaTerminal(p_actual.set_no_terminales[k],"r",getNumeroProduccion(p_actual)));
                }
            }
        }
    }

    int print()
    {
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

    string getString(string str)
    {
        string res="";
        for(int i=0;str[i]!=0;i++)
            res+=str[i];
        return res;
    }

    void escribirParser()
    {
        ofstream myfile;
        myfile.open ("MiParser.java");

        //lectura parte1
        ifstream f("Auxiliar1", ifstream::in);
        std::stringstream buffer;
        buffer << f.rdbuf();
        std::string contents(buffer.str());
        myfile<<getString(gramatica.string_import);
        myfile<<getString(gramatica.string_parser_code);
        myfile<<contents;
        //escritura
        for(int i=0;i<lista_producciones.size();i++)
        {
            myfile<<"Produccion produccion"<<i<<"=new Produccion(\""<<getString(lista_producciones[i].nombre)<<"\");"<<endl;
            for(int j=0;j<lista_producciones[i].simbolos.size();j++)
            {
                if(compararCadenas(lista_producciones[i].simbolos[j].tipo,"no terminal"))
                    myfile<<"produccion"<<i<<".simbolos.add(new Simbolo(\""<<getString(lista_producciones[i].simbolos[j].nombre)<<"\"));"<<endl;
                else
                    myfile<<"produccion"<<i<<".simbolos.add(new Simbolo(\""<<getString(lista_producciones[i].simbolos[j].nombre)<<"\"));"<<endl;
            }
            myfile<<"gramatica.add(produccion"<<i<<");"<<endl;
        }
        myfile<<endl<<endl;


        for(int i=0;i<filas.size();i++)
        {
            myfile<<"Fila fila"<<i<<"=new Fila();"<<endl;
            for(int j=0;j<filas[i].terminales.size();j++)
            {
                myfile<<"fila"<<i<<".terminales.add(new FilaTerminal(\""<<getString(filas[i].terminales[j].terminal)<<"\", \""<<getString(filas[i].terminales[j].tipo)<<"\","<<filas[i].terminales[j].nodo<<"));"<<endl;
            }
            for(int j=0;j<filas[i].no_terminales.size();j++)
            {
                myfile<<"fila"<<i<<".no_terminales.add(new FilaNoTerminal(\""<<getString(filas[i].no_terminales[j].no_terminal)<<"\","<<filas[i].no_terminales[j].nodo<<"));"<<endl;
            }
            myfile<<"filas.add(fila"<<i<<");"<<endl;
        }
        myfile<<"}"<<endl;

        //escritura de funciones de pila
        myfile<<"Object ejecutarProduccion(int numero,ArrayList<Object> valores_pops)"<<endl;
        myfile<<"{"<<endl;
            myfile<<"ArrayList<Object> dolar=new ArrayList<Object>();"<<endl;
            myfile<<"for(int i=valores_pops.size()-1;i>=0;i--)"<<endl;
            myfile<<"{"<<endl;
                myfile<<"dolar.add(valores_pops.get(i));"<<endl;
            myfile<<"}"<<endl;
        for(int i=1;i<lista_producciones.size();i++)
        {
            myfile<<"if(numero=="<<i<<")"<<endl;
            myfile<<"{"<<endl;
                myfile<<"Object RESULT=null;"<<endl;
                //myfile<<"System.out.println(numero);"<<endl;
                string str=getString(lista_producciones[i].codigo);
                string str_res="";
                for(int j=0;str[j]!='\0';j++)
                {
                    if(str[j]=='$')
                    {
                        string num="";
                        j++;
                        for(;str[j]>='0'&&str[j]<='9';j++)
                            num+=str[j];
                        string nombre_p2=lista_producciones[i].simbolos[atoi(num.c_str())].nombre;
                        string tipo_p2=gramatica.getTipoProduccion(nombre_p2);
                        j--;
                //cout<<"%%"<<atoi(num.c_str())<<nombre_p2<<tipo_p2<<endl;
                        str_res+="("+tipo_p2+")dolar.get("+num+")";
                    }else
                    {
                        str_res+=str[j];
                    }
                }
                myfile<<str_res<<endl;
                //myfile<<getString(lista_producciones[i].codigo)<<endl;
                myfile<<"return (Integer)RESULT;"<<endl;
            myfile<<"}"<<endl;
        }
            myfile<<"return null;"<<endl;
        myfile<<"}"<<endl;

        //lectura parte2
        ifstream f2("Auxiliar2", ifstream::in);
        std::stringstream buffer2;
        buffer2 << f2.rdbuf();
        std::string contents2(buffer2.str());
        myfile<<contents2;

        f.close();
        f2.close();
        myfile.close();
    }

    void escribirAutomata()
    {
        ofstream myfile;
        myfile.open ("Automata", ofstream::out | ofstream::trunc);
        for(int i=0;i<lista_nodos.size();i++)
        {
            string temp_f=lista_nodos[i].getString()+"#";
            myfile<<"%i"<<i<<endl;
            for(int i=0;temp_f[i]!='#';i++)
            {
                if(temp_f[i]!='\0')
                    myfile<<temp_f[i];
            }
        }
        myfile<<"@"<<endl;
        for(int i=0;i<filas.size();i++)
        {
            for(int j=0;j<filas[i].terminales.size();j++)
            {
                if(compararCadenas(filas[i].terminales[j].tipo,"d"))
                {
                    myfile<<i<<"%";
                    string s_temp=filas[i].terminales[j].terminal;
                    for(int k=0;filas[i].terminales[j].terminal[k]!='\0';k++)
                        myfile<<filas[i].terminales[j].terminal[k];
                    myfile<<"%"<<filas[i].terminales[j].nodo<<endl;
                }
            }
        }

        for(int i=0;i<filas.size();i++)
        {
            for(int j=0;j<filas[i].no_terminales.size();j++)
            {
                myfile<<i<<"%";
                for(int k=0;filas[i].no_terminales[j].no_terminal[k]!='\0';k++)
                    myfile<<filas[i].no_terminales[j].no_terminal[k];
                myfile<<"%"<<filas[i].no_terminales[j].nodo<<endl;
            }
        }
    }

    int getNumeroNodo(Produccion produccion)
    {
        produccion.posicion++;
        for(int i=0;i<lista_nodos.size();i++)
        {
            Nodo n_actual=lista_nodos[i];
            if(n_actual.producciones[0].compararProduccionContieneTerminales(produccion))//!!!!
                return i;
            if(n_actual.producciones.size()>1)
            if(n_actual.producciones[1].compararProduccionContieneTerminales(produccion))//!!!!
                return i;
            /*
            for(int j=0;j<n_actual.producciones.size();j++)
            {
                Produccion p_actual=n_actual.producciones[j];
                bool validaciones=false;
                //if()
                //if(!compararCadenas(p_actual.nombre,n_actual.producciones[0].nombre))
                //    break;
                if(p_actual.compararProduccionSinTerminales(produccion))//!!!!
                    return i;
            }*/
        }
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

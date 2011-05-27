class Terminal
{
public:
    string nombre;
    Terminal(string nombre)
    {
        this->nombre=nombre;
    }
};

class NoTerminal
{
public:
    string tipo;
    string nombre;
    NoTerminal(string tipo,string nombre)
    {
        this->tipo=tipo;
        this->nombre=nombre;
    }
};

class Simbolo
{
public:
    string tipo,nombre;
    Simbolo(string tipo, string nombre)
    {
        this->tipo=tipo;
        this->nombre=nombre;
    }
};

class Produccion
{
public:
    vector<Simbolo> simbolos;
    vector<string> set_no_terminales;
    int posicion;
    string nombre;
    Produccion(string nombre)
    {
        this->nombre=nombre;
        posicion=0;
    }
    Simbolo getSimboloActual()
    {
        return simbolos[posicion];
    }
    void print()
    {
        cout<<nombre<<"->";
        for(int i=0;i<simbolos.size();i++)
        {
            cout<<" ";
            if(posicion==i)
                cout<<".";
            cout<<simbolos[i].nombre;
        }
        if(posicion==simbolos.size())
            cout<<".";
        cout<<"{";
        for(int i=0;i<set_no_terminales.size();i++)
            cout<<set_no_terminales[i]<<",";
        cout<<"}";
        cout<<endl;
    }

};

class Gramatica
{
public:
    vector<Produccion> lista_producciones;
    vector<Terminal> terminales;
    vector<NoTerminal> no_terminales;

    string string_import,string_parser_code,string_class;

    vector<Token> tokens;
    int i;
    bool compararToken(string tipo,string lexema)
    {
        i++;
        return tokens[i-1].tipo==tipo && tokens[i-1].lexema==lexema;
    }
    bool compararToken(string tipo)
    {
        i++;
        return tokens[i-1].tipo==tipo;
    }
    void agregarSimbolo(string nombre_produccion,Simbolo simbolo)
    {
        int _i;
        int i2;
        for(_i=0;_i<lista_producciones.size();_i++)
            if(lista_producciones[_i].nombre==nombre_produccion)
                i2=_i;
        if(existeNoTerminal(simbolo.nombre))
            simbolo.tipo="no terminal";
        if(existeTerminal(simbolo.nombre))
            simbolo.tipo="terminal";
        lista_producciones[i2].simbolos.push_back(simbolo);
    }
    Gramatica()
    {

    }
    Gramatica(Lexico lexico)
    {
        string_parser_code=string_import=string_class="";
        i=0;
        this->tokens=lexico.tokens;
        if(s())
        {
            if(!validacionProduccionesUtilizadas())
                cout<<"Error de semantica: existen no terminales sin una produccion"<<endl;
            cout<<"Gramatica correcta"<<endl;
        }
        else
            cout<<"Gramatica incorrecta"<<endl;
    }
    bool s()
    {
        for(;;)
        {
            if(tokens[i].tipo=="string import")
            {
                if(string_import=="")
                {
                    string_import= " "+tokens[i].lexema;
                }else
                {
                    cout<<"Error de semantica: solo puede haber un solo import"<<endl;
                    return false;
                }
                i++;
            }
            else if(tokens[i].tipo=="string parser")
            {
                if(string_parser_code=="")
                {
                    string_parser_code= " "+tokens[i].lexema;
                }else
                {
                    cout<<"Error de semantica: solo puede haber un solo parser code"<<endl;
                    return false;
                }
                i++;
            }else if(tokens[i].tipo=="string class")
            {
                if(string_class=="")
                {
                    string_class= " "+tokens[i].lexema;
                }else
                {
                    cout<<"Error de semantica: solo puede haber un solo %class"<<endl;
                    return false;
                }
                i++;
            }else
            {
                break;
            }
        }
        clase();

        return gramatica();
    }
    bool clase()
    {
        if(compararToken("puntuacion","%"))
        {
            if(compararToken("palabra reservada","class"))
            {
                if(compararToken("cadena"))
                {
                    return true;
                }else
                    i--;
            }else
                i--;
        }else
            i--;
        return false;
    }
    bool gramatica()
    {
        if(!declaraciones())
        {
            cout<<"Decalracion incorrecta."<<endl;
            return false;
        }
        if(!producciones())
        {
            cout<<"Produccion incorrecta."<<endl;
            return false;
        }
        return true;
    }
    bool declaraciones()
    {
        for(;;)
        {
            if(compararToken("eof"))
                return true;
            else
                i--;
            if(compararToken("palabra reservada","terminal"))
            {
                if(!listaTerminal())
                {
                    cout<<"Error: se esperaba una lista de terminales."<<endl;
                    return false;
                }
                if(!compararToken("puntuacion",";"))
                {
                    cout<<"Error: se esperaba ;."<<endl;
                    return false;
                }
            }else
            {
                i--;
                if(compararToken("palabra reservada","nonterminal"))
                {
                    if(!compararToken("cadena"))
                    {
                        cout<<"Error: se esperaba un tipo de noterminal."<<endl;
                        return false;
                    }
                    if(!listaNoTerminal(tokens[i-1].lexema))
                    {
                        cout<<"Error: se esperaba una lista de terminales."<<endl;
                        return false;
                    }
                    if(!compararToken("puntuacion",";"))
                    {
                        cout<<"Error: se esperaba ;."<<endl;
                        return false;
                    }
                }else
                {
                    i--;
                    return true;
                }
            }
        }
    }
    bool producciones()
    {
        for(;;)
        {
            if(compararToken("eof"))
                return true;
            else
                i--;
        if(!compararToken("cadena"))
        {
            cout<<"Error: se esperaba un no terminal."<<endl;
            return false;
        }
        string nombre_produccion=tokens[i-1].lexema;
        if(!existeNoTerminal(tokens[i-1].lexema))
        {
            cout<<"Error de semantica: solo los no terminales pueden producir. ";
            if(existeTerminal(tokens[i-1].lexema))
                cout<<tokens[i-1].lexema<<" es un terminal";
            cout<<endl;
            return false;
        }
        string nombre_produccion2=tokens[i-1].lexema;
        lista_producciones.push_back(nombre_produccion2);
        if(!compararToken("puntuacion","->"))
        {
            cout<<"Error: se esperaba ->."<<endl;
            return false;
        }
        if(!caso(nombre_produccion))
        {
            cout<<"Error: se esperaba un caso dentro de la produccion."<<endl;
            return false;
        }
        for(;;)
        {
            if(!compararToken("puntuacion","|"))
            {
                i--;
                break;
            }
            lista_producciones.push_back(nombre_produccion2);
            if(!caso(nombre_produccion))
            {
                cout<<"Error: se esperaba un caso dentro de la produccion."<<endl;
                return false;
            }
        }
        if(!compararToken("puntuacion",";"))
        {
            cout<<"Error: se esperaba ;."<<endl;
            return false;
        }
        }
        return true;
    }
    bool listaTerminal()
    {
        if(compararToken("cadena"))
        {
            if(!existeTerminal(tokens[i-1].lexema))
                terminales.push_back(Terminal(tokens[i-1].lexema));
            else
            {
                cout<<"Error de semantica: ya existe el terminal "<<tokens[i-1].lexema<<endl;
                return false;
            }
            for(;;)
            {
                if(compararToken("puntuacion",","))
                {
                    if(!compararToken("cadena"))
                        return false;
                    if(!existeTerminal(tokens[i-1].lexema))
                        terminales.push_back(Terminal(tokens[i-1].lexema));
                    else
                    {
                        cout<<"Error de semantica: ya existe el terminal "<<tokens[i-1].lexema<<endl;
                        return false;
                    }
                }else
                {
                    i--;
                    break;
                }
            }
        }else
            return false;
        return true;
    }
    bool listaNoTerminal(string tipo)
    {
        if(compararToken("cadena"))
        {

            if(!existeNoTerminal(tokens[i-1].lexema))
                no_terminales.push_back(NoTerminal(tipo,tokens[i-1].lexema));
            else
            {
                cout<<"Error de semantica: ya existe el no terminal "<<tokens[i-1].lexema<<endl;
                return false;
            }

            for(;;)
            {
                if(compararToken("puntuacion",","))
                {
                    if(!compararToken("cadena"))
                        return false;

                    if(!existeNoTerminal(tokens[i-1].lexema))
                        no_terminales.push_back(NoTerminal(tipo,tokens[i-1].lexema));
                    else
                    {
                        cout<<"Error de semantica: ya existe el no terminal "<<tokens[i-1].lexema<<endl;
                        return false;
                    }

                }else
                {
                    i--;
                    break;
                }
            }
        }else
            return false;
        return true;
    }
    bool caso(string nombre_produccion)
    {
        for(;;)
        {
            if(compararToken("cadena"))
            {
                //AQUI
                agregarSimbolo(nombre_produccion,Simbolo("?",tokens[i-1].lexema));
                if(!existeNoTerminal(tokens[i-1].lexema) && !existeTerminal(tokens[i-1].lexema))
                {
                    cout<<"Error de semantica: no se ha declarado el simbolo "<<tokens[i-1].lexema<<endl;
                    return false;
                }
            }else
            {
                i--;
                if(compararToken("codigo"))
                {
                    if(compararToken("cadena"))
                    {
                        //AQUI
                        agregarSimbolo(nombre_produccion,Simbolo("?",tokens[i-1].lexema));
                        if(!existeNoTerminal(tokens[i-1].lexema) && !existeTerminal(tokens[i-1].lexema))
                        {
                            cout<<"Error de semantica: no se ha declarado el simbolo "<<tokens[i-1].lexema<<endl;
                            return false;
                        }
                    }else
                    {
                        i--;
                        return true;
                    }
                }else
                {
                    i--;
                    return true;
                }
            }
        }
    }
    void printTerminales()
    {
        int size_terminales=terminales.size();
        for(int i=0;i<size_terminales;i++)
            cout<<terminales[i].nombre<<endl;
    }
    void printNoTerminales()
    {
        int size_no_terminales=no_terminales.size();
        for(int i=0;i<size_no_terminales;i++)
            cout<<no_terminales[i].tipo<<":"<<no_terminales[i].nombre<<endl;
    }
    void printProducciones()
    {
        int size_producciones=lista_producciones.size();
        for(int i=0;i<size_producciones;i++)
        {
            cout<<lista_producciones[i].nombre<<endl;
            cout<<"=================="<<endl;
            for(int j=0;j<lista_producciones[i].simbolos.size();j++)
            {
                cout<<"-"<<lista_producciones[i].simbolos[j].nombre<<endl;
                cout<<" "<<lista_producciones[i].simbolos[j].tipo<<endl;
            }
        }
    }
    bool existeTerminal(string nombre)
    {
        int size_terminales=terminales.size();
        for(int i=0;i<size_terminales;i++)
            if(terminales[i].nombre[0]==nombre[0])
                return true;
        return false;
    }
    bool existeNoTerminal(string nombre)
    {
        int size_no_terminales=no_terminales.size();
        for(int i=0;i<size_no_terminales;i++)
        {
            if(no_terminales[i].nombre[0]==nombre[0])
                return true;
        }
        return false;
    }
    bool validacionProduccionesUtilizadas()
    {
        int size_producciones=lista_producciones.size();
        int size_no_terminales=no_terminales.size();
        for(int i=0;i<size_no_terminales;i++)
        {
            bool flag=false;
            for(int j=0;j<size_producciones;j++)
                if(lista_producciones[j].nombre[0]==no_terminales[i].nombre[0])
                    flag=true;
            if(!flag)
                return false;
        }
        return true;

    }
};

int getLenght(string str)
{
    int i;
    for(i=0;str[i]!='\0';i++);
    return i;
}
bool compararCadenas(string str1,string str2)
{
    if(getLenght(str1)!=getLenght(str2))
        return false;
    for(int i=0;i<getLenght(str1);i++)
    {
        if(str1[i]!=str2[i])
            return false;
    }
    return true;
}
bool contieneCadena(vector<string> lista,string str)
{
    bool flag=false;
    for(int l=0;l<lista.size();l++)
        if(compararCadenas(lista[l],str))
            flag=true;
    return flag;
}

int intContieneCadena(vector<string> lista,string str)
{
    for(int l=0;l<lista.size();l++)
        if(compararCadenas(lista[l],str))
            return l;
    return -1;
}

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
    bool procesado;
    string tipo;

    string codigo;
    Produccion(string nombre,string tipo)
    {
        this->nombre=nombre;
        posicion=0;
        procesado=false;
        codigo="";
        this->tipo=tipo;
    }
    bool compararProduccion(Produccion pb)
    {
        Produccion pa=*this;
        if(pa.simbolos.size()!=pb.simbolos.size())
            return false;
        if(pa.set_no_terminales.size()!=pb.set_no_terminales.size())
            return false;
        for(int i=0;i<pa.simbolos.size();i++)
            if(!compararCadenas(pa.simbolos[i].nombre,pb.simbolos[i].nombre))
                return false;
        for(int i=0;i<pa.set_no_terminales.size();i++)
            if(!compararCadenas(pa.set_no_terminales[i],pb.set_no_terminales[i]))
                return false;
        return pa.posicion==pb.posicion;
    }
    bool compararProduccionContieneTerminales(Produccion pb)
    {
        Produccion pa=*this;
        if(pa.simbolos.size()!=pb.simbolos.size())
            return false;
        if(pa.set_no_terminales.size()<pb.set_no_terminales.size())
            return false;
        for(int i=0;i<pa.simbolos.size();i++)
            if(!compararCadenas(pa.simbolos[i].nombre,pb.simbolos[i].nombre))
                return false;

        for(int i=0;i<pb.set_no_terminales.size();i++)
        {
            if(!contieneCadena(pa.set_no_terminales,pb.set_no_terminales[i]))
                return false;
        }
        return pa.posicion==pb.posicion;
    }
    bool compararProduccionSinTerminales(Produccion pb)
    {
        Produccion pa=*this;
        if(pa.simbolos.size()!=pb.simbolos.size())
            return false;
        for(int i=0;i<pa.simbolos.size();i++)
            if(!compararCadenas(pa.simbolos[i].nombre,pb.simbolos[i].nombre))
                return false;
        return pa.posicion==pb.posicion;
    }
    bool compararProduccionSimple(Produccion pb)
    {
        Produccion pa=*this;
        if(pa.simbolos.size()!=pb.simbolos.size())
            return false;
        for(int i=0;i<pa.simbolos.size();i++)
            if(!compararCadenas(pa.simbolos[i].nombre,pb.simbolos[i].nombre))
                return false;
        return true;
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
        cout<<endl<<"codigo:"<<codigo<<endl;
    }
    string getString()
    {
        string res="";
        res+=nombre+"->";
        for(int i=0;i<simbolos.size();i++)
        {
            res+=" ";
            if(posicion==i)
                res+=".";
            res+=simbolos[i].nombre;
        }
        if(posicion==simbolos.size())
            res+=".";
        res+="{";
        for(int i=0;i<set_no_terminales.size();i++)
            res+=set_no_terminales[i]+",";
        res+="}";

        res+="\n";
        return res;
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
    vector< vector<string> > first;
    vector<string> simbolos;
    int i;
    bool agregarAFirst(string simbolo,string a_agregar)
    {
        if(!contieneCadena(first[intContieneCadena(simbolos,simbolo)],a_agregar))
        {
            first[intContieneCadena(simbolos,simbolo)].push_back(a_agregar);
            return true;
        }
        return false;
    }
    vector<string> getFirst(string simbolo)
    {
        return first[intContieneCadena(simbolos,simbolo)];
    }
    void procesarPrimeros()
    {
        for(int i=0;i<terminales.size();i++)
            simbolos.push_back(terminales[i].nombre);
        for(int i=0;i<no_terminales.size();i++)
            simbolos.push_back(no_terminales[i].nombre);

        //inicio
        //for each x ∈ T, FIRST(x) ← {x}
        //for each A ∈ NT, FIRST(A) ← Ø
        for(int i=0;i<simbolos.size();i++)
        {
            vector<string> lista_vacia;
            first.push_back(lista_vacia);
        }
        for(int i=0;i<simbolos.size();i++)
            if(existeTerminal(simbolos[i]))
            {
                first[i].push_back(simbolos[i]);
            }
        //while (FIRST sets are still changing)
        bool cambiado;
        do
        {
            cambiado=false;
            for(int i=0;i<lista_producciones.size();i++)//for each p ∈ P, of the form A→β,
            {
                Produccion p=lista_producciones[i];
                string A=p.nombre;
                if(p.simbolos.size()==0)//if β is ε then
                {
                    if(agregarAFirst(A,"epsilon"))//FIRST(A) ← FIRST(A) ∪ { ε }
                        cambiado=true;
                }
                else
                {
                    //FIRST(A) ← FIRST(A) ∪ ( FIRST(B1) – { ε } )
                    string B=p.simbolos[0].nombre;
                    for(int j=0;j<getFirst(B).size();j++)
                        if(!compararCadenas(getFirst(B)[j],"epsilon"))
                            if(agregarAFirst(A,getFirst(B)[j]))
                                cambiado=true;
                    //for i ← 1 to k–1 by 1 while ε ∈ FIRST(Bi )
                    for(int j=0;j<p.simbolos.size()-1;j++)
                    {
                        string B=p.simbolos[j].nombre;
                        if(!contieneCadena(getFirst(B),"epsilon"))
                            break;

                        //FIRST(A) ← FIRST(A) ∪ ( FIRST(Bi +1) – { ε } )
                        string Bsig=p.simbolos[j+1].nombre;
                        for(int k=0;k<getFirst(Bsig).size();k++)
                            if(!compararCadenas(getFirst(Bsig)[k],"epsilon"))
                                if(agregarAFirst(A,getFirst(Bsig)[k]))
                                    cambiado=true;

                        //if i = k–1 and ε ∈ FIRST(Bk)
                        if(j==p.simbolos.size()-2 && contieneCadena(getFirst(Bsig),"epsilon"))
                            if(agregarAFirst(A,"epsilon"))
                                cambiado=true;
                    }

                }
            }
        }while(cambiado);
    }
    void printFirst()
    {
        for(int i=0;i<simbolos.size();i++)
        {
            cout<<simbolos[i]<<": ";
            for(int j=0;j<first[i].size();j++)
                cout<<first[i][j]<<",";
            cout<<endl;
        }
    }
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
            if(compararCadenas(lista_producciones[_i].nombre,nombre_produccion))
                i2=_i;
        if(existeNoTerminal(simbolo.nombre))
            simbolo.tipo="no terminal";
        if(existeTerminal(simbolo.nombre))
            simbolo.tipo="terminal";
        lista_producciones[i2].simbolos.push_back(simbolo);
    }
    void agregarCodigo(string nombre_produccion,string codigo)
    {
        int _i;
        int i2;
        for(_i=0;_i<lista_producciones.size();_i++)
            if(compararCadenas(lista_producciones[_i].nombre,nombre_produccion))
                i2=_i;
        lista_producciones[i2].codigo=codigo;
    }
    string getTipoProduccion(string nombre)
    {
        if(!existeNoTerminal(nombre))
            return "String";
        for(int i=0;i<no_terminales.size();i++)
            if(compararCadenas(nombre,no_terminales[i].nombre))
                return no_terminales[i].tipo;
        return "Nula";
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
        procesarPrimeros();
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

        string tipo_terminal="";
        for(int i=0;i<no_terminales.size();i++)
            if(compararCadenas(no_terminales[i].nombre,nombre_produccion2))
                tipo_terminal=no_terminales[i].tipo;

        lista_producciones.push_back(Produccion(nombre_produccion2,tipo_terminal));
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

            string tipo_terminal="";
            for(int i=0;i<no_terminales.size();i++)
                if(compararCadenas(no_terminales[i].nombre,nombre_produccion2))
                    tipo_terminal=no_terminales[i].tipo;
            lista_producciones.push_back(Produccion(nombre_produccion2,tipo_terminal));
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
                    agregarCodigo(nombre_produccion,tokens[i-1].lexema);
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
                cout<<"codigo:"<<lista_producciones[i].codigo<<endl;
            }
        }
    }
    bool existeTerminal(string nombre)
    {
        int size_terminales=terminales.size();
        for(int i=0;i<size_terminales;i++)
            if(compararCadenas(terminales[i].nombre,nombre))
                return true;
        return false;
    }
    bool existeNoTerminal(string nombre)
    {
        int size_no_terminales=no_terminales.size();
        for(int i=0;i<size_no_terminales;i++)
        {
            if(compararCadenas(no_terminales[i].nombre,nombre))
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
                if(compararCadenas(lista_producciones[j].nombre,no_terminales[i].nombre))
                    flag=true;
            if(!flag)
                return false;
        }
        return true;

    }
};

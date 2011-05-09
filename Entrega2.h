class Misterio
{
public:
    vector<Produccion> lista_producciones;
    vector< vector<Produccion> > nodos;
    Misterio(vector<Produccion> lista_producciones)
    {
        this->lista_producciones=lista_producciones;
        aumentarProduccion();
    }
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
    void aumentarProduccion()
    {
        lista_producciones.insert(lista_producciones.begin(),Produccion("prima_"+lista_producciones[0].nombre));
        lista_producciones[0].simbolos.push_back(Simbolo("no terminal",lista_producciones[1].nombre));
    }
    void printProducciones()
    {
        int size_producciones=lista_producciones.size();
        for(int i=0;i<size_producciones;i++)
        {
            cout<<endl;
            cout<<lista_producciones[i].nombre<<endl;
            cout<<"=================="<<endl;
            for(int j=0;j<lista_producciones[i].simbolos.size();j++)
            {
                cout<<"-"<<lista_producciones[i].simbolos[j].nombre;
                cout<<" ("<<lista_producciones[i].simbolos[j].tipo<<")"<<endl;
            }
        }
    }
    void printProduccion(Produccion produccion)
    {
        cout<<produccion.nombre<<"->";
        for(int i=0;i<produccion.simbolos.size();i++)
        {
            cout<<" ";
            if(produccion.posicion==i)
                cout<<".";
            cout<<produccion.simbolos[i].nombre;
        }
        if(produccion.posicion==produccion.simbolos.size())
            cout<<".";
        cout<<"{";
        for(int i=0;i<produccion.set_no_terminales.size();i++)
            cout<<produccion.set_no_terminales[i]<<",";
        cout<<"}";
        cout<<endl;
    }
    vector <Produccion> crearNodo(Produccion produccion_actual,int simbolo)
    {
        vector <Produccion> lista_actual;
        produccion_actual.posicion=simbolo;
        lista_actual.push_back(produccion_actual);
        if(simbolo>=produccion_actual.simbolos.size())
            return lista_actual;
        Simbolo simbolo_actual=produccion_actual.simbolos[simbolo];
        if(simbolo_actual.tipo=="no terminal")
        {
            for(int i=0;i<lista_producciones.size();i++)
            {
                if(compararCadenas(lista_producciones[i].nombre,simbolo_actual.nombre))
                {
                    vector <Produccion> temp=crearNodo(lista_producciones[i],0);
                    for(int i=0;i<temp.size();i++)
                        lista_actual.push_back(temp[i]);
                }
            }
        }
        return lista_actual;
    }
    void printNodo(int i)
    {
        vector<Produccion> lista=nodos[i];
        cout<<"I"<<i<<endl;
        for(int i=0;i<lista.size();i++)
            printProduccion(lista[i]);
    }
    vector<string> primero(string produccion)
    {
        vector <string> resultado;
        for(int i=0;i<lista_producciones.size();i++)
        {
            if(compararCadenas(lista_producciones[i].nombre,produccion))
                if(lista_producciones[i].simbolos.size()!=0)
                    if(compararCadenas(lista_producciones[i].simbolos[0].tipo,"terminal"))
                        resultado.push_back(lista_producciones[i].simbolos[0].nombre);
                    else
                    {
                        vector<string> temp=primero(lista_producciones[i].simbolos[0].nombre);
                        for(int _i=0;_i<temp.size();_i++)
                            resultado.push_back(temp[_i]);
                    }
                else
                    resultado.push_back("E");
        }
        return resultado;
    }
    bool compararProducciones(Produccion pa,Produccion pb)
    {
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
    bool compararListaProducciones(vector<Produccion> pa,vector<Produccion> pb)
    {
        if(pa.size()!=pb.size())
            return false;
        for(int i=0;i<pa.size();i++)
            if(!compararProducciones(pa[i],pb[i]))
                return false;
        return true;
    }
    void funcionCreacionRecursiva(Produccion primera,int posicion)
    {
        //Fin de la recursion
        if(primera.simbolos.size()<posicion)
            return;
        //Agregacion de no terminales siguientes de B
        //primera.set_no_terminales.clear();
        vector<string> set_no_terminales;
        if(posicion>=primera.simbolos.size()-1)
            set_no_terminales.push_back("$");
        else
        {
            string b=primera.simbolos[posicion+1].nombre;
            set_no_terminales=primero(b);
        }
        //Creacion de nodo
        vector<Produccion> i0=crearNodo(primera,posicion);
        //Agregacion de los no termnales
        for(int i=1;i<i0.size();i++)
            i0[i].set_no_terminales=set_no_terminales;
        //Agrego nodo si no existe
        for(int i=0;i<nodos.size();i++)
            if(compararListaProducciones(nodos[i],i0))
                return;
        nodos.push_back(i0);
        //Sub llamada recursiva
        ////vector<Produccion> subconjunto;
        ////for(int i=1;i<i0.size();i++)
            ////subconjunto.push_back(i0[i]);


        //LLamada recursiva para cada elemento
        for(int i=0;i<i0.size();i++)
            funcionCreacionRecursiva(i0[i],posicion+1);
        if(i0.size()>1)
            funcionCreacionRecursiva(i0[1],0);
    }
    void funcion_misterio2()
    {
        Produccion inicial=lista_producciones[0];
        inicial.set_no_terminales.push_back("$");
        funcionCreacionRecursiva(inicial,0);

        for(int i=0;i<nodos.size();i++)
            printNodo(i);
    }
};

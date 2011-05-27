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
string toString(int x)
{
    std::stringstream out;
    out << x;
    return out.str();
}

    bool existeString(vector<string>lista,string str)
    {
        for(int i=0;i<lista.size();i++)
            if(compararCadenas(lista[i],str))
                return true;
        return false;
    }
    vector<string> unionListaStrings(vector<string>v1,vector<string>v2)
    {
        for(int i=0;i<v1.size();i++)
            if(!existeString(v1,v2[i]))
                v1.push_back(v2[i]);
        return v1;
    }

class Nodo
{
public:
    string nombre;
    vector<Produccion>producciones;
    Nodo(string nombre)
    {
        this->nombre=nombre;
    }

    void agregarProduccion(Produccion produccion)
    {
        producciones.push_back(produccion);
    }
    Produccion getProduccion(int pos)
    {
        return producciones[pos];
    }
    void print()
    {
        for(int i=0;i<producciones.size();i++)
            getProduccion(i).print();
    }
};
class Misterio
{
public:
    vector<Produccion> lista_producciones;
    vector< vector<Produccion> > nodos;
    int num_nodo;
    Gramatica gramatica;
    Misterio(Gramatica gramatica)
    {
        this->lista_producciones=gramatica.lista_producciones;
        aumentarProduccion();
        num_nodo=0;
        gramatica=gramatica;
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
    void printNodo(int i)
    {
        vector<Produccion> lista=nodos[i];
        cout<<"I"<<i<<endl;
        for(int i=0;i<lista.size();i++)
            lista[i].print();
    }

    ////
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
    //
    vector<string> primero(string produccion)
    {
        vector <string> resultado;
        if(!existeProduccion(produccion))
        {
            resultado.push_back(produccion);
            return resultado;
        }
        for(int i=0;i<lista_producciones.size();i++)
        {
            if(compararCadenas(lista_producciones[i].nombre,produccion))
                if(lista_producciones[i].simbolos.size()!=0)
                    if(compararCadenas(lista_producciones[i].simbolos[0].tipo,"terminal"))
                    {
                        resultado.push_back(lista_producciones[i].simbolos[0].nombre);
                    }
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
    vector<string> getListaPrimeros(Produccion produccion,vector<string> lista_anterior)
    {
        vector<string> primeros;
        if(produccion.posicion+1>=produccion.simbolos.size())
        {
            return lista_anterior;
            //primeros.push_back("$");
        }
        else
        {
            vector<string> temp=primero(produccion.simbolos[produccion.posicion+1].nombre);
            for(int j=0;j<temp.size();j++)
            {
                primeros.push_back(temp[j]);
            }
        }
        return primeros;
    }

    vector<Produccion> getProduccionesRecursiva(Produccion produccion,vector<string> sp)
    {
        vector<Produccion> resultado;
        produccion.set_no_terminales=sp;
        //agrego inicial
        resultado.push_back(produccion);

        Simbolo s_actual=produccion.getSimboloActual();
        if(existeProduccion(s_actual.nombre))
        {
            for(int i=0;i<lista_producciones.size();i++)
            {
                if(compararCadenas(lista_producciones[i].nombre,s_actual.nombre))
                {
                    if(existeProduccion(lista_producciones[i].simbolos[0].nombre))
                    {
                        vector<Produccion>temp=getProduccionesRecursiva(lista_producciones[i],getListaPrimeros(lista_producciones[i],sp));
                        for(int j=0;j<temp.size();j++)
                            resultado.push_back(temp[j]);
                    }else
                    {
                        Produccion temp=lista_producciones[i];
                        temp.set_no_terminales=getListaPrimeros(produccion,sp);
                        resultado.push_back(temp);
                    }
                }
            }
        }

        return resultado;
    }
    bool existeProduccion(string nombre)
    {
        for(int i=0;i<lista_producciones.size();i++)
            if(compararCadenas(lista_producciones[i].nombre,nombre))
                return true;
        return false;
    }
    Nodo getNodo(Produccion produccion,string nombre)
    {
        Nodo nodo(nombre);
        //Creacion de produccion inicial
        Produccion p_incial=produccion;
        //Agregacion de produccion inicial
        if(p_incial.simbolos.size()>=p_incial.posicion)
            nodo.agregarProduccion(p_incial);
        //Validacion de fin de posicion
        if(p_incial.simbolos.size()<=p_incial.posicion)
            return nodo;

        //Get el simbolo actual
        Simbolo s_actual=p_incial.getSimboloActual();
        //Llamada recursiva si es no terminal
        if(s_actual.tipo=="no terminal")
        {
            for(int i=0;i<lista_producciones.size();i++)
                if(compararCadenas(lista_producciones[i].nombre,s_actual.nombre))
                {
                    vector<string>s_temp;s_temp.push_back("$");
                    vector<Produccion> temp=getProduccionesRecursiva(lista_producciones[i],getListaPrimeros(p_incial,s_temp));
                    for(int i=0;i<temp.size();i++)
                        nodo.agregarProduccion(temp[i]);
                }
        }
        return nodo;
    }
    bool noRepetida(Nodo nodo,vector<Nodo> nodos)
    {
        for(int i=0;i<nodos.size();i++)
            if(compararProducciones(nodo.producciones[0],nodos[i].producciones[0]))
                return false;
        return true;
    }
    vector<Nodo> procesarNodo(Nodo nodo)
    {
        vector<Nodo> nodos;
        for(int i=0;i<nodo.producciones.size();i++)//para cada produccion
        {
            Produccion temp=nodo.producciones[i];
            temp.posicion++;//avanzo la la posicion del punto
            num_nodo++;//avanzo el numero de i
            nodos.push_back(getNodo(temp,"i"+toString(num_nodo)));
        }
        return nodos;
    }
    void funcionMisterio()
    {
        vector<Nodo> nodos;

        //Crear I0
        Nodo i0=getNodo(lista_producciones[0],"i0");
        i0.producciones[0].set_no_terminales.push_back("$");
        nodos.push_back(i0);

        //Ciclo main de procesamiento de nodos
        for(int x=0;x<nodos.size();x++)
        {
            vector<Nodo> n_temp=procesarNodo(nodos[x]);//get nodo a procesar
            for(int i=0;i<n_temp.size();i++)//para cada produccion
                if(n_temp[i].producciones.size()>0)//si no esta vacia
                    if(noRepetida(n_temp[i],nodos))//si no esta repetida
                        nodos.push_back(n_temp[i]);//agregar nodo
        }

        //Imprimir todos los nodos
        for(int i=0;i<nodos.size();i++)
        {
            cout<<"i"+toString(i)<<endl;
            nodos[i].print();
        }
    }
};


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
    bool existe(vector<Nodo> nodos)
    {
        for(int i=0;i<nodos.size();i++)
            if(producciones[0].compararProduccion(nodos[i].producciones[0]))
                return true;
        return false;
    }
    int intExisteSinPrimeros(vector<Nodo> nodos)
    {
        for(int i=0;i<nodos.size();i++)
            if(producciones[0].compararProduccionSinTerminales(nodos[i].producciones[0]))
                return i;
        return -1;
    }
};
class Entrega2
{
public:
    vector<Produccion> lista_producciones;
    vector<Nodo> lista_nodos;
    int num_nodo;
    Gramatica gramatica;
    Entrega2(Gramatica gramatica)
    {
        this->lista_producciones=gramatica.lista_producciones;
        num_nodo=0;
        this->gramatica=gramatica;
        //aumentar la produccion
        lista_producciones.insert(lista_producciones.begin(),Produccion("prima_"+lista_producciones[0].nombre));
        lista_producciones[0].simbolos.push_back(Simbolo("no terminal",lista_producciones[1].nombre));
        //generar nodos
        generarNodos();
    }
    vector<string> getListaPrimeros(Produccion produccion,vector<string> lista_anterior)
    {
        vector<string> primeros;
        if(produccion.posicion+1>=produccion.simbolos.size())
        {
            if(lista_anterior.size()==0)//!!!!!!!!!!!!!!
              lista_anterior.push_back("$");
            return lista_anterior;
        }
        else
        {
            vector<string> temp=gramatica.primero(produccion.simbolos[produccion.posicion+1].nombre);
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
        if(gramatica.existeNoTerminal(s_actual.nombre))
        {
            for(int i=0;i<lista_producciones.size();i++)
            {
                if(compararCadenas(lista_producciones[i].nombre,s_actual.nombre))
                {
                    if(gramatica.existeNoTerminal(lista_producciones[i].simbolos[0].nombre))
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
                    vector<string>s_temp;
                    s_temp=produccion.set_no_terminales;
                    vector<Produccion> temp=getProduccionesRecursiva(lista_producciones[i],getListaPrimeros(p_incial,s_temp));
                    for(int i=0;i<temp.size();i++)
                        nodo.agregarProduccion(temp[i]);
                }
        }
        return nodo;
    }
    vector<Nodo> procesarNodo(Nodo nodo)
    {
        vector<Nodo> nodos;
        for(int i=0;i<nodo.producciones.size();i++)//para cada produccion
            nodo.producciones[i].procesado=false;
        for(int i=0;i<nodo.producciones.size();i++)//para cada produccion
        {
            Produccion temp=nodo.producciones[i];
            if(!temp.procesado)
            {
                nodo.producciones[i].procesado=true;
                temp.posicion++;//avanzo la la posicion del punto
                num_nodo++;//avanzo el numero de i
                Nodo n_temp=getNodo(temp,"i"+toString(num_nodo));
                for(int j=i+1;j<nodo.producciones.size();j++)//agregar repetidos!!!!!!!!!!!!
                {
                    if(temp.posicion<=temp.simbolos.size() && nodo.producciones[j].posicion<nodo.producciones[j].simbolos.size())
                    {
                        if(compararCadenas(nodo.producciones[j].getSimboloActual().nombre,temp.simbolos[temp.posicion-1].nombre))//si encuentro uno repetido
                        {
                            //creo un nodo temporar
                            Produccion p_temp2=nodo.producciones[j];
                            p_temp2.posicion++;
                            nodo.producciones[j].procesado=true;
                            Nodo n_temp2=getNodo(p_temp2,"?"+toString(num_nodo));
                            //!!!!!!!!!!!!!
                            for(int k=0;k<n_temp2.producciones.size();k++)//agrego las producciones/set_no_terminales del temporar al actual
                            {
                                bool flag=false;
                                for(int l=0;l<n_temp2.producciones.size();l++)
                                    if(n_temp.producciones[l].compararProduccionSinTerminales(n_temp2.producciones[k]))//caso set no terminales
                                    {
                                        for(int m=0;m<n_temp2.producciones[l].set_no_terminales.size();m++)
                                            n_temp.producciones[l].set_no_terminales.push_back(n_temp2.producciones[l].set_no_terminales[m]);
                                        flag=true;
                                        break;
                                    }
                                if(!flag)//caso agrego completo
                                    n_temp.producciones.push_back(n_temp2.producciones[k]);
                            }
                        }
                    }
                }//fin agregar repetidos
                nodos.push_back(n_temp);
            }
        }
        return nodos;
    }
    vector<Nodo> generarNodos()
    {
        //Crear I0
        Nodo i0=getNodo(lista_producciones[0],"i0");
        i0.producciones[0].set_no_terminales.push_back("$");
        lista_nodos.push_back(i0);

        //Ciclo main de procesamiento de nodos
        for(int x=0;x<lista_nodos.size();x++)
        {
            vector<Nodo> n_temp=procesarNodo(lista_nodos[x]);//get nodo a procesar
            for(int i=0;i<n_temp.size();i++)//para cada produccion
                if(n_temp[i].producciones.size()>0)//si no esta vacia
                    if(!n_temp[i].existe(lista_nodos))//si no esta repetida
                        lista_nodos.push_back(n_temp[i]);//agregar nodo
        }

        //Imprimir todos los nodos
        for(int i=0;i<lista_nodos.size();i++)
        {
            cout<<"i"+toString(i)<<endl;
            lista_nodos[i].print();
        }
        return lista_nodos;
    }
};

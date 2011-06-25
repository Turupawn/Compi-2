
bool contieneProduccionSinTerminales(vector<Produccion>lista,Produccion produccion)
{
    bool flag=false;
    for(int l=0;l<lista.size();l++)
        if(produccion.compararProduccionSinTerminales(lista[l]))
            flag=true;
    return flag;
}
int intContieneProduccionSinTerminales(vector<Produccion>lista,Produccion produccion)
{
    for(int l=0;l<lista.size();l++)
        if(produccion.compararProduccionSinTerminales(lista[l]))
            return l;
    return -1;
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
    string getString()
    {
        string res="";
        for(int i=0;i<producciones.size();i++)
            res+=getProduccion(i).getString();
        return res;
    }
    bool existe(vector<Nodo> nodos)
    {
        for(int i=0;i<nodos.size();i++)
            if(producciones.size()>0 && nodos[i].producciones.size()>0)
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
        lista_producciones.insert(lista_producciones.begin(),Produccion("prima_"+lista_producciones[0].nombre,lista_producciones[0].tipo));
        lista_producciones[0].simbolos.push_back(Simbolo("no terminal",lista_producciones[1].nombre));
        //generar nodos
        generarNodos();
    }
    Nodo getNodo(Produccion produccion,string nombre)
    {
        vector<string> look_ahead_padre=produccion.set_no_terminales;
        Nodo nodo(nombre);
        //Creacion de produccion inicial
        Produccion p_incial=produccion;
        //Agregacion de produccion inicial
        if(p_incial.simbolos.size()>=p_incial.posicion)
            nodo.agregarProduccion(p_incial);
        //Validacion de fin de posicion
        if(p_incial.simbolos.size()<=p_incial.posicion)
            return nodo;
        for(int i=0;i<nodo.producciones.size();i++)//for each produccion del nodo
        {
            Produccion p_actual=nodo.producciones[i];
            if(p_actual.simbolos.size()==0)
                continue;
            Simbolo s_actual=p_actual.getSimboloActual();
            if(s_actual.tipo=="no terminal")//para cada no terminal
            {
                for(int j=0;j<lista_producciones.size();j++)//agregar sus producciones
                {
                    if(compararCadenas(lista_producciones[j].nombre,s_actual.nombre))
                    {
                        Produccion produccion_a_agregar=lista_producciones[j];
                        int pos_prod=intContieneProduccionSinTerminales(nodo.producciones,produccion_a_agregar);
                        if(pos_prod==-1)
                        {
                            int x=look_ahead_padre.size();
                            for(int k=0;k<x;k++)//agregacion de cada uno si no existe
                            {
                                if(!contieneCadena(produccion_a_agregar.set_no_terminales,look_ahead_padre[k]))
                                    produccion_a_agregar.set_no_terminales.push_back(look_ahead_padre[k]);
                            }
                            //agregar los los primeros de beta tbn
                            if(p_actual.posicion+1<p_actual.simbolos.size())
                            {
                                string beta=p_actual.simbolos[p_actual.posicion+1].nombre;
                                //vector <string> primero_beta=gramatica.primero(beta);
                                vector <string> primero_beta=gramatica.getFirst(beta);
                                for(int k=0;k<primero_beta.size();k++)
                                {
                                    if(!contieneCadena(produccion_a_agregar.set_no_terminales,primero_beta[k]))
                                        produccion_a_agregar.set_no_terminales.push_back(primero_beta[k]);
                                }
                            }
                            //agregar los look ahead acarreados tbn
                            for(int k=0;k<p_actual.set_no_terminales.size();k++)
                            {
                                if(!contieneCadena(produccion_a_agregar.set_no_terminales,p_actual.set_no_terminales[k]))
                                    produccion_a_agregar.set_no_terminales.push_back(p_actual.set_no_terminales[k]);
                            }
                            nodo.agregarProduccion(produccion_a_agregar);
                        }else
                        {
                            //nodo.producciones[pos_prod];
                            //agregar los los primeros de beta tbn
                            if(p_actual.posicion+1<p_actual.simbolos.size())
                            {
                                string beta=p_actual.simbolos[p_actual.posicion+1].nombre;
                                //vector <string> primero_beta=gramatica.primero(beta);
                                vector <string> primero_beta=gramatica.getFirst(beta);
                                for(int k=0;k<primero_beta.size();k++)
                                {
                                    if(!contieneCadena(nodo.producciones[pos_prod].set_no_terminales,primero_beta[k]))
                                        nodo.producciones[pos_prod].set_no_terminales.push_back(primero_beta[k]);
                                }
                            }
                        }
                    }
                }
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
                                for(int l=0;l<n_temp.producciones.size();l++)
                                    if(n_temp.producciones[l].compararProduccionSinTerminales(n_temp2.producciones[k]))//caso set no terminales
                                    {
                                        for(int m=0;m<n_temp.producciones[l].set_no_terminales.size();m++)
                                            n_temp.producciones[l].set_no_terminales.push_back(n_temp2.producciones[k].set_no_terminales[m]);
                                        flag=true;
                                        break;
                                    }

                                if(!flag)//caso agrego completo
                                    n_temp.producciones.push_back(n_temp2.producciones[k]);
                            }
                        }
                    }
                }//fin agregar repetidos
                if(!n_temp.existe(lista_nodos) && n_temp.producciones.size()>0 && !n_temp.existe(nodos))
                    nodos.push_back(n_temp);
            }
        }
        return nodos;
    }
    vector<Nodo> agruparNodos(vector<Nodo>nodos)
    {
        vector<Nodo>resultado;
        for(int i=0;i<nodos.size();i++)//for each nodo n_actual
        {
            bool flag=false;
            Nodo n_actual=nodos[i];
            for(int j=0;j<resultado.size();j++)//lo busco versus los agregados en resultado
                if(n_actual.producciones.size()>0&&resultado[j].producciones.size()>0)
                if(n_actual.producciones[0].compararProduccionSinTerminales(resultado[j].producciones[0]) && j!=i)//si encuentro uno igual sin los look ahead
                {
                    flag=true;//marco flag q encontre para no pushearlo a resultado y...
                    for(int k=0;k<n_actual.producciones.size();k++)//hago union
                    {
                        Produccion p_actual=n_actual.producciones[k];
                        for(int l=0;l<p_actual.set_no_terminales.size();l++)
                        {
                            if(resultado[j].producciones.size()<=k)
                                break;
                            string la_actual=p_actual.set_no_terminales[l];
                            if(!contieneCadena(resultado[j].producciones[k].set_no_terminales,la_actual))
                                resultado[j].producciones[k].set_no_terminales.push_back(la_actual);
                        }
                    }
                }
            if(!flag)//no encontre ninguno igual
            {
                resultado.push_back(n_actual);// lo pusheo
            }
        }
        return resultado;//:D
    }
    vector<Nodo> generarNodos()
    {
        //Crear I0
        Produccion p_i0=lista_producciones[0];
        p_i0.set_no_terminales.push_back("$");
        Nodo i0=getNodo(p_i0,"i0");
        lista_nodos.push_back(i0);

        //Ciclo main de procesamiento de nodos
        for(int x=0;x<lista_nodos.size();x++)
        {
            vector<Nodo> n_temp=procesarNodo(lista_nodos[x]);//get nodo a procesar
            //n_temp[0].print();
            //while ( getchar() != '\n');
            //cout<<x<<endl;
            //cout.flush();

            for(int i=0;i<n_temp.size();i++)//para cada nodo
                if(n_temp[i].producciones.size()>0)//si no esta vacio
                    if(!n_temp[i].existe(lista_nodos))//si no esta repetido
                        lista_nodos.push_back(n_temp[i]);//agregar nodo
        }
        //agruparacion de nodos
        lista_nodos=agruparNodos(lista_nodos);
        //Imprimir todos los nodos
        for(int i=0;i<lista_nodos.size();i++)
        {
            cout<<"i"+toString(i)<<endl;
            lista_nodos[i].print();
        }
        return lista_nodos;
    }
};

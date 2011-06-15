
import com.sun.istack.internal.FinalArrayList;
import java.lang.reflect.Array;
import java.util.ArrayList;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author userr
 */
class ListaTokens
{
    ArrayList<String>tokens;
    int pos;
    public ListaTokens()
    {
        tokens=new ArrayList<String>();
        pos=0;
    }
    String nextToken()
    {
        pos++;
        return tokens.get(pos-1);
    }
}

class Pila
{
    ArrayList<ElementoPila> elementos;
    public Pila()
    {
        elementos=new ArrayList<ElementoPila>();
    }
    void push(ElementoPila e)
    {
        elementos.add(e);
    }
    ElementoPila pop()
    {
        ElementoPila temp=elementos.get(elementos.size()-1);
        elementos.remove(elementos.size()-1);
        return temp;
    }
}

class ElementoPila
{
    int simbolo;
    int nodo;
    String simbolo_produccion;
    String tipo;

    public ElementoPila(int simbolo, int nodo)
    {
        this.simbolo = simbolo;
        this.nodo = nodo;
        tipo="terminal";
    }
    public ElementoPila(String simbolo_produccion, int nodo)
    {
        this.simbolo_produccion = simbolo_produccion;
        this.nodo = nodo;
        tipo="no terminal";
    }
    public void print()
    {
        System.out.print(" "+nodo);
        if(tipo.equals("terminal"))
            System.out.print(simbolo);
        else
            System.out.print(simbolo_produccion);
    }
}
class FilaTerminal
{
    String terminal;
    String tipo;
    int nodo;
    public FilaTerminal(String terminal,String tipo,int nodo)
    {
        this.terminal=terminal;
        this.tipo=tipo;
        this.nodo=nodo;
    }
};
class FilaNoTerminal
{
    String no_terminal;
    int nodo;
    FilaNoTerminal(String no_terminal,int nodo)
    {
        this.no_terminal=no_terminal;
        this.nodo=nodo;
    }
};
class Fila
{
    ArrayList<FilaTerminal> terminales;
    ArrayList<FilaNoTerminal> no_terminales;
    public Fila()
    {
        terminales=new ArrayList<FilaTerminal>();
        no_terminales=new ArrayList<FilaNoTerminal>();
    }
};

class Simbolo
{
    int terminal;
    String no_terminal;
    String tipo;

    public Simbolo(int terminal)
    {
        this.terminal=terminal;
        tipo="terminal";
    }

    public Simbolo(String no_terminal)
    {
        this.no_terminal=no_terminal;
        tipo="no terminal";
    }
}

class Produccion
{
   String  nombre;
   ArrayList<Simbolo> simbolos;

    public Produccion(String nombre)
    {
        simbolos=new ArrayList<Simbolo>();
        this.nombre = nombre;
    }

};

public class MiParser {
    ArrayList<Produccion>gramatica;
    ArrayList<Fila> filas;
    public MiParser()
    {
        filas=new FinalArrayList<Fila>();
        gramatica=new ArrayList<Produccion>();

        //Inicializar gramatica
        //Inicializar tabla

Produccion produccion0=new Produccion("prima_S");
produccion0.simbolos.add(new Simbolo("S"));
gramatica.add(produccion0);
Produccion produccion1=new Produccion("S");
produccion1.simbolos.add(new Simbolo("C"));
produccion1.simbolos.add(new Simbolo("C"));
gramatica.add(produccion1);
Produccion produccion2=new Produccion("C");
produccion2.simbolos.add(new Simbolo("c"));
produccion2.simbolos.add(new Simbolo("C"));
gramatica.add(produccion2);
Produccion produccion3=new Produccion("C");
produccion3.simbolos.add(new Simbolo("d"));
gramatica.add(produccion3);


Fila fila0=new Fila();
fila0.terminales.add(new FilaTerminal("c", "d",3));
fila0.terminales.add(new FilaTerminal("d", "d",4));
fila0.no_terminales.add(new FilaNoTerminal("S",1));
fila0.no_terminales.add(new FilaNoTerminal("C",2));
filas.add(fila0);
Fila fila1=new Fila();
fila1.terminales.add(new FilaTerminal("$", "a",-1));
filas.add(fila1);
Fila fila2=new Fila();
fila2.terminales.add(new FilaTerminal("c", "d",3));
fila2.terminales.add(new FilaTerminal("d", "d",4));
fila2.no_terminales.add(new FilaNoTerminal("C",5));
filas.add(fila2);
Fila fila3=new Fila();
fila3.terminales.add(new FilaTerminal("c", "d",3));
fila3.terminales.add(new FilaTerminal("d", "d",4));
fila3.no_terminales.add(new FilaNoTerminal("C",6));
filas.add(fila3);
Fila fila4=new Fila();
fila4.terminales.add(new FilaTerminal("$", "r",3));
fila4.terminales.add(new FilaTerminal("c", "r",3));
fila4.terminales.add(new FilaTerminal("d", "r",3));
filas.add(fila4);
Fila fila5=new Fila();
fila5.terminales.add(new FilaTerminal("$", "r",1));
filas.add(fila5);
Fila fila6=new Fila();
fila6.terminales.add(new FilaTerminal("$", "r",2));
fila6.terminales.add(new FilaTerminal("c", "r",2));
fila6.terminales.add(new FilaTerminal("d", "r",2));
filas.add(fila6);

    }
    void print()
    {
        for(Fila f : filas)
        {
            for(FilaTerminal ft : f.terminales)
            {
                System.out.print(ft.terminal+ft.tipo+ft.nodo+", ");
            }
            System.out.print(" | ");
            for(FilaNoTerminal ft : f.no_terminales)
            {
                System.out.print(ft.no_terminal+ft.nodo+", ");
            }
            System.out.println();
        }
    }
    boolean verificarTokens (ListaTokens lista_tokens) throws Exception
    {
        int fila_actual=0;
        String token=lista_tokens.nextToken();
        Pila pila=new Pila();
        pila.push(new ElementoPila(-1,0));

        do
        {
            if(esDesplazar(fila_actual, token))
            {
                pila.push(new ElementoPila(token, getFilaTerminal(fila_actual, token).nodo));//push
                fila_actual=getFilaTerminal(fila_actual, token).nodo;//desplazar
                token=lista_tokens.nextToken();//consumir token
            }else if(esReducir(fila_actual, token))
            {
                //Popear la pila
                int numero_produccion=getFilaTerminal(fila_actual, token).nodo;
                ArrayList<Simbolo>simbolos=getSimbolos(numero_produccion);
                for(int i=simbolos.size()-1;i>=0;i--)
                {
                    ElementoPila e=pila.pop();
                    if(!compararPilaSimbolo(e,simbolos.get(i)))
                        return false;
                }
                //get variables necesarias
                String nombre_produccion=getNombreProduccion(numero_produccion);
                int pos=pila.elementos.get(pila.elementos.size()-1).nodo;
                int get_desplazamiento=getFilaNoTerminal(pos, nombre_produccion).nodo;
                //pushear
                pila.push(new ElementoPila(nombre_produccion, get_desplazamiento));
                //desplazo
                fila_actual=get_desplazamiento;

                int x=10;
            }else if(esAceptacion(fila_actual, token))
            {
                return true;
            }else
            {
                return false;
            }
        }while(true);

        //return fila_actual==1;
    }

    boolean compararPilaSimbolo(ElementoPila e,Simbolo s)
    {
        if(!e.tipo.equals(s.tipo))
            return false;
        if(e.tipo.equals("terminal"))
            return e.simbolo==s.terminal;
        return e.simbolo_produccion.equals(s.no_terminal);
    }

    boolean esDesplazar(int estado_actual,String token)
    {
        if(getFilaTerminal(estado_actual,token)==null)
            return false;
        return getFilaTerminal(estado_actual,token).tipo.equals("d");
    }

    boolean esReducir(int estado_actual,String token)
    {
        if(getFilaTerminal(estado_actual,token)==null)
            return false;
        return getFilaTerminal(estado_actual,token).tipo.equals("r");
    }


    boolean esAceptacion(int estado_actual,String token)
    {
        if(getFilaTerminal(estado_actual,token)==null)
            return false;
        return getFilaTerminal(estado_actual,token).tipo.equals("a");
    }

    FilaTerminal getFilaTerminal(int estado_actual,String token)
    {
        Fila f_actual=filas.get(estado_actual);
        for(FilaTerminal ft:f_actual.terminales)
        {
            if(ft.terminal.equals(token))
                return ft;
        }
        return null;
    }

    FilaNoTerminal getFilaNoTerminal(int estado_actual,String token)
    {
        Fila f_actual=filas.get(estado_actual);
        for(FilaNoTerminal fnt:f_actual.no_terminales)
        {
            if(fnt.no_terminal.equals(token))
                return fnt;
        }
        return null;
    }

    ArrayList<Simbolo> getSimbolos(int produccion)
    {
        return gramatica.get(produccion).simbolos;
    }

    String getNombreProduccion(int produccion)
    {
        return gramatica.get(produccion).nombre;
    }
}



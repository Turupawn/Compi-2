 
testttt qwert
 
parrrsededed afaf

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
    Object valor;

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
    public ElementoPila(String simbolo_produccion, int nodo,Object valor)
    {
        this.simbolo_produccion = simbolo_produccion;
        this.nodo = nodo;
        this.valor=valor;
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

Produccion produccion0=new Produccion("prima_EP");
produccion0.simbolos.add(new Simbolo("EP"));
gramatica.add(produccion0);
Produccion produccion1=new Produccion("EP");
produccion1.simbolos.add(new Simbolo("E"));
produccion1.simbolos.add(new Simbolo("PYC"));
gramatica.add(produccion1);
Produccion produccion2=new Produccion("E");
produccion2.simbolos.add(new Simbolo("E"));
produccion2.simbolos.add(new Simbolo("PLUS"));
produccion2.simbolos.add(new Simbolo("F"));
gramatica.add(produccion2);
Produccion produccion3=new Produccion("E");
produccion3.simbolos.add(new Simbolo("E"));
produccion3.simbolos.add(new Simbolo("MIN"));
produccion3.simbolos.add(new Simbolo("F"));
gramatica.add(produccion3);
Produccion produccion4=new Produccion("E");
produccion4.simbolos.add(new Simbolo("F"));
gramatica.add(produccion4);
Produccion produccion5=new Produccion("F");
produccion5.simbolos.add(new Simbolo("F"));
produccion5.simbolos.add(new Simbolo("TIMES"));
produccion5.simbolos.add(new Simbolo("T"));
gramatica.add(produccion5);
Produccion produccion6=new Produccion("F");
produccion6.simbolos.add(new Simbolo("F"));
produccion6.simbolos.add(new Simbolo("DIV"));
produccion6.simbolos.add(new Simbolo("T"));
gramatica.add(produccion6);
Produccion produccion7=new Produccion("F");
produccion7.simbolos.add(new Simbolo("T"));
gramatica.add(produccion7);
Produccion produccion8=new Produccion("T");
produccion8.simbolos.add(new Simbolo("LPAREN"));
produccion8.simbolos.add(new Simbolo("E"));
produccion8.simbolos.add(new Simbolo("RPAREN"));
gramatica.add(produccion8);
Produccion produccion9=new Produccion("T");
produccion9.simbolos.add(new Simbolo("num"));
gramatica.add(produccion9);


Fila fila0=new Fila();
fila0.terminales.add(new FilaTerminal("LPAREN", "d",5));
fila0.terminales.add(new FilaTerminal("num", "d",6));
fila0.no_terminales.add(new FilaNoTerminal("EP",1));
fila0.no_terminales.add(new FilaNoTerminal("E",2));
fila0.no_terminales.add(new FilaNoTerminal("F",3));
fila0.no_terminales.add(new FilaNoTerminal("T",4));
filas.add(fila0);
Fila fila1=new Fila();
fila1.terminales.add(new FilaTerminal("$", "a",-1));
filas.add(fila1);
Fila fila2=new Fila();
fila2.terminales.add(new FilaTerminal("PYC", "d",7));
fila2.terminales.add(new FilaTerminal("PLUS", "d",8));
fila2.terminales.add(new FilaTerminal("MIN", "d",9));
filas.add(fila2);
Fila fila3=new Fila();
fila3.terminales.add(new FilaTerminal("TIMES", "d",10));
fila3.terminales.add(new FilaTerminal("DIV", "d",11));
fila3.terminales.add(new FilaTerminal("$", "r",4));
fila3.terminales.add(new FilaTerminal("PYC", "r",4));
fila3.terminales.add(new FilaTerminal("PLUS", "r",4));
fila3.terminales.add(new FilaTerminal("MIN", "r",4));
fila3.terminales.add(new FilaTerminal("RPAREN", "r",4));
filas.add(fila3);
Fila fila4=new Fila();
fila4.terminales.add(new FilaTerminal("$", "r",7));
fila4.terminales.add(new FilaTerminal("PYC", "r",7));
fila4.terminales.add(new FilaTerminal("PLUS", "r",7));
fila4.terminales.add(new FilaTerminal("MIN", "r",7));
fila4.terminales.add(new FilaTerminal("TIMES", "r",7));
fila4.terminales.add(new FilaTerminal("DIV", "r",7));
fila4.terminales.add(new FilaTerminal("RPAREN", "r",7));
filas.add(fila4);
Fila fila5=new Fila();
fila5.terminales.add(new FilaTerminal("LPAREN", "d",5));
fila5.terminales.add(new FilaTerminal("num", "d",6));
fila5.no_terminales.add(new FilaNoTerminal("E",12));
fila5.no_terminales.add(new FilaNoTerminal("F",3));
fila5.no_terminales.add(new FilaNoTerminal("T",4));
filas.add(fila5);
Fila fila6=new Fila();
fila6.terminales.add(new FilaTerminal("$", "r",9));
fila6.terminales.add(new FilaTerminal("PYC", "r",9));
fila6.terminales.add(new FilaTerminal("PLUS", "r",9));
fila6.terminales.add(new FilaTerminal("MIN", "r",9));
fila6.terminales.add(new FilaTerminal("TIMES", "r",9));
fila6.terminales.add(new FilaTerminal("DIV", "r",9));
fila6.terminales.add(new FilaTerminal("RPAREN", "r",9));
filas.add(fila6);
Fila fila7=new Fila();
fila7.terminales.add(new FilaTerminal("$", "r",1));
filas.add(fila7);
Fila fila8=new Fila();
fila8.terminales.add(new FilaTerminal("LPAREN", "d",5));
fila8.terminales.add(new FilaTerminal("num", "d",6));
fila8.no_terminales.add(new FilaNoTerminal("F",13));
fila8.no_terminales.add(new FilaNoTerminal("T",4));
filas.add(fila8);
Fila fila9=new Fila();
fila9.terminales.add(new FilaTerminal("LPAREN", "d",5));
fila9.terminales.add(new FilaTerminal("num", "d",6));
fila9.no_terminales.add(new FilaNoTerminal("F",14));
fila9.no_terminales.add(new FilaNoTerminal("T",4));
filas.add(fila9);
Fila fila10=new Fila();
fila10.terminales.add(new FilaTerminal("LPAREN", "d",5));
fila10.terminales.add(new FilaTerminal("num", "d",6));
fila10.no_terminales.add(new FilaNoTerminal("T",15));
filas.add(fila10);
Fila fila11=new Fila();
fila11.terminales.add(new FilaTerminal("LPAREN", "d",5));
fila11.terminales.add(new FilaTerminal("num", "d",6));
fila11.no_terminales.add(new FilaNoTerminal("T",16));
filas.add(fila11);
Fila fila12=new Fila();
fila12.terminales.add(new FilaTerminal("RPAREN", "d",17));
fila12.terminales.add(new FilaTerminal("PLUS", "d",8));
fila12.terminales.add(new FilaTerminal("MIN", "d",9));
filas.add(fila12);
Fila fila13=new Fila();
fila13.terminales.add(new FilaTerminal("TIMES", "d",10));
fila13.terminales.add(new FilaTerminal("DIV", "d",11));
fila13.terminales.add(new FilaTerminal("$", "r",2));
fila13.terminales.add(new FilaTerminal("PYC", "r",2));
fila13.terminales.add(new FilaTerminal("PLUS", "r",2));
fila13.terminales.add(new FilaTerminal("MIN", "r",2));
fila13.terminales.add(new FilaTerminal("RPAREN", "r",2));
filas.add(fila13);
Fila fila14=new Fila();
fila14.terminales.add(new FilaTerminal("TIMES", "d",10));
fila14.terminales.add(new FilaTerminal("DIV", "d",11));
fila14.terminales.add(new FilaTerminal("$", "r",3));
fila14.terminales.add(new FilaTerminal("PYC", "r",3));
fila14.terminales.add(new FilaTerminal("PLUS", "r",3));
fila14.terminales.add(new FilaTerminal("MIN", "r",3));
fila14.terminales.add(new FilaTerminal("RPAREN", "r",3));
filas.add(fila14);
Fila fila15=new Fila();
fila15.terminales.add(new FilaTerminal("$", "r",5));
fila15.terminales.add(new FilaTerminal("PYC", "r",5));
fila15.terminales.add(new FilaTerminal("PLUS", "r",5));
fila15.terminales.add(new FilaTerminal("MIN", "r",5));
fila15.terminales.add(new FilaTerminal("TIMES", "r",5));
fila15.terminales.add(new FilaTerminal("DIV", "r",5));
fila15.terminales.add(new FilaTerminal("RPAREN", "r",5));
filas.add(fila15);
Fila fila16=new Fila();
fila16.terminales.add(new FilaTerminal("$", "r",6));
fila16.terminales.add(new FilaTerminal("PYC", "r",6));
fila16.terminales.add(new FilaTerminal("PLUS", "r",6));
fila16.terminales.add(new FilaTerminal("MIN", "r",6));
fila16.terminales.add(new FilaTerminal("TIMES", "r",6));
fila16.terminales.add(new FilaTerminal("DIV", "r",6));
fila16.terminales.add(new FilaTerminal("RPAREN", "r",6));
filas.add(fila16);
Fila fila17=new Fila();
fila17.terminales.add(new FilaTerminal("$", "r",8));
fila17.terminales.add(new FilaTerminal("PYC", "r",8));
fila17.terminales.add(new FilaTerminal("PLUS", "r",8));
fila17.terminales.add(new FilaTerminal("MIN", "r",8));
fila17.terminales.add(new FilaTerminal("TIMES", "r",8));
fila17.terminales.add(new FilaTerminal("DIV", "r",8));
fila17.terminales.add(new FilaTerminal("RPAREN", "r",8));
filas.add(fila17);
}
Object ejecutarProduccion(int numero,ArrayList<Object> valores_pops)
{
ArrayList<Object> dolar=new ArrayList<Object>();
for(int i=valores_pops.size()-1;i>=0;i--)
{
dolar.add(valores_pops.get(i));
}
if(numero==1)
{
Object RESULT=null;
{System.out.print((Integer)dolar.get(0));}
return (Integer)RESULT;
}
if(numero==2)
{
Object RESULT=null;
{ RESULT=(Integer)dolar.get(0)+(Integer)dolar.get(2); }
return (Integer)RESULT;
}
if(numero==3)
{
Object RESULT=null;
{ RESULT=(Integer)dolar.get(0)-(Integer)dolar.get(2); }
return (Integer)RESULT;
}
if(numero==4)
{
Object RESULT=null;
{ RESULT=(Integer)dolar.get(0); }
return (Integer)RESULT;
}
if(numero==5)
{
Object RESULT=null;
{ RESULT=(Integer)dolar.get(0)*(Integer)dolar.get(2); }
return (Integer)RESULT;
}
if(numero==6)
{
Object RESULT=null;
{ RESULT=(Integer)dolar.get(0)/(Integer)dolar.get(2); }
return (Integer)RESULT;
}
if(numero==7)
{
Object RESULT=null;
{ RESULT=(Integer)dolar.get(0); }
return (Integer)RESULT;
}
if(numero==8)
{
Object RESULT=null;
{ RESULT=(Integer)dolar.get(1); }
return (Integer)RESULT;
}
if(numero==9)
{
Object RESULT=null;
{ RESULT=new Integer((String)dolar.get(0)); }
return (Integer)RESULT;
}
return null;
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
                pila.push(new ElementoPila(token, getFilaTerminal(fila_actual, token).nodo,token));//push
                fila_actual=getFilaTerminal(fila_actual, token).nodo;//desplazar
                token=lista_tokens.nextToken();//consumir token
            }else if(esReducir(fila_actual, token))
            {
                //Popear la pila
                int numero_produccion=getFilaTerminal(fila_actual, token).nodo;
                ArrayList<Simbolo>simbolos=getSimbolos(numero_produccion);

                ArrayList<Object>valores_pops=new ArrayList<Object>();
                for(int i=simbolos.size()-1;i>=0;i--)
                {
                    ElementoPila e=pila.pop();
                    valores_pops.add(e.valor);
                    if(!compararPilaSimbolo(e,simbolos.get(i)))
                        return false;
                }
                
                //get variables necesarias
                String nombre_produccion=getNombreProduccion(numero_produccion);
                int pos=pila.elementos.get(pila.elementos.size()-1).nodo;
                int get_desplazamiento=getFilaNoTerminal(pos, nombre_produccion).nodo;
                //pushear
                pila.push(new ElementoPila(nombre_produccion, get_desplazamiento,ejecutarProduccion(numero_produccion,valores_pops)));
                //desplazo
                fila_actual=get_desplazamiento;
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




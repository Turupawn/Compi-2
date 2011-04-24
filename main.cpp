#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Token
{
public:
    string tipo;
    string lexema;
    Token(string tipo,string lexema)
    {
        this->tipo=tipo;
        this->lexema=lexema;
    }
};

class Lexico
{
public:
    string archivo;
    vector<Token> tokens;
    vector<string> palabras_reservadas;
    Lexico(string path)
    {
        archivo="";
        ifstream read;
        read.open("archivo.txt",ios::in | ios::binary);
        if(!read)
        cout<<"Can't read the file";
        while(read)
        {
            archivo+=read.get();
        }
        //cout<<archivo;
        read.close();
        palabras_reservadas.push_back("import");
        palabras_reservadas.push_back("class");
        palabras_reservadas.push_back("parser_code");
        palabras_reservadas.push_back("terminal");
        palabras_reservadas.push_back("nonterminal");
    }
    bool esLetra(char caracter)
    {
        if((caracter>=97 && caracter<=122)||(caracter>=65 && caracter<=90)||caracter=='_')
            return true;
        return false;
    }
    bool esNumero(char caracter)
    {
        if(caracter>=48 && caracter<=57)
            return true;
        return false;
    }
    bool esPalabraReservada(string cadena)
    {
        int size_palabras_reservadas=palabras_reservadas.size();
        for(int i=0;i<size_palabras_reservadas;i++)
            if(palabras_reservadas[i]==cadena)
                return true;
        return false;
    }
    bool generarTokens()
    {
        int estado=0;
        int size_archivo=archivo.length();
        string token="";
        for(int i=0;i<size_archivo-1;i++)
        {
            char actual=archivo[i];
            if(actual!=' ' && actual!='\n' && actual!='\t')
                token+=actual;
            switch (estado)
            {
                case 0:
                    if(actual==' ' || actual=='\n' || actual=='\t')
                    {
                        estado=0;
                    }else if(esLetra(actual))
                    {
                        estado=1;
                    }else if(actual=='{')
                    {
                        estado=2;
                    }else if(actual=='-')
                    {
                        estado=3;
                    }else if(actual=='|')
                    {
                        estado=0;
                        tokens.push_back(Token("puntuacion",token));
                        token="";
                    }else if(actual=='<')
                    {
                        estado=4;
                    }else if(actual=='%')
                    {
                        estado=5;
                    }else if(actual==';')
                    {
                        estado=0;
                        tokens.push_back(Token("puntuacion",token));
                        token="";
                    }else if(actual==',')
                    {
                        estado=0;
                        tokens.push_back(Token("puntuacion",token));
                        token="";
                    }
                    else
                    {
                        cout<<"Error lexico se esperaba: letra, '{', '-', '|', '<', '>' o '|'"<<endl;
                        return false;
                    }
                break;
                case 1:
                    if(esLetra(actual) || esNumero(actual))
                    {
                        estado=1;
                    }else
                    {
                        estado=0;
                        if(token[token.length()-1]==',' || token[token.length()-1]==';' || token[token.length()-1]=='|' || token[token.length()-1]=='{' || token[token.length()-1]=='-' || token[token.length()-1]=='<' || token[token.length()-1]=='%')
                            token[token.length()-1]='\0';
                        if(esPalabraReservada(token))
                            tokens.push_back(Token("palabra reservada",token));
                        else
                            tokens.push_back(Token("cadena",token));
                        if(token=="import")
                        {
                            string token_str_import="";
                            for(;archivo[i]!='%' && archivo[i+1]!='>';i++)
                            {
                                token_str_import+=archivo[i];
                            }
                            tokens.push_back(Token("string import",token_str_import));
                        }
                        if(token=="parser_code")
                        {
                            string token_str_parser="";
                            for(;archivo[i]!='%' && archivo[i+1]!='>';i++)
                            {
                                token_str_parser+=archivo[i];
                            }
                            tokens.push_back(Token("string parser",token_str_parser));
                        }
                        token="";
                        i--;
                    }
                break;
                case 2:
                    if(actual!='}' && i!=size_archivo-1)
                    {
                        estado=2;
                    }else if(actual!='}' && i==size_archivo-1)
                    {
                        cout<<"Error: se esperaba '}'"<<endl;
                        return false;
                    }else
                    {
                        estado=0;
                        tokens.push_back(Token("codigo",token));
                        token="";
                    }
                break;
                case 3:
                    if(actual=='>')
                    {
                        estado=0;
                        tokens.push_back(Token("puntuacion",token));
                        token="";
                    }else
                    {
                        cout<<"Error lexico: se esperaba '>'"<<endl;
                        return false;
                    }
                break;
                case 4:
                    if(actual=='%')
                    {
                        estado=0;
                        tokens.push_back(Token("puntuacion",token));
                        token="";
                    }else
                    {
                        cout<<"Error lexico: se esperaba '%'"<<endl;
                        return false;
                    }
                break;
                case 5:
                    if(actual=='>')
                    {
                        estado=0;
                        tokens.push_back(Token("puntuacion",token));
                        token="";
                    }else
                    {
                        estado=0;
                        tokens.push_back(Token("puntuacion","%"));
                        token="";
                        i--;
                    }
                break;
            }
        }
        tokens.push_back(Token("eof","eof"));
        return true;
    }
    void printTokens()
    {
        int size_tokens=tokens.size();
        for(int i=0;i<size_tokens;i++)
        {
            cout<<tokens[i].tipo<<"     \t"<<tokens[i].lexema<<endl;
        }
    }
};

class Simbolo
{
public:
    string tipo;//terinal o no terminal
    string valor;
};

class Produccion
{
public:
    string no_terminal;
    vector<Simbolo> simbolos;
};

class Gramatica
{
public:
    vector<Produccion> lista_producciones;
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
    Gramatica(Lexico lexico)
    {
        i=0;
        this->tokens=lexico.tokens;
        if(s())
            cout<<"Gramatica correcta";
        else
            cout<<"Gramatica incorrecta";
    }
    bool s()
    {
        import();
        clase();
        codigo();
        return gramatica();
    }
    bool import()
    {
        if(compararToken("puntuacion","<%"))
        {
            if(compararToken("palabra reservada","import"))
            {
                if(compararToken("string import"))
                {
                    if(compararToken("puntuacion","%>"))
                        return true;
                    else
                        i--;
                }else
                    i--;
            }else
                i--;
        }else
            i--;
        return false;
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
    bool codigo()
    {
        if(compararToken("puntuacion","<%"))
        {
            if(compararToken("palabra reservada","parser_code"))
            {
                if(compararToken("string parser"))
                {
                    if(compararToken("puntuacion","%>"))
                        return true;
                    else
                        i--;
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
                    if(!listaNoTerminal())
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
        if(!compararToken("puntuacion","->"))
        {
            cout<<"Error: se esperaba ->."<<endl;
            return false;
        }
        if(!caso())
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
            if(!caso())
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
            for(;;)
            {
                if(compararToken("puntuacion",","))
                {
                    if(!compararToken("cadena"))
                        return false;
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
    bool listaNoTerminal()
    {
        if(compararToken("cadena"))
        {
            for(;;)
            {
                if(compararToken("puntuacion",","))
                {
                    if(!compararToken("cadena"))
                        return false;
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
    bool caso()
    {
        for(;;)
        {
            if(compararToken("cadena"))
            {

            }else
            {
                i--;
                if(compararToken("codigo"))
                {
                    if(compararToken("cadena"))
                    {

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
};

int main()
{
    Lexico lexico("archivo.txt");
    lexico.generarTokens();
    lexico.printTokens();
    Gramatica gramatica(lexico);
    return 0;
}

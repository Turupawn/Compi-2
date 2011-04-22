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
    vector<Produccion> producciones;
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
        return import() && clase() && codigo() && gramatica();
    }
    bool import()
    {
        if(compararToken("puntuacion","<%"))
        if(compararToken("cadena","import"))
        if(compararToken("string import"))
        if(compararToken("puntuacion","%>"))
            return true;
        return false;
    }
    bool clase()
    {
        if(compararToken("puntuacion","%"))
        if(compararToken("cadena","class"))
        if(compararToken("cadena"))
            return true;
        return false;
    }
    bool codigo()
    {
        if(compararToken("puntuacion","<%"))
        if(compararToken("cadena","parser_code"))
        if(compararToken("string parser"))
        if(compararToken("puntuacion","%>"))
            return true;
        return false;
    }
    bool gramatica()
    {
        return true;
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

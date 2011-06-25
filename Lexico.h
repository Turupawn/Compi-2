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
    Lexico(char* path)
    {
        archivo="";

        //lectura parte1
        ifstream f(path, ifstream::in);
        std::stringstream buffer;
        buffer << f.rdbuf();
        std::string contents(buffer.str());

        archivo=contents;

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
            if(estado==2 && (actual==' ' || actual=='\n' || actual=='\t'))
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
                        string lexema="";
                        i++;
                        bool flag=false;
                        for(;archivo[i]!='%' && archivo[i+1]!='>';i++)
                        {
                            if(i==archivo.length()-1)
                            {
                                cout<<"Error lexico: se esperaba '%>'"<<endl;
                                return false;
                            }
                            if(archivo[i]==' ')
                                continue;
                            else
                            {
                                for(;archivo[i]!='%' && archivo[i+1]!='>';i++)
                                {
                                    if(i==archivo.length()-1)
                                    {
                                        cout<<"Error lexico: se esperaba '%>'"<<endl;
                                        return false;
                                    }
                                    lexema+=archivo[i];
                                    if(lexema=="import")
                                    {
                                        i++;
                                        lexema="";
                                        for(;archivo[i]!='%' && archivo[i+1]!='>';i++)
                                            lexema+=archivo[i];
                                        flag=true;
                                        tokens.insert(tokens.begin(),Token("string import",lexema));
                                        break;
                                    }
                                    if(lexema=="parser_code")
                                    {
                                        i++;
                                        lexema="";
                                        for(;archivo[i]!='%' && archivo[i+1]!='>';i++)
                                            lexema+=archivo[i];
                                        flag=true;
                                        tokens.insert(tokens.begin(),Token("string parser",lexema));
                                        break;
                                    }
                                }
                                break;
                            }

                        }
                        i+=2;
                        estado=0;
                        //tokens.push_back(Token("puntuacion",token));
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
                        //tokens.push_back(Token("puntuacion","%"));
                        //i++;
                        string lexema="";

                        for(;;i++)
                        {
                            if(archivo[i]==' ')
                                continue;
                            else
                            {
                                for(;archivo[i]!=' ' && archivo[i]!='\n' && archivo[i]!='\t';i++)
                                {
                                    lexema+=archivo[i];
                                    if(lexema=="class")
                                    {
                                        lexema="";
                                        i++;
                                        for(;;i++)
                                        {
                                            if(archivo[i]==' ')
                                                continue;
                                            else
                                                break;
                                        }
                                        for(;archivo[i]!=' ' && archivo[i]!='\n' && archivo[i]!='\t';i++)
                                        {
                                            lexema+=archivo[i];
                                        }

                                        tokens.insert(tokens.begin(),Token("string class",lexema));
                                        break;
                                    }
                                }
                                break;
                            }
                        }
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

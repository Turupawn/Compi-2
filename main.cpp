#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Proyecto
{
public:
    string archivo;
    Proyecto(string path)
    {
        archivo="";
        char buffer;
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
    void generarTokens()
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
                        estado=4;
                    }else if(actual=='|')
                    {
                        //???
                        estado=0;
                        cout<<"Nuevo toquen 6?:   \t"+token<<endl;
                        token="";
                    }else if(actual=='<')
                    {
                        estado=7;
                    }else if(actual=='%')
                    {
                        estado=9;
                    }else if(actual==';')
                    {
                        //???
                        estado=0;
                        cout<<"Nuevo toquen 11?:\t"+token<<endl;
                        token="";
                    }else if(actual==',')
                    {
                        //???
                        estado=0;
                        cout<<"Nuevo toquen 12?:\t"+token<<endl;
                        token="";
                    }
                    else
                    {
                        cout<<"Error lexico se esperaba: letra, '{', '-', '|', '<', '>' o '|'"<<endl;
                        return;
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
                        cout<<"Nuevo toquen 1:  \t"+token<<endl;
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
                        return;
                    }else
                    {
                        //???
                        estado=0;
                        cout<<"Nuevo toquen 3?:   \t"+token<<endl;
                        token="";
                    }
                break;
                case 3:
                    //LOL nada?
                break;
                case 4:
                    if(actual=='>')
                    {
                        //???
                        estado=0;
                        cout<<"Nuevo token 5?:    \t"+token<<endl;
                        token="";
                    }else
                    {
                        cout<<"Error lexico: se esperaba '>'"<<endl;
                        return;
                    }
                break;
                case 5:
                    //LOL nada?
                break;
                case 6:
                    //LOL nada?
                break;
                case 7:
                    if(actual=='%')
                    {
                        //???
                        estado=0;
                        cout<<"Nuevo token 8?:   \t"+token<<endl;
                        token="";
                    }else
                    {
                        cout<<"Error lexico: se esperaba '%'"<<endl;
                        return;
                    }
                break;
                case 8:
                    //LOL nada?
                break;
                case 9:
                    if(actual=='>')
                    {
                        //???
                        estado=0;
                        cout<<"Nuevo token 10?:\t"+token<<endl;
                        token="";
                    }else
                    {
                        estado=0;
                        token[token.length()-1]='\0';
                        cout<<"Nuevo token 9?:    \t"+token<<endl;
                        token="";
                        i--;
                    }
                break;
                case 10:
                break;
                case 11:
                break;
                case 12:
                break;
            }
        }
    }
};
int main()
{
    Proyecto proyecto("archivo.txt");
    proyecto.generarTokens();
    return 0;
}

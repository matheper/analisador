#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#define TAM 1000

#define CONSTINTEIRO 1
#define ID 2
#define MAIS 3
#define MENOS 4
#define MULTIPLICACAO 5
#define DIVISAO 6
#define RESTO 7
#define MENOR 8
#define MAIOR 9
#define IGUAL 10
#define MAIORIGUAL 11
#define MENORIGUAL 12
#define DIFERENTE 13
#define ATRIBUICAO 14
#define DIVINTEIRA 15
#define ABREPAR 16
#define FECHAPAR 17
#define ABRECOLCHETE 18
#define FECHACOLCHETE 19
#define DOISPONTOS 20
#define PONTOPONTO 21
#define VIRGULA 22
#define POTENCIA 23
#define PONTOEVIRGULA 24
#define CONSTREAL 25
#define ALGORITMO 26
#define VAR 27
#define INICIO 28
#define FIMALGORITMO 29
#define PARA 30
#define DE 31
#define ATE 32
#define FACA 33
#define FIMPARA 34
#define REPITA 35
#define ENQUANTO 36
#define FIMENQUANTO 37
#define SE 38
#define ENTAO 39
#define SENAO 40
#define FIMSE 41
#define ESCREVA 42
#define LEIA 43
#define ESCREVAL 44
#define INTEIRO 45
#define REAL 46
#define E 47
#define OU 48
#define LITERAL 49
#define VETOR 50
#define LOGICO 51
#define VERDADEIRO 52
#define FALSO 53
#define FUNCAO 54
#define FIMFUNCAO 55
#define PROCEDIMENTO 56
#define FIMPROCEDIMENTO 57
#define RETORNE 58
#define NAO 59
#define PASSO 60
#define STRING 61
#define COMENT 62

char token[TAM];
int pos, codToken, linha=0;

FILE *arquivoSaida, *arquivoEntrada, *algoritmoSaida;
char s[TAM], codigo[TAM];

char *codigoC = "";

char *STRINGTEMP ="";

void concatenaCodigo(char **entrada, char *format, ...);
int lerLinha();
void NomeToken(int cod, char* nome);
int reconhecedor(char s[]);
int palavraReservada(char s[]);
int analisadorLexico();
int nomeAlgoritmo(char **val);
int listaIdentificadores(char **val);
int variavelSimples(char **val);
int matriz();
int tipoVariavel(char **val);
int declaracaoVariaveisFunc();
int declaracaoVariaveis(char **val);
int listaParametros(char **val);
int parametros(char **val);
int listaIdentificadoresTipoVariavel(char **val, char **tipoVariavelVal);
int tipoRetorno(char **val);
int funcao(char **val);
int procedimento(char **val);
int var(char **val);
int E0(char **val);
int E0a(char **val);
int E1(char **val);
int E1a(char **val);
int E2(char **val);
int E3(char **val);
int E4(char **val);
int E4a(char **val);
int E5(char **val);
int E5a(char **val);
int E6(char **val);
int E7(char **val);
int termo(char **val);
int chamadaFuncao(char **val);
int passagemParametros(char **val);
int pParametros(char **val);
int variavel(char **val);
int vetorFuncao(char **val);
int tipoMatriz();
int inteiro(char **val);
int constante(char **val);
int comando(char **val);
int listaComandos(char **val);
int comandos();
int listaVariaveis(char **val);
int fimse(char **val);
int passo(char **val);
int analisadorSintatico();
int main();

int lerLinha(){
    int i;
    if(fgets(s, TAM, arquivoEntrada)>0){
        linha++;
        pos=0;
        i=0; 
        while (s[i]){
            s[i]=tolower(s[i]);
            i++;
        }
        return 1;
    }
    return 0;
}

void nomeToken(int cod, char* nome){
    char tabelaTokens[63][20] = {
        "","TK_Const_Int","TK_Ident","TK_Mais","TK_Menos",
        "TK_Mult","TK_Divide","TK_Resto","TK_Menor",
        "TK_Maior","TK_Igual","TK_MaiorIgual","TK_MenorIgual",
        "TK_Diferente","TK_Atrib","TK_DivInt","TK_Abre_par",
        "TK_Fecha_par","TK_AbreColchete","TK_FechaColchete",
        "TK_Dois_pontos","TK_pontoponto","TK_Virgula",
        "TK_Potenciacao","TK_Ponto_e_virgula","TK_Const_Real",
        "TK_Algoritmo","TK_Var","TK_Inicio","TK_Fim_Alg",
        "TK_Para","TK_De","TK_Ate","TK_Faca","TK_Fimpara",
        "TK_Repita","TK_Enquanto","TK_FimEnquanto","TK_Se",
        "TK_Entao","TK_Senao","TK_Fimse","TK_Escreva","TK_Leia",
        "TK_EscrevaL","TK_Inteiro","TK_Real","TK_E",
        "TK_OU","TK_Literal","TK_Vetor","TK_Logico",
        "TK_Verdadeiro","TK_Falso","TK_Funcao","TK_Fimfuncao",
        "TK_Procedimento","TK_Fimprocedimento","TK_Retorne",
        "TK_NAO","TK_Passo","TK_String","TK_Coment"
    };
    strcpy(nome, tabelaTokens[cod]);
}

int reconhecedor(char s[]){
    int estado=0, posT = 0, posAnterior;
    char tokenAnterior[TAM];
    while (1)
        switch(estado){  
            //inicial
            case 0: if(s[pos]==' ' || s[pos]=='\n' || s[pos]=='\t'); //espaco em branco
                        else if (s[pos]>='0' && s[pos]<='9')//inteiro
                            estado = CONSTINTEIRO;
                        else if(s[pos]>='a' && s[pos]<='z')//identificador
                            estado = ID;
                        else if(s[pos]=='"'){//string
                            estado = STRING;
                            token[posT++] = s[pos];
                            pos++;
                        }
                        else if(s[pos]=='.')
                            estado = PONTOPONTO;
                        else if(s[pos]=='+')
                            estado = MAIS;
                        else if(s[pos]=='-')
                            estado = MENOS;
                        else if(s[pos]=='*')
                            estado = MULTIPLICACAO;
                        else if(s[pos]=='/')
                            estado = DIVISAO;
                        else if(s[pos]==92)
                            estado = DIVINTEIRA;
                        else if(s[pos]=='%')
                            estado = RESTO;
                        else if(s[pos]=='<')
                            estado = MENOR;
                        else if(s[pos]=='>')
                            estado = MAIOR;
                        else if(s[pos]=='=')
                            estado = IGUAL;
                        else if(s[pos]=='(')
                            estado = ABREPAR;
                        else if(s[pos]==')')
                            estado = FECHAPAR;
                        else if(s[pos]=='[')
                            estado = ABRECOLCHETE;
                        else if(s[pos]==']')
                            estado = FECHACOLCHETE;
                        else if(s[pos]==':')
                            estado = DOISPONTOS;
                        else if(s[pos]==',')
                            estado = VIRGULA;
                        else if(s[pos]=='^')
                            estado = POTENCIA;
                        else if(s[pos]==';')
                            estado = PONTOEVIRGULA;
                        else return 0;
                        if(s[pos] != ' ' && s[pos]!= '\t') token[posT++] = s[pos];

                        pos++;
                        break;
            case CONSTINTEIRO: if (s[pos]>='0'&& s[pos]<='9'){
                                   token[posT++] = s[pos];
                                   pos++;
                               }
                        else if (s[pos]=='.'){
                            posAnterior = pos;
                            strcpy(tokenAnterior,token);
                            token[posT++]=s[pos];
                            pos++;
                            estado = CONSTREAL;
                        }
                        else{
                            token[posT]=0;
                            codToken = CONSTINTEIRO;
                            return codToken;
                        }
                        break;


            case CONSTREAL: if (s[pos]>='0'&& s[pos]<='9'){
                                token[posT++] = s[pos];
                                pos++;
                            }
                            else if (s[pos]=='.'){
                                pos = posAnterior;
                                strcpy(token,tokenAnterior);
                                token[--posT]=0;
                                codToken = CONSTINTEIRO;
                                return codToken;
                            }
                            else{
                                token[posT]=0;
                                codToken = CONSTREAL;
                                return codToken;
                            }
                            break;
            case ID: if (s[pos]>='a' && s[pos]<='z' || s[pos]=='_'
                             || s[pos]>='0' && s[pos]<='9'){
                         token[posT++] = s[pos];
                         pos++;
                     }
                     else{
                         token[posT]=0;
                         codToken = ID;
                         return codToken;
                     }
                     break;
            case STRING: if (s[pos]!='"'){
                             token[posT++] = s[pos];
                             pos++;
                         }
                         else{
                             token[posT++] = s[pos];
                             pos++;     
                             token[posT]=0;
                             codToken = STRING;
                             return codToken;
                         }
                         break;
            case COMENT: while (s[pos]!=0 && s[pos]!='\n'){
                             token[posT++] = s[pos];
                             pos++;
                         }
                         token[posT]=0;
                         codToken = COMENT;
                         return codToken;
            case DIVISAO: if (s[pos]!='/'){
                              token[posT]=0;
                              codToken = DIVISAO;
                              return codToken; 
                          }else{
                              token[posT++] = s[pos];
                              pos++;
                              estado = COMENT;
                          }
                          break;
            case MAIS:
                          token[posT]=0;
                          codToken = MAIS;
                          return codToken;
            case MENOS:
                          token[posT]=0;
                          codToken = MENOS;
                          return codToken;
            case MULTIPLICACAO:
                          token[posT]=0;
                          codToken = MULTIPLICACAO;
                          return codToken;
            case DIVINTEIRA:
                          token[posT]=0;
                          codToken = DIVINTEIRA;
                          return codToken;
            case RESTO:
                          token[posT]=0;
                          codToken = RESTO;
                          return codToken;
            case MENOR:
                          if (s[pos]=='='){
                              token[posT++] = s[pos];
                              token[posT]=0;
                              pos++;
                              codToken = MENORIGUAL;
                          }
                          else if (s[pos]=='>'){
                              token[posT++] = s[pos];
                              token[posT]=0;
                              pos++;
                              codToken = DIFERENTE;
                          }
                          else if (s[pos]=='-'){
                              token[posT++] = s[pos];
                              token[posT]=0;
                              pos++;
                              codToken = ATRIBUICAO;
                          }
                          else{
                              token[posT]=0;
                              codToken = MENOR;
                          }
                          return codToken;
                          break;
            case MAIOR:
                          if (s[pos]=='='){
                              token[posT++] = s[pos];
                              token[posT]=0;
                              pos++;
                              codToken = MAIORIGUAL;
                          }
                          else{
                              token[posT]=0;
                              codToken = MAIOR;
                          }
                          return codToken;
                          break;
            case IGUAL:
                          token[posT]=0;
                          codToken = IGUAL;
                          return codToken;
                          break;
            case ABREPAR:
                          token[posT]=0;
                          codToken = ABREPAR;
                          return codToken;
                          break;
            case FECHAPAR:
                          token[posT]=0;
                          codToken = FECHAPAR;
                          return codToken;
                          break;
            case ABRECOLCHETE:
                          token[posT]=0;
                          codToken = ABRECOLCHETE;
                          return codToken;
                          break;
            case FECHACOLCHETE:
                          token[posT]=0;
                          codToken = FECHACOLCHETE;
                          return codToken;
                          break;
            case DOISPONTOS:
                          token[posT]=0;
                          codToken = DOISPONTOS;
                          return codToken;
                          break;
            case PONTOPONTO:
                          if (s[pos]=='.'){
                              token[posT++] = s[pos];
                              token[posT]=0;
                              pos++;
                              codToken = PONTOPONTO;
                              return codToken;
                          }
                          break;
            case POTENCIA:
                          token[posT]=0;
                          codToken = POTENCIA;
                          return codToken;
                          break;
            case PONTOEVIRGULA:
                          token[posT]=0;
                          codToken = PONTOEVIRGULA;
                          return codToken;
                          break;
            case VIRGULA:
                          token[posT]=0;
                          codToken = VIRGULA;
                          return codToken;
                          break;

        }
}

int palavraReservada(char s[])
{
    int i, palavras = 35;
    char dicionario[35][20] = {
        "algoritmo", "var", "inicio","fimalgoritmo",
        "para","de","ate","faca","fimpara","repita",
        "enquanto","fimenquanto","se","entao","senao",
        "fimse","escreva","leia","escreval",
        "inteiro","real","e","ou","literal",
        "vetor","logico","verdadeiro","falso",
        "funcao","fimfuncao","procedimento",
        "fimprocedimento","retorne","nao","passo"
    };

    for(i=0; i<palavras;i++)
    {
        if(!strcmp(dicionario[i],s))
        {
            codToken = 26+i;
            return codToken;
        }
    }
}

int analisadorLexico()
{
    int tipo;
    char nome[20];

    while(s[pos]=='\0' || s[pos]=='\n')
        if (!lerLinha())
            return 0;
    tipo = reconhecedor(s);
    if(tipo){
        if(tipo == ID){
            palavraReservada(token);
        }
        nomeToken(codToken,nome);
        fprintf(arquivoSaida, "Cod: %02d\tLinha: %d\tTipo: %20s\tLexema: %s\n",
                codToken, linha, nome, token);
        if(tipo == COMENT)
            analisadorLexico();
    }
    if(!tipo && s[pos]!='\0'){
        printf("Erro linha %d\tCaracter Invalido: %c", linha, s[pos]);
        exit(0);
    }
    return codToken;
}

/*
   Matheus Pereira
   25/10/11
   Linguagens Formais
 */

int nomeAlgoritmo(char **val){
    if(codToken == STRING){
        concatenaCodigo(val,"//%s\n", token);
        analisadorLexico();
    }
    return 1;
}

int listaIdentificadores(char **val){
    char *id = "", *listaIdentificadoresS = "";
    if (codToken == VIRGULA){
        analisadorLexico();
        if(codToken == ID){
            concatenaCodigo(&id, token);
            analisadorLexico();
            listaIdentificadores(&listaIdentificadoresS);
            concatenaCodigo(val, ", %s%s",id, listaIdentificadoresS);
        }
        else{
            printf("Esperava identificador apos virgula na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }
    return 1;
}

int variavelSimples(char **val){
    if(codToken == INTEIRO || codToken == REAL || codToken == LOGICO || codToken == LITERAL){
        if (codToken == INTEIRO) concatenaCodigo(val, "int ");
        else if (codToken == REAL) concatenaCodigo(val, "float ");
        else if (codToken == LOGICO) concatenaCodigo(val, "bool ");
        else if (codToken == LITERAL) concatenaCodigo(val, "char * ");
        analisadorLexico();
        return 1;
    }
    return 0;
}

int matriz(){
    if(codToken == VIRGULA){
        analisadorLexico();
        if(codToken == CONSTINTEIRO){
            analisadorLexico();
            if(codToken == PONTOPONTO){
                analisadorLexico();
                if(codToken == CONSTINTEIRO){
                    analisadorLexico();
                }
                else{
                    printf("Esperava valor inteiro na linha %d\nencontrou %s\n", linha, token);
                    exit(0);
                }
            }
            else{
                printf("Esperava ponto ponto na linha %d\nencontrou %s\n", linha, token);
                exit(0);
            }
        }
        else{
            printf("Esperava valor inteiro na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }
    return 1;
}

int tipoVariavel(char **val){
    char *variavelSimplesVal = "";
    if(variavelSimples(&variavelSimplesVal)){
        concatenaCodigo(val, "%s", variavelSimplesVal);
        return 1;
    }
    if(codToken == VETOR){
        analisadorLexico();
        if(codToken == ABRECOLCHETE){
            analisadorLexico();
            if(codToken == CONSTINTEIRO){
                analisadorLexico();
                if(codToken == PONTOPONTO){
                    analisadorLexico();
                    if(codToken == CONSTINTEIRO){
                        analisadorLexico();
                        matriz();
                        if(codToken == FECHACOLCHETE){
                            analisadorLexico();
                            if(codToken == DE){
                                analisadorLexico();
                                if(variavelSimples(&STRINGTEMP)){
                                    return 1;
                                }
                                else{
                                    printf("Esperava tipo na linha %d\nencontrou %s\n", linha, token);
                                    exit(0);
                                }
                            }
                            else{
                                printf("Esperava 'de' na linha %d\nencontrou %s\n", linha, token);
                                exit(0);
                            }
                        }
                        else{
                            printf("Esperava fecha colchete %d\nencontrou %s\n", linha, token);
                            exit(0);
                        }
                    }
                    else{
                        printf("Esperava valor inteiro na linha %d\nencontrou %s\n", linha, token);
                        exit(0);
                    }
                }
                else{
                    printf("Esperava ponto pontos na linha %d\nencontrou %s\n", linha, token);
                    exit(0);
                }
            }
            else{
                printf("Esperava valor inteiro na linha %d\nencontrou %s\n", linha, token);
                exit(0);
            }
        }
        else{
            printf("Esperava abre colchete na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }
    return 0;
}

declaracaoVariaveisFunc(){
    if(codToken == ID){
        analisadorLexico();
        listaIdentificadores(&STRINGTEMP);
        if(codToken == DOISPONTOS){
            analisadorLexico();
            if (!tipoVariavel(&STRINGTEMP)){
                printf("Esperava tipo na linha %d\nencontrou %s\n", linha, token);
                exit(0);
            }
            declaracaoVariaveisFunc();
        }
        else{
            printf("Esperava dois pontos ou virgula na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }
}

int declaracaoVariaveis(char **val){
    char *declaracaoVariaveisS="", *listaIdentificadoresVal="",
         *procedimentoVal="", *funcaoVal="", *tipoVariavelVal="", *id="";
    if(codToken == ID){
        concatenaCodigo(&id, "%s", token);
        analisadorLexico();
        listaIdentificadores(&listaIdentificadoresVal);
        if(codToken == DOISPONTOS){
            analisadorLexico();
            if (!tipoVariavel(&tipoVariavelVal)){
                printf("Esperava tipo na linha %d\nencontrou %s\n", linha, token);
                exit(0);
            }
            declaracaoVariaveis(&declaracaoVariaveisS);
            concatenaCodigo(val, "%s%s%s%s%s", tipoVariavelVal, id, listaIdentificadoresVal, ";\n", declaracaoVariaveisS);
        }
        else{
            printf("Esperava dois pontos ou virgula na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }
    if(codToken == FUNCAO){
        analisadorLexico();
        funcao(&funcaoVal);
        declaracaoVariaveis(&declaracaoVariaveisS);
        concatenaCodigo(val, "%s%s", funcaoVal, declaracaoVariaveisS);
    }
    if(codToken == PROCEDIMENTO){
        analisadorLexico();
        procedimento(&procedimentoVal);
        declaracaoVariaveis(&declaracaoVariaveisS);
        concatenaCodigo(val, "%s%s%s", procedimentoVal, "\n", declaracaoVariaveisS);
    }
    return 1;
}

int listaIdentificadoresTipoVariavel(char **val, char **tipoVariavelVal){
    char *id = "", *listaIdentificadoresS = "";
    if (codToken == VIRGULA){
        analisadorLexico();
        if(codToken == ID){
            concatenaCodigo(&id, token);
            analisadorLexico();
            listaIdentificadoresTipoVariavel(&listaIdentificadoresS, tipoVariavelVal);
        }
        else{
            printf("Esperava identificador apos virgula na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }
    else if(codToken == DOISPONTOS){
        analisadorLexico();
        tipoVariavel(tipoVariavelVal);
        return 1;
    }
    else{
        printf("Esperava dois pontos ou virgula apos identificador na linha %d\nencontrou %s\n", linha, token);
        exit(0);
    }
    concatenaCodigo(val, ", %s%s%s", *tipoVariavelVal, id, listaIdentificadoresS);
    return 1;
}

int listaParametros(char **val){
    char *parametrosVal="";
    if(codToken == PONTOEVIRGULA){
        analisadorLexico();
        parametros(&parametrosVal);
        concatenaCodigo(val,"%s, %s", *val, parametrosVal);
    }
    return 1;
}

int parametros(char **val){
    char *id="", *tipoVariavelVal="", *listaIdentificadoresTipoVariavelVal = "", *listaParametrosVal="";
    if(codToken == ID){
        concatenaCodigo(&id,"%s", token);
        analisadorLexico();
        listaIdentificadoresTipoVariavel(&listaIdentificadoresTipoVariavelVal, &tipoVariavelVal);
        listaParametros(&listaParametrosVal);
        concatenaCodigo(val,"%s%s%s%s", tipoVariavelVal, id, listaIdentificadoresTipoVariavelVal, listaParametrosVal);
    }
    else if(codToken == VAR){
        analisadorLexico();
        if(codToken == ID){
            analisadorLexico();
            listaIdentificadores(&STRINGTEMP);
            if(codToken == DOISPONTOS){
                analisadorLexico();
                if(!variavelSimples(&STRINGTEMP)){
                    printf("Esperava tipo na linha %d\nencontrou %s\n", linha, token);
                    exit(0);
                }
            }
            else{
                printf("Esperava dois pontos na linha %d\nencontrou %s\n", linha, token);
                exit(0);
            }
        }
        else{
            printf("Esperava identificador na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }

    return 1;
}

int tipoRetorno(char **val){
    if(codToken == INTEIRO || codToken == REAL || codToken == LOGICO){
        if (codToken == INTEIRO) concatenaCodigo(val, "int ");
        else if (codToken == REAL) concatenaCodigo(val, "float ");
        else if (codToken == LOGICO) concatenaCodigo(val, "bool ");
        analisadorLexico();
    }
    else{
        printf("Esperava tipo na linha %d\nencontrou %s\n", linha, token);
        exit(0);
    }
    return 1;
}

int funcao(char **val){
    char *id="", *parametrosVal="", *tipoRetornoVal="",
         *varVal="", *listaComandosVal="";
    if(codToken == ID){
        concatenaCodigo(&id, "%s", token);
        analisadorLexico();
        if(codToken == ABREPAR){
            analisadorLexico();
            parametros(&parametrosVal);
            if(codToken == FECHAPAR){
                analisadorLexico();
                if(codToken == DOISPONTOS){
                    analisadorLexico();
                    tipoRetorno(&tipoRetornoVal);
                    var(&varVal);
                    if(codToken == INICIO){
                        analisadorLexico();
                        listaComandos(&listaComandosVal);
                        if(codToken == FIMFUNCAO){
                            analisadorLexico();
                            concatenaCodigo(val, "%s%s%s%s%s%s%s%s", tipoRetornoVal, id, "(", parametrosVal, "){\n", varVal, listaComandosVal, "}\n");
                            return 1;
                        }
                        else{
                            printf("Esperava 'fimfuncao' na linha %d\nencontrou %s\n", linha, token);
                            exit(0);
                        }
                    }
                    else{
                        printf("Esperava 'inicio' na linha %d\nencontrou %s\n", linha, token);
                        exit(0);
                    }
                }
                else{
                    printf("Esperava dois pontos na linha %d\nencontrou %s\n", linha, token);
                    exit(0);
                }
            }
            else{
                printf("Esperava fecha parenteses na linha %d\nencontrou %s\n", linha, token);
                exit(0);
            }
        }
        else{
            printf("Esperava abre parenteses na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }
    else{
        printf("Esperava nome da funcao na linha %d\nencontrou %s\n", linha, token);
        exit(0);
    }
    return 1;
}

int procedimento(char **val){
    char *id="", *parametrosVal="parametrosVal", *varVal="", *listaComandosVal="";
    if(codToken == ID){
        concatenaCodigo(&id,"%s", token);
        analisadorLexico();
        if(codToken == ABREPAR){
            analisadorLexico();
            parametros(&parametrosVal);
            if(codToken == FECHAPAR){
                analisadorLexico();
                var(&varVal);
                if(codToken == INICIO){
                    analisadorLexico();
                    listaComandos(&listaComandosVal);
                    if(codToken == FIMPROCEDIMENTO){
                        analisadorLexico();
                        concatenaCodigo(val,"%s%s%s%s%s%s%s%s", "void ", id, "(", parametrosVal, "){\n", varVal, listaComandosVal, "\n}\n");
                        return 1;
                    }
                    else{
                        printf("Esperava 'fimprocedimento' na linha %d\nencontrou %s\n", linha, token);
                        exit(0);
                    }
                }
                else{
                    printf("Esperava 'inicio' na linha %d\nencontrou %s\n", linha, token);
                    exit(0);
                }
            }
            else{
                printf("Esperava fecha parenteses na linha %d\nencontrou %s\n", linha, token);
                exit(0);
            }
        }
        else{
            printf("Esperava abre parenteses na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }
    else{
        printf("Esperava nome do procedimento na linha %d\nencontrou %s\n", linha, token);
        exit(0);
    }
}

int var(char **val){
    char *declaracaoVariaveisVal="";
    if(codToken == VAR){
        analisadorLexico();
        declaracaoVariaveis(&declaracaoVariaveisVal);
        concatenaCodigo(val, "%s", declaracaoVariaveisVal);
    }
    return 1;
}

int E0(char **val){
    int retorno;
    char *E1Val = "", *E0aVal = "";
    retorno = E1(&E1Val);
    E0a(&E0aVal);
    concatenaCodigo(val,"%s%s", E1Val, E0aVal);
    return retorno;
}

int E0a(char **val){
    char *E1Val ="", *E0aVal = "";
    if(codToken == OU){
        analisadorLexico();
        E1(&E1Val);
        E0a(&E0aVal);
        concatenaCodigo(val,"%s||%s", E1Val, E0aVal);
    }
}

int E1(char **val){
    char *E2Val = "", *E1aVal = "";
    int retorno;
    retorno = E2(&E2Val);
    E1a(&E1aVal);
    concatenaCodigo(val,"%s%s", E2Val, E1aVal);
    return retorno;
}

int E1a(char **val){
    char *E2Val ="", *E1aVal = "";
    if(codToken == E){
        analisadorLexico();
        E2(&E2Val);
        E1a(&E1aVal);
        concatenaCodigo(val,"%s&&%s", E2Val, E1aVal);
    }
}

int E2(char **val){
    char *E2Val ="", *E3Val = "";
    if(codToken == NAO){
        analisadorLexico();
        E2(&E2Val);
        concatenaCodigo(val,"!%s", E2Val);
    }
    else {
        int retorno = E3(&E3Val);
        concatenaCodigo(val,E3Val);
        return retorno;
    }
}

int E3(char **val){
    char *E4Val="", *E42Val="", *opVal="";
    int retorno;
    retorno = E4(&E4Val);
    if(codToken == MAIOR || codToken == MAIORIGUAL ||
            codToken == MENOR || codToken == MENORIGUAL ){
        concatenaCodigo(&opVal, " %s ", token);
        analisadorLexico();
        E4(&E42Val);
    }
    concatenaCodigo(val, "%s%s%s", E4Val, opVal, E42Val);
    return retorno;
}

int E4(char **val){
    char *E4aVal="", *E5Val="";
    int retorno;
    retorno = E5(&E5Val);
    E4a(&E4aVal);
    concatenaCodigo(val,"%s%s", E5Val, E4aVal);
    return retorno;
}

int E4a(char **val){
    char *E5Val = "", *E4aVal = "", *opVal="";
    if(codToken == MAIS || codToken == MENOS){
        concatenaCodigo(&opVal," %s ", token);
        analisadorLexico();
        E5(&E5Val);
        E4a(&E4aVal);
    }
    concatenaCodigo(val, "%s%s%s", opVal, E5Val, E4aVal);
}

int E5(char **val){
    char *E6Val ="", *E5aVal;
    int retorno;
    retorno = E6(&E6Val);
    E5a(&E5aVal);
    concatenaCodigo(val, "%s%s", E6Val, E5aVal);
    return retorno;
}

int E5a(char **val){
    char *E6Val ="", *E5aVal="", *opVal="";
    if(codToken == DIVISAO || codToken == MULTIPLICACAO ||
            codToken == RESTO || codToken == DIVINTEIRA ){
        concatenaCodigo(&opVal," %s ", token);
        analisadorLexico();
        E6(&E6Val);
        E5a(&E5aVal);
    }
    concatenaCodigo(val, "%s%s%s", opVal, E6Val, E5aVal);
}

int E6(char **val){
    char *E7Val="", *E6Val="";
    int retorno;
    retorno = E7(&E7Val);
    if(codToken == POTENCIA){
        analisadorLexico();
        E6(&E6Val);
        concatenaCodigo(val, "pow(%s, %s)", E7Val,E6Val);
    }
    else{
        concatenaCodigo(val, "%s%s", E7Val,E6Val);
    }
    return retorno;
}
int E7(char **val){
    char *E7Val ="", *termoVal="";
    int retorno;
    if(codToken == MENOS){
        analisadorLexico();
        E7(&E7Val);
        concatenaCodigo(val, "-%s", E7Val);
    }
    else{
        retorno = termo(&termoVal);
        concatenaCodigo(val, termoVal);
        return retorno;
    }
}

int termo(char **val){
    char *E0Val ="", *variavelVal="", *constanteVal="";
    if(codToken == ABREPAR){
        analisadorLexico();
        if (E0(&E0Val)){
            if(codToken == FECHAPAR){
                analisadorLexico();
                concatenaCodigo(val,"(%s)", E0Val);
                return 1;
            }
            else{
                printf("Esperava fecha parenteses na linha %d\nencontrou %s\n", linha, token);
                exit(0);
            }
        }
        else{
            printf("Esperava expressao na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }
    else if(variavel(&variavelVal)){
        concatenaCodigo(val,"%s",variavelVal);
        return 1;
    }
    else if(constante(&constanteVal)){
        concatenaCodigo(val,"%s", constanteVal);
        return 1;
    }
    return 0;
}

int chamadaFuncao(char **val){
    char *passagemParametrosVal="";
    if(codToken == ABREPAR){
        analisadorLexico();
        passagemParametros(&passagemParametrosVal);
        if(codToken == FECHAPAR){
            analisadorLexico();
            concatenaCodigo(val,"(%s)", passagemParametrosVal);
        }
        else{
            printf("Esperava fecha parenteses na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }

    return 1;
}

int passagemParametros(char **val){
    char *E0Val="", *pParametrosVal="";
    if(E0(&E0Val)){
        pParametros(&pParametrosVal);
    }
    concatenaCodigo(val,"%s%s",E0Val, pParametrosVal);
    return 1;
}

int pParametros(char **val){
    char *E0Val="", *pParametrosVal="";
    if(codToken == VIRGULA){
        analisadorLexico();
        E0(&E0Val);
        pParametros(&pParametrosVal);
        concatenaCodigo(val,", ");
    }
    concatenaCodigo(val,"%s%s%s", *val, E0Val, pParametrosVal);
}

int variavel(char **val){
    char *id="", *vetorFuncaoVal="";
    int retorno;
    if(codToken == ID){
        concatenaCodigo(&id,"%s",token);
        analisadorLexico();
        retorno = vetorFuncao(&vetorFuncaoVal);
        concatenaCodigo(val,"%s%s", id, vetorFuncaoVal);
        return retorno;
    }
    return 0;
}

int vetorFuncao(char **val){
    char *inteiroVal="", *passagemParametrosVal="";
    if(codToken == ABRECOLCHETE){
        analisadorLexico();
        if (inteiro(&inteiroVal)){
            tipoMatriz();
            if(codToken == FECHACOLCHETE){
                analisadorLexico();
                return 1;
            }
            else{
                printf("Esperava fecha colchete na linha %d\nencontrou %s\n", linha, token);
                exit(0);
            }
        }
        else{
            printf("Esperava valor inteiro na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }
    else if(codToken == ABREPAR){
        analisadorLexico();
        passagemParametros(&passagemParametrosVal);
        if(codToken == FECHAPAR){
            analisadorLexico();
            concatenaCodigo(val,"(%s)", passagemParametrosVal);
            return 2;
        }
        else{
            printf("Esperava fecha parenteses na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }
    return 1;
}

int tipoMatriz(){
    char *inteiroVal="";
    if(codToken == VIRGULA){
        analisadorLexico();
        if(inteiro(&inteiroVal))
            return 1;
        else{
            printf("Esperava valor inteiro na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }
    return 1;
}

int inteiro(char **val){
    if(codToken == CONSTINTEIRO || codToken == ID){
        concatenaCodigo(val,"%s",token);
        analisadorLexico();
        return 1;
    }
    return 0;
}

int constante(char **val){
    if(codToken == CONSTINTEIRO || codToken == CONSTREAL ||
            codToken == VERDADEIRO || codToken == FALSO ||codToken == STRING){
        concatenaCodigo(val,"%s",token);
        analisadorLexico();
        return 1;
    }
    return 0;
}

int listaVariaveis(char **val){
    char *variavelVal="", *lVariavelVal="";
    if(variavel(&variavelVal) == 1){
        lVariavel();
        concatenaCodigo(val,"%s%s", variavelVal, lVariavelVal);
    }
    else{
        printf("Esperava variavel na linha %d\nencontrou %s\n", linha, token);
        exit(0);
    }
}

int lVariavel(){
    char *variavelVal="";
    if(codToken == VIRGULA){
        analisadorLexico();
        if(variavel(&variavelVal) == 1){
            lVariavel();
        }
        else{
            printf("Esperava variavel na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }
    return 1;
}

int listaComandos(char **val){
    char *comandoVal="", *listaComandosVal="";
    if (comando(&comandoVal))
        listaComandos(&listaComandosVal);
    concatenaCodigo(val,"%s%s", comandoVal, listaComandosVal);
    return 1;
}

int fimse(char **val){
    char *listaComandosVal="";
    if(codToken == FIMSE){
        analisadorLexico();
    }
    else{
        if(codToken == SENAO){
            analisadorLexico();
            listaComandos(&listaComandosVal);
            if(codToken == FIMSE){
                analisadorLexico();
                concatenaCodigo(val,"\nelse{\n%s\n}\n", listaComandosVal);
            }
            else{
                printf("Esperava fimse na linha %d\nencontrou %s\n", linha, token);
                exit(0);
            }
        }
        else{
            printf("Esperava fimse ou senao na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }
    return 1;
}

int passo(char **val){
    char *inteiroVal="";
    if(codToken == PASSO){
        analisadorLexico();
        inteiro(&inteiroVal);
        concatenaCodigo(val,"%s",inteiroVal);
    }
    concatenaCodigo(val,"1");

}

int comando(char **val){
    char *listaComandosVal="", *variavelVal="", *E0Val="", *inteiro1Val="",
         *passagemParametrosVal="", *inteiro2Val="", *fimseVal="",
         *passoVal="", *listaVariaveisVal="", *formatoVal="";
    int tVar = variavel(&variavelVal);
    if(tVar>1){
        return 1;
    }
    else if(tVar == 1){
        if(codToken == ATRIBUICAO){
            analisadorLexico();
            if(E0(&E0Val)){
                concatenaCodigo(val,"%s = %s;\n", variavelVal, E0Val);
                return 1;
            }
            else{
                printf("Esperava expressao na linha %d\nencontrou %s\n", linha, token);
                exit(0);
            }
        }
        else{
            printf("Esperava <- na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }
    if(codToken == LEIA){
        analisadorLexico();
        if(codToken == ABREPAR){
            analisadorLexico();
            listaVariaveis(&listaVariaveisVal);
            if(codToken == FECHAPAR){
                analisadorLexico();
                concatenaCodigo(val,"scanf(\"%s\", %s);\n", formatoVal, listaVariaveisVal);
                return 1;
            }
            else{
                printf("Esperava fecha parenteses na linha %d\nencontrou %s\n", linha, token);
                exit(0);
            }
        }
        else{
            printf("Esperava abre parenteses na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }
    if(codToken == ESCREVA || codToken == ESCREVAL){
        analisadorLexico();
        if(codToken == ABREPAR){
            analisadorLexico();
            passagemParametros(&passagemParametrosVal);
            if(codToken == FECHAPAR){
                analisadorLexico();
                concatenaCodigo(val,"printf(\"%s\", %s);\n", formatoVal, passagemParametrosVal);
                return 1;
            }
            else{
                printf("Esperava fecha parenteses na linha %d\nencontrou %s\n", linha, token);
                exit(0);
            }
        }
        else{
            printf("Esperava abre parenteses na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }
    if(codToken == SE){
        analisadorLexico();
        if(E0(&E0Val)){
            if(codToken == ENTAO){
                analisadorLexico();
                listaComandos(&listaComandosVal);
                fimse(&fimseVal);
                concatenaCodigo(val,"if (%s){\n%s\n}%s",E0Val, listaComandosVal, fimseVal);
                return 1;
            }
            else{
                printf("Esperava entao na linha %d\nencontrou %s\n", linha, token);
                exit(0);
            }
        }
        else{
            printf("Esperava expressao na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }
    if(codToken == REPITA){
        analisadorLexico();
        listaComandos(&listaComandosVal);
        if(codToken == ATE){
            analisadorLexico();
            E0(&E0Val);
            concatenaCodigo(val,"do{\n%s}while(!(%s));\n", listaComandosVal, E0Val);
            return 1;
        }
        else{
            printf("Esperava ate na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }
    if(codToken == ENQUANTO){
        analisadorLexico();
        if(E0(&E0Val)){
            if(codToken == FACA){
                analisadorLexico();
                listaComandos(&listaComandosVal);
                if(codToken == FIMENQUANTO){
                    analisadorLexico();
                    concatenaCodigo(val,"while(%s){\n%s}\n", E0Val, listaComandosVal);
                    return 1;
                }
                else{
                    printf("Esperava fimenquanto na linha %d\nencontrou %s\n", linha, token);
                    exit(0);
                }
            }
            else{
            printf("Esperava faca na linha %d\nencontrou %s\n", linha, token);
            }
        }
        else{
            printf("Esperava expressao na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }
    if(codToken == PARA){
        analisadorLexico();
        if(variavel(&variavelVal) == 1){
            if(codToken == DE){
                analisadorLexico();
                if(inteiro(&inteiro1Val)){
                    if(codToken == ATE){
                        analisadorLexico();
                        if(inteiro(&inteiro2Val)){
                            passo(&passoVal);
                            if(codToken == FACA){
                                analisadorLexico();
                                listaComandos(&listaComandosVal);
                                if(codToken == FIMPARA){
                                    analisadorLexico();
                                    concatenaCodigo(val,"for( %s = %s; %s < %s; %s += %s){\n%s}\n",
                                                    variavelVal, inteiro1Val, variavelVal, inteiro2Val,
                                                    variavelVal, passoVal, listaComandosVal);
                                    return 1;
                                }
                                else{
                                    printf("Esperava fimpara na linha %d\nencontrou %s\n", linha, token);
                                    exit(0);
                                }
                            }
                            else{
                                printf("Esperava faca na linha %d\nencontrou %s\n", linha, token);
                                exit(0);
                            }
                        }
                        else{
                            printf("Esperava inteiro na linha %d\nencontrou %s\n", linha, token);
                            exit(0);
                        }
                    }
                    else{
                        printf("Esperava ate na linha %d\nencontrou %s\n", linha, token);
                        exit(0);
                    }
                }
                else{
                    printf("Esperava inteiro na linha %d\nencontrou %s\n", linha, token);
                    exit(0);
                }
            }
            else{
                printf("Esperava de na linha %d\nencontrou %s\n", linha, token);
                exit(0);
            }
        }
        else{
            printf("Esperava variavel de controle na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }
    if (codToken == RETORNE){
        analisadorLexico();
        E0(&E0Val);
        concatenaCodigo(val,"return %s;\n",E0Val);
        return 1;
    }
    return 0;
}

int analisadorSintatico()
{
    int cod;
    char *varVal="", *listaComandosVal="", *nomeAlgoritmoVal="";
    analisadorLexico();
    if(codToken == ALGORITMO){
        analisadorLexico();
        nomeAlgoritmo(&nomeAlgoritmoVal);
        var(&varVal);
        if(codToken == INICIO){
            analisadorLexico();
            listaComandos(&listaComandosVal);
            if(codToken == FIMALGORITMO){
                concatenaCodigo(&codigoC, "%s%s%s%s%s%s","#include <stdio.h>\n#include <stdlib.h>\n#include <math.h>\n",
                                          nomeAlgoritmoVal, varVal, "int main(){\n", listaComandosVal, "\n}\n");
            }
            else{
                printf("Esperava palavra 'Fimalgoritmo' na linha %d\nencontrou %s\n", linha, token);
                exit(0);
            }

        }
        else{
            printf("Esperava palavra 'Inicio' na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }
    else{
        printf("Esperava palavra 'Algoritmo' na linha %d\nencontrou %s\n", linha, token);
        exit(0);
    }
    return 1;
}

/*
char *concatenaCodigo(char *format, ...)
{
    va_list args;
    va_start(args, format);
    int n = vsnprintf(NULL, 0, format, args) + 1;  // Note the +1!
    va_end(args);                                  // vsnprintf() 'uses up' args
    char *newString = (char *) malloc(n);
    if (newString != 0)
    {
        va_start(args, format);                        // Restart args
        vsprintf(newString, format, args);
        va_end(args);
    }
    return newString;
}
*/

void concatenaCodigo(char **entrada, char *format, ...)
{
    va_list args;
    va_start(args, format);
    int n = vsnprintf(NULL, 0, format, args) + 1;  /* Note the +1! */
    va_end(args);                                  /* vsnprintf() 'uses up' args */
    char *newString = (char *) malloc(n);
    if (newString != 0)
    {
        va_start(args, format);                        /* Restart args */
        vsprintf(newString, format, args);
        va_end(args);
    }
    *entrada = newString;
}

int main()
{   
    char *saida = "saida.lex", algoritmoC[FILENAME_MAX], entrada[FILENAME_MAX];

    strcpy (entrada, "algoritmo");
//    printf("Digite nome do arquivo de entrada: ");
//    scanf("%s", &entrada);
    strcpy (algoritmoC, entrada);
    strcat (algoritmoC, ".c");

    if((arquivoEntrada = fopen(entrada, "r"))==NULL){
        printf("\nErro ao abrir arquivo de entrada: %s\n", entrada);
        getchar();
        exit(0);
    }
    if((algoritmoSaida = fopen(algoritmoC, "w"))==NULL){
        printf("\nErro ao criar arquivo de saida: %s\n", algoritmoC);
        getchar();
        exit(0);
    }
    if((arquivoSaida = fopen(saida, "w"))==NULL){
        printf("\nErro ao criar arquivo de saida: %s\n", saida);
        getchar();
        exit(0);
    }
    if(lerLinha())
        if(analisadorSintatico()){
            printf("Algoritmo Reconhecido!\n");
        }

    fprintf(algoritmoSaida, "%s", codigoC);
    fclose(arquivoSaida);
    fclose(arquivoEntrada);
    fclose(algoritmoSaida);
    int teste = 10;
//    getchar();
}

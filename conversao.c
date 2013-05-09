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
int E0(char *codEntrada);
int E0a(char *codEntrada);
int E1(char *codEntrada);
int E1a(char *codEntrada);
int E2(char *codEntrada);
int E3(char *codEntrada);
int E4(char *codEntrada);
int E4a(char *codEntrada);
int E5(char *codEntrada);
int E5a(char *codEntrada);
int E6(char *codEntrada);
int E7(char *codEntrada);
int termo(char *codEntrada);
int passagemParametros();
int pParametros();
int variavel();
int vetorFuncao();
int tipoMatriz();
int inteiro();
int constante();
int listaComandos();
int comandos();
int listaVariaveis();
int fimse();
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

    if (*listaIdentificadoresS){
        concatenaCodigo(val, "%s%s, %s", *tipoVariavelVal, id, listaIdentificadoresS);
    }
    else{
        concatenaCodigo(val, ", %s%s", *tipoVariavelVal, id);
    }
    return 1;
}

int listaParametros(char **val){
    char *parametrosVal="";
    if(codToken == PONTOEVIRGULA){
        analisadorLexico();
        parametros(&parametrosVal);
        concatenaCodigo(val,"%s; %s", *val, parametrosVal);
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
        if (listaIdentificadoresTipoVariavelVal)
            concatenaCodigo(val,"%s%s, %s%s", tipoVariavelVal, id, listaIdentificadoresTipoVariavelVal, listaParametrosVal);
        else
            concatenaCodigo(val,"%s%s%s", tipoVariavelVal, id, listaIdentificadoresTipoVariavelVal, listaParametrosVal);
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
                        listaComandos();
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
    char *id="", *parametrosVal="parametrosVal", *varVal="", *listaComandosVal="listaComandosVal";
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
                    listaComandos();
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

int E0(char *codEntrada){
    int retorno;
    char *codE1 = "", *codE0a = "";
    retorno = E1(codE1);
    E0a(codE0a);
    return retorno;
}

int E0a(char *codEntrada){
    char *codE1 ="", *codE0a = "";
    if(codToken == OU){
        analisadorLexico();
        E1(codE1);
        E0a(codE0a);
    }
}

int E1(char *codEntrada){
    char *codE2 = "", *codE1a = "";
    int retorno;
    retorno = E2(codE2);
    E1a(codE1a);
    return retorno;
}

int E1a(char *codEntrada){
    char *codE2 ="", *codE1a = "";
    if(codToken == E){
        analisadorLexico();
        E2(codE2);
        E1a(codE1a);
    }
}

int E2(char *codEntrada){
    char *codE2 ="", *codE3 = "";
    if(codToken == NAO){
        analisadorLexico();
        E2(codE2);
    }
    else {
        int retorno = E3(codE3);
        return retorno;
    }
}

int E3(char *codEntrada){
    char *codE4 ="";
    int retorno;
    retorno = E4(codE4);
    if(codToken == MAIOR || codToken == MAIORIGUAL ||
            codToken == MENOR || codToken == MENORIGUAL ){
        analisadorLexico();
        E4(codE4);
    }
    return retorno;
}

int E4(char *codEntrada){
    char *sintetizado ="";
    int retorno;
    retorno = E5(sintetizado);
    E4a(sintetizado);
    return retorno;
}

int E4a(char *codEntrada){
    char *codE5 = "", *codE4a = "";
    if(codToken == MAIS || codToken == MENOS){
        analisadorLexico();
        E5(codE5);
        E4a(codE4a);
    }
}

int E5(char *codEntrada){
    char *sintetizado ="";
    int retorno;
    retorno = E6(sintetizado);
    E5a(sintetizado);
    return retorno;
}

int E5a(char *codEntrada){
    char *sintetizado ="";
    if(codToken == DIVISAO || codToken == MULTIPLICACAO ||
            codToken == RESTO || codToken == DIVINTEIRA ){
        analisadorLexico();
        E6(sintetizado);
        E5a(sintetizado);
    }
}

int E6(char *codEntrada){
    char *sintetizado ="";
    int retorno;
    retorno = E7(sintetizado);
    if(codToken == POTENCIA){
        analisadorLexico();
        E6(sintetizado);
    }
    return retorno;
}
int E7(char *codEntrada){
    char *sintetizado ="";
    if(codToken == MENOS){
        analisadorLexico();
        E7(sintetizado);
    }
    else{
        return termo(sintetizado);
    }
}

int termo(char *codEntrada){
    char *sintetizado ="";
    if(codToken == ABREPAR){
        analisadorLexico();
        if (E0(sintetizado)){
            if(codToken == FECHAPAR){
                analisadorLexico();
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
    else{
        if(variavel() || constante()){
            return 1;
        }
    }
    return 0;
}

int chamadaFuncao(){
    if(codToken == ABREPAR){
        analisadorLexico();
        passagemParametros();
        if(codToken == FECHAPAR){
            analisadorLexico();
        }
        else{
            printf("Esperava fecha parenteses na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }

    return 1;
}

int passagemParametros(){
    if(E0(STRINGTEMP)){
        pParametros();
    }
    return 1;
}

int pParametros(){
    if(codToken == VIRGULA){
        analisadorLexico();
        E0(STRINGTEMP);
        pParametros();
    }
}

int variavel(){
    if(codToken == ID){
        analisadorLexico();
        return vetorFuncao();
    }
    return 0;
}

int vetorFuncao(){
    if(codToken == ABRECOLCHETE){
        analisadorLexico();
        if (inteiro()){
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
        passagemParametros();
        if(codToken == FECHAPAR){
            analisadorLexico();
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
    if(codToken == VIRGULA){
        analisadorLexico();
        if(inteiro())
            return 1;
        else{
            printf("Esperava valor inteiro na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }
    return 1;
}

int inteiro(){
    if(codToken == CONSTINTEIRO || codToken == ID){
        analisadorLexico();
        return 1;
    }
    return 0;
}

int constante(){
    if(codToken == CONSTINTEIRO || codToken == CONSTREAL ||
            codToken == VERDADEIRO || codToken == FALSO ||codToken == STRING){
        analisadorLexico();
        return 1;
    }
    return 0;
}

int listaVariaveis(){
    if(variavel() == 1){
        lVariavel();
    }
    else{
        printf("Esperava variavel na linha %d\nencontrou %s\n", linha, token);
        exit(0);
    }
}

int lVariavel(){
    if(codToken == VIRGULA){
        analisadorLexico();
        if(variavel() == 1){
            lVariavel();
        }
        else{
            printf("Esperava variavel na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }
    return 1;
}

int listaComandos(){
    if (comando())
        listaComandos();
    return 1;
}

int fimse(){
    if(codToken == FIMSE){
        analisadorLexico();
    }
    else{
        if(codToken == SENAO){
            analisadorLexico();
            listaComandos();
            if(codToken == FIMSE){
                analisadorLexico();
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

int comando(){
    int tVar = variavel();
    if(tVar>1){
        return 1;
    }
    else if(tVar == 1){
        if(codToken == ATRIBUICAO){
            analisadorLexico();
            if(E0(STRINGTEMP))
                return 1;
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
            listaVariaveis();
            if(codToken == FECHAPAR){
                analisadorLexico();
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
            passagemParametros();
            if(codToken == FECHAPAR){
                analisadorLexico();
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
        if(E0(STRINGTEMP)){
            if(codToken == ENTAO){
                analisadorLexico();
                listaComandos();
                fimse();
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
        listaComandos();
        if(codToken == ATE){
            analisadorLexico();
            E0(STRINGTEMP);
            return 1;
        }
        else{
            printf("Esperava ate na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }
    if(codToken == ENQUANTO){
        analisadorLexico();
        if(E0(STRINGTEMP)){
            listaComandos();
            if(codToken == FIMENQUANTO){
                analisadorLexico();
                return 1;
            }
            else{
                printf("Esperava fimenquanto na linha %d\nencontrou %s\n", linha, token);
                exit(0);
            }
        }
        else{
            printf("Esperava expressao na linha %d\nencontrou %s\n", linha, token);
            exit(0);
        }
    }
    if(codToken == PARA){
        analisadorLexico();
        if(variavel() == 1){
            if(codToken == DE){
                analisadorLexico();
                if(inteiro()){
                    if(codToken == ATE){
                        analisadorLexico();
                        if(inteiro()){
                            if(codToken == FACA){
                                analisadorLexico();
                                listaComandos();
                                if(codToken == FIMPARA){
                                    analisadorLexico();
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
        E0(STRINGTEMP);
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
            listaComandos();
            if(codToken == FIMALGORITMO){
                concatenaCodigo(&codigoC, "%s%s%s%s%s%s","#include <stdio.h>\n#include <stdlib.h>\n",
                                          nomeAlgoritmoVal, varVal, "int main(){\n", listaComandosVal, "}\n");
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
//    getchar();
}


#ifndef GERADORARTES_QUADRO_H
#define GERADORARTES_QUADRO_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define LINHA 20
#define COLUNA 80

typedef struct TipoDesenho{
    char* tipo; // asterisco, soma, x, proprio
    char** desenho; // desenho em matriz
    int dimensao; // dimensao da matriz quadrada
}TipoDesenho;

// OPERACOES BASICAS DO QUADRO
char** iniciarQuadro(int linha, int coluna);
char** criarQuadro();
void imprimirQuadro(char **quadro,int linha, int coluna);

// OPERACOES DE DESENHO
TipoDesenho* buscarDesenho(char* desenhoEscolhido);
void inserirDesenho(char** quadro, int posLinhaQuadro, int posColunaQuadro, char** desenho, int linhaDesenho, int colunaDesenho);
int conferirEspacoQuadro(char** quadro, int posLinhaQuadro, int posColunaQuadro, char** desenho, int linhaDesenho, int colunaDesenho);
void qntDesenho(char** quadro, TipoDesenho* figura, int quantidade);

#endif //GERADORARTES_QUADRO_H

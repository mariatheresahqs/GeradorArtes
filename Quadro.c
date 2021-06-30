
#include "Quadro.h"


/*
 * ****************************************************
 * OPERACOES BASICAS DO QUADRO
 * ****************************************************
*/
char** iniciarQuadro(int linha, int coluna){
    /*
     * ALOCANDO ESPACO PARA UM QUADRO EM BRANCO SEM MOLDURA
     */
    char** quadro = (char**) malloc(linha * sizeof(char*));
    for (int i = 0; i < linha; i++) {
        quadro[i] = (char*) malloc (coluna * sizeof(char));
        for (int j = 0; j < coluna; j++) {
            quadro[i][j] = ' ';
        }
    }
    return quadro;
}

char** criarQuadro() {
    /*
     * CRIAR QUADRO EM BRANCO COM MOLDURA
    */
    int linha = LINHA;
    int coluna = COLUNA;
    char** quadro = iniciarQuadro(linha,coluna);
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            if (i == 0 || i == (linha-1)){
                quadro[i][j] = '-';
            } else if (j == 0 || j == (coluna-1) ){
                quadro[i][j] = '|';
            } else {
                quadro[i][j] = ' ';
            }
        }
    }
    return quadro;
}

void imprimirQuadro(char **quadro,int linha, int coluna){
    for(int i=0;i<linha;i++){
        for(int j=0;j<coluna;j++){
            printf("%c",quadro[i][j]);
        }
        printf("\n");
    }
}

/*
 * ****************************************************
 * OPERACOES DE DESENHO
 * ****************************************************
*/

TipoDesenho* buscarDesenho(char* desenhoEscolhido){
    /*
    * LER DESENHO DO ARQUIVO
    */
    TipoDesenho* pntDesenho = (TipoDesenho*) malloc(sizeof (TipoDesenho));
    FILE *file;
    file = fopen(desenhoEscolhido, "r");
    pntDesenho->tipo = desenhoEscolhido;
    fscanf(file, "%d", &pntDesenho->dimensao);
    fgetc(file);
    // alocando espaco para o desenho
    pntDesenho->desenho = iniciarQuadro(pntDesenho->dimensao, pntDesenho->dimensao);
    // preenchendo o desenho
    for(int i=0;i<pntDesenho->dimensao;i++){
        for(int j=0;j<pntDesenho->dimensao;j++){
            pntDesenho->desenho[i][j] = fgetc(file);
        }
        fgetc(file);
    }
    fclose(file);
    return pntDesenho;
}

void inserirDesenho(char** quadro, int posLinhaQuadro, int posColunaQuadro, char** desenho, int linhaDesenho, int colunaDesenho){
    /*
    * INSERIR DESENHO NAS POSICOES ALEATORIAS DO QUADRO
    */
    int auxLinDesenho = 0, auxColDesenho = 0;
    for(int i = posLinhaQuadro; i<(posLinhaQuadro+linhaDesenho);i++){
        for(int j = posColunaQuadro; j<(posColunaQuadro+colunaDesenho);j++){
            quadro[i][j] = desenho[auxLinDesenho][auxColDesenho];
            auxColDesenho++;
        }

        auxColDesenho = 0;
        auxLinDesenho++;
    }
}

int conferirEspacoQuadro(char** quadro, int posLinhaQuadro, int posColunaQuadro, char** desenho, int linhaDesenho, int colunaDesenho){
    /*
    * CONFERIR RESTRICOES DE ESPACO E OCUPACAO
    */
    int inserir_flag = 1; // 0 - nao; 1 - sim;
    // Verificar se a posicao escolhida no quadro somado ao tamanho do desenho
    // nao ultrapassa as dimensoes do quadro
    if( posLinhaQuadro<0 ||
        posColunaQuadro<0 ||
        posLinhaQuadro+linhaDesenho>=LINHA ||
        posColunaQuadro+colunaDesenho>=COLUNA){
        inserir_flag = 0;
        return inserir_flag;
    }
    // Verificar se  o espaco nessa posicao escolhida
    // ja nao esta preenchido
    for(int i = posLinhaQuadro; i<(posLinhaQuadro+linhaDesenho);i++){
        for(int j = posColunaQuadro; j<(posColunaQuadro+colunaDesenho);j++){
            if(quadro[i][j]!=' '){
                inserir_flag = 0;
            }
        }
    }
    // Inserir desenho no quadro:
    // imagem cabe nas dimensoes do quadro e o espaco esta livre
    if(inserir_flag==1) {
        inserirDesenho(quadro, posLinhaQuadro, posColunaQuadro, desenho, linhaDesenho, colunaDesenho);
    }
    return inserir_flag;
}

void qntDesenho(char** quadro, TipoDesenho* figura, int quantidade){
    /*
    * INSERIR QUANTIDADE DE DESENHOS DESEJADA
    */

    // Verificar se quantidade escolhida
    // esta dentro dos criterios (0 a 100)
    srand(time(NULL));
    int qnt;
    if(quantidade<0) qnt = 1+(rand()%99);
    else if(quantidade>100) qnt = 100;
    else qnt = quantidade;

    // Selecionar posicoes aleatorias no
    // para inserir cada desenho
    int posLinhaQuadro, posColunaQuadro, inserir_flag;
    while (qnt!=0){
        posLinhaQuadro = 1+(rand()%LINHA);
        posColunaQuadro = 1+(rand()%COLUNA);
        inserir_flag = conferirEspacoQuadro(quadro, posLinhaQuadro, posColunaQuadro, figura->desenho, figura->dimensao, figura->dimensao);
        if(inserir_flag==1){
            qnt--;
        }
    }
}

#include "Menu.h"
#include "Quadro.h"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define RESET "\x1B[0m"

int opcoes() {
    int opcao;
    printf(YEL "______________________________________________________________________\n");
    printf(BLU "Escolha o tipo de figura basica a ser usada para criar a obra:\n");
    printf(RESET"1 - Asterisco simples\n");
    printf("2 - Simbolo de soma com asteriscos\n");
    printf("3 - Letra X com asteriscos\n");
    printf("4 - Figuras aleatorias\n");
    printf("5 - Figura surpresa\n");
    printf("0 - Sair\n");
    printf(YEL "______________________________________________________________________\n");
    printf(GRN "Digite o tipo de figura basica desejada: ");
    scanf("%d", &opcao);
    printf(YEL"______________________________________________________________________\n");
    if (opcao > 5 || opcao < 0) {
        printf(RED"Opção Invalida. Tente novamente!\n");
        opcoes();
    }
    return opcao;
}

void numeroFiguras(char** quadro, TipoDesenho* figura){
    int quantidade;
    printf("Digite a quantidade de figuras (menor ou igual a zero para aleatorio): ");
    scanf("%d", &quantidade);
    qntDesenho(quadro, figura, quantidade);
}


int numeroFigurasAleatorias(){
    int quantidade, qnt;
    printf("Digite a quantidade de figuras (menor ou igual a zero para aleatorio): ");
    scanf("%d", &quantidade);

    if(quantidade<0) qnt = 1+(rand()%99);
    else if(quantidade>100) qnt = 100;
    else qnt = quantidade;

    return qnt;
}


void menu() {
    char **quadro;
    TipoDesenho *figura;
    int escolha = 1, qntFigAleatorias[3], qnt, figAleatoria;

    printf(RED "\nPROGRAMA GERADOR DE OBRA DE ARTE:\n");
    while (1) {
        escolha = opcoes();
        if (escolha == 0) {
            printf("Programa encerrado!");
            return;
        }
        else {
            quadro = criarQuadro();
            if (escolha == 1) {
                figura = buscarDesenho("asterisco.txt");
            };
            if (escolha == 2) {
                figura = buscarDesenho("soma.txt");
            };
            if (escolha == 3) {
                figura = buscarDesenho("x.txt");
            };
            if (escolha == 4) {
                qnt = numeroFigurasAleatorias();
                if(qnt>1) {
                    qntFigAleatorias[0] = (rand() % (qnt - 1));
                    qnt -= qntFigAleatorias[0];
                    qntFigAleatorias[1] = (rand() % (qnt - 1));
                    qnt -= qntFigAleatorias[1];
                    qntFigAleatorias[2] = qnt;

                    // carregar cada imagem na tela
                    figura = buscarDesenho("asterisco.txt");
                    qntDesenho(quadro, figura, qntFigAleatorias[0]);
                    figura = buscarDesenho("soma.txt");
                    qntDesenho(quadro, figura, qntFigAleatorias[1]);
                    figura = buscarDesenho("x.txt");
                    qntDesenho(quadro, figura, qntFigAleatorias[2]);
                } else{
                    figAleatoria = rand()%4;
                    printf("figAle %d\n",figAleatoria);
                    if(figAleatoria==1) figura = buscarDesenho("asterisco.txt");
                    if(figAleatoria==2) figura = buscarDesenho("soma.txt");
                    if(figAleatoria==3) figura = buscarDesenho("x.txt");
                    qntDesenho(quadro, figura, qnt);
                }
            };
            if (escolha == 5) {
                figura = buscarDesenho("bird.txt");
                qnt = numeroFigurasAleatorias();
                if(qnt>34) qnt = 34;
                qntDesenho(quadro, figura, qnt);
            }
            if (escolha != 4 && escolha!=5) {
                numeroFiguras(quadro, figura);
            }
            imprimirQuadro(quadro, LINHA, COLUNA);
        }
    }
}

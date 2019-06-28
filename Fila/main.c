#include "fila.h"
#include <string.h>

int menu();

int main () {

    Descritor *fila = NULL;
    int op;

    system("clear||cls");
    do {
        op = menu();
        switch (op) {
        case 0:
            system("clear||cls");
            printf("Falou =D\n");
        break;
        case 1: {
            system("clear||cls");
            int tamanho;
            printf("Informe o tamanho da fila: ");
            scanf("%d", &tamanho);
            fila = criaFila(tamanho);
            if(fila != NULL) printf("Fila alocada !!\n\n");
            else printf("Nao foi possivel alocar a fila !!\n\n");
        } break;
        case 2:
            system("clear||cls");
            if(desalocaFila(&fila)) 
                printf("Fila desalocada !!\n\n");
        break;
        case 3: {
            system("clear||cls");
            int tamanho = tamanhoFila(fila);
            if(tamanho != -1)
                printf("O tamanho da fila eh de %d cliente(s).\n\n", tamanho);
        } break;
        case 4: {
            system("clear||cls");
            int flag = filaCheia(fila);
            if(flag == 1) printf("A fila esta cheia !!\n\n");
            else if(flag == 0) printf("A fila nao esta cheia !!\n\n");
        } break;
        case 5: {
            system("clear||cls");
            int flag = filaVazia(fila);
            if(flag == 1) printf("A fila esta vazia !!\n\n");
            else if(flag == 0) printf("A fila nao esta vazia !!\n\n");
        } break;
        case 6:
            system("clear||cls");
            if(insereFinal(fila, novoCliente()) == 1)
                printf("Cliente inserido no final !!\n\n");
        break;
        case 7:
            system("clear||cls");
            if(removeInicio(fila) == 1)
                printf("Cliente do inicio removido !!\n\n");
        break;
        case 8:
            system("clear||cls");
            imprime(fila);
        break;
        default:
            printf("Opcao nao encontrada !!\n\n");
            break;
        }
    } while (op != 0);
    
    if(fila != NULL) 
        desalocaFila(&fila);
    return 0;
}

int menu() {

    int op;
    printf("0 - Sair\n");
    printf("1 - Aloca fila\n");
    printf("2 - Desaloca fila\n");
    printf("3 - Tamanho da fila\n");
    printf("4 - Fila cheia ?\n");
    printf("5 - Fila vazia ?\n");
    printf("6 - Insere no final\n");
    printf("7 - Remove no inicio\n");
    printf("8 - Imprime fila\n\n");

    printf("Escolha uma opcao: ");
    scanf("%d", &op);
    return op;
}
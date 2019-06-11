#include "lista.h"
#include <string.h>

int menu();

int main () {

    Descritor *lista = NULL;
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
            printf("Informe o tamanho da lista: ");
            scanf("%d", &tamanho);
            lista = criaLista(tamanho);
            if(lista != NULL) printf("Lista alocada !!\n\n");
            else printf("Nao foi possivel alocar a lista !!\n\n");
        } break;
        case 2:
            system("clear||cls");
            if(desalocaLista(&lista)) 
                printf("Lista desalocada !!\n\n");
        break;
        case 3: {
            system("clear||cls");
            int tamanho = tamanhoLista(lista);
            if(tamanho != -1)
                printf("O tamanho da lista eh de %d cliente(s).\n\n", tamanho);
        } break;
        case 4: {
            system("clear||cls");
            int flag = listaCheia(lista);
            if(flag == 1) printf("A lista esta cheia !!\n\n");
            else if(flag == 0) printf("A lista nao esta cheia !!\n\n");
        } break;
        case 5: {
            system("clear||cls");
            int flag = listaVazia(lista);
            if(flag == 1) printf("A lista esta vazia !!\n\n");
            else if(flag == 0) printf("A lista nao esta vazia !!\n\n");
        } break;
        case 6:
            system("clear||cls");
            if(insereInicio(lista, novoCliente()) == 1) 
                printf("Cliente inserido no inicio !!\n\n");
        break;
        case 7:
            system("clear||cls");
            if(insereFinal(lista, novoCliente()) == 1)
                printf("Cliente inserido no final !!\n\n");
        break;
        case 8: {
            system("clear||cls");
            int posicao;
            printf("Informe a posicao que deseja inserir o cliente: ");
            scanf("%d", &posicao);
            if(inserePosicao(lista, novoCliente(), posicao) == 1)
                printf("Cliente inserido na posicao %d !!\n\n", posicao);
        } break;
        case 9:
            system("clear||cls");
            if(removeInicio(lista) == 1)
                printf("Cliente do inicio removido !!\n\n");
        break;
        case 10:
            system("clear||cls");
            if(removeFinal(lista) == 1)  
                printf("Cliente do final removido !!\n\n");
        break;
        case 11: {
            system("clear||cls");
            int posicao;
            printf("Informe a posicao que deseja remover: ");
            scanf("%d", &posicao);
            if(removePosicao(lista, posicao) == 1)
                printf("Cliente da posicao %d removido !!\n\n");
        } break;
        case 12: {
            system("clear||cls");
            int id;
            printf("Informe o ID do cliente que deseja remover: ");
            scanf("%d", &id);
            if(removeID(lista, id) == 1)
                printf("Cliente com o ID %d removido !!\n\n");
        } break;
        case 13: {
            system("clear||cls");
            Cliente cliente;
            cliente.ID = -1;
            int posicao, flag;
            printf("Informe a posicao que deseja buscar: ");
            scanf("%d", &posicao);
            flag = buscaPosicao(lista, &cliente, posicao);
            if(flag == 1) {
                printf("ID: %d\n", cliente.ID);
                printf("Nome: %s\n", cliente.nome);
                printf("Telefone: %s\n\n", cliente.telefone);
            } else if(flag == 0)
                printf("ID: %d\n\n", cliente.ID);
        } break;
        case 14: {
            system("clear||cls");
            int id, flag;
            printf("Informe o ID do cliente que deseja buscar: ");
            scanf("%d", &id);
            flag = buscaElemento(lista, id);
            if(flag == 1)
                printf("Cliente com ID %d encontrado !!\n\n", id);
            else if(flag == 0)
                printf("Cliente com ID %d nao encontrado !!\n\n", id);
        } break;
        case 15:
            system("clear||cls");
            imprime(lista);
        break;
        default:
            printf("Opcao nao encontrada !!\n\n");
            break;
        }
    } while (op != 0);
    
    if(lista != NULL) 
        desalocaLista(&lista);
    return 0;
}

int menu() {

    int op;
    printf("0 - Sair\n");
    printf("1 - Aloca lista\n");
    printf("2 - Desaloca lista\n");
    printf("3 - Tamanho da lista\n");
    printf("4 - Lista cheia ?\n");
    printf("5 - Lista vazia ?\n");
    printf("6 - Insere no inicio\n");
    printf("7 - Insere no final\n");
    printf("8 - Insere no meio\n");
    printf("9 - Remove no inicio\n");
    printf("10 - Remove no final\n");
    printf("11 - Remove por posicao\n");
    printf("12 - Remove por ID\n");
    printf("13 - Busca por posicao\n");
    printf("14 - Busca por ID\n");
    printf("15 - Imprime lista\n\n");

    printf("Escolha uma opcao: ");
    scanf("%d", &op);
    return op;
}
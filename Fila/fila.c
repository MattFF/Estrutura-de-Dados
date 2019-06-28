#include "fila.h"

struct descritor {
    int quantidade;
    int tamanho;
    int inicio;
    int fim;
    Cliente *dados;
};

Descritor* criaFila(int tamanho) {
    Descritor* fila = (Descritor*) malloc (sizeof(Descritor));
    if(fila != NULL) {
        fila->quantidade = 0;
        fila->inicio = 0;
        fila->fim = -1;
        fila->tamanho = tamanho;
        fila->dados = (Cliente*) malloc (sizeof(Cliente) * tamanho);
        if(fila->dados == NULL) {
            free(fila);
            return NULL;
        }
    }
    return fila;
}

int desalocaFila(Descritor **fila) {
    if(*fila == NULL) {
        printf("Fila nao alocada !!\n\n");
        return 0;
    }
    free((*fila)->dados);
    free(*fila);
    *fila = NULL;
    return 1;
}

int tamanhoFila(Descritor *fila) {
    if(fila == NULL) {
        printf("Fila nao alocada !!\n\n");
        return -1;
    }
    return fila->quantidade;
}

int filaCheia(Descritor *fila) {
    if(fila == NULL) {
        printf("Fila nao alocada !!\n\n");
        return -1;
    }
    return (fila->quantidade == fila->tamanho);
}

int filaVazia(Descritor *fila) {
    if(fila == NULL) {
        printf("Fila nao alocada !!\n\n");
        return -1;
    }
    return (fila->quantidade == 0);
}

int insereFinal(Descritor *fila, Cliente cliente) {
    if(fila == NULL) {
        printf("Fila nao alocada !!\n\n");
        return -1;
    }
    if(fila->quantidade == fila->tamanho) {
       printf("Fila cheia !!\n\n");
       return 0; 
    }

    if(fila->quantidade == 0) {
        fila->dados[fila->inicio] = cliente;
        fila->fim = fila->inicio;
    } else {
        fila->fim = (fila->fim + 1) % fila->tamanho;
        fila->dados[fila->fim] = cliente;
    }
    fila->quantidade++;
    return 1;
}

int removeInicio(Descritor *fila) {
    if(fila == NULL) {
        printf("Fila nao alocada !!\n\n");
        return -1;
    }
    if(fila->quantidade == 0) {
        printf("Fila vazia !!\n\n");
        return 0;
    }
    fila->inicio = (fila->inicio + 1) % fila->tamanho;
    fila->quantidade--;
    return 1;
}

void imprime(Descritor *fila) {
    if(fila == NULL) {
        printf("Fila nao alocada !!\n\n");
        return;
    }
    if(fila->quantidade == 0) {
        printf("Fila Vazia !!\n\n");
        return;
    }
    int i = fila->inicio - 1;
    if(i < 0) i = fila->tamanho - 1;
    do {
        i = (i + 1) % fila->tamanho;
        printf("ID: %d\n", fila->dados[i].ID);
        printf("Nome: %s\n", fila->dados[i].nome);
        printf("Telefone: %s\n\n", fila->dados[i].telefone);
    } while (i != fila->fim);
}

Cliente novoCliente() {
    Cliente c;

    printf("Informe o ID do cliente: ");
    scanf("%d", &c.ID);
    printf("Informe o nome do cliente: ");
    scanf("%s", c.nome);
    printf("Informe o telefone do cliente: ");
    scanf("%s", c.telefone);

    return c;
}
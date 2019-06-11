#include "lista.h"

struct descritor {
    int quantidade;
    int tamanho;
    int inicio;
    int fim;
    Cliente *dados;
};

Descritor* criaLista(int tamanho) {
    Descritor* lista = (Descritor*) malloc (sizeof(Descritor));
    if(lista != NULL) {
        lista->quantidade = 0;
        lista->inicio = 0;
        lista->fim = -1;
        lista->tamanho = tamanho;
        lista->dados = (Cliente*) malloc (sizeof(Cliente) * tamanho);
        if(lista->dados == NULL) {
            free(lista);
            return NULL;
        }
    }
    return lista;
}

int desalocaLista(Descritor **lista) {
    if(*lista == NULL) {
        printf("Lista nao alocada !!\n\n");
        return 0;
    }
    free((*lista)->dados);
    free(*lista);
    *lista = NULL;
    return 1;
}

int tamanhoLista(Descritor *lista) {
    if(lista == NULL) {
        printf("Lista nao alocada !!\n\n");
        return -1;
    }
    return lista->quantidade;
}

int listaCheia(Descritor *lista) {
    if(lista == NULL) {
        printf("Lista nao alocada !!\n\n");
        return -1;
    }
    return (lista->quantidade == lista->tamanho);
}

int listaVazia(Descritor *lista) {
    if(lista == NULL) {
        printf("Lista nao alocada !!\n\n");
        return -1;
    }
    return (lista->quantidade == 0);
}

int insereInicio(Descritor *lista, Cliente cliente) {
    if(lista == NULL) {
        printf("Lista nao alocada !!\n\n");
        return -1;
    }
    if(lista->quantidade == lista->tamanho) {
        printf("Lista cheia !!\n\n");
        return 0;
    }

    if(lista->quantidade == 0) {
        lista->dados[lista->inicio] = cliente;
        lista->fim = lista->inicio;
    }
    else {
        lista->inicio--;
        if (lista->inicio < 0) lista->inicio = lista->tamanho - 1;
        lista->dados[lista->inicio] = cliente;
    }
    lista->quantidade++;
    return 1;
}

int inserePosicao(Descritor *lista, Cliente cliente, int pos) {

    if(lista == NULL) {
        printf("Lista nao alocada !!\n\n");
        return -1;
    }

    if(lista->quantidade == lista->tamanho) {
       printf("Lista cheia !!\n\n");
       return 0; 
    }
    
    if(pos < 1 || pos > lista->quantidade + 1) {
        printf("Posicao invalida !!\n\n");
        return 0;
    }

    if(lista->quantidade == 0) {
        insereInicio(lista, cliente);
        return 1;
    }

    int i = lista->fim, j = ((lista->inicio + pos - 1) % lista->tamanho) - 1;
    if (j < 0) j = lista->tamanho - 1;
    
    int aux;
    while (i != j) {
        aux = (i + 1) % lista->tamanho;
        lista->dados[aux] = lista->dados[i];
        i--;
        if(i < 0) i = lista->tamanho - 1;
    }
    lista->fim = (lista->fim + 1) % lista->tamanho;
    lista->dados[(lista->inicio + pos - 1) % lista->tamanho] = cliente;
    lista->quantidade++;
    return 1;
}

int insereFinal(Descritor *lista, Cliente cliente) {
    if(lista == NULL) {
        printf("Lista nao alocada !!\n\n");
        return -1;
    }
    if(lista->quantidade == lista->tamanho) {
       printf("Lista cheia !!\n\n");
       return 0; 
    }

    if(lista->quantidade == 0) {
        insereInicio(lista, cliente);
        return 1;
    } else {
        lista->fim = (lista->fim + 1) % lista->tamanho;
    }
    lista->dados[lista->fim] = cliente;
    lista->quantidade++;
    return 1;
}

int removeInicio(Descritor *lista) {
    if(lista == NULL) {
        printf("Lista nao alocada !!\n\n");
        return -1;
    }
    if(lista->quantidade == 0) {
        printf("Lista vazia !!\n\n");
        return 0;
    }
    lista->inicio = (lista->inicio + 1) % lista->tamanho;
    lista->quantidade--;
    return 1;
}

int removeFinal(Descritor *lista) {
    if(lista == NULL) {
        printf("Lista nao alocada !!\n\n");
        return -1;
    }
    if(lista->quantidade == 0) {
        printf("Lista vazia !!\n\n");
        return 0;
    }
    lista->fim--;
    if(lista->fim < 0) lista->fim = lista->tamanho - 1;
    lista->quantidade--;
    return 1;
}

int removeID(Descritor *lista, int id) {
    if(lista == NULL) {
        printf("Lista nao alocada !!\n\n");
        return -1;
    }
    if(lista->quantidade == 0) {
        printf("Lista vazia !!\n\n");
        return 0;
    }
    int i = lista->inicio, j = (lista->fim + 1) % lista->tamanho;
    while (i != j) {
        if(lista->dados[i].ID == id) break;
        i = (i + 1) % lista->tamanho;
    }
    if(i == j) {
        printf("Cliente com o ID %d nao encontrado !!\n\n", id);
        return 0;
    }
    while(i != lista->fim) {
        int aux = (i + 1) % lista->tamanho;
        lista->dados[i] = lista->dados[aux];
        i = (i + 1) % lista->tamanho;
    }
    lista->fim--;
    if(lista->fim < 0) lista->fim = lista->tamanho - 1;
    lista->quantidade--;
    return 1;
}

int removePosicao(Descritor *lista, int pos) {
    if(lista == NULL) {
        printf("Lista nao alocada !!\n\n");
        return -1;
    }
    if(lista->quantidade == 0) {
        printf("Lista vazia !!\n\n");
        return 0;
    }
    if(pos < 1 || pos > lista->quantidade) {
        printf("Posicao invalida !!\n\n");
        return 0;
    }
    int i = (lista->inicio + pos - 1) % lista->tamanho;
    while(i != lista->fim) {
        int aux = (i + 1) % lista->tamanho;
        lista->dados[i] = lista->dados[aux];
        i = (i + 1) % lista->tamanho;
    }
    lista->fim--;
    if(lista->fim < 0) lista->fim = lista->tamanho - 1;
    lista->quantidade--;
    return 1;
}

int buscaPosicao(Descritor *lista, Cliente *cliente, int pos) {
    if(lista == NULL) {
        printf("Lista nao alocada !!\n\n");
        return -1;
    }
    if(lista->quantidade == 0) {
        printf("Lista vazia !!\n\n");
        return 0;
    }
    if(pos < 1 || pos > lista->quantidade) {
        printf("Posicao invalida !!\n\n");
        return 0;
    }
    pos = (lista->inicio + pos - 1) % lista->tamanho;
    *cliente = lista->dados[pos];
    return 1;
}

int buscaElemento(Descritor *lista, int id) {
    if(lista == NULL) {
        printf("Lista nao alocada !!\n\n");
        return -1;
    }
    if(lista->quantidade == 0) {
        printf("Lista vazia !!\n\n");
        return 0;
    }
    int i = lista->inicio, j = (lista->fim + 1) % lista->tamanho;
    while (i != j) {
        if(lista->dados[i].ID == id) {
            return 1;
        }
        i = (i + 1) % lista->tamanho;
    }
    return 0;
}

void imprime(Descritor *lista) {
    if(lista == NULL) {
        printf("Lista não alocada !!\n\n");
        return;
    }
    if(lista->quantidade == 0) {
        printf("Lista Vazia !!\n\n");
        return;
    }
    int i = lista->inicio;
    while (i != (lista->fim + 1) % lista->tamanho) {
        printf("Nome: %s\n", lista->dados[i].nome);
        printf("ID: %d\n", lista->dados[i].ID);
        printf("Telefone: %s\n\n", lista->dados[i].telefone);
        i = (i + 1) % lista->tamanho;
    }
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

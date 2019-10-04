#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
    int data;
    int altura;
    struct tree *esq;
    struct tree *dir;
} Tree;

int fator(Tree **root) { //Fator
    if(*root == NULL) return 0;
    if((*root)->esq == NULL && (*root)->dir == NULL) return 0;
    if((*root)->esq == NULL) return (*root)->altura * -1;
    if((*root)->dir == NULL) return (*root)->altura;
    return (*root)->esq->altura - (*root)->dir->altura;
}

int maximo(Tree **esq, Tree **dir) {
    if(*esq == NULL && *dir == NULL) return 0;
    if(*esq == NULL) return (*dir)->altura + 1;
    if(*dir == NULL) return (*esq)->altura + 1;
    if((*esq)->altura > (*dir)->altura) return (*esq)->altura + 1;
    else return (*dir)->altura + 1;
}

//Rotações em Arvore Binaria Balanceada/AVL.
void rse (Tree **root) { //Rotação Simples a Esquerda
    if(*root == NULL) return;
    Tree *aux = *root;
    *root = (*root)->dir;
    aux->dir = (*root)->esq;
    (*root)->esq = aux;
    aux->altura = maximo(&aux->esq, &aux->dir);
    (*root)->altura = maximo(&(*root)->esq, &(*root)->dir);
}

void rsd (Tree **root) { //Rotação Simples a Direita
    if(*root == NULL) return;
    Tree *aux = *root;
    *root = (*root)->esq;
    aux->esq = (*root)->dir;
    (*root)->dir = aux;
    aux->altura = maximo(&aux->esq, &aux->dir);
    (*root)->altura = maximo(&(*root)->esq, &(*root)->dir);
}

void rdd(Tree **root) { //Rotação Dupla a Direita
    if(*root == NULL) return;
    rse(&(*root)->esq);
    rsd(&(*root));
}

void rde(Tree **root) { //Rotação Dupla a Esquerda
    if(*root == NULL) return;
    rsd(&(*root)->dir);
    rse(&(*root));
}

void corrige(Tree **root) {
    if(*root == NULL) return;
    int fat = fator(&(*root));
    if(fat < -1) {
        if(fator(&(*root)->dir) <= 0)
            rse(&(*root));
        else 
            rde(&(*root));
    } else if(fat > 1) {
        if(fator(&(*root)->esq) >= 0)
            rsd(&(*root));
        else 
            rdd(&(*root));
    }
}

Tree* maiorElemento(Tree *root) {
    if(root == NULL) return NULL;
    Tree *aux = root;
    while (aux->dir != NULL) aux = aux->dir;
    return aux;
}

Tree* menorElemento(Tree *root) {
    if(root == NULL) return NULL;
    Tree *aux = root;
    while(aux->esq != NULL) aux = aux->esq;
    return aux;
}

int qtdElementos(Tree **root) {
    if(*root == NULL) return 0;
    return 1 + qtdElementos(&(*root)->esq) + qtdElementos(&(*root)->dir);
}

Tree* removeMaior(Tree *root) {
    if(root == NULL) return NULL;
    if(root->dir == NULL) {
        Tree *aux = root->esq;
        free(root);
        return aux;
    }
    root->dir = removeMaior(root->dir);
    return root;
}

void mostraFolhas(Tree **root) {
    if(*root == NULL) return;
    if((*root)->esq == NULL && (*root)->dir == NULL)
        printf("%d ", (*root)->data);
    mostraFolhas(&(*root)->esq);
    mostraFolhas(&(*root)->dir);
}

int comprimentoRaizToN(Tree **root, int data) {
    if(*root == NULL) return -1;
    if(data == (*root)->data) return 0;
    if(data > (*root)->data) return 1 + comprimentoRaizToN(&(*root)->dir, data);
    else if(data < (*root)->data) return 1 + comprimentoRaizToN(&(*root)->esq, data);
}

void N_to_Raiz(Tree **root, int data) {
    if(*root == NULL) return;
    if((*root)->data == data) {
        printf("%d ", data);
        return;
    }
    if(data > (*root)->data) N_to_Raiz(&(*root)->dir, data);
    else N_to_Raiz(&(*root)->esq, data);
    printf("%d ", (*root)->data);
}

void destruir(Tree *root) {
    if(root == NULL) return;
    destruir(root->esq);
    destruir(root->dir);
    free(root);
}

Tree* removeNo(Tree *root, int data) {
    if(root == NULL) return 0;
    if(data == root->data) {
        if(root->esq == NULL) {
            Tree *aux = root;
            root = root->dir;
            free(aux);
            return root;
        } else if(root->dir == NULL) {
            Tree *aux = root;
            root = root->esq;
            free(aux);
            return root;
        } else if(root->esq != NULL && root->dir != NULL) {
            Tree *aux = maiorElemento(root->esq);
            root->data = aux->data;
            root->esq = removeNo(root->esq, root->data);
            return root;
        }
    }
    if(data > root->data) {
        root->dir = removeNo(root->dir, data);
        root->altura = maximo(&root->esq, &root->dir);
        return root;
    }
    else {
        root->esq = removeNo(root->esq, data);
        root->altura = maximo(&root->esq, &root->dir);
        return root;
    }
    
}

void addNode(Tree **root, int data) {
    if(*root == NULL) {
        *root = (Tree*) malloc (sizeof(Tree));
        (*root)->altura = 0;
        (*root)->data = data;
        (*root)->esq = NULL;
        (*root)->dir = NULL;
    }
    else if(data > (*root)->data) {
        addNode(&(*root)->dir, data);
    }
    else {
        addNode(&(*root)->esq, data);
    }
    (*root)->altura = maximo(&(*root)->esq, &(*root)->dir);
    corrige(&(*root));
}

void preOrder(Tree *root) {
    if(root == NULL) return;
    printf("%d [%d] (%d) \n", root->data, root->altura, fator(&root));
    preOrder(root->esq);
    preOrder(root->dir);
}

void inOrder(Tree *root) {
    if(root == NULL) return;
    inOrder(root->esq);
    printf("%d ", root->data);
    inOrder(root->dir);
}

void posOrder(Tree *root) {
    if(root == NULL) return;
    posOrder(root->esq);
    posOrder(root->dir);
    printf("%d ", root->data);
}

int menu();

int main () {

    Tree* root = NULL;
    int i, op;

    /*int input[12] = {50, 55, 40, 45, 12, 34, 22, 78, 10, 5, 1, 25};
    for(i = 0; i < 12; ++i) {
        addNode(&root, input[i]);
    }*/
    system("clear || cls");
    do {
        op = menu();
        switch (op) {
        case 0:
            system("clear || cls");
            printf("Falou :D\n");
        break;
        case 1: {
            int valor;
            system("clear || cls");
            printf("Informe um valor para inserir: ");
            scanf("%d", &valor);
            addNode(&root, valor);
        } break;
        case 2:
            system("clear || cls");
            printf("Pre..: ");
            preOrder(root);
            printf("\n");
        break;
        case 3:
            system("clear || cls");
            printf("In.: ");
            inOrder(root);
            printf("\n");
        break;
        case 4:
            system("clear || cls");
            printf("Pos..:");
            posOrder(root);
            printf("\n");
        break;
        case 5:
            system("clear || cls");
            printf("Numero de elementos: %d", qtdElementos(&root));
            printf("\n");
        break;
        case 6: {
            root *maior;
            system("clear || cls");
            maior = maiorElemento(root);
            if(maior != NULL) printf("Maior Elemento: %d\n", maior->data);
            else printf("Arvore Vazia !!\n");
        }
        break;
        case 7:{
            root *menor;
            system("clear || cls");
            menor = menorElemento(root);
            if(menor != NULL) printf("Menor Elemento: %d\n", menor->data);
            else printf("Arvore Vazia !!\n");
        }
        break;
        case 8:{
            system("clear || cls");
            if((root = removeMaior(root)) != NULL) printf("Maior elemento removido !!\n");
            else printf("Arvore Vazia !!\n");
        }
        break;
        case 9:
            system("clear || cls");
            printf("Folhas..: ");
            mostraFolhas(&root);
            printf("\n");
        break;
        case 10: {
            system("clear || cls");
            int n;
            printf("Informe um no: ");
            scanf("%d", &n);
            printf("Comprimento da raiz ate %d: %d\n", n, comprimentoRaizToN(&root, n));
        }
        break;
        case 11: {
            int n;
            system("clear || cls");
            printf("Informe um no: ");
            scanf("%d", &n);
            N_to_Raiz(&root, n);
            printf("\n");
        }
        break;
        case 12:
            system("clear || cls");
            printf("Altura da arvore: %d\n", root->altura);
        break;
        case 13: {
            system("clear || cls");
            int n;
            printf("Informe o no que deseja remover: ");
            scanf("%d", &n);
            if((root = removeNo(root, n)) != NULL) printf("No (%d) removido.\n", n);
            else printf("Falha ao remover o no (%d).\n", n);
        }
        break;
        case 14:
            system("clear || cls");
            destruir(root);
            root = NULL;
        break;
        case 15:
            system("clear || cls");
            rse(&root);
        break;
        case 16:
            system("clear || cls");
            rsd(&root);
        break;
        case 17:
            system("clear || cls");
            rde(&root);
        break;
        case 18:
            system("clear || cls");
            rdd(&root);
        break;
        default:
            printf("Opcao invalida");
        break;
        }
    } while (op != 0);

    return 0;
}

int menu() {
    int op;
    printf("0 - Sair\n");
    printf("1 - Inserir\n");
    printf("2 - Pre-Ordem\n");
    printf("3 - Em-Ordem\n");
    printf("4 - Pos-Ordem\n");
    printf("5 - Quantidade de elementos\n");
    printf("6 - Maior Elemento\n");
    printf("7 - Menor Elemento\n");
    printf("8 - Remove Maior Elemento\n");
    printf("9 - Exibe folhas\n");
    printf("10 - Comprimento da raiz ate qualquer no\n");
    printf("11 - Caminho do no ate a raiz\n");
    printf("12 - Altura da arvore\n");
    printf("13 - Remove qualquer no\n");
    printf("14 - Destroi\n");
    printf("15 - Rotacao simples a esquerda\n");
    printf("16 - Rotacao simples a direita\n");
    printf("17 - Rotacao dupla a esquerda\n");
    printf("18 - Rotacao dupla a direita\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &op);
    return op;
}
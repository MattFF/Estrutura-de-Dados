#ifndef LISTA_H
#define LISTA_H
#include <stdio.h>
#include <stdlib.h>

typedef struct cliente {
    int ID;
    char nome[50];
    char telefone[20];
} Cliente;

typedef struct descritor Descritor;
Descritor* criaLista(int);
int buscaPosicao(Descritor*, Cliente*, int);
int inserePosicao(Descritor*, Cliente, int);
int insereInicio(Descritor*, Cliente);
int insereFinal(Descritor*, Cliente);
int buscaElemento(Descritor*, int);
int removePosicao(Descritor*, int);
int desalocaLista(Descritor**);
int removeID(Descritor*, int);
int tamanhoLista(Descritor*);
int removeInicio(Descritor*);
int removeFinal(Descritor*);
int listaCheia(Descritor*);
int listaVazia(Descritor*);
void imprime(Descritor*);
Cliente novoCliente();

#endif
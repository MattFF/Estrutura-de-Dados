#ifndef FILA_H
#define FILA_H
#include <stdio.h>
#include <stdlib.h>

typedef struct cliente {
    int ID;
    char nome[50];
    char telefone[20];
} Cliente;

typedef struct descritor Descritor;
Descritor* criaFila(int);
int desalocaFila(Descritor **);
int tamanhoFila(Descritor *);
int filaCheia(Descritor *);
int filaVazia(Descritor *);
int insereFinal(Descritor *, Cliente);
int removeInicio(Descritor *);
void imprime(Descritor *);
Cliente novoCliente();

#endif
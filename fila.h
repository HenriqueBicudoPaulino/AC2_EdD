#ifndef FILA_H
#define FILA_H

#include "item.h"

typedef struct no_fila
{
  Item dado;
  struct no_fila *prox;
} NoFila;

typedef struct
{
  NoFila *inicio;
  NoFila *fim;
} Fila;

void cria_fila(Fila *f);

int fila_vazia(Fila *f);

int enfileira(Fila *f, Item i);

int desenfileira(Fila *f, Item *i);

void exibe_fila(Fila *f);

void libera_fila(Fila *f);

int quantidade_total_fila(Fila *f);

Item *busca_na_fila(Fila *f, int quantidade_necessaria);

#endif

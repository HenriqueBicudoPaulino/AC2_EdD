#ifndef ARVORE_H
#define ARVORE_H

#include "fila.h"

typedef struct no_arvore {
  int part_number;
  Fila fila_lotes;
  struct no_arvore *esq, *dir;
} NoArvore;

typedef NoArvore *Arvore;

void cria_arvore(Arvore *a);

NoArvore *busca_arvore(Arvore *a, int part_number);

int insere_arvore(Arvore *a, int part_number, Item item);

int utiliza_item_arvore(Arvore *a, int part_number, int quantidade);

int descarta_item_arvore(Arvore *a, int part_number, int quantidade);

void exibe_arvore(Arvore a);

void libera_arvore(Arvore *a);

#endif


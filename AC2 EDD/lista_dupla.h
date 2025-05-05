#ifndef LISTA_DUPLA_H
#define LISTA_DUPLA_H

#include "fila.h"

typedef struct no_lista {
  int part_number;
  Fila fila_lotes;
  struct no_lista *prox, *ant;
} NoLista;

typedef NoLista *Lista;

void cria_lista(Lista *l);
int lista_vazia(Lista *l);
NoLista *busca_lista(Lista *l, int part_number);
int insere_ordenado_lista(Lista *l, int part_number, Item item);
int utiliza_item_lista(Lista *l, int part_number, int quantidade);
int descarta_item_lista(Lista *l, int part_number, int quantidade);
void exibe_lista(Lista *l);
void libera_lista(Lista *l);

#endif


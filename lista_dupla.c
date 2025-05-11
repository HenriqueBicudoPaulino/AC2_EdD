#include "lista_dupla.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cria_lista(Lista *l) { *l = NULL; }

int lista_vazia(Lista *l) { return *l == NULL; }

NoLista *busca_lista(Lista *l, int part_number) {
  NoLista *aux = *l;
  while (aux && aux->part_number < part_number) {
    aux = aux->prox;
  }
  if (aux && aux->part_number == part_number) {
        return aux;
  }
  return NULL;
}

int insere_ordenado_lista(Lista *l, int part_number, Item item) {
  NoLista *aux = *l, *ant = NULL;
  while (aux && aux->part_number < part_number) {
    ant = aux;
    aux = aux->prox;
  }
  if (aux && aux->part_number == part_number) {
    return enfileira(&aux->fila_lotes, item);
  }
  NoLista *novo = (NoLista *)malloc(sizeof(NoLista));
  if (!novo)
    return 0;
  novo->part_number = part_number;
  cria_fila(&novo->fila_lotes);
  enfileira(&novo->fila_lotes, item);
  novo->prox = aux;
  novo->ant = ant;
  if (aux)
    aux->ant = novo;
  if (ant)
    ant->prox = novo;
  else
    *l = novo;
  return 1;
}

int utiliza_item_lista(Lista *l, int part_number, int quantidade) {
  NoLista *no = busca_lista(l, part_number);
  if (!no)
    return 0;
  NoFila *aux = no->fila_lotes.inicio;
  while (aux && quantidade > 0) {
    if (aux->dado.flag == 1 && esta_valido(aux->dado)) {
      int usar = (aux->dado.quantidade < quantidade) ? aux->dado.quantidade : quantidade;
      aux->dado.quantidade -= usar;
      quantidade -= usar;
    }
    aux = aux->prox;
  }
  return quantidade == 0;
}

int descarta_item_lista(Lista *l, int part_number, int quantidade) {
  return utiliza_item_lista(l, part_number, quantidade);
}

void exibe_lista(Lista *l) {
  NoLista *aux = *l;
  while (aux) {
    //printf("PartNumber: %d\n", aux->part_number);
    //exibe_fila(&aux->fila_lotes);
    aux = aux->prox;
  }
}

void libera_lista(Lista *l) {
  NoLista *aux;
  while (*l) {
    aux = *l;
    libera_fila(&aux->fila_lotes);
    *l = aux->prox;
    free(aux);
  }
}

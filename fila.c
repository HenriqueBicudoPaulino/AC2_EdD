#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

void cria_fila(Fila *f) { f->inicio = f->fim = NULL; }

int fila_vazia(Fila *f) { return f->inicio == NULL; }

int enfileira(Fila *f, Item i) {
  NoFila *novo = (NoFila *)malloc(sizeof(NoFila));
  if (!novo)
    return 0;
  novo->dado = i;
  novo->prox = NULL;
  if (fila_vazia(f)) {
    f->inicio = f->fim = novo;
  } else {
    f->fim->prox = novo;
    f->fim = novo;
  }
  return 1;
}

int desenfileira(Fila *f, Item *i) {
  if (fila_vazia(f))
    return 0;
  NoFila *tmp = f->inicio;
  *i = tmp->dado;
  f->inicio = tmp->prox;
  if (!f->inicio)
    f->fim = NULL;
  free(tmp);
  return 1;
}

void exibe_fila(Fila *f) {
  NoFila *aux = f->inicio;
  while (aux) {
    printf("%d (%s) [%s] - Qtde: %d\n", aux->dado.part_number,
           aux->dado.descricao, aux->dado.localizacao, aux->dado.quantidade);
    aux = aux->prox;
  }
}

void libera_fila(Fila *f) {
  Item i;
  while (!fila_vazia(f)) {
    desenfileira(f, &i);
  }
}

Item *busca_na_fila(Fila *f, int quantidade_necessaria) {
  NoFila *aux = f->inicio;
  while (aux) {
    if (aux->dado.quantidade >= quantidade_necessaria && aux->dado.flag == 1) {
      return &aux->dado;
    }
    aux = aux->prox;
  }
  return NULL;
}

// Nova fun��o para remover lotes com quantidade zero
void remove_lotes_zerados(Fila *f) {
  NoFila *aux = f->inicio, *ant = NULL;
  while (aux) {
    NoFila *prox = aux->prox;
    if (aux->dado.quantidade == 0) {
      if (ant) {
        ant->prox = prox;
      } else {
        f->inicio = prox;
      }
      if (!prox) {
        f->fim = ant;
      }
      free(aux);
    } else {
      ant = aux;
    }
    aux = prox;
  }
}

int quantidade_total_fila(Fila *f)
{
  int total = 0;
  NoFila *aux = f->inicio;
  while (aux)
  {
    if (aux->dado.flag == 1 && esta_valido(aux->dado))
      total += aux->dado.quantidade;
    aux = aux->prox;
  }
  return total;
}

#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>

void cria_arvore(Arvore *a) { *a = NULL; }

NoArvore *busca_arvore(Arvore *a, int part_number)
{
  if (!*a || (*a)->part_number == part_number)
    return *a;
  if (part_number < (*a)->part_number)
    return busca_arvore(&(*a)->esq, part_number);
  else
    return busca_arvore(&(*a)->dir, part_number);
}

int insere_arvore(Arvore *a, int part_number, Item item)
{
  if (!*a)
  {
    *a = (NoArvore *)malloc(sizeof(NoArvore));
    if (!*a)
      return 0;
    (*a)->part_number = part_number;
    cria_fila(&(*a)->fila_lotes);
    (*a)->esq = (*a)->dir = NULL;
  }
  if ((*a)->part_number == part_number)
  {
    return enfileira(&(*a)->fila_lotes, item);
  }
  if (part_number < (*a)->part_number)
    return insere_arvore(&(*a)->esq, part_number, item);
  else
    return insere_arvore(&(*a)->dir, part_number, item);
}

int utiliza_item_arvore(Arvore *a, int part_number, int quantidade)
{
  NoArvore *no = busca_arvore(a, part_number);
  if (!no)
    return 0;
  NoFila *aux = no->fila_lotes.inicio;
  while (aux && quantidade > 0)
  {
    if (aux->dado.flag == 1 && esta_valido(aux->dado))
    {
      int usar = (aux->dado.quantidade < quantidade) ? aux->dado.quantidade : quantidade;
      aux->dado.quantidade -= usar;
      quantidade -= usar;
    }
    aux = aux->prox;
  }
  return quantidade == 0;
}

int descarta_item_arvore(Arvore *a, int part_number, int quantidade)
{
  return utiliza_item_arvore(a, part_number, quantidade);
}

void exibe_arvore(Arvore a)
{
  if (!a)
    return;
  exibe_arvore(a->esq);
  // printf("PartNumber: %d\n", a->part_number);
  // exibe_fila(&a->fila_lotes);
  exibe_arvore(a->dir);
}

void libera_arvore(Arvore *a)
{
  if (!*a)
    return;
  libera_arvore(&(*a)->esq);
  libera_arvore(&(*a)->dir);
  libera_fila(&(*a)->fila_lotes);
  free(*a);
  *a = NULL;
}

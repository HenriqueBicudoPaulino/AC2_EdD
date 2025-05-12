#include "lista_dupla.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cria_lista(Lista *l) { *l = NULL; }

int lista_vazia(Lista *l) { return *l == NULL; }

NoLista *busca_lista(Lista *l, int part_number)
{
  NoLista *aux = *l;
  while (aux && aux->part_number < part_number)
  {
    aux = aux->prox;
  }
  if (aux && aux->part_number == part_number)
  {
    return aux;
  }
  return NULL;
}

int insere_ordenado_lista(Lista *l, int part_number, Item item)
{
  NoLista *aux = *l, *ant = NULL;
  while (aux && aux->part_number < part_number)
  {
    ant = aux;
    aux = aux->prox;
  }
  if (aux && aux->part_number == part_number)
  {
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

int utiliza_item_lista(Lista *l, int part_number, int quantidade)
{
  NoLista *no = busca_lista(l, part_number);
  if (!no || fila_vazia(&no->fila_lotes))
    return 0;

  // Verifica se a quantidade solicitada é maior que o total disponível
  int total_disponivel = quantidade_total_fila(&no->fila_lotes);
  if (quantidade > total_disponivel)
    return 0;

  // Processa os lotes, reduzindo quantidades e removendo lotes vazios
  int qtd_restante = quantidade;
  NoFila *aux = no->fila_lotes.inicio;
  while (aux && qtd_restante > 0)
  {
    if (aux->dado.flag == 1 && esta_valido(aux->dado))
    {
      int usar = (aux->dado.quantidade < qtd_restante) ? aux->dado.quantidade : qtd_restante;
      aux->dado.quantidade -= usar;
      qtd_restante -= usar;

      // Se a quantidade do lote for zero, remove o lote
      if (aux->dado.quantidade == 0)
      {
        Item temp;
        desenfileira(&no->fila_lotes, &temp);
        aux = no->fila_lotes.inicio; // Atualiza o ponteiro após remoção
      }
      else
      {
        aux = aux->prox;
      }
    }
    else
    {
      aux = aux->prox;
    }
  }
  return qtd_restante == 0;
}

int descarta_item_lista(Lista *l, int part_number, int quantidade)
{
  return utiliza_item_lista(l, part_number, quantidade);
}

void exibe_lista(Lista *l)
{
  NoLista *aux = *l;
  while (aux)
  {
    aux = aux->prox;
  }
}

void libera_lista(Lista *l)
{
  NoLista *aux;
  while (*l)
  {
    aux = *l;
    libera_fila(&aux->fila_lotes);
    *l = aux->prox;
    free(aux);
  }
}
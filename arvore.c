#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>

void cria_arvore(Arvore *a) { *a = NULL; }

NoArvore *busca_arvore(Arvore *a, int part_number) {
  if (!*a || (*a)->part_number == part_number)
    return *a;
  if (part_number < (*a)->part_number)
    return busca_arvore(&(*a)->esq, part_number);
  else
    return busca_arvore(&(*a)->dir, part_number);
}

int insere_arvore(Arvore *a, int part_number, Item item) {
  if (!*a) {
    *a = (NoArvore *)malloc(sizeof(NoArvore));
    if (!*a)
      return 0;
    (*a)->part_number = part_number;
    cria_fila(&(*a)->fila_lotes);
    (*a)->esq = (*a)->dir = NULL;
  }
  if ((*a)->part_number == part_number) {
    return enfileira(&(*a)->fila_lotes, item);
  }
  if (part_number < (*a)->part_number)
    return insere_arvore(&(*a)->esq, part_number, item);
  else
    return insere_arvore(&(*a)->dir, part_number, item);
}

// Helper function to find the minimum node in a subtree
NoArvore *minimo_arvore(Arvore *a) {
  if (!*a) return NULL;
  while ((*a)->esq) a = &(*a)->esq;
  return *a;
}

// Helper function to remove a node from the BST
void remove_no_arvore(Arvore *a, int part_number) {
  if (!*a) return;
  if (part_number < (*a)->part_number) {
    remove_no_arvore(&(*a)->esq, part_number);
  } else if (part_number > (*a)->part_number) {
    remove_no_arvore(&(*a)->dir, part_number);
  } else {
    // Node found
    NoArvore *no = *a;
    if (!no->esq) {
      *a = no->dir;
      libera_fila(&no->fila_lotes);
      free(no);
    } else if (!no->dir) {
      *a = no->esq;
      libera_fila(&no->fila_lotes);
      free(no);
    } else {
      // Node has two children
      NoArvore *min = minimo_arvore(&no->dir);
      no->part_number = min->part_number;
      no->fila_lotes = min->fila_lotes; // Transfer the queue
      remove_no_arvore(&no->dir, min->part_number); // Remove the minimum node
    }
  }
}

int utiliza_item_arvore(Arvore *a, int part_number, int quantidade) {
  NoArvore *no = busca_arvore(a, part_number);
  if (!no || fila_vazia(&no->fila_lotes))
    return 0;
    
  NoFila *aux = no->fila_lotes.inicio;
  
  int total_disponivel = quantidade_total_fila(&no->fila_lotes);
  if (quantidade > total_disponivel)
    return 0;
    
	int qtd_restante = quantidade;	
  while (aux && qtd_restante > 0) {
    if (aux->dado.flag == 1 && esta_valido(aux->dado)) {
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
    return qtd_restante == 0;
  }
  // Remove lotes com quantidade zero
  remove_lotes_zerados(&no->fila_lotes);
  // Se a fila de lotes ficou vazia, remove o nó da árvore
  if (fila_vazia(&no->fila_lotes)) {
    remove_no_arvore(a, part_number);
  }
  return quantidade == 0;
}

int descarta_item_arvore(Arvore *a, int part_number, int quantidade) {
  return utiliza_item_arvore(a, part_number, quantidade);
}

void exibe_arvore(Arvore a) {
  if (!a)
    return;
  exibe_arvore(a->esq);
  printf("PartNumber: %d\n", a->part_number);
  exibe_fila(&a->fila_lotes);
  exibe_arvore(a->dir);
}

void libera_arvore(Arvore *a) {
  if (!*a)
    return;
  libera_arvore(&(*a)->esq);
  libera_arvore(&(*a)->dir);
  libera_fila(&(*a)->fila_lotes);
  free(*a);
  *a = NULL;
}

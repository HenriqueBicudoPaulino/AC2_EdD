#include "fila_localizacoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cria_fila_localizacoes(FilaLocalizacoes *l) { *l = NULL; }

int insere_fila_localizacoes(FilaLocalizacoes *l, char *localizacao, Item item) {
    NoLocalizacao *aux = *l, *ant = NULL;
    while (aux && strcmp(aux->localizacao, localizacao) < 0) {
        ant = aux;
        aux = aux->prox;
    }
    if (aux && strcmp(aux->localizacao, localizacao) == 0) {
        return enfileira(&aux->fila_lotes, item);
    }
    NoLocalizacao *novo = (NoLocalizacao *)malloc(sizeof(NoLocalizacao));
    if (!novo) return 0;
    strcpy(novo->localizacao, localizacao);
    cria_fila(&novo->fila_lotes);
    enfileira(&novo->fila_lotes, item);
    novo->prox = aux;
    novo->ant = ant;
    if (aux) aux->ant = novo;
    if (ant) ant->prox = novo;
    else *l = novo;
    return 1;
}

void exibe_fila_localizacoes(FilaLocalizacoes *l) {
    NoLocalizacao *aux = *l;
    while (aux) {
        printf("Localizacao: %s\n", aux->localizacao);
        exibe_fila(&aux->fila_lotes);
        aux = aux->prox;
    }
}

void libera_fila_localizacoes(FilaLocalizacoes *l) {
    NoLocalizacao *aux;
    while (*l) {
        aux = *l;
        libera_fila(&aux->fila_lotes);
        *l = aux->prox;
        free(aux);
    }
}
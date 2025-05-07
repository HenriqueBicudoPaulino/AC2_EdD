#ifndef LISTA_LOCALIZACOES_H
#define LISTA_LOCALIZACOES_H

#include "fila.h"
#include <string.h>

typedef struct no_localizacao {
    char localizacao[4];
    Fila fila_lotes;
    struct no_localizacao *prox, *ant;
} NoLocalizacao;

typedef NoLocalizacao *ListaLocalizacoes;

void cria_lista_localizacoes(ListaLocalizacoes *l);

int insere_lista_localizacoes(ListaLocalizacoes *l, char *localizacao, Item item);

void exibe_lista_localizacoes(ListaLocalizacoes *l);

void libera_lista_localizacoes(ListaLocalizacoes *l);

#endif
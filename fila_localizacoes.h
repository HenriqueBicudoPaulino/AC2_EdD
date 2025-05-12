#ifndef FILA_LOCALIZACOES_H
#define FILA_LOCALIZACOES_H

#include "fila.h"
#include <string.h>

typedef struct no_localizacao
{
    char localizacao[4];
    Fila fila_lotes;
    struct no_localizacao *prox, *ant;
} NoLocalizacao;

typedef NoLocalizacao *FilaLocalizacoes;

void cria_fila_localizacoes(FilaLocalizacoes *l);

int insere_fila_localizacoes(FilaLocalizacoes *l, char *localizacao, Item item);

void exibe_fila_localizacoes(FilaLocalizacoes *l);

void libera_fila_localizacoes(FilaLocalizacoes *l);

#endif
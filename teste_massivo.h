#ifndef TESTE_MASSIVO_H
#define TESTE_MASSIVO_H

#include "lista_dupla.h"
#include "arvore.h"
#include "fila_localizacoes.h"
#include "item.h"
#include <time.h>

// Gera uma localização no formato LLN (A-Z A-Z 0-9) com base em um índice
void gerar_localizacao(char *loc, int idx);

// Executa o teste massivo, inserindo múltiplos itens em cada localização
void teste_massivo(Lista *lista, Arvore *arvore, FilaLocalizacoes *fila_loc);

#endif
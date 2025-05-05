#ifndef ITEM_H
#define ITEM_H

typedef struct {
  int part_number;		 //númerico
  char descricao[100];
  char data_entrada[11]; // formato DD/MM/AAAA
  char localizacao[4];   // Ex: AA1
  int shelf_life;        // em meses
  int flag;             // 1 = liberado, 0 = retido
  int quantidade;        // quantidade no lote
} Item;

int esta_valido(Item item);

void imprime_item(Item item);

int valida_localizacao(char *localizacao);

#endif

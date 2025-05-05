#ifndef ITEM_H
#define ITEM_H

typedef struct {
  int part_number;
  char descricao[100];
  char data_entrada[11]; // formato DD/MM/AAAA
  char localizacao[4];   // Ex: AA1
  int shelf_life;        // em dias
  int flag;              // 1 = liberado, 0 = retido
  int quantidade;        // quantidade no lote
} Item;

#endif


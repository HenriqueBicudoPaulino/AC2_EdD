#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "item.h"

int esta_valido(Item item) {
    int dia, mes, ano;

    if (sscanf(item.data_entrada, "%d/%d/%d", &dia, &mes, &ano) != 3) {
        fprintf(stderr, "Data inválida: %s\n", item.data_entrada);
        return 0;
    }

    time_t t = time(NULL);
    
    struct tm *data_atual = localtime(&t);
    
    int ano_atual = data_atual->tm_year + 1900;
    
    int mes_atual = data_atual->tm_mon + 1;

    int meses_passados = (ano_atual - ano) * 12 + (mes_atual - mes);

    return meses_passados < item.shelf_life ? 1 : 0;
}
void imprime_item(Item item) {
    printf("Part Number: %d\n", item.part_number);
    printf("Descricao: %s\n", item.descricao);
    printf("Data de Entrada: %s\n", item.data_entrada);
    printf("Localizacao: %s\n", item.localizacao);
    printf("Shelf Life (meses): %d\n", item.shelf_life);
    printf("Flag: %s\n", item.flag == 1 ? "Liberado" : "Retido");
    printf("Quantidade: %d\n", item.quantidade);
}


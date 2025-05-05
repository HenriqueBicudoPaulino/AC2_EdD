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


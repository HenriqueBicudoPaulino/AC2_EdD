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

    // Ajuste para considerar o dia
    int expired = 0;
    if (ano_atual > ano) {
        expired = (ano_atual - ano) * 12 + mes_atual - mes > item.shelf_life;
    } else if (ano_atual == ano) {
        if (mes_atual > mes) {
            expired = mes_atual - mes > item.shelf_life;
        } else if (mes_atual == mes) {
            expired = data_atual->tm_mday > dia;
        }
    }
    return !expired;
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

int valida_localizacao(char *localizacao) {
    if (strlen(localizacao) != 3) return 0;
    if (localizacao[0] < 'A' || localizacao[0] > 'D') return 0;
    if (localizacao[1] < 'A' || localizacao[1] > 'T') return 0;
    if (localizacao[2] < '1' || localizacao[2] > '5') return 0;
    return 1;
}

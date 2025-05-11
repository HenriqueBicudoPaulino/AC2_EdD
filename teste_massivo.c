#include "teste_massivo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Gera uma localização única no formato LLN (ex.: AA0 até ZZ9)
void gerar_localizacao(char *loc, int idx) {
    int digit = idx % 10;         // Último caractere: 0-9 (base 10)
    int k = idx / 10;             // Divide para o próximo nível
    int letra2 = k % 26;          // Segunda letra: A-Z (base 26)
    k = k / 26;                   // Divide novamente
    int letra1 = k % 26;          // Primeira letra: A-Z (base 26)
    loc[0] = 'A' + letra1;        // Define primeira letra
    loc[1] = 'A' + letra2;        // Define segunda letra
    loc[2] = '0' + digit;         // Define número
    loc[3] = '\0';                // Termina a string
}

// Realiza um teste massivo inserindo 100 itens por localização
void teste_massivo(Lista *lista, Arvore *arvore, FilaLocalizacoes *fila_loc) {
    // Constantes configuráveis
    const int total_prateleiras = 26 * 26 * 10; // Total de localizações: 17.576 (A-Z A-Z 0-9)
    const int itens_por_local = 100;            // Número de itens por localização

    int i, j;
    clock_t ini, fim;

    // Loop sobre todas as localizações possíveis
    for (i = 0; i < total_prateleiras; i++) {
        char localizacao[4];
        gerar_localizacao(localizacao, i);      // Gera a localização atual
        int part_number = i + 1;                // Número de peça único para cada localização

        // Insere 100 itens para este part_number nesta localização
        for (j = 0; j < itens_por_local; j++) {
            Item novo;
            novo.part_number = part_number;
            sprintf(novo.descricao, "Material %d - Lote %d", part_number, j + 1); // Descrição única por lote
            strcpy(novo.localizacao, localizacao);
            novo.shelf_life = 12;      // Vida útil em meses (ajustável)
            novo.flag = 1;             // Item liberado
            novo.quantidade = 1;       // Quantidade por item (ajustável)

            // Define a data de entrada como a data atual
            time_t t = time(NULL);
            struct tm *data_atual = localtime(&t);
            snprintf(novo.data_entrada, sizeof(novo.data_entrada), "%02d/%02d/%04d",
                     data_atual->tm_mday, data_atual->tm_mon + 1, data_atual->tm_year + 1900);

            // Inserção na lista com medição de tempo
            ini = clock();
            insere_ordenado_lista(lista, novo.part_number, novo);
            fim = clock();
            printf("Inserido na Lista em %.5lfs (PN: %d, Loc: %s)\n",
                   (double)(fim - ini) / CLOCKS_PER_SEC, novo.part_number, novo.localizacao);

            // Inserção na árvore com medição de tempo
            ini = clock();
            insere_arvore(arvore, novo.part_number, novo);
            fim = clock();
            printf("Inserido na Arvore em %.5lfs (PN: %d, Loc: %s)\n",
                   (double)(fim - ini) / CLOCKS_PER_SEC, novo.part_number, novo.localizacao);

            // Inserção na fila de localizações
            insere_fila_localizacoes(fila_loc, novo.localizacao, novo);
        }
    }

    // Testes adicionais para verificar o funcionamento
    int part_number_teste = total_prateleiras / 2; // Testa um part_number intermediário
    ini = clock();
    busca_lista(lista, part_number_teste);
    fim = clock();
    printf("Busca na Lista em %.5lfs (PN: %d)\n", (double)(fim - ini) / CLOCKS_PER_SEC, part_number_teste);

    ini = clock();
    busca_arvore(arvore, part_number_teste);
    fim = clock();
    printf("Busca na Arvore em %.5lfs (PN: %d)\n", (double)(fim - ini) / CLOCKS_PER_SEC, part_number_teste);
}
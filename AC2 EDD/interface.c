#include <stdio.h>
#include <time.h>
#include "interface.h"

void menu(Lista *lista, Arvore *arvore) {
    int opcao;
    Item novo;
    clock_t ini, fim;
    int part_number, quantidade;

    do {
        printf("\n1 - Buscar\n2 - Inserir\n3 - Utilizar\n4 - Descartar\n0 - Sair\nOpcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o Part Number: ");
                scanf("%d", &part_number);

                ini = clock();
                busca_lista(lista, part_number);
                fim = clock();
                printf("Tempo Lista: %.5lfs\n", (double)(fim - ini) / CLOCKS_PER_SEC);

                ini = clock();
                busca_arvore(arvore, part_number);
                fim = clock();
                printf("Tempo Arvore: %.5lfs\n", (double)(fim - ini) / CLOCKS_PER_SEC);
                break;

            case 2:
                printf("Part Number: "); scanf("%d", &novo.part_number);
                printf("Descricao: "); scanf("%s", novo.descricao);
                printf("Data Entrada (DD/MM/AAAA): "); scanf("%s", novo.data_entrada);
                printf("Localizacao (Ex: AB1): "); scanf("%s", novo.localizacao);
                printf("Shelf Life (dias): "); scanf("%d", &novo.shelf_life);
                printf("Flag (1=liberado / 0=retido): "); scanf("%d", &novo.flag);
                printf("Quantidade: "); scanf("%d", &novo.quantidade);

                ini = clock();
                insere_ordenado_lista(lista, novo.part_number, novo);
                fim = clock();
                printf("Inserido na Lista em %.5lfs\n", (double)(fim - ini) / CLOCKS_PER_SEC);

                ini = clock();
                insere_arvore(arvore, novo.part_number, novo);
                fim = clock();
                printf("Inserido na Arvore em %.5lfs\n", (double)(fim - ini) / CLOCKS_PER_SEC);
                break;

            case 3:
                printf("Digite Part Number e Quantidade a Utilizar: ");
                scanf("%d %d", &part_number, &quantidade);

                ini = clock();
                utiliza_item_lista(lista, part_number, quantidade);
                fim = clock();
                printf("Utilizaado na Lista em %.5lfs\n", (double)(fim - ini) / CLOCKS_PER_SEC);

                ini = clock();
                utiliza_item_arvore(arvore, part_number, quantidade);
                fim = clock();
                printf("Utilizado na Arvore em %.5lfs\n", (double)(fim - ini) / CLOCKS_PER_SEC);
                break;

            case 4:
                printf("Digite Part Number e Quantidade a Descartar: ");
                scanf("%d %d", &part_number, &quantidade);

                ini = clock();
                descarta_item_lista(lista, part_number, quantidade);
                fim = clock();
                printf("Descartado na Lista em %.5lfs\n", (double)(fim - ini) / CLOCKS_PER_SEC);

                ini = clock();
                descarta_item_arvore(arvore, part_number, quantidade);
                fim = clock();
                printf("Descartado na Arvore em %.5lfs\n", (double)(fim - ini) / CLOCKS_PER_SEC);
                break;

            case 0:
                printf("Encerrando...\n");
                break;
        }
    } while (opcao != 0);
}

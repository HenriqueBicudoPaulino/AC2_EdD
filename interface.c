#include <stdio.h>
#include <time.h>
#include "interface.h"
#include "item.h"  // Para imprime_item e valida_localizacao

void menu(Lista *lista, Arvore *arvore) {
    int opcao;
    Item novo;
    clock_t ini, fim;
    int part_number, quantidade;

    do {
        printf("========================================\n");
		printf("                 MENU                   \n");
		printf("========================================\n");
		printf("1 - Buscar\n");
		printf("2 - Inserir\n");
		printf("3 - Utilizar\n");
		printf("4 - Descartar\n");
		printf("0 - Sair\n");
		printf("Selecione uma opcao: ");

        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nDigite o Part Number: ");
                scanf("%d", &part_number);
				
                ini = clock();
                NoLista *resultado_lista = busca_lista(lista, part_number);
                fim = clock();
                printf("\nTempo Lista: %.5lfs\n", (double)(fim - ini) / CLOCKS_PER_SEC);
                if (resultado_lista && !fila_vazia(&resultado_lista->fila_lotes)) {
                    printf("\nItem encontrado na lista:\n");
                    Item result_lista = resultado_lista->fila_lotes.inicio->dado;
                    imprime_item(result_lista);
                } else {
                    printf("\nItem nao encontrado na lista ou fila vazia.\n");
                }

                ini = clock();
                NoArvore *resultado_arvore = busca_arvore(arvore, part_number);
                fim = clock();
                printf("\nTempo Arvore: %.5lfs\n", (double)(fim - ini) / CLOCKS_PER_SEC);
                if (resultado_arvore && !fila_vazia(&resultado_arvore->fila_lotes)) {
                    printf("Item encontrado na arvore:\n");
                    Item result_arvore = resultado_arvore->fila_lotes.inicio->dado;
                    imprime_item(result_arvore);
                } else {
                    printf("Item nao encontrado na arvore ou fila vazia.\n");
                }
                break;

            case 2:
                printf("\nPart Number: "); scanf("%d", &novo.part_number);
                printf("Descricao: "); scanf("%s", novo.descricao);
                do {
                    printf("Localizacao (Ex: AB1): "); scanf("%s", novo.localizacao);
                    if (!valida_localizacao(novo.localizacao)) {
                        printf("\nLocalizacao invalida. Tente novamente.\n");
                    }
                } while (!valida_localizacao(novo.localizacao));
                printf("Shelf Life (meses): "); scanf("%d", &novo.shelf_life);
                printf("Flag (1=liberado / 0=retido): "); scanf("%d", &novo.flag);
                printf("Quantidade: "); scanf("%d", &novo.quantidade);
				
				// Data de entrada como data atual
				time_t t = time(NULL);
			    struct tm *data_atual = localtime(&t);
			    snprintf(novo.data_entrada, sizeof(novo.data_entrada), "%02d/%02d/%04d",
             	data_atual->tm_mday, data_atual->tm_mon + 1, data_atual->tm_year + 1900);
             	
                ini = clock();
                insere_ordenado_lista(lista, novo.part_number, novo);
                fim = clock();
                printf("\nInserido na Lista em %.5lfs\n", (double)(fim - ini) / CLOCKS_PER_SEC);

                ini = clock();
                insere_arvore(arvore, novo.part_number, novo);
                fim = clock();
                printf("Inserido na Arvore em %.5lfs\n", (double)(fim - ini) / CLOCKS_PER_SEC);
                break;

            case 3:
                printf("\nDigite Part Number e Quantidade a Utilizar: ");
                scanf("%d %d", &part_number, &quantidade);
				
                ini = clock();
                utiliza_item_lista(lista, part_number, quantidade);
                fim = clock();
                printf("\nUtilizado na Lista em %.5lfs\n", (double)(fim - ini) / CLOCKS_PER_SEC);

                ini = clock();
                utiliza_item_arvore(arvore, part_number, quantidade);
                fim = clock();
                printf("Utilizado na Arvore em %.5lfs\n", (double)(fim - ini) / CLOCKS_PER_SEC);
                break;

            case 4:
                printf("\nDigite Part Number e Quantidade a Descartar: ");
                scanf("%d %d", &part_number, &quantidade);

                ini = clock();
                descarta_item_lista(lista, part_number, quantidade);
                fim = clock();
                printf("\nDescartado na Lista em %.5lfs\n", (double)(fim - ini) / CLOCKS_PER_SEC);

                ini = clock();
                descarta_item_arvore(arvore, part_number, quantidade);
                fim = clock();
                printf("Descartado na Arvore em %.5lfs\n", (double)(fim - ini) / CLOCKS_PER_SEC);
                break;

            case 0:
                printf("\n\nEncerrando...\n\n");
                break;
        }
    } while (opcao != 0);
}

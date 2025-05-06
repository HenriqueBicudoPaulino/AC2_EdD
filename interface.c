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
        printf("\n1 - Buscar\n2 - Inserir\n3 - Utilizar\n4 - Descartar\n0 - Sair\nOpcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o Part Number: ");
                scanf("%d", &part_number);
				
                ini = clock();
                NoLista *resultado_lista = busca_lista(lista, part_number);
                fim = clock();
                printf("Tempo Lista: %.5lfs\n", (double)(fim - ini) / CLOCKS_PER_SEC);
                if (resultado_lista && !fila_vazia(&resultado_lista->fila_lotes)) {
                    printf("Item encontrado na lista:\n");
                    Item result_lista = resultado_lista->fila_lotes.inicio->dado;
                    imprime_item(result_lista);
                } else {
                    printf("Item não encontrado na lista ou fila vazia.\n");
                }

                ini = clock();
                NoArvore *resultado_arvore = busca_arvore(arvore, part_number);
                fim = clock();
                printf("Tempo Arvore: %.5lfs\n", (double)(fim - ini) / CLOCKS_PER_SEC);
                if (resultado_arvore && !fila_vazia(&resultado_arvore->fila_lotes)) {
                    printf("Item encontrado na arvore:\n");
                    Item result_arvore = resultado_arvore->fila_lotes.inicio->dado;
                    imprime_item(result_arvore);
                } else {
                    printf("Item não encontrado na arvore ou fila vazia.\n");
                }
                break;

            case 2:
                printf("Part Number: "); scanf("%d", &novo.part_number);
                printf("Descricao: "); scanf("%s", novo.descricao);
                do {
                    printf("Localizacao (Ex: AB1): "); scanf("%s", novo.localizacao);
                    if (!valida_localizacao(novo.localizacao)) {
                        printf("Localizacao invalida. Tente novamente.\n");
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
                printf("Utilizado na Lista em %.5lfs\n", (double)(fim - ini) / CLOCKS_PER_SEC);

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

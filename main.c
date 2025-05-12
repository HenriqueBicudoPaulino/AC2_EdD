#include "interface.h"
#include "lista_dupla.h"
#include "arvore.h"

int main()
{
    Lista lista;   // Lista duplamente encadeada
    Arvore arvore; // �rvore bin�ria de busca

    // Inicializa as estruturas de dados
    cria_lista(&lista);
    cria_arvore(&arvore);

    // Chama o menu para interagir com o usu�rio
    menu(&lista, &arvore);

    // Libera a mem�ria alocada
    libera_lista(&lista);
    libera_arvore(&arvore);

    return 0;
}

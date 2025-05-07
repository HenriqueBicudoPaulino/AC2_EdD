#include "interface.h"
#include "lista_dupla.h"
#include "arvore.h"

int main() {
    Lista lista;       // Lista duplamente encadeada
    Arvore arvore;     // Árvore binária de busca

    // Inicializa as estruturas de dados
    cria_lista(&lista);
    cria_arvore(&arvore);

    // Chama o menu para interagir com o usuário
    menu(&lista, &arvore);

    // Libera a memória alocada
    libera_lista(&lista);
    libera_arvore(&arvore);

    return 0;
}

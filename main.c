#include "interface.h"

int main() {
  Lista lista;
  Arvore arvore;
  cria_lista(&lista);
  cria_arvore(&arvore);

  menu(&lista, &arvore);

  libera_lista(&lista);
  libera_arvore(&arvore);

  return 0;
}

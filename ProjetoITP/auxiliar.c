#include <stdio.h>
#include <stdlib.h>

void imprimeMenu(){
  printf("\n-=-=-=-=-=-=-MENU=-=-=-=-=-=-\n");
  printf("Escolha uma opção abaixo\n\n");
  printf("(1) CRIAR NOVA TABELA\n");
  printf("(2) ADICIONAR DADOS A UMA TABELA\n");
  printf("(3) VISUALIZAR DADOS DA TABELA\n");
  printf("(4) LISTAR TABELAS\n");
  printf("(5) PESQUISAR VALOR EM UMA TABELA\n");
  printf("(6) APAGAR LINHA\n");
  printf("(7) APAGAR TABELA EXISTENTE\n");
  printf("(8) ENCERRAR SESSÃO\n");
  printf(">> ");
}

char *lerString(char *str){
  char ch;
  int i;

  if (str == NULL) {
    str = (char *)malloc(1 * sizeof(char));
    if (str == NULL) {
      printf("Erro na alocação dinâmica");
      free(str);
      return NULL;
    }
  }

  i = 0;
  ch = getchar();
  if(ch == '\n'){
    ch = getchar();
  }
  while(ch != '\n'){
    str[i] = ch;
    i++;
    str = realloc(str, (i+1) * sizeof(char));
    if(str == NULL){
      printf("Erro na realocacao dinamica");
      free(str);
      return NULL;
    }

    ch = getchar();
  }

  str[i] = '\0';
  return str;
}

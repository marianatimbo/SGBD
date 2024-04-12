#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"
#include "arquivos.h"
#include "auxiliar.h"


Tabela *criarTabela(Tabela *tabela, int *tam) {
  //aloca espaço para a tabela;
  tabela = (Tabela *)realloc(tabela, (*tam + 1) * sizeof(Tabela));
  if (tabela == NULL) {
    printf("Erro na realocação dinâmica\n");
    return NULL;
  }
  printf("\n=-=-=-=-=CRIAR TABELA=-=-=-=-=\n");

  printf("\nDigite o nome da tabela:\n");
  printf(">> ");
  tabela[*tam].nome = lerString(tabela[*tam].nome);
  
  //verifica se o nome da tabela já existe;
  for (int i = 0; i < *tam; i++) {
    if (strcmp(tabela[*tam].nome, tabela[i].nome) == 0) {
      printf("Essa tabela já existe!\n");
      printf("Digite outro nome para essa tabela:\n");
      printf(">> ");
      tabela[*tam].nome = lerString(tabela[*tam].nome);
      i = -1;
    }
  }

  printf("Digite um nome de coluna para a chave primária da tabela:\n");
  printf(">> ");
  tabela[*tam].chave = lerString(tabela[*tam].chave);
  
  //verifica se o nome de coluna para chave primaria já existe;
  for (int i = 0; i < *tam; i++) {
    if (strcmp(tabela[*tam].chave, tabela[i].chave) == 0) {
      printf("Essa chave primária já existe!\n");
      printf("Digite outra chave primária para essa tabela:\n");
      printf(">> ");
      tabela[*tam].chave = lerString(tabela[*tam].chave);
    }
  }

  printf("Digite o número de colunas da tabela %s:\n", tabela[*tam].nome);
  printf(">> ");
  scanf("%d", &tabela[*tam].qnt_colunas);
  while (tabela[*tam].qnt_colunas < 1) {
    printf("A tabela precisa ter uma quantidade de colunas maior que zero!\n");
    printf("Digite o número de colunas da tabela %s:\n", tabela[*tam].nome);
    printf(">> ");
    scanf("%d", &tabela[*tam].qnt_colunas);
  }

  //preenche a coluna 1 para ser a coluna chave
  tabela[*tam].qnt_colunas += 1;
  tabela[*tam].colunas =
      (Coluna *)malloc(tabela[*tam].qnt_colunas * sizeof(Coluna));
  if (tabela[*tam].colunas == NULL) {
    printf("Erro na realocação dinâmica\n");
    return NULL;
  }
  tabela[*tam].colunas[0].nome = tabela[*tam].chave;

  //preenche as colunas com o nome das colunas;
  for (int i = 1; i < tabela[*tam].qnt_colunas; i++) {
    printf("Digite o nome da coluna %d:\n", i);
    printf(">> ");
    tabela[*tam].colunas[i].nome = lerString(tabela[*tam].colunas[i].nome);
    printf("Digite o tipo de dado da coluna %d:\n", i);
    printf("(1) int | (2) float | (3) char | (4) String\n");
    printf(">> ");
    scanf("%d", &tabela[*tam].colunas[i].tipo);
  }

  //contador de linhas
  tabela[*tam].qnt_linhas = 0;

  //salva as informacoes da tabela no arquivo da propria;
  salvarTabela(tabela[*tam]);

  printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
  printf("Tabela %s criada com sucesso!\n", tabela[*tam].nome);
  printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
  
  //atualiza o tamanho da tabela;
  *tam = *tam + 1;
  return tabela;
}

Tabela *listarTabelas(Tabela *tabela, int *tam) {
  printf("\n=-=-=-=-=LISTAR TABELAS=-=-=-=-=\n");

  if (*tam == 0) {
    printf("Não há nenhuma tabela criada no sistema!\n");
    printf("Deseja criar uma tabela?\n");
    printf("1 - Sim\n");
    printf("2 - Nao\n");
    printf(">> ");
    int op;
    scanf("%d", &op);
    
    while (op != 1 && op != 2) {
      printf("Opção inválida, tente novamente!\n");
      printf(">> ");
      scanf("%d", &op);
    }

    if (op == 1) {
      tabela = criarTabela(tabela, tam);
      printf("\n-=-=-=- VIZUALIZAR TABELAS -=-=-=-\n");
    }
    else if (op == 2) {
      printf("Voltando ao menu principal...\n");
      return tabela;
    }
  } 
  printf("\nTabelas existentes:\n");
  for (int i = 0; i < *tam; i++) {
    printf("Tabela %d: %s\n", i + 1, tabela[i].nome);
  }

  return tabela;
}

Tabela *apagarTabela(Tabela *tabela, int *tam) {
  printf("\n=-=-=-=-=APAGAR TABELA=-=-=-=-=-=\n");
  if (*tam == 0) {
    printf("Não há nenhuma tabela criada no sistema!\n");
    printf("Deseja criar uma tabela?\n");
    printf("1 - Sim\n");
    printf("2 - Nao\n");
    printf(">> ");
    int op;
    scanf("%d", &op);

    while (op != 1 && op != 2) {
      printf("Opção inválida, tente novamente!\n");
      printf(">> ");
      scanf("%d", &op);
    }

    if (op == 1) {
      tabela = criarTabela(tabela, tam);
      printf("\n=-=-=-=-=APAGAR TABELA=-=-=-=-=\n");
    }
    else if (op == 2) {
      printf("Voltando ao menu principal...\n");
      return tabela;
    }
  }

  printf("\nDigite o nome da tabela que deseja apagar:\n");
  printf(">> ");
  char* nome_tab = NULL;  
  nome_tab = lerString(nome_tab);

  for(int i = 0; i < *tam; i++){
    if(strcmp(nome_tab, tabela[i].nome) == 0){
  
      for (int j = i; j < (*tam - 1); j++) {
        tabela[j] = tabela[j + 1];
      }
      (*tam)--;
      
      tabela = (Tabela *)realloc(tabela, (*tam) * sizeof(Tabela));

      char caminho[21 + strlen(nome_tab) + 1];
      sprintf(caminho, "arquivos/tabelas/%s.txt", nome_tab);

      int removed = remove(caminho);

      printf("%s", caminho);

      if (removed == 0) {
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("Tabela apagada com sucesso!\n");
        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        
      } else {
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("Algum erro ocorreu!\n");
        printf("Erro foi: %s\n", strerror(errno));
        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
      }
    }
    else if(i == *tam-1){
      printf("Tabela não encontrada!\n");
    }
  }
  
  free(nome_tab);
  return tabela;
}

void liberarMemoria(Tabela *tabela, int *tam) {
  
  for (int i = 0; i < *tam; i++) {
    //libera memoria para o nome da tabela;
    free(tabela[i].nome);
    for (int j = 0; j < tabela[i].qnt_colunas; j++) {
      //para o nome da coluna;
      free(tabela[i].colunas[j].nome);
      for (int k = 0; k < tabela[i].qnt_linhas; k++) {
        //para cada dado da coluna;
        free(tabela[i].colunas[j].dados[k].nome);
      }
      free(tabela[i].colunas[j].dados);
    }
    free(tabela[i].colunas);
  }
  free(tabela);
}
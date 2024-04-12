#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "definitions.h"
#include "arquivos.h"
#include "auxiliar.h"
#include "tabelas.h"

Tabela *adicionarDados(Tabela *tabela, int* tam){
  printf("\n=-=-=-=-=ADICIONAR DADOS=-=-=-=-=-=\n");

  //se não houver tabela criada;
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
      //volta para a funcao para adicionar dados;
      printf("\n=-=-=-=-= ADICONAR DADOS =-=-=-=-=\n");
    }
    else if (op == 2) {
      printf("Voltando ao menu principal...\n");
      return tabela;
    }
  }
  
  //se ja houver tabela criada;
  printf("\nDigite o nome da tabela que deseja adicionar dados:\n");
  printf(">> ");
  char* nome_tab = NULL;  
  nome_tab = lerString(nome_tab);

  //busca tabela;
  for(int i = 0; i < *tam; i++){
    if(strcmp(nome_tab, tabela[i].nome) == 0){
      int l = tabela[i].qnt_linhas;
      printf("Digite uma chave primária para essa linha, sendo do tipo inteiro sem sinal\n");
      printf(">> ");
        
      tabela[i].colunas[0].dados = (Dado *)realloc(tabela[i].colunas[0].dados, (l + 1) * sizeof(Dado));
      tabela[i].colunas[0].dados[l].nome = NULL;
      tabela[i].colunas[0].dados[l].nome = lerString(tabela[i].colunas[0].dados[l].nome);

      //verifica se a chave ja existe em alguma outra linha;
      for(int k = 0; k < tabela[i].qnt_linhas; k++){
        if(strcmp(tabela[i].colunas[0].dados[l].nome, tabela[i].colunas[0].dados[k].nome) == 0){
          printf("Essa chave primária já existe!\n");
          printf("Digite outra chave primária para a linha\n");
          printf(">> ");
          tabela[i].colunas[0].dados[l].nome = NULL;
          tabela[i].colunas[0].dados[l].nome = lerString(tabela[i].colunas[0].dados[l].nome);
          k = -1;
         }
      }
      //reccebe os dados;
      printf("Digite o dado da %dª linha para cada coluna:\n", l + 1);
      for(int j = 1; j < tabela[i].qnt_colunas; j++){
        printf(">> Coluna %s: ", tabela[i].colunas[j].nome);
        tabela[i].colunas[j].dados = (Dado *)realloc(tabela[i].colunas[j].dados, (l + 1) * sizeof(Dado));
        tabela[i].colunas[j].dados[l].nome = lerString(tabela[i].colunas[j].dados[l].nome);
      }

      //salva os dados no arquivo dela;
      salvarDados(tabela[i]);
        
      printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
      printf("Dados adicionados com sucesso!\n");
      printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

      //aumentar o numero de linhas;
      tabela[i].qnt_linhas = l + 1;
      break;
    }
    else if(i == *tam-1){
      printf("Tabela não encontrada!\n");
    }
  }

  free(nome_tab); 
  return tabela;
}

Tabela* visualizarDados(Tabela *tabela, int* tam){
  printf("\n=-=-=-=-=VISUALIZAR DADOS=-=-=-=-=\n");
  
  //se nao ha tabela criada;
  if(*tam == 0){
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
      printf("\n=-=-=-=-=VISUALIZAR DADOS=-=-=-=-=\n");
    }
    else if (op == 2) {
      printf("Voltando ao menu principal...\n");
      return tabela;
    }
  }
  
  printf("Digite o nome da tabela que deseja visualizar dados:\n");
  printf(">> ");
  char* nome_tab = NULL;
  nome_tab = lerString(nome_tab);
  
  for(int i = 0; i < *tam; i++){
    if(strcmp(nome_tab, tabela[i].nome) == 0){
      if(tabela[i].qnt_linhas == 0){
        printf("Não há dados nessa tabela!\n");
        printf("Deseja adicionar dados?\n");
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
          printf("\n=-=-=-=-=VISUALIZAR DADOS=-=-=-=-=\n");
        }
        else if (op == 2) {
          printf("Voltando ao menu principal...\n");
          return tabela;
        }
      }
      
      //imprime os dados
      printf("--------- %s ---------\n", tabela[i].nome);
      printf("Linhas: ");
      for(int j = 0; j < tabela[i].qnt_colunas; j++){
        printf("|");
        printf(" %s |", tabela[i].colunas[j].nome);
      }
      printf("\n");
      for(int j = 0; j < tabela[i].qnt_linhas; j++){
        printf("Linha %d: ", j + 1);
        for(int k = 0; k < tabela[i].qnt_colunas; k++){
          printf("|");
          printf(" %s |", tabela[i].colunas[k].dados[j].nome);
        }
        printf("\n");
      }
      break;
    }
    else{
      printf("Tabela não encontrada!\n");
    }
  }

  free(nome_tab);  
  return tabela;
}


Tabela* pesquisarValor(Tabela *tabela, int* tam){
  printf("\n=-=-=-=-=PESQUISAR VALOR=-=-=-=-=\n");
  if(*tam == 0){
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
      printf("\n=-=-=-=-= PESQUISAR DADOS =-=-=-=\n");
    }
    else if (op == 2) {
      printf("Voltando ao menu principal...\n");
      return tabela;
    }
  }
  printf("Digite o nome da tabela que deseja pesquisar um valor:\n");
  printf(">> ");
  char* nome_tab = NULL;
  nome_tab = lerString(nome_tab);
    
  for(int i = 0; i < *tam; i++){
    if(strcmp(nome_tab, tabela[i].nome) == 0){
      //if nao tiver dados
      if(tabela[i].qnt_linhas == 0){
        printf("Não há dados nessa tabela!\n");
        printf("Deseja adicionar dados?\n");
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
          tabela = adicionarDados(tabela, tam);
          printf("\n=-=-=-=-= PESQUISAR DADOS =-=-=-=\n");
        }
        else if (op == 2) {
          printf("Voltando ao menu principal...\n");
          return tabela;
        }
          
      }
        
      printf("Digite o nome da coluna que deseja pesquisar um valor:\n");
      for(int j = 0; j < tabela[i].qnt_colunas; j++){
        printf("> %s\n", tabela[i].colunas[j].nome);
      }
      printf(">> ");
      char* nome_col = NULL;
      nome_col = lerString(nome_col);
      for(int j = 0; j < tabela[i].qnt_colunas; j++){
        if(strcmp(nome_col, tabela[i].colunas[j].nome) == 0){
          printf("Digite o nome do dado que deseja pesquisar:\n");
          printf(">> ");
          char* nome_dado = NULL;
          nome_dado = lerString(nome_dado);
          printf("Selecione o que deseja pesquisar:\n");
          printf("1 - valores maior que o valor informado\n");
          printf("2 - valores maior ou igual ao valor informado\n");
          printf("3 - valores igual o valor informado\n");
          printf("4 - valores menor que o valor informado\n");
          printf("5 - valores menor ou igual ao valor informado\n");
          printf("6 - valores próximo ao valor informado\n");
          printf(">> ");
          int op;
          scanf("%d", &op);
          int cont = 0;
          
          switch(op){
            case 1: 
              for(int k = 0; k < tabela[i].qnt_linhas; k++){
                if(strcmp(tabela[i].colunas[j].dados[k].nome, nome_dado) > 0){
                  cont++;
                  if(cont == 1){
                    printf("Valores maiores que %s: \n", nome_dado);
                  }
                  printf("%s", tabela[i].colunas[j].dados[k].nome);
                }
              }
              break;
            case 2:
              for(int k = 0; k < tabela[i].qnt_linhas; k++){
                if(strcmp(tabela[i].colunas[j].dados[k].nome, nome_dado) > 0 || strcmp(tabela[i].colunas[j].dados[k].nome, nome_dado) == 0 ){
                  cont++;
                  if(cont == 1){
                    printf("Valores maiores ou iguais a %s: \n", nome_dado);
                  }
                  printf("%s", tabela[i].colunas[j].dados[k].nome);
                 }
              }
              break;
            
            case 3:
              for(int k = 0; k < tabela[i].qnt_linhas; k++){
                if(strcmp(tabela[i].colunas[j].dados[k].nome, nome_dado) == 0 ){
                  cont++;
                  if(cont == 1){
                    printf("Valores iguais a %s: \n", nome_dado);
                  }
                  printf("%s", tabela[i].colunas[j].dados[k].nome);
                }
              }
              break;
            
            case 4:
              for(int k = 0; k < tabela[i].qnt_linhas; k++){
                if(strcmp(tabela[i].colunas[j].dados[k].nome, nome_dado) < 0){
                  cont++;
                  if(cont == 1){
                    printf("Valores menores que %s: \n", nome_dado);
                  }
                  printf("%s", tabela[i].colunas[j].dados[k].nome);
                 }
              }
              break;
            
            case 5:
              for(int k = 0; k < tabela[i].qnt_linhas; k++){
                if(strcmp(tabela[i].colunas[j].dados[k].nome, nome_dado) < 0 || strcmp(tabela[i].colunas[j].dados[k].nome, nome_dado) == 0 ){
                  cont++;
                  if(cont == 1){
                    printf("Valores menores ou iguais a %s: \n", nome_dado);
                  }
                  printf("%s", tabela[i].colunas[j].dados[k].nome);
                 }
              }
              break;
            case 6:
              if(tabela[i].colunas[j].tipo != 4){
                printf("Essa coluna não é do tipo String");
              }
              for(int k = 0; k < tabela[i].qnt_linhas; k++){
                if(strcmp(tabela[i].colunas[j].dados[k].nome, nome_dado) > 0 || strcmp(tabela[i].colunas[j].dados[k].nome, nome_dado) < 0 ){
                  cont++;
                  if(cont == 1){
                    printf("Valores maiores que %s: \n", nome_dado);
                  }
                  printf("%s", tabela[i].colunas[j].dados[k].nome);
                 }
              }
              break;
            
            default: printf("Opção inválida"); break;
            }
          
            
          }
          else if(i == tabela[i].qnt_colunas - 1){
            printf("Essa tabela não possui essa coluna");
          }
        }
      free(nome_col);
      }
    }
  free(nome_tab);
  return tabela;
}

Tabela *apagarLinha(Tabela *tabela, int *tam) {
  printf("\n=-=-=-=-=APAGAR LINHA=-=-=-=-=-=\n");
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

  printf("\nDigite o nome da tabela que deseja apagar os dados:\n");
  printf(">> ");
  char* nome_tab = NULL;  
  nome_tab = lerString(nome_tab);

  for(int i = 0; i < *tam; i++){
    if(strcmp(nome_tab, tabela[i].nome) == 0){
      
      printf("--------- %s ---------\n", tabela[i].nome);
      printf("Linhas: ");
      for(int j = 0; j < tabela[i].qnt_colunas; j++){
        printf("|");
        printf(" %s |", tabela[i].colunas[j].nome);
      }
      printf("\n");
      for(int j = 0; j < tabela[i].qnt_linhas; j++){
        printf("Linha %d: ", j + 1);
        for(int k = 0; k < tabela[i].qnt_colunas; k++){
          printf("|");
          printf(" %s |", tabela[i].colunas[k].dados[j].nome);
        }
        printf("\n");
      }

      int op = 0;
      
      printf("\nDigite o número da linha que deseja apagar:\n");
      printf(">> ");
      scanf("%d", &op);

      for(int k = 0; k < tabela[i].qnt_colunas; k++){
        for(int j = 0; j < tabela[i].qnt_linhas; j++){
          if (j == op - 1) {
            tabela[i].colunas[k].dados[j] = tabela[i].colunas[k].dados[j + 1];
            tabela[i].colunas[k].dados = (Dado *)realloc(tabela[i].colunas[k].dados, (tabela[i].qnt_linhas - 1) * sizeof(Dado));
          }
        }
      }
      
      tabela[i].qnt_linhas--;

      int outrasLinhas = 1 + tabela[i].qnt_colunas;
      int linhaApagar = outrasLinhas + op;

      removerLinha(linhaApagar, tabela[i].nome);

      printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
      printf("Linha removida com sucesso!\n");
      printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

    } 
    else if(i == *tam-1){
      printf("Tabela não encontrada!\n");
    }
  }

  return tabela;
}
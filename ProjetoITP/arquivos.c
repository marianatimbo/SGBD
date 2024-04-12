#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "definitions.h"
#include "auxiliar.h"

void salvarDados(Tabela tabela){
  FILE *arquivo;
  int l = tabela.qnt_linhas;

  char caminho[21 + strlen(tabela.nome) + 1];
  sprintf(caminho, "arquivos/tabelas/%s.txt", tabela.nome);

  arquivo = fopen(caminho, "a");

  if (arquivo == NULL){
    printf("Erro ao abrir o arquivo");
    printf("Erro foi: %s\n", strerror(errno));
    fclose(arquivo);
  } 
  else{
    for(int i = 0; i < tabela.qnt_colunas; i++){
      fprintf(arquivo, "%s ", tabela.colunas[i].dados[l].nome);
    }
    fprintf(arquivo, "\n");
    fclose(arquivo);
  }
}

void salvarTabela(Tabela tabela) {
  FILE *arquivo;
  
  char caminho[21 + strlen(tabela.nome) + 1];
  sprintf(caminho, "arquivos/tabelas/%s.txt", tabela.nome);
  
  arquivo = fopen(caminho, "a");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo");
    printf("Erro foi: %s\n", strerror(errno));
    fclose(arquivo);
  } 
  else {
    fprintf(arquivo, "%s %d %s\n", tabela.nome, tabela.qnt_colunas  , tabela.chave);
    for(int i = 0; i < tabela.qnt_colunas; i++){
      if(i == 0){
        fprintf(arquivo, "%s %d\n", tabela.colunas[i].nome, 1);
      }
      else{
        fprintf(arquivo, "%s %d\n", tabela.colunas[i].nome, tabela.colunas[i].tipo);
      }
    }
    fclose(arquivo);
  }
}

void removerLinha(int linha, char *nome) {
  FILE *inputFile, *tempFile;
  char buffer[1000];
  int currentLine = 1;

  char caminho[21 + strlen(nome) + 1];
  sprintf(caminho, "arquivos/tabelas/%s.txt", nome);

  inputFile = fopen(caminho, "r");
  if (inputFile == NULL) {
    printf("Erro ao abrir o arquivo");
    printf("Erro foi: %s\n", strerror(errno));
    fclose(inputFile);
    return;
  } 

  tempFile = fopen("arquivos/tabelas/temp.txt", "w");
  if (tempFile == NULL) {
    printf("Erro ao abrir o arquivo");
    printf("Erro foi: %s\n", strerror(errno));
    fclose(tempFile);
    return;
  } 

  while (fgets(buffer, sizeof(buffer), inputFile) != NULL) {
    if (currentLine != linha) {
      fputs(buffer, tempFile);
    }
    currentLine++;
  }

  fclose(inputFile);
  fclose(tempFile);

  remove(caminho);

  if (rename("arquivos/tabelas/temp.txt", caminho) != 0) {
    printf("Erro ao renomear o arquivo temporário");
    return;
  }
}

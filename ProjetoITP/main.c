#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "definitions.h"
#include "tabelas.h"
#include "auxiliar.h"
#include "tuplas.h"
#include "arquivos.h"

int main(){
  int opcao;

  int cont = 0;
  Tabela *banco = NULL;
  
  do{
    imprimeMenu();
    scanf("%d", &opcao);
    switch(opcao){
      case 1: banco = criarTabela(banco, &cont); break;
      case 2: banco = adicionarDados(banco, &cont); break;
      case 4: banco = listarTabelas(banco, &cont); break;
      case 3: banco = visualizarDados(banco, &cont); break;
      case 5: banco = pesquisarValor(banco, &cont); break;
      case 6: banco = apagarLinha(banco, &cont); break;
      case 7: banco = apagarTabela(banco, &cont); break;
      case 8:
        liberarMemoria(banco, &cont);
        printf("\nSESSÃO ENCERRADA COM SUCESSO!");
        break;
      default: printf("\nOpção inválida, tente novamente.\n");
    }

  } while(opcao != 8);
  
  return 0;
}
typedef struct {
  char *nome;
} Dado;

typedef struct {
  char *nome;
  int tipo;
  Dado *dados;
} Coluna;

typedef struct {
  char *nome;
  char *chave;
  int qnt_colunas; 
  int qnt_linhas; 
  Coluna *colunas;
} Tabela;

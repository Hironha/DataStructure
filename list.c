#include <stdio.h>
#include <stdlib.h>

struct no{
  struct no *proximo;
  int valor;
};
typedef struct no no;



char menu(no *cabecalho){
  char opc;
  int quantidade = ((cabecalho == NULL) ? (0) : (cabecalho->valor));
  fprintf(stdout, "Quantidade de elementos inseridos: %d.\n", quantidade);
  printf("1-Inserir.\n");
  printf("2-Remover.\n");
  printf("3-Imprimir.\n");
  printf("4-Buscar.\n");
  printf("5-Sair.\n");
  printf("Insira a opcao: ");
  scanf(" %c", &opc);
  setbuf(stdin, NULL);
  system("cls");

  return opc;
}

void buscar(no *lista){
  no *aux = lista;
  int valor, retorno;
  int count = 0;

  fprintf(stdout, "Informe o valor que deseja buscar: ");
  retorno = fscanf(stdin, " %d", &valor);
  setbuf(stdin, NULL);

  if(!retorno){
    fprintf(stdout, "Valor invalido.\n");
    return;
  }
  while(aux != NULL && aux->valor != valor){
    aux = aux->proximo;
    count++;
  }

  if(aux == NULL){
    fprintf(stdout, "Valor nao encontrado.\n");
    return;
  }

  fprintf(stdout, "Valor [%d] encontrado na posicao %d.\n", valor, count);
}
void inserir(no **lista, no **cabecalho){
  int valor, retorno;
  no *aux = NULL, *atual = NULL;
  printf("Informe o valor que deseja inserir: ");
  retorno = scanf(" %d", &valor);
  setbuf(stdin, NULL);

  if(!retorno){
    printf("Entrada invalida.\n");
    return;
  }

  aux = (no*)malloc(sizeof(no));
  aux->valor = valor;
  aux->proximo = NULL;

  //se é o primeiro valor a ser inserido na lista
  if(*lista == NULL){
    *lista = aux;
    *cabecalho = (no*)malloc(sizeof(no));
    (*cabecalho)->proximo = aux;
    (*cabecalho)->valor = 1;
    fprintf(stdout, "Valor inserido: %d.\n", aux->valor);
    return;
  }

  //se valor a ser inserido é menor que o primeiro valor
  if(aux->valor < (*lista)->valor){
    aux->proximo = *lista;
    *lista = aux;
    fprintf(stdout, "Valor inserido: %d.\n", aux->valor);
    return;
  }

  //caso comum
  atual = *lista;
  while(atual->proximo != NULL && atual->proximo->valor <= valor){
    atual = atual->proximo;
  }

  if(atual->valor == valor){
    fprintf(stdout, "Valor [%d] ja existente na lista.\n", valor);
    return;
  }
  //se é o maior valor, insere no final
  if(atual->proximo == NULL)
    atual->proximo = aux;
  //senão, insere no lugar apropriado
  else{
    aux->proximo = atual->proximo;
    atual->proximo = aux;
  }
  (*cabecalho)->valor += 1;
  fprintf(stdout, "Valor inserido: %d.\n", aux->valor);
}

void imprimir(no *lista){
  no *aux = lista;
  if(lista == NULL){
    fprintf(stdout, "A lista esta vazia.\n");
    return;
  }
  while(aux->proximo != NULL){
    printf("%d -> ", aux->valor);
    aux = aux->proximo;
  }
  fprintf(stdout, "%d\n", aux->valor);
}

void remover(no *lista){
  no *aux = lista, *temp;
  int valor, retorno;

  fprintf(stdout, "Informe o valor a ser removido: ");
  retorno = fscanf(stdin, " %d", &valor);
  setbuf(stdin, NULL);
  if(!retorno){
    fprintf(stdout, "Valor invalido.\n");
    return;
  }

  while(aux != NULL && aux->proximo->valor != valor){
    aux = aux->proximo;
  }

  if(aux == NULL){
    fprintf(stdout, "Valor [%d] nao encontrado.\n", valor);
    return;
  }

  temp = aux->proximo;
  aux->proximo = aux->proximo->proximo;
  free(temp);
}

int main(int argc, char**argv){
  char opc = 'a';
  no *cabecalho = NULL;
  no *lista = NULL;

  system("cls");
  while(opc != '5'){
    opc = menu(cabecalho);
    switch(opc){
      case('1'):
        inserir(&lista, &cabecalho);
        break;
      case('2'):
        remover(lista);
        break;
      case('3'):
        imprimir(lista);
        break;
      case('4'):
        buscar(lista);
        break;
      case('5'):
        remover(lista);
        break;
      default:
        fprintf(stdout, "Codigo invalido.\n");
        break;
    }
    system("pause");
    system("cls");
  }

  free(lista);
  free(cabecalho);
  return 0;
}

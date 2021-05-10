#include <stdio.h>
#include <stdlib.h>

struct no {
  struct no *proximo;
  int valor;
};

typedef struct no no;

//passando o endereço do ponteiro para não ter que retornar o valor
//visto que em C as passagens são todas por valores
int pop(no **self){
  int valor;
  no *aux = NULL;
  if(*self == NULL){
    fprintf(stdout, "Pilha vazia.\n");
    return -1;
  }
  aux = *self;
  valor = aux->valor;
  *self = aux->proximo;
  free(aux);

  return valor;
}

void push(no **self, int valor){
  no *aux = (no*)malloc(sizeof(no));
  aux->valor = valor;
  aux->proximo = *self;
  *self = aux;
}

int menu(){
	int opc, retorno;

	printf("1-Push.\n");
	printf("2-Pop.\n");
	printf("3-Topo da pilha.\n");
	printf("4-Imprimir.\n");
	printf("5-Sair.\n");
	printf("\nInsira a opcao: ");
	retorno = scanf(" %d", &opc);
  if(retorno == 0){
    setbuf(stdin, NULL);
    fprintf(stdout, "\n");
    return 0;
  }
	return (opc);
}

void inserirValor(no **p){
  int num, retorno;
  printf("Informe o valor: ");
  retorno = scanf(" %d", &num);
  if(retorno == 0){
    setbuf(stdin, NULL);
    fprintf(stdout, "Valor invalido. Insira um numero inteiro.\n");
    return;
  }
  push(p, num);
}

void retirarValor(no **p){
  int aux = pop(p);
  (aux == - 1) ? (fprintf(stdout, "")) : (fprintf(stdout, "Removido: %d\n", aux));
}

void valorTopo(no **self){
  if(*self == NULL){
    fprintf(stdout, "Pilha vazia!.\n");
    return;
  }
  fprintf(stdout, "Topo: %d.\n", (*self)->valor);
  system("pause");
  system("cls");
}

void imprimirPilha(no **self){
  no *aux = *self;
  if(*self == NULL) {
    fprintf(stdout, "Pilha vazia!\n");
    return;
  }
  fprintf(stdout, "Valores da pilha:");
  while(aux != NULL){
    fprintf(stdout, " %d", aux->valor);
    aux = aux->proximo;
  }
  fprintf(stdout, ".\n");
}

void sairPilha(no **self){
  if(*self != NULL){
    free(*self);
  }
  fprintf(stdout, "Pilha limpa. Saindo do programa.\n");
  exit(0);
}

void main(int argc, char **argv){
  int opc = 0;
  no *pilha = NULL;
  void (*options[5])(no **) = {inserirValor, retirarValor, valorTopo, imprimirPilha, sairPilha};
  while(opc != -1){
    opc = menu();
    if(opc > 0 && opc < 6){
      (*options[opc-1])(&pilha);
    }else{
      fprintf(stdout, "Opcao invalida.\n");
    }
    system("pause");
    system("cls");
  }
}

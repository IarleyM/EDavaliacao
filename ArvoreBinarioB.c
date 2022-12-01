#include<stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "ArvB.h"

typedef struct Pessoa{
	char nome[50];
	int ID;
}Pessoa;

typedef struct No{
	Pessoa pessoa;
	struct no *direita, *esquerda;
}NoArv;

Pessoa ler_pessoa(){
	Pessoa p;
	printf("\tInforme um nome da pessoa: ");
	fgets(p.nome, 49, stdin);
	printf("\tInforme o ID: ");
	scanf("%d", &p.ID);
	return p;
}

void imprimir_pessoa(){
	Pessoa p;
	printf("\tNome: %s\tID: %d\n", p.nome, p.ID);
}

NoArv* inserir_versao_1(NoArv *raiz, Pessoa p){
	if(raiz == NULL){
		NoArv *aux = malloc(sizeof(NoArv));
		aux->pessoa = p;
		aux->esquerda = NULL;
		aux->direita = NULL;
		return aux;
	}else{
		if(p.ID < raiz->pessoa.ID)
			raiz->esquerda = inserir_versao_1(raiz->esquerda, p);
		else
			raiz->direita = inserir_versao_1(raiz->direita, p);
		return raiz;
	}
}

void inserir_versao_2(NoArv **raiz, Pessoa p){
	if(*raiz == NULL){
		*raiz = malloc(sizeof(NoArv));
		(*raiz)->pessoa = p;
		(*raiz)->esquerda = NULL;
		(*raiz)->direita = NULL;
	}else{
		if(p.ID < (*raiz)->pessoa.ID)
			inserir_versao_2(&((*raiz)->esquerda), p);
		else
			inserir_versao_2(&((*raiz)->direita), p);
	}
}

void inserir_versao_3(NoArv **raiz, Pessoa p){
	NoArv * aux = *raiz;
	while(aux){
		if(p.ID < aux->pessoa.ID)
			raiz = &aux->esquerda;
		else
			raiz = &aux->direita;
		aux=*raiz;
	}
	aux = malloc(sizeof(NoArv));
	aux->pessoa= p;
	aux->esquerda = NULL;
	aux->direita = NULL;
	*raiz = aux;
}

NoArv* buscar_versao_1(NoArv *raiz, Pessoa ID){
	Pessoa p;
	if(raiz){
		if(p.ID == raiz->pessoa.ID){
			return raiz;
		}else if(p.ID < raiz->pessoa.ID)
			return buscar_versao_1(raiz->esquerda, ID);
		else
			return buscar_versao_1(raiz->direita, ID);
	}
	return NULL;
}

NoArv* buscar_versao_2(NoArv* raiz, int ID){
	while(raiz){
		if(ID < raiz->pessoa.ID)
			raiz = raiz->esquerda;
		else if(ID > raiz->pessoa.ID)
			raiz = raiz->direita;
		else
			return raiz;
	}
	return NULL;
}

int altura(NoArv* raiz){
	if(raiz == NULL){
		return -1;
	}else{
		int esq = altura(raiz->esquerda);
		int dir = altura(raiz->direita);
		if(esq > dir){
			return esq + 1;
		}else
			return dir + 1;
	}
}

NoArv* remover(NoArv* raiz, int ID){
	if(raiz == NULL){
		printf("Valor nao encontrado.");
		return NULL;
	}else{//PROCURAR NO PARA REMOVER
		if(raiz->pessoa.ID == ID){
			//REMOVER NOS FOLHAS
			if(raiz->esquerda == NULL && raiz->direita == NULL){
				free(raiz);
				printf("Filho removido: %d\n", ID);
			}else{
				//REMOVER NOS QUE POSSUEM 2 FILHOS		
				if(raiz->esquerda != NULL && raiz->direita != NULL){
					Pessoa p;
					NoArv *aux = raiz->esquerda;
					while(aux->direita != NULL){
						aux = aux->direita;
						p = raiz->pessoa;
						raiz->pessoa = aux->pessoa;
						aux->pessoa = p;
						printf("Elemento trocado: %d\n", ID);
						raiz->esquerda = remover(raiz->esquerda, ID);
						return raiz;
				}
				}else{
					NoArv *aux;
					if(raiz->esquerda != NULL)
						aux = raiz->esquerda;
					else
						aux = raiz->direita;
					free(raiz);
					printf("Ente com 1 filho removido: %d\n", ID);
					return aux;
				}
			}
		}else{
			if(ID < raiz->pessoa.ID)
				raiz->esquerda = remover(raiz->esquerda, ID);
			else
				raiz->direita = remover(raiz->direita, ID);
		}
	}
}

void imprimir_versao_1(NoArv *raiz){
	if(raiz){
		imprimir_pessoa(raiz->pessoa);
		imprimir_versao_1(raiz->esquerda);
		imprimir_versao_1(raiz->direita);
	}
}

void imprimir_versao_2(NoArv *raiz){
	if(raiz){
		imprimir_versao_2(raiz->esquerda);
		imprimir_pessoa(raiz->pessoa);
		imprimir_versao_2(raiz->direita);
	}
}

NoArv* apagar_arvore(NoArv *raiz){
	if(raiz==NULL){
		printf("Arvore esta vazia");
	}else{
		while(raiz != NULL){
			return NULL;
		}
	}
}

int main (){
	NoArv *busca, *raiz = NULL;
	int opc;
	int ID;
	printf("===========Arvore Genealogica============");
	
	do{
		printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Buscar\n\t4 - Altura\n\t5 - Remover\n\n\t6 - Apagar Arvore\n");
		scanf("%d", &opc);
		scanf("%c");
		switch(opc){
			case 0:
				printf("\nSaindo...\n");
				break;
			case 1:
				inserir_versao_3(&raiz, ler_pessoa());
				break;
			case 2:
				printf("\n\tPrimeira impressao:\n\t");
				imprimir_versao_1(raiz);
				printf("\n\tSegundo impressao:\n\t");
				imprimir_versao_2(raiz);
				printf("\n");
				break;
			case 3:
				printf("\n\tDigite o ID a ser procurado: ");
				scanf("%d", &ID);
				busca = buscar_versao_2(raiz, ID);
				if(busca){
					printf("\n\tValor escontrado:");
					imprimir_pessoa(busca->pessoa);
				}
				else
					printf("\n\tValor nao encontrado! :(");
				break;
			case 4:
				printf("\n\tAltura da arvore: %d\n\n", altura(raiz));
				break;
			case 5:
				printf("\t");
				imprimir_versao_2(raiz);
				printf("\n\tInforme o ID a ser removido: ");
				scanf("%d", &ID);
				raiz = remover(raiz, ID);
				break;
			case 6:
				remover_arvore(raiz);
				break;
			default:
				if(opc != 0){
					printf("\n\tOpcao invalido\n");
				break;
			}
	}
	}while(opc != 0);
	return 0;

}
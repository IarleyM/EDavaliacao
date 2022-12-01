typedef struct Pessoa{
	char nome[50];
	int ID;
}Pessoa;

typedef struct No{
	Pessoa pessoa;
	struct no *direita, *esquerda;
}NoArv;

Pessoa ler_pessoa();
void imprimir_pessoa();
void inserir_versao_3(NoArv **raiz, Pessoa p);
void imprimir_versao_1(NoArv *raiz);
void imprimir_versao_2(NoArv *raiz);
NoArv* buscar_versao_2(NoArv* raiz, int ID);
NoArv* remover(NoArv* raiz, int ID);
NoArv* apagar_arvore(NoArv *raiz);
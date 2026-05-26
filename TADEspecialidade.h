#ifndef TADESPECIALIDADE_H
#define TADESPECIALIDADE_H
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

struct TpAnimal
{
	char nome[30], especie[30], data[12], prioridade[30];
	int tempoEspera, tempoProc;
	TpAnimal *prox;
};

struct TpDescFila
{
	TpAnimal *Inicio, *Fim;
	int Qtde;
};

struct TpAtendente
{
	int id, ocupado, TempoRestante, totalAtendidos;
	TpAnimal *animalAtual;
	TpAtendente *prox;
};

struct TpDescAtendente
{
	TpAtendente *Inicio, *Fim;
	int Qtde;
};

struct TpEspecialidade
{
	char nome[30];
	TpDescFila fila;
	TpDescAtendente atendentes;
	int atendidos;
	int totalEsperaEmerg, totalEsperaUrgen, totalEsperaRotin;
	int contEmerg, contUrgen, contRotin;
	int restantesEmerg, restantesUrgen, restantesRotin;
	TpEspecialidade *prox, *ant;
};

struct TpDescEsp
{
	TpEspecialidade *Inicio, *Fim;
	int Qtde;
};

void inicializarFila(TpDescFila &F)
{
	F.Qtde = 0;
	F.Inicio = F.Fim = NULL;
}

void inicializarEsp(TpDescEsp &D)
{
	D.Qtde = 0;
	D.Inicio = D.Fim = NULL;
}

int lerInteiro(int min, int max)
{
	int valor;
	printf("Digite um valor entre %d e %d: ", min, max);
	fflush(stdin);
	scanf("%d", &valor);
	while(valor < min || valor > max)
	{
		printf("ERRO: valor deve ser entre %d e %d. Digite: ", min, max);
		fflush(stdin);
		scanf("%d", &valor);
	}
	return valor;
}

void criarAtendentes(TpEspecialidade *novo, int nAtend)
{
	TpAtendente *at;
	int i;
	for(i = 0; i < nAtend; i++)
	{
		at = new TpAtendente;
		at->prox = NULL;
		at->animalAtual = NULL;
		at->id = i + 1;
		at->ocupado = 0;
		at->totalAtendidos = 0;
		at->TempoRestante = 0;
		if(novo->atendentes.Inicio == NULL)
			novo->atendentes.Inicio = novo->atendentes.Fim = at;
		else
		{
			novo->atendentes.Fim->prox = at;
			novo->atendentes.Fim = at;
		}
		novo->atendentes.Qtde++;
	}
}

TpEspecialidade *criarEspecialidade(char *nome, int nAtend)
{
	TpEspecialidade *novo;
	novo = new TpEspecialidade;
	novo->prox = NULL;
	novo->ant = NULL;
	novo->atendidos = 0;
	novo->totalEsperaEmerg = 0;
	novo->totalEsperaUrgen = 0;
	novo->totalEsperaRotin = 0;
	novo->contEmerg = 0;
	novo->contUrgen = 0;
	novo->contRotin = 0;
	novo->restantesEmerg = 0;
	novo->restantesUrgen = 0;
	novo->restantesRotin = 0;
	novo->fila.Inicio = NULL;
	novo->fila.Fim = NULL;
	novo->fila.Qtde = 0;
	novo->atendentes.Inicio = NULL;
	novo->atendentes.Fim = NULL;
	novo->atendentes.Qtde = 0;
	strcpy(novo->nome, nome);
	criarAtendentes(novo, nAtend);
	return novo;
}

void InserirInicioEsp(TpDescEsp &D)
{
	char nome[30];
	int nAtend;
	TpEspecialidade *novo;
	printf("Inserir Especialidades no Inicio\n");
	printf("Nome (0 para sair): ");
	fflush(stdin);
	scanf("%[^\n]", nome);
	while(stricmp(nome, "0") != 0)
	{
		printf("Quantos atendentes para %s? (1-10): ", nome);
		nAtend = lerInteiro(1, 10);
		novo = criarEspecialidade(nome, nAtend);
		if(D.Inicio == NULL)
			D.Inicio = D.Fim = novo;
		else
		{
			novo->prox = D.Inicio;
			D.Inicio->ant = novo;
			D.Inicio = novo;
		}
		D.Qtde++;
		printf("Nome (0 para sair): ");
		fflush(stdin);
		scanf("%[^\n]", nome);
	}
}

void InserirFimEsp(TpDescEsp &D)
{
	char nome[30];
	int nAtend;
	TpEspecialidade *novo;
	printf("Inserir Especialidades no Fim\n");
	printf("Nome (0 para sair): ");
	fflush(stdin);
	scanf("%[^\n]", nome);
	while(stricmp(nome, "0") != 0)
	{
		printf("Quantos atendentes para %s? (1-10): ", nome);
		nAtend = lerInteiro(1, 10);
		novo = criarEspecialidade(nome, nAtend);
		if(D.Fim == NULL)
			D.Fim = D.Inicio = novo;
		else
		{
			novo->ant = D.Fim;
			D.Fim->prox = novo;
			D.Fim = novo;
		}
		D.Qtde++;
		printf("Nome (0 para sair): ");
		fflush(stdin);
		scanf("%[^\n]", nome);
	}
}

int ListaVazia(TpDescEsp D)
{
	return D.Inicio == NULL && D.Fim == NULL && D.Qtde == 0;
}

TpEspecialidade *ElementoInicioEsp(TpDescEsp D)
{
	return D.Inicio;
}

TpEspecialidade *ElementoFimEsp(TpDescEsp D)
{
	return D.Fim;
}

void retirarInicioEsp(TpDescEsp &D)
{
	TpEspecialidade *ret;
	if(D.Inicio == NULL)
		printf("Lista vazia nada a Retirar!\n");
	else
	{
		ret = D.Inicio;
		D.Inicio = D.Inicio->prox;
		if(D.Inicio != NULL)
			D.Inicio->ant = NULL;
		else
			D.Fim = NULL;
		delete ret;
		D.Qtde--;
	}
}

void retirarFimEsp(TpDescEsp &D)
{
	TpEspecialidade *ret;
	if(D.Fim == NULL)
		printf("Lista Vazia nada a Retirar!\n");
	else
	{
		ret = D.Fim;
		D.Fim = D.Fim->ant;
		if(D.Fim != NULL)
			D.Fim->prox = NULL;
		else
			D.Inicio = NULL;
		delete ret;
		D.Qtde--;
	}
}

void RemoverEsp(TpDescEsp &D)
{
	TpEspecialidade *aux;
	char nome[30];
	printf("Remover Especialidade\n");
	printf("Nome: ");
	fflush(stdin);
	scanf("%[^\n]", nome);
	if(D.Inicio == NULL)
		printf("Lista vazia!\n");
	else
	{
		aux = D.Inicio;
		while(aux != NULL && stricmp(aux->nome, nome) != 0)
			aux = aux->prox;
		if(aux == NULL)
			printf("Especialidade nao encontrada!\n");
		else
		{
			if(aux->ant != NULL)
				aux->ant->prox = aux->prox;
			else
				D.Inicio = aux->prox;
			if(aux->prox != NULL)
				aux->prox->ant = aux->ant;
			else
				D.Fim = aux->ant;
			delete aux;
			D.Qtde--;
			printf("Especialidade removida!\n");
		}
	}
}

void LiberarFila(TpDescFila &F)
{
	TpAnimal *aux;
	if(F.Inicio == NULL)
	{
		F.Fim = NULL;
		F.Qtde = 0;
		return;
	}
	aux = F.Inicio;
	F.Inicio = F.Inicio->prox;
	delete aux;
	LiberarFila(F);
}

void LiberarEspaco(TpDescEsp &D)
{
	TpEspecialidade *aux;
	TpAtendente *atend, *proxAtend;
	if(D.Inicio == NULL)
	{
		D.Fim = NULL;
		D.Qtde = 0;
		return;
	}
	aux = D.Inicio;
	D.Inicio = D.Inicio->prox;
	LiberarFila(aux->fila);
	atend = aux->atendentes.Inicio;
	while(atend != NULL)
	{
		proxAtend = atend->prox;
		delete atend;
		atend = proxAtend;
	}
	delete aux;
	LiberarEspaco(D);
}

void ExibirEsp(TpDescEsp D)
{
	TpEspecialidade *aux;
	int i = 1;
	printf("\n+================================+\n");
	printf("|    ESPECIALIDADES CADASTRADAS  |\n");
	printf("+================================+\n");
	if(ListaVazia(D))
	{
		printf("| Lista vazia!                   |\n");
		printf("+================================+\n");
		return;
	}
	aux = D.Inicio;
	while(aux != NULL)
	{
		printf("| %d - %-28s|\n", i, aux->nome);
		printf("|   Animais na fila: %-11d  |\n", aux->fila.Qtde);
		printf("|   Atendidos:       %-11d  |\n", aux->atendidos);
		printf("|   Atendentes:      %-11d  |\n", aux->atendentes.Qtde);
		printf("+--------------------------------+\n");
		aux = aux->prox;
		i++;
	}
	printf("| Total de especialidades: %-5d  |\n", D.Qtde);
	printf("+================================+\n");
}

#endif

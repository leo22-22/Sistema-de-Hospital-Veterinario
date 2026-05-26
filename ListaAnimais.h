#ifndef LISTAANIMAIS_H
#define LISTAANIMAIS_H
#include "TADEspecialidade.h"

int FilaVazia(TpDescFila F);
int ValorPrioridade(TpAnimal Animal);
TpAnimal *NovoAnimal(TpAnimal Animal);
void InserirOrdenadoPrioridade(TpDescFila &F, TpAnimal Animal);
TpEspecialidade *MenorFila(TpDescEsp &D);
int LerLinhaArquivo(FILE *ptr, TpAnimal &Animal);
void ExibirFila(TpDescFila F);

int FilaVazia(TpDescFila F)
{
	return F.Qtde == 0;
}

TpAnimal *NovoAnimal(TpAnimal Animal)
{
	TpAnimal *No;
	No = new TpAnimal;
	*No = Animal;
	No->prox = NULL;
	return No;
}

int ValorPrioridade(TpAnimal Animal)
{
	if(strcmp(Animal.prioridade, "Emergencia") == 0)
		return 3;
	if(strcmp(Animal.prioridade, "Urgencia") == 0)
		return 2;
	if(strcmp(Animal.prioridade, "Rotina") == 0)
		return 1;
	return 0;
}

void InserirOrdenadoPrioridade(TpDescFila &F, TpAnimal Animal)
{
	TpAnimal *Novo, *Atual;
	Novo = NovoAnimal(Animal);
	if(F.Qtde == 0)
		F.Inicio = F.Fim = Novo;
	else if(ValorPrioridade(Animal) > ValorPrioridade(*F.Inicio))
	{
		Novo->prox = F.Inicio;
		F.Inicio = Novo;
	}
	else if(ValorPrioridade(Animal) <= ValorPrioridade(*F.Fim))
	{
		F.Fim->prox = Novo;
		F.Fim = Novo;
	}
	else
	{
		Atual = F.Inicio;
		while(Atual->prox != NULL &&
			ValorPrioridade(Animal) <= ValorPrioridade(*(Atual->prox)))
			Atual = Atual->prox;
		Novo->prox = Atual->prox;
		Atual->prox = Novo;
	}
	F.Qtde++;
}

TpEspecialidade *MenorFila(TpDescEsp &D)
{
	TpEspecialidade *aux = D.Inicio;
	TpEspecialidade *menor = D.Inicio;
	if(D.Inicio == NULL)
		return NULL;
	while(aux != NULL)
	{
		if(aux->fila.Qtde < menor->fila.Qtde)
			menor = aux;
		aux = aux->prox;
	}
	return menor;
}

int LerLinhaArquivo(FILE *ptr, TpAnimal &Animal)
{
	Animal.tempoEspera = 0;
	return fscanf(ptr, " %[^,],%d,%[^,],%[^,],%[^,\n]",
		Animal.prioridade, &Animal.tempoProc,
		Animal.nome, Animal.data, Animal.especie) == 5;
}

void ExibirFila(TpDescFila F)
{
	TpAnimal *Atual = F.Inicio;
	if(F.Qtde == 0)
	{
		printf("\nFila vazia");
		return;
	}
	while(Atual != NULL)
	{
		printf("\nPrioridade: %s", Atual->prioridade);
		printf("\nNome:       %s", Atual->nome);
		printf("\nTempo:      %d", Atual->tempoProc);
		printf("\nEspecie:    %s", Atual->especie);
		printf("\nData:       %s", Atual->data);
		printf("\n--------------------");
		Atual = Atual->prox;
	}
	printf("\n\nTotal na fila: %d", F.Qtde);
	printf("\nPressione qualquer tecla...");
	getch();
}

#endif

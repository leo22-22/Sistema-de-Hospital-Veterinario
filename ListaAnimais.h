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


void InicializarFila(TpDescFila &F);
int FilaVazia(TpDescFila F);
int ValorPrioridade(TpAnimal Animal);
TpAnimal *NovoAnimal(TpAnimal Animal);
void InserirOrdenadoPrioridade(TpDescFila &F, TpAnimal Animal);
//TpAnimal RetirarAnimal(TpDescritorFila &Desc);
//TpAnimal ElementoInicio(TpDescritorFila Desc);
//TpAnimal ElementoFim(TpDescritorFila Desc);
void ExibirFila(TpDescFila F);
//void LiberarFila(TpDescritorFila &Desc);

void InicializarFila(TpDescFila &F)
{
	F.Inicio = NULL;
	F.Fim = NULL;
	F.Qtde = 0;
}


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
	{
		F.Inicio = Novo;
		F.Fim = Novo;
	}
	else
	{
		if(ValorPrioridade(Animal) > ValorPrioridade(*F.Inicio))
		{
			Novo->prox = F.Inicio;
			F.Inicio = Novo;
		}
		else
		{
			if(ValorPrioridade(Animal) <= ValorPrioridade(*F.Fim))
			{
				F.Fim->prox = Novo;
				F.Fim = Novo;
			}
			else
			{
				Atual = F.Inicio;

				while(Atual->prox != NULL &&
					  ValorPrioridade(Animal) <= ValorPrioridade(*(Atual->prox)))
				{
					Atual = Atual->prox;
				}

				Novo->prox = Atual->prox;
				Atual->prox = Novo;
			}
		}
	}

	F.Qtde++;
}

void ExibirFila(TpDescFila F)
{
	TpAnimal *Atual;

	Atual = F.Inicio;

	if(F.Qtde == 0)
	{
		printf("\nFila vazia");
	}
	else
	{
		while(Atual != NULL)
		{
			printf("\nPrioridade: %s", Atual->prioridade);
			printf("\nNome: %s", Atual->nome);
			printf("\nTempo: %d", Atual->tempoProc);
			printf("\nEspecie: %s", Atual->especie);
			printf("\nData: %s", Atual->data);
			printf("\n--------------------");

			Atual = Atual->prox;
			getch();
		}
	}

}

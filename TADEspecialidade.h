struct TpAnimal{
	char nome[30], especie[30], data[12];
	int prioridade, tempoEspera, tempoProc;
	TpAnimal *prox;
};

struct TpDescFila{
	TpAnimal *Inicio,*Fim;
	int Qtde;
};

struct TpEspecialidade{
	char nome[30];
	TpDescFila fila;
	int atendidos;
	TpEspecialidade *prox, *ant;
};

struct TpDescEsp{
	TpEspecialidade *Inicio, *Fim;
	int Qtde;
};

struct TpAtendente{
	int id, ocupado, TempoRestante, totalAtendidos;
	TpAnimal *animalAtual;
};


void inicializarFila(TpDescFila &F)
{
	F.Qtde = 0;
	F.Inicio = F.Fim = NULL;
}

void inicializarEsp(TpDescEsp &D)
{
	D.Qtde = 0;
	D.Inicio = D. Fim = NULL;
}

void InserirInicioEsp(TpDescEsp &D)
{
	TpEspecialidade *novo;
	char nome[30];
	printf("Inserir Especialidades no Inicio\n");
	printf("Nome (0 para sair): ");
	scanf("%s", nome);
	
	while(stricmp(nome,"0")!=0)
	{
		novo = new TpEspecialidade;
		novo -> prox = NULL;
		novo ->ant = NULL;
		novo -> atendidos = 0;
		novo -> fila.Inicio = NULL;
		novo -> fila.Fim = NULL;
		novo -> fila.Qtde = 0;
		strcpy(novo -> nome,nome);
		if(D.Inicio == NULL)
			D.Inicio = D.Fim = novo;
		else{
			novo -> prox = D.Inicio;
			D.Inicio -> ant = novo;
			D.Inicio = novo;
		}
		D.Qtde++;
		printf("Nome (0 para sair): ");
		scanf("%s", nome);
	}
}

void InserirFimEsp(TpDescEsp &D)
{
	TpEspecialidade *novo;
	char nome[30];
	
	printf("Inserir Especialidades no Fim\n");
	printf("Nome (0 para sair): ");
	scanf("%s", nome);
	
	while(stricmp(nome, "0")!=0)
	{
		novo = new TpEspecialidade;
		novo -> prox = NULL;
		novo -> ant = NULL;
		novo -> atendidos = 0;
		novo -> fila.Inicio = NULL;
		novo -> fila.Fim = NULL;
		novo -> fila.Qtde = 0;
		strcpy(novo->nome, nome);
		if(D.Fim == NULL)
			D.Fim = D.Inicio = novo;
		else{
			novo -> ant = D.Fim;
			D.Fim->prox = novo;
			D.Fim = novo;
		}
		D.Qtde++;
		printf("Nome (0 para sair): ");
		scanf("%s", nome);
	}
}

int ListaVazia(TpDescEsp D){
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
	clrscr();
	printf("Retirar Elemento Inicial\n");
	if(D.Inicio == NULL)
		printf("Lista vazia nada a Retirar!\n");
	else{
		ret = D.Inicio;
		D.Inicio = D.Inicio -> prox;
		if(D.Inicio != NULL)
			D.Inicio -> ant = NULL;
		else
			D.Fim = NULL;
		delete ret;
		D.Qtde--;
	}
}

void retirarFimEsp(TpDescEsp &D)
{
	TpEspecialidade *ret;
	clrscr();
	printf("Retirar Elemento Final\n");
	if(D.Fim == NULL)
		printf("Lista Vazia nada a Retirar!\n");
	else{
		ret = D.Fim;
		D.Fim = D.Fim -> ant;
		if(D.Fim != NULL)
			D.Fim -> prox = NULL;
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
    scanf("%s", nome);

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

void LiberarEspaco(TpDescEsp &D)
{
	TpEspecialidade *aux;
	
	while(D.Inicio != NULL)
	{
		aux = D.Inicio;
		D.Inicio = D.Inicio ->prox;
		delete aux;
	}
	D.Fim = NULL;
	D.Qtde = 0;
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
        printf("+--------------------------------+\n");
        aux = aux->prox;
        i++;
    }

    printf("| Total de especialidades: %-5d  |\n", D.Qtde);
    printf("+================================+\n");
}

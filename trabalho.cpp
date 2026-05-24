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

void inicializarEsp(TpDescEsp &D)
{
	D.Qtde = 0;
	D.Inicio = D. Fim = NULL;
}

void inicializarFila(TpDescFila &F)
{
	F.Qtde = 0;
	F.Inicio = F.Fim = NULL;
}

void InserirEsp(TpDescEsp &D)
{
	
	
}

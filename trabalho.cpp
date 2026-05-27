#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <windows.h>
#include <string.h>
#include "TADEspecialidade.h"
#include "ListaAnimais.h"
#include "TADMoldura.h"
#include <time.h>

int AtendentesOcupados(TpAtendente *atend)
{
	int resultado;
	resultado = 0;
	if(atend == NULL)
		resultado = 0;
	else if(atend->ocupado)
		resultado = 1;
	else
		resultado = AtendentesOcupados(atend->prox);
	return resultado;
}

int FilasOcupadas(TpEspecialidade *esp)
{
	int resultado;
	resultado = 0;
	if(esp == NULL)
		resultado = 0;
	else if(!FilaVazia(esp->fila))
		resultado = 1;
	else if(AtendentesOcupados(esp->atendentes.Inicio))
		resultado = 1;
	else
		resultado = FilasOcupadas(esp->prox);
	return resultado;
}

void ContarRestantes(TpEspecialidade *esp)
{
	TpAnimal *animal;
	animal = esp->fila.Inicio;
	while(animal != NULL)
	{
		if(strcmp(animal->prioridade, "Emergencia") == 0)
			esp->restantesEmerg++;
		else if(strcmp(animal->prioridade, "Urgencia") == 0)
			esp->restantesUrgen++;
		else
			esp->restantesRotin++;
		animal = animal->prox;
	}
}

void AlocarAtendente(TpEspecialidade *esp)
{
	TpAtendente *atend;
	TpAnimal *aux;
	char msg[60];
	atend = esp->atendentes.Inicio;
	while(atend != NULL)
	{
		if(!atend->ocupado && !FilaVazia(esp->fila))
		{
			aux = esp->fila.Inicio;
			esp->fila.Inicio = esp->fila.Inicio->prox;
			if(esp->fila.Inicio == NULL)
				esp->fila.Fim = NULL;
			esp->fila.Qtde--;
			atend->animalAtual = aux;
			atend->TempoRestante = aux->tempoProc;
			atend->ocupado = 1;
			atend->totalAtendidos++;
			sprintf(msg, "[->]A%d pegou %-10s (%s) %dut",
				atend->id, atend->animalAtual->nome,
				atend->animalAtual->prioridade, atend->TempoRestante);
			adicionarLog(10, msg);
		}
		atend = atend->prox;
	}
}

void ProcessarAtendente(TpEspecialidade *esp)
{
	TpAtendente *atend;
	char msg[60];
	atend = esp->atendentes.Inicio;
	while(atend != NULL)
	{
		if(atend->ocupado)
		{
			atend->TempoRestante--;
			sprintf(msg, "[..]A%d %-12s| restam %dut",
				atend->id, atend->animalAtual->nome,
				atend->TempoRestante);
			adicionarLog(7, msg);
			if(atend->TempoRestante == 0)
			{
				sprintf(msg, "[OK]A%d TERMINOU %-10s!",
					atend->id, atend->animalAtual->nome);
				adicionarLog(12, msg);
				esp->atendidos++;
				if(strcmp(atend->animalAtual->prioridade, "Emergencia") == 0)
				{
					esp->totalEsperaEmerg += atend->animalAtual->tempoEspera;
					esp->contEmerg++;
				}
				else if(strcmp(atend->animalAtual->prioridade, "Urgencia") == 0)
				{
					esp->totalEsperaUrgen += atend->animalAtual->tempoEspera;
					esp->contUrgen++;
				}
				else
				{
					esp->totalEsperaRotin += atend->animalAtual->tempoEspera;
					esp->contRotin++;
				}
				delete atend->animalAtual;
				atend->animalAtual = NULL;
				atend->ocupado = 0;
				atend->TempoRestante = 0;
			}
		}
		atend = atend->prox;
	}
}

void IncrementarEspera(TpAnimal *animal)
{
	if(animal != NULL)
	{
		animal->tempoEspera++;
		IncrementarEspera(animal->prox);
	}
}

int PausaComTecla(TpDescEsp &E)
{
	int i, opcao, encerrar;
	encerrar = 0;
	while(kbhit())
		getch();
	for(i = 0; i < 25; i++)
	{
		Sleep(15);
		if(kbhit())
		{
			opcao = getch();
			if(opcao == '1')
				InserirInicioEsp(E);
			else if(opcao == '2')
				InserirFimEsp(E);
			else if(opcao == '3')
				RemoverEsp(E);
			else
			{
				adicionarLog(12, "Encerrando simulacao...");
				encerrar = 1;
			}
		}
	}
	return encerrar;
}

void Relatorio(TpDescEsp &E, int ut)
{
	TpEspecialidade *esp;
	int totalEmerg, totalUrgen, totalRotin;
	int restEmerg, restUrgen, restRotin;
	float mediaEmerg, mediaUrgen, mediaRotin;
	int somaEspEmerg, somaEspUrgen, somaEspRotin;

	totalEmerg   = totalUrgen   = totalRotin   = 0;
	restEmerg    = restUrgen    = restRotin    = 0;
	somaEspEmerg = somaEspUrgen = somaEspRotin = 0;

	esp = E.Inicio;
	while(esp != NULL)
	{
		ContarRestantes(esp);
		totalEmerg   += esp->contEmerg;
		totalUrgen   += esp->contUrgen;
		totalRotin   += esp->contRotin;
		restEmerg    += esp->restantesEmerg;
		restUrgen    += esp->restantesUrgen;
		restRotin    += esp->restantesRotin;
		somaEspEmerg += esp->totalEsperaEmerg;
		somaEspUrgen += esp->totalEsperaUrgen;
		somaEspRotin += esp->totalEsperaRotin;
		esp = esp->prox;
	}

	mediaEmerg = 0;
	mediaUrgen = 0;
	mediaRotin = 0;
	if(totalEmerg > 0)
		mediaEmerg = (float)somaEspEmerg / totalEmerg;
	if(totalUrgen > 0)
		mediaUrgen = (float)somaEspUrgen / totalUrgen;
	if(totalRotin > 0)
		mediaRotin = (float)somaEspRotin / totalRotin;

	system("cls");
	printf("+==================================================+\n");
	printf("|      RELATORIO FINAL - HOSPITAL VETERINARIO     |\n");
	printf("|                  UT Total: %-5d               |\n", ut);
	printf("+==================================================+\n");
	printf("|                                                  |\n");
	printf("|  ANIMAIS ATENDIDOS POR PRIORIDADE:               |\n");
	printf("|  Emergencia: %-5d                              |\n", totalEmerg);
	printf("|  Urgencia:   %-5d                              |\n", totalUrgen);
	printf("|  Rotina:     %-5d                              |\n", totalRotin);
	printf("|  Total:      %-5d                              |\n", totalEmerg + totalUrgen + totalRotin);
	printf("|                                                  |\n");
	printf("|  TEMPO MEDIO DE ESPERA POR PRIORIDADE:           |\n");
	printf("|  Emergencia: %6.2f ut                          |\n", mediaEmerg);
	printf("|  Urgencia:   %6.2f ut                          |\n", mediaUrgen);
	printf("|  Rotina:     %6.2f ut                          |\n", mediaRotin);
	printf("|                                                  |\n");
	printf("|  ANIMAIS QUE PERMANECERAM NA FILA:               |\n");
	printf("|  Emergencia: %-5d                              |\n", restEmerg);
	printf("|  Urgencia:   %-5d                              |\n", restUrgen);
	printf("|  Rotina:     %-5d                              |\n", restRotin);
	printf("|  Total:      %-5d                              |\n", restEmerg + restUrgen + restRotin);
	printf("|                                                  |\n");
	printf("|  DETALHES POR ESPECIALIDADE:                     |\n");
	printf("|--------------------------------------------------||\n");
	esp = E.Inicio;
	while(esp != NULL)
	{
		printf("|  %-15s atendidos:%-4d restantes:%-4d     |\n",
			esp->nome, esp->atendidos, esp->fila.Qtde);
		esp = esp->prox;
	}
	printf("|                                                  |\n");
	printf("+==================================================+\n");
	printf("Pressione qualquer tecla para sair...");
	getch();
}

TpEspecialidade *EspecialidadeAleatoria(TpDescEsp &D)
{
	TpEspecialidade *aux;
	int posicao, i;

	if(D.Inicio == NULL || D.Qtde == 0)
		return NULL;

	posicao = rand() % D.Qtde;

	aux = D.Inicio;
	for(i = 0; i < posicao; i++)
		aux = aux->prox;

	return aux;
}

void Simular(TpDescEsp &E)
{
	TpEspecialidade *esp;
	TpAnimal Animal;
	TpEspecialidade *menor;
	FILE *ptr;
	char msg[60];
	char sep[60];
	int ut = 0, arquivoOk = 1, tempoSim;
	int tempoChegada = 5;

	fixarJanela();
	system("cls");
	desenharTelaInicial();
	inicializarEsp(E);
	InserirInicioEsp(E);

	ptr = fopen("Animais.txt", "r");
	if(ptr == NULL)
	{
		gotoxy(35, 18);
		printf("Erro ao abrir Animais.txt!                ");
		gotoxy(35, 19);
		printf("Pressione qualquer tecla...");
		getch();
		LiberarEspaco(E);
		return;
	}

	gotoxy(35, 18);
	printf("Arquivo Animais.txt aberto!               ");
	gotoxy(35, 19);
	printf("Tempo da simulacao (ut): ");
	tempoSim = lerInteiro(1, 9999);
	gotoxy(35, 20);
	printf("Pressione qualquer tecla para iniciar...");
	getch();

	system("cls");
	desenharBordas();
	lin_log = LIN_INICIO;

	srand(time(NULL));

	while((arquivoOk || FilasOcupadas(E.Inicio)) && ut <= tempoSim)
	{
		atualizarTela(E, ut, tempoSim, arquivoOk);

		if(arquivoOk && ut % tempoChegada == 0)
		{
			if(LerLinhaArquivo(ptr, Animal))
			{
				menor = EspecialidadeAleatoria(E);

				if(menor != NULL)
				{
					InserirOrdenadoPrioridade(menor->fila, Animal);
					sprintf(msg, "[+]UT=%-3d %-10s (%s)->%s",
						ut, Animal.nome,
						Animal.prioridade, menor->nome);
					adicionarLog(14, msg);
				}
			}
			else
			{
				arquivoOk = 0;
				fclose(ptr);
				adicionarLog(11, "[!] Arquivo concluido!");
			}
		}

		esp = E.Inicio;
		while(esp != NULL)
		{
			sprintf(sep, "--- LOG %s ---", esp->nome);
			adicionarLog(13, sep);
			AlocarAtendente(esp);
			ProcessarAtendente(esp);
			IncrementarEspera(esp->fila.Inicio);
			adicionarLog(8, "..............................");
			esp = esp->prox;
		}

		if(PausaComTecla(E))
		{
			if(arquivoOk)
				fclose(ptr);
			Relatorio(E, ut);
			LiberarEspaco(E);
			return;
		}

		ut++;
	}

	if(arquivoOk)
		fclose(ptr);

	Relatorio(E, ut);
	LiberarEspaco(E);
}

int main(void)
{
	TpDescEsp E;
	Simular(E);
	return 0;
}

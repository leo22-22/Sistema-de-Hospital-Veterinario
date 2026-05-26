#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <windows.h>
#include <string.h>
#include "TADEspecialidade.h"
#include "ListaAnimais.h"
#include "TADMoldura.h"

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
			sprintf(msg, "[->]A%d pegou %-10s (%s) %dut", atend->id, atend->animalAtual->nome, atend->animalAtual->prioridade, atend->TempoRestante);
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
			sprintf(msg, "[..]A%d %-12s| restam %dut", atend->id, atend->animalAtual->nome, atend->TempoRestante);
			adicionarLog(7, msg);
			if(atend->TempoRestante == 0)
			{
				sprintf(msg, "[OK]A%d TERMINOU %-10s!", atend->id, atend->animalAtual->nome);
				adicionarLog(12, msg);
				esp->atendidos++;
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
		Sleep(100);
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

void Simular(TpDescEsp &E)
{
	TpEspecialidade *esp;
	TpAnimal Animal;
	TpEspecialidade *menor;
	FILE *ptr;
	char msg[60];
	char sep[60];
	int ut = 0, arquivoOk = 1;

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
	printf("Pressione qualquer tecla para iniciar...");
	getch();

	system("cls");
	desenharBordas();
	lin_log = LIN_INICIO;

	while(arquivoOk || FilasOcupadas(E.Inicio))
	{
		atualizarTela(E, ut, arquivoOk);

		if(arquivoOk)
		{
			if(LerLinhaArquivo(ptr, Animal))
			{
				menor = MenorFila(E);
				if(menor != NULL)
				{
					InserirOrdenadoPrioridade(menor->fila, Animal);
					sprintf(msg, "[+]UT=%-3d %-10s (%s)->%s", ut, Animal.nome, Animal.prioridade, menor->nome);
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
			LiberarEspaco(E);
			return;
		}
		ut++;
	}

	if(arquivoOk)
		fclose(ptr);

	adicionarLog(10, "Simulacao concluida!");
	sprintf(msg, "UT total: %d", ut);
	adicionarLog(10, msg);
	gotoxy(1, LIN_RODAPE + 1);
	printf("Simulacao concluida! UT=%d | Pressione qualquer tecla...", ut);
	getch();
	LiberarEspaco(E);
}

int main(void)
{
	TpDescEsp E;
	Simular(E);
	return 0;
}

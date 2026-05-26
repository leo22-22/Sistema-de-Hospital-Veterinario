#ifndef TADMOLDURA_H
#define TADMOLDURA_H
#include <conio2.h>
#include <windows.h>
#include "TADEspecialidade.h"
#include "ListaAnimais.h"

#define COL_FILA     1
#define COL_LOG     62
#define COL_MAX    119
#define LIN_CAB      1
#define LIN_INICIO   3
#define LIN_RODAPE  49
#define LARG_FILA   58
#define LARG_LOG    57

int lin_log = LIN_INICIO;

void fixarJanela()
{
	HWND hwnd;
	HANDLE hConsole;
	SMALL_RECT windowSize;
	COORD bufferSize;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	bufferSize.X = 120;
	bufferSize.Y = 51;
	SetConsoleScreenBufferSize(hConsole, bufferSize);
	windowSize.Left   = 0;
	windowSize.Top    = 0;
	windowSize.Right  = 119;
	windowSize.Bottom = 50;
	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
	hwnd = GetConsoleWindow();
	SetWindowLong(hwnd, GWL_STYLE,
		GetWindowLong(hwnd, GWL_STYLE) & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX);
}

void limparBloco(int x1, int y1, int x2, int y2)
{
	int i, j;
	for(i = y1; i <= y2; i++)
	{
		gotoxy(x1, i);
		for(j = 0; j < (x2 - x1 + 1); j++)
			putchar(' ');
	}
}

void desenharTelaInicial()
{
	system("cls");
	textcolor(14);
	gotoxy(35, 3);
	printf("+==========================================+");
	gotoxy(35, 4);
	printf("|    HOSPITAL VETERINARIO - ED I 2026     |");
	gotoxy(35, 5);
	printf("|            FIPP / UNOESTE               |");
	gotoxy(35, 6);
	printf("+==========================================+");
	gotoxy(35, 7);
	printf("|                                          |");
	gotoxy(35, 8);
	printf("|      Configuracao inicial do sistema     |");
	gotoxy(35, 9);
	printf("|                                          |");
	gotoxy(35, 10);
	printf("|  - Digite o nome da especialidade        |");
	gotoxy(35, 11);
	printf("|  - Defina o numero de atendentes (1-10)  |");
	gotoxy(35, 12);
	printf("|  - Digite 0 para finalizar               |");
	gotoxy(35, 13);
	printf("|                                          |");
	gotoxy(35, 14);
	printf("+==========================================+");
	textcolor(7);
	gotoxy(35, 16);
}

void desenharBordas()
{
	int i;
	textcolor(14);
	gotoxy(1, LIN_CAB);
	for(i = 1; i <= 120; i++)
		putchar('=');
	gotoxy(1, LIN_CAB + 1);
	printf("| %-56s| %-56s|", "  FILA / ATENDENTES", "  LOG DE EVENTOS");
	gotoxy(1, LIN_CAB + 2);
	for(i = 1; i <= 120; i++)
		putchar('=');
	gotoxy(1, LIN_RODAPE);
	for(i = 1; i <= 120; i++)
		putchar('=');
	for(i = LIN_INICIO; i < LIN_RODAPE; i++)
	{
		gotoxy(COL_LOG - 1, i);
		putchar('|');
		gotoxy(COL_MAX + 1, i);
		putchar('|');
		gotoxy(1, i);
		putchar('|');
	}
	textcolor(7);
}

void desenharCabecalho(int ut, int arquivoOk)
{
	char status[20];
	textcolor(15);
	gotoxy(1, LIN_CAB);
	if(arquivoOk)
		strcpy(status, "Lendo arquivo...");
	else
		strcpy(status, "Arquivo concluido");
	printf("=[ HOSPITAL VETERINARIO - ED I 2026 ]=[ UT: %-5d ]=[ %-17s ]===============", ut, status);
	textcolor(7);
}

void desenharRodape()
{
	textcolor(11);
	gotoxy(1, LIN_RODAPE + 1);
	printf("| [1] Inserir Inicio  [2] Inserir Fim  [3] Remover  | qualquer tecla encerra simulacao          |");
	textcolor(7);
}

void adicionarLog(int cor, char *msg)
{
	if(lin_log >= LIN_RODAPE)
	{
		limparBloco(COL_LOG, LIN_INICIO, COL_MAX, LIN_RODAPE - 1);
		lin_log = LIN_INICIO;
	}
	textcolor(cor);
	gotoxy(COL_LOG, lin_log);
	printf("%-57s", msg);
	textcolor(7);
	lin_log++;
}

void exibirFilaMoldura(TpDescEsp &D)
{
	TpEspecialidade *esp;
	TpAtendente *atend;
	TpAnimal *animal;
	int lin, i, maxAnim, maxAtend, totalEsp;
	char prior[10];

	limparBloco(COL_FILA, LIN_INICIO, COL_LOG - 2, LIN_RODAPE - 1);

	totalEsp = D.Qtde;
	if(totalEsp == 0)
		totalEsp = 1;

	int linsPorEsp = (LIN_RODAPE - LIN_INICIO - 1) / totalEsp;
	if(linsPorEsp < 5)
		linsPorEsp = 5;

	lin = LIN_INICIO;
	esp = D.Inicio;

	while(esp != NULL && lin < LIN_RODAPE - 1)
	{
		textcolor(15);
		gotoxy(COL_FILA, lin);
		printf("|+--[ %-10s fila:%-3d atend:%-3d atendes:%-2d ]--+",
			esp->nome, esp->fila.Qtde,
			esp->atendidos, esp->atendentes.Qtde);
		lin++;

		maxAnim = linsPorEsp / 2;
		if(maxAnim < 1)
			maxAnim = 1;

		animal = esp->fila.Inicio;
		i = 0;
		while(animal != NULL && i < maxAnim && lin < LIN_RODAPE - 1)
		{
			if(strcmp(animal->prioridade, "Emergencia") == 0)
			{
				textcolor(12);
				strcpy(prior, "EMERG");
			}
			else if(strcmp(animal->prioridade, "Urgencia") == 0)
			{
				textcolor(14);
				strcpy(prior, "URGEN");
			}
			else
			{
				textcolor(8);
				strcpy(prior, "ROTIN");
			}
			gotoxy(COL_FILA, lin);
			printf("|  [%s] %-12s %3dut  esp:%3dut",
				prior, animal->nome,
				animal->tempoProc, animal->tempoEspera);
			animal = animal->prox;
			i++;
			lin++;
		}

		if(esp->fila.Qtde > maxAnim && lin < LIN_RODAPE - 1)
		{
			textcolor(8);
			gotoxy(COL_FILA, lin);
			printf("|  (+%d animais na fila...)", esp->fila.Qtde - maxAnim);
			lin++;
		}

		maxAtend = linsPorEsp - maxAnim - 1;
		if(maxAtend < 1)
			maxAtend = 1;

		atend = esp->atendentes.Inicio;
		i = 0;
		while(atend != NULL && i < maxAtend && lin < LIN_RODAPE - 1)
		{
			gotoxy(COL_FILA, lin);
			if(atend->ocupado)
			{
				textcolor(10);
				printf("|  A%-2d [OCUPADO] %-12s restam: %3dut",
					atend->id, atend->animalAtual->nome,
					atend->TempoRestante);
			}
			else
			{
				textcolor(8);
				printf("|  A%-2d [LIVRE]", atend->id);
			}
			atend = atend->prox;
			i++;
			lin++;
		}

		textcolor(8);
		gotoxy(COL_FILA, lin);
		printf("|");
		for(i = 0; i < LARG_FILA - 1; i++)
			putchar('-');
		lin++;

		esp = esp->prox;
	}
	textcolor(7);
}

void atualizarTela(TpDescEsp &D, int ut, int arquivoOk)
{
	desenharCabecalho(ut, arquivoOk);
	exibirFilaMoldura(D);
	desenharRodape();
}

#endif

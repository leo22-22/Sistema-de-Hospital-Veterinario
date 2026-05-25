#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include "TADEspecialidade.h"
#include "TADAnimal.h"

void menu()
{
    system("cls");
    printf("+==========================================+\n");
    printf("|     HOSPITAL VETERINARIO - ED I 2026    |\n");
    printf("|          FIPP / UNOESTE                 |\n");
    printf("+==========================================+\n");
    printf("|                                         |\n");
    printf("|  ESPECIALIDADES:                        |\n");
    printf("|  [1] Inserir Especialidade Inicio       |\n");
    printf("|  [2] Inserir Especialidade Fim          |\n");
    printf("|  [3] Remover Especialidade              |\n");
    printf("|  [4] Exibir Especialidades              |\n");
    printf("|                                         |\n");
    printf("|  ANIMAIS:                               |\n");
    printf("|  [5] Carregar Arquivo                   |\n");
    printf("|  [6] Exibir Fila de Especialidade       |\n");
    printf("|                                         |\n");
    printf("|  [0] Sair                               |\n");
    printf("|                                         |\n");
    printf("+==========================================+\n");
    printf("  Opcao: ");
}

void inicializarAtendentes(TpDescAtendente &A, int numeroAtend)
{
	TpAtendente *novo;
	int i;
	A.Inicio = A.Fim = NULL;
	A.Qtde = 0;
	
	for(i=0;i<numeroAtend ; i++)
	{
		novo = new TpAtendente;
		novo -> prox = NULL;
		novo -> animalAtual = NULL;
		novo -> id = i+1;
		novo -> ocupado = 0;
		novo -> totalAtendidos = 0;
		novo -> TempoRestante = 0;
		
		if(A.Inicio == NULL)
			A.Inicio = A.Fim = novo;
		else{
			A.Fim -> prox = novo;
			A.Fim = novo;
		}
		A.Qtde++;
	}
}
 
int main(void)
{
    TpDescEsp D;
    TpDescAtendente A;
    int opcao, nAtende;

    inicializarEsp(D);
	printf("Quantos Atendentes?\n");
	scanf("%d", &nAtende);
	
	inicializarAtendentes(A,nAtende);
	 
    do
    {
        menu();
        scanf("%d", &opcao);
 
        switch(opcao)
        {
            case 1:
                InserirInicioEsp(D);
                break;
            case 2:
                InserirFimEsp(D);
                break;
            case 3:
                RemoverEsp(D);
                printf("\nPressione qualquer tecla...");
                getch();
                break;
            case 4:
                ExibirEsp(D);
                printf("\nPressione qualquer tecla...");
                getch();
                break;
            case 5:
                CarregarArquivo(D);
                printf("\nPressione qualquer tecla...");
                getch();
                break;
            case 6:
                ExibirFilaEsp(D);
                printf("\nPressione qualquer tecla...");
                getch();
                break;
            case 0:
                printf("\nEncerrando...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
                getch();
                break;
        }
 
    }while(opcao != 0);
 
    LiberarEspaco(D);
    return 0;
}

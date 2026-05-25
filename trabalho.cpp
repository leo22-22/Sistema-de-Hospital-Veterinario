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

void LiberarAtendentes(TpDescAtendente &A)
{
	TpAtendente *aux;
	
	while(A.Inicio != NULL)
	{
		aux = A.Inicio;
		A.Inicio = A.Inicio -> prox;
		delete aux;
	}
	
	A.Fim = NULL;
	A.Qtde = 0;
}

void Simular(TpDescEsp &E, TpDescAtendente &A)
{
	TpAtendente *Aten;
	TpEspecialidade *Esp;
	TpAnimal *Animal;
	TpAnimal *aux;
	int ut = 0 ;
	int tempoSimulacao;
	int opcao;
	
	inicializarEsp(E);
	InserirInicioEsp(E);
	
	printf("Quantos atendentes?\n");
	sanf("%d",&opcao);
	inicializarAtendentes(A, opcao);
	
	CarregarArquivo(E);
	
	printf("Tempo da Simulacao(ut): ");
	scanf("%d", &tempoSimulacao);
	
	while(ut<=tempoSimulacao)
	{
		system("cls");

        printf("/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\n");
        printf("|     HOSPITAL VETERINARIO - ED I 2026    |\n");
        printf("|          UT atual: %-5d                |\n", ut);
        printf("/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\n");

        printf("\n[1] Inserir Especialidade Inicio");
        printf("\n[2] Inserir Especialidade Fim");
        printf("\n[3] Remover Especialidade");
        printf("\n[ENTER] Continuar simulacao\n");
        printf("Opcao: ");
        
        if(hbhit())
        {
        	opcao = getche();
        	
        	if(opcao =='1')
        		InserirInicioEsp(E);
        	else if(opcao == '2')
        		InserirFimEsp(E);
        	else if(opcao == '3')
        		RemoverEsp(E);
        }
        
        ExibirEsp(E);
        
        esp = D.Inicio;
        
        while(esp != NULL)
        {
        	atend = D.Inicio;
        	while(atend != NULL)
        	{
        		if(!atend->ocupado && !FilaVazia(esp->fila))
        		{
        			aux = esp->fila.
        		}
        	}
        }
	}
	
}
 
int main(void)
{
    Simular();
    return 0;
}

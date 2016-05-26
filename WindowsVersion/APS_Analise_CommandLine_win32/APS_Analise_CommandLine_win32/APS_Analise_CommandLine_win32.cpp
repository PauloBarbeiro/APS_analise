// APS_Analise_CommandLine_win32.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<iostream>
#include <sstream>
#include<conio.h>
#include<stdlib.h>

#include <Windows.h>
#include <sys/timeb.h>
#include <ctime>

#include <limits>
#include <time.h>
#include <math.h>
#include <vector>

#include <fstream>
#include <thread>

#ifdef max
#undef max
#endif

#include "AlgoritmosOrdenacao.h"

void criaVetorRandomico(int tamanho, std::vector<int> vetor) {

	int i = 0;
	for (i = 0; i < tamanho; i++) {
		vetor[i] = rand();
	}

}


static void show_usage(std::string name) {
	std::cerr << "--- # ALGORITMOS DE ORDENA��O #---\nvers�o Linux Ubuntu 14.10\n\n" << "Uso:  <op��es> \n" <<
		"\t -h, --help\t Mostra esse painel de ajuda.\n" <<
		"\t -t, --tamanho\t Tamanho do vetor de dados para ordena��o. \n\t\t\tSeguido de um n�mero inteiro, define o tamanho para o vetor de testes:\n\t\t\t -t 10000 -> vetor com dez mil unidades rand�micas.\n" <<
		"\t -rep, --repeticoes\t N�mero de repeti��es de testes. \n\t\t\tSeguido de um n�mero inteiro, define a quantidade de testes:\n\t\t\t -r 10 -> vetor com dez mil unidades rand�micas.\n" <<
		"\tMODOS DE EXECU��O:\n" <<
		"\t -tempo, \t Executa testes de tempo.\n" <<
		//"\t -cpu, \t Executa testes de tempo.\n" <<
		"\t -ticks, \t Executa testes de clock ticks.\n" <<
		"\t -ciclos, \t Executa testes de ciclos.\n" <<
		"\t -multi, \t Executa em multithreads.\n" <<
		"\t -all, \t\t Executa todos os algoritmos.\n" <<
		"\t -bubble, \t\t Executa algoritmo BubbleSort.\n" <<
		"\t -quick, \t\t Executa algoritmo QuickSort.\n" <<
		"\t -merge, \t\t Executa algoritmo MergeSort.\n" <<
		std::endl;
}



int main(int argc, const char * argv[]) {

	
	int objetivoTeste = 0;
	int tamanho = 10;
	//const int tamanho;
	char mtarefas;
	int totalExec = 1;
	bool start_input = true;
	int algoritmo = 0;

	if (argc > 1) {
		std::cout << "Com parametors \n";
		start_input = false;

		for (int a = 1; a<argc; ++a) {

			if (std::string(argv[a]) == "-h" || std::string(argv[a]) == "--help") {
				show_usage(argv[a]);
				return 0;
			}
			if (std::string(argv[a]) == "-t" || std::string(argv[a]) == "--tamanho") {
				std::istringstream ss(argv[a + 1]);
				int x;
				if (!(ss >> x)) {
					std::cerr << "Par�metro inv�lido para atributo -t (" << argv[a + 1] << ")" << std::endl;
					return 0;
				}
				tamanho = x;
				std::cout << "\t Tamanho dos vetores: " << tamanho << std::endl;
			}
			if (std::string(argv[a]) == "-rep" || std::string(argv[a]) == "--repeticoes") {
				std::istringstream ss(argv[a + 1]);
				int x;
				if (!(ss >> x)) {
					std::cerr << "Par�metro inv�lido para atributo -r (" << argv[a + 1] << ")" << std::endl;
					return 0;
				}
				totalExec = x;
				std::cout << "\t Total de repeti��es: " << totalExec << std::endl;
			}
			if (std::string(argv[a]) == "-tempo") {
				objetivoTeste = 1;
			}
			if (std::string(argv[a]) == "-ticks") {
				objetivoTeste = 2;
				std::cout << "\t Testes de Clock Ticks: OK" << std::endl;
			}
			if (std::string(argv[a]) == "-ciclos") {
				objetivoTeste = 3;
				std::cout << "\t Testes de Ciclos: OK" << std::endl;
			}
			//if (std::string(argv[a]) == "-cpu") {
			//	objetivoTeste = 2;
			//	std::cout << "\t Testes de CPU: OK" << std::endl;
			//}
			if (std::string(argv[a]) == "-multi") {
				mtarefas = 'y';
				std::cout << "\t MultiTarefas: OK" << std::endl;
			}
			else { mtarefas = 'n'; }
			if (std::string(argv[a]) == "-all") {
				algoritmo = 4;
				std::cout << "\t Todos os Algoritmos: OK" << std::endl;
			}
			if (std::string(argv[a]) == "-bubble") {
				algoritmo = 1;
				std::cout << "\t Todos o Algoritmo BubbleSort: OK" << std::endl;
			}
			if (std::string(argv[a]) == "-quick") {
				algoritmo = 2;
				std::cout << "\t Todos o Algoritmo QuickSort: OK" << std::endl;
			}
			if (std::string(argv[a]) == "-merge") {
				algoritmo = 3;
				std::cout << "\t Todos o Algoritmo MergeSort: OK" << std::endl;
			}

		}


	}
	std::cout << "= = = = = APS An�lise de Algoritmos de ordena��o = = = = = \n\n";




	do {

		if (argc <= 0 && start_input == true) {
			//int algoritmo = 0;
			std::cout << "Escolha o algoritmo a ser testado:\n" << std::endl;
			std::cout << "1:BubbleSort \t 2:QuickSort: \t 3:MergeSort \t 4:Todos\n" << std::endl;

			while (!(std::cin >> algoritmo)) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Valor inv�lido.  Tente novamente: ";
			}


			std::cout << "   ---- Configura��es de testes ---- \n" << std::endl;


			std::cout << "O que deseja testar nos algoritmos?:\n" << std::endl;
			std::cout << "1:Tempo de execu��o \t 3:ClockTicks \t 4:Ciclos de execu��o\n" << std::endl;

			while (!(std::cin >> objetivoTeste)) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Valor inv�lido.  Tente novamente: ";
			}



			std::cout << "Digite o tamanho do vetor para testes:" << std::endl;
			while (!(std::cin >> tamanho)) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Valor inv�lido.  Tente novamente: ";
			}



			std::cout << "Digite a quantidade de execus�es para essa bateria de testes:" << std::endl;
			while (!(std::cin >> totalExec)) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Valor inv�lido.  Tente novamente: ";
			}



			std::cout << "Usar multitarefas nos testes? Y/N" << std::endl;
			std::cin >> mtarefas;
			bool wrong_input = true;
			if (!(mtarefas != 'Y' && mtarefas != 'y') || !(mtarefas != 'N' && mtarefas != 'n')) {
				wrong_input = false;
			}
			while (wrong_input) {
				std::cout << "Valor inv�lido.  Tente novamente: ";
				std::cin >> mtarefas;
				if (!(mtarefas != 'Y' && mtarefas != 'y') || !(mtarefas != 'N' && mtarefas != 'n')) {
					wrong_input = false;
				}
				std::cin.clear();
			}

		}


		// --------------------------------------- SINGLETASK

			//std::vector<int[]> vetor_de_testes(1);
			//vetor_de_testes.reserve(1);

			const int tama = tamanho;
			int vetor_de_testes[tama];

			//criaVetorRandomico(tamanho, vbs);

			BubbleSort *bubbleS;
			QuickSort *quickS;
			MergeSort *mergeS;
			std::cout << "ALgoritmo: " << algoritmo << std::endl;
			switch (algoritmo) {
			case 1:
				bubbleS = new BubbleSort();
				break;
			case 2:
				quickS = new QuickSort();
				break;
			case 3:
				mergeS = new MergeSort();
				break;
			case 4:
				bubbleS = new BubbleSort();
				quickS = new QuickSort();
				mergeS = new MergeSort();
				break;
			}

			int count_exec = 0;
			while (count_exec < totalExec) {

				//1:Tempo de execu��o \t 2:Tempo de CPU: \t 3:ClockTicks \t 4:Ciclos de execu��o
				switch (algoritmo) {
				case 1:
					std::cout << "Iniciando testes BubbleSort ..." << std::endl;
					if (objetivoTeste == 1) {
						criaVetorRandomico(tamanho, vetor_de_testes[0]);
						bubbleS->avaliaTempoDeExecucaoTotal(vetor_de_testes[0], tamanho, true);
					}
					//else if (objetivoTeste == 2) {
					//	criaVetorRandomico(tamanho, vetor_de_testes);
					//	bubbleS->avaliaTempoCPU(vetor_de_testes, tamanho, true);
					//}
					else if (objetivoTeste == 2) {
						criaVetorRandomico(tamanho, vetor_de_testes[0]);
						bubbleS->avaliaClockTicksTotal(vetor_de_testes[0], tamanho, true);
					}
					else if (objetivoTeste == 3) {
						criaVetorRandomico(tamanho, vetor_de_testes[0]);
						bubbleS->avaliaCiclosTotal(vetor_de_testes[0], tamanho, true);
					}
					break;
				case 2:
					std::cout << "Iniciando testes QuickSort ..." << std::endl;
					if (objetivoTeste == 1) {
						criaVetorRandomico(tamanho, vetor_de_testes[0]);
						quickS->avaliaTempoDeExecucaoTotal(vetor_de_testes[0], tamanho, true);
					}
					//else if (objetivoTeste == 2) {
					//	criaVetorRandomico(tamanho, vetor_de_testes);
					//	quickS->avaliaTempoCPU(vetor_de_testes, tamanho, true);
					//}
					else if (objetivoTeste == 2) {
						criaVetorRandomico(tamanho, vetor_de_testes[0]);
						quickS->avaliaClockTicksTotal(vetor_de_testes[0], tamanho, true);
					}
					else if (objetivoTeste == 3) {
						criaVetorRandomico(tamanho, vetor_de_testes[0]);
						quickS->avaliaCiclosTotal(vetor_de_testes[0], tamanho, true);
					}
					break;
				case 3:
					std::cout << "Iniciando testes MergeSort ..." << std::endl;
					if (objetivoTeste == 1) {
						criaVetorRandomico(tamanho, vetor_de_testes[0]);
						mergeS->avaliaTempoDeExecucaoTotal(vetor_de_testes[0], 0, tamanho - 1, tamanho, true);
					}
					//else if (objetivoTeste == 2) {
					//	criaVetorRandomico(tamanho, vetor_de_testes);
					//	mergeS->avaliaTempoCPU(vetor_de_testes, 0, tamanho - 1, tamanho, true);
					//}
					else if (objetivoTeste == 2) {
						criaVetorRandomico(tamanho, vetor_de_testes[0]);
						mergeS->avaliaClockTicksTotal(vetor_de_testes[0], 0, tamanho - 1, tamanho, true);
					}
					else if (objetivoTeste == 3) {
						criaVetorRandomico(tamanho, vetor_de_testes[0]);
						mergeS->avaliaCiclosTotal(vetor_de_testes[0], 0, tamanho - 1, tamanho, true);
					}
					break;
				case 4:
					std::cout << "Iniciando testes em todos os algoritmos ..." << std::endl;
					if (objetivoTeste == 1) {
						criaVetorRandomico(tamanho, vetor_de_testes[0]);
						bubbleS->avaliaTempoDeExecucaoTotal(vetor_de_testes[0], tamanho, true);
						criaVetorRandomico(tamanho, vetor_de_testes[0]);
						quickS->avaliaTempoDeExecucaoTotal(vetor_de_testes[0], tamanho, true);
						criaVetorRandomico(tamanho, vetor_de_testes[0]);
						mergeS->avaliaTempoDeExecucaoTotal(vetor_de_testes[0], 0, tamanho - 1, tamanho, true);
					}
					//else if (objetivoTeste == 2) {
					//	criaVetorRandomico(tamanho, vetor_de_testes);
					//	bubbleS->avaliaTempoCPU(vetor_de_testes, tamanho, true);
					//	criaVetorRandomico(tamanho, vetor_de_testes);
					//	quickS->avaliaTempoCPU(vetor_de_testes, tamanho, true);
					//	criaVetorRandomico(tamanho, vetor_de_testes);
					//	mergeS->avaliaTempoCPU(vetor_de_testes, 0, tamanho - 1, tamanho, true);
					//}
					else if (objetivoTeste == 2) {
						criaVetorRandomico(tamanho, vetor_de_testes[0]);
						bubbleS->avaliaClockTicksTotal(vetor_de_testes[0], tamanho, true);
						criaVetorRandomico(tamanho, vetor_de_testes[0]);
						quickS->avaliaClockTicksTotal(vetor_de_testes[0], tamanho, true);
						criaVetorRandomico(tamanho, vetor_de_testes[0]);
						mergeS->avaliaClockTicksTotal(vetor_de_testes[0], 0, tamanho - 1, tamanho, true);
					}
					else if (objetivoTeste == 3) {
						criaVetorRandomico(tamanho, vetor_de_testes[0]);
						bubbleS->avaliaCiclosTotal(vetor_de_testes[0], tamanho, true);
						criaVetorRandomico(tamanho, vetor_de_testes[0]);
						quickS->avaliaCiclosTotal(vetor_de_testes[0], tamanho, true);
						criaVetorRandomico(tamanho, vetor_de_testes[0]);
						mergeS->avaliaCiclosTotal(vetor_de_testes[0], 0, tamanho - 1, tamanho, true);
					}
					break;
				}

				count_exec += 1;
			}

		

		std::cout << "Confira os resultados gravados nos arquivos de log.\n" << std::endl;

		

		char start_test;
		std::cout << "Reiniciar os Testes? Y/N" << std::endl;
		std::cin >> start_test;
		if (!(start_test != 'Y' && start_test != 'y')) {
			start_input = true;
		}
		else if (!(start_test != 'N' && start_test != 'n')) {
			start_input = false;
		}
	} while (start_input);



	return 0;

}
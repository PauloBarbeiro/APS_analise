#include "stdafx.h"
#include "AlgoritmosOrdenacao.h"


#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#define BILLION 1000000000L


void AlgoritmosOrdenacao::gravaRegistroDeTempo(std::string nome, int tam, bool thread) {
	struct tm timeinfo;
	struct tm timeinfo2;
	localtime_s(&timeinfo, &startTime);
	localtime_s(&timeinfo2, &endTime);
	strftime(inicio, 20, "%Y-%m-%d %H:%M:%S", &timeinfo);
	strftime(fim, 20, "%Y-%m-%d %H:%M:%S", &timeinfo2);

	std::string textFileName = nome + ".txt";

	std::ofstream textFile;
	std::ostringstream strs;
	strs << elapsedTime;
	std::string fileContent = "algoritmo:";
	fileContent += algoritmo;
	fileContent += "|tamanho:";
	fileContent += tam;
	fileContent += "|mainThread:";
	fileContent += thread;
	fileContent += "|inicio:";
	fileContent += inicio;
	fileContent += "|fim:";
	fileContent += fim;
	fileContent += "|duracao(nanosec):";
	fileContent += strs.str();
	fileContent += "\n";

	textFile.open(textFileName, std::ios::app);
	textFile << fileContent;
	textFile.close();

}

void AlgoritmosOrdenacao::gravaRegistroDeTicks(std::string nome, int tam, bool thread) {

	struct tm timeinfo;
	struct tm timeinfo2;
	localtime_s(&timeinfo, &startTime);
	localtime_s(&timeinfo2, &endTime);
	strftime(inicio, 20, "%Y-%m-%d %H:%M:%S", &timeinfo);
	strftime(fim, 20, "%Y-%m-%d %H:%M:%S", &timeinfo2);

	std::string textFileName = nome + ".txt";

	std::ofstream textFile;

	textFile.open(textFileName, std::ios::app);
	textFile << "algoritmo:" << algoritmo << "|tamanho:" << tam << "|mainThread:" << thread << "|inicio:" << inicio << "|fim:" << fim << "|clockticks:" << t << std::endl;
	textFile.close();

}


void AlgoritmosOrdenacao::gravaRegistroDeCiclos(std::string nome, int tam, bool thread) {

	struct tm timeinfo;
	struct tm timeinfo2;
	localtime_s(&timeinfo, &startTime);
	localtime_s(&timeinfo2, &endTime);
	strftime(inicio, 20, "%Y-%m-%d %H:%M:%S", &timeinfo);
	strftime(fim, 20, "%Y-%m-%d %H:%M:%S", &timeinfo2);

	std::string textFileName = nome + ".txt";

	std::ofstream textFile;

	textFile.open(textFileName, std::ios::app);
	textFile << "algoritmo:" << algoritmo << "|tamanho:" << tam << "|mainThread:" << thread << "|inicio:" << inicio << "|fim:" << fim << "|ciclos:" << ciclos << std::endl;
	textFile.close();

}
//*/

/* ========================================================================================  */



void BubbleSort::avaliaTempoDeExecucaoTotal(int *v, int tam, bool thread) {
	int tamanho = tam;
	//inicio da avaliação
	time(&startTime);
	// get ticks per second
	QueryPerformanceFrequency(&frequency);
	// start timer
	QueryPerformanceCounter(&t1);



	int i = tam;
	int trocou;
	do {
		tam--;
		trocou = 0;
		for (i = 0; i < tam; i++) {
			if (v[i] > v[i + 1]) {
				int aux = 0;
				aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				trocou = 1;
				//for(k = 0; k < j; k++)
				//    printf("%d ", v[k]);
				//printf("%d",i);
			}
		}
	} while (trocou);

	//fim da avaliação
	// tempo em milisegundos
	QueryPerformanceCounter(&t2);
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
	time(&endTime);

	gravaRegistroDeTempo("BubbleSort_TempoExecTotal", tamanho, thread);

}

void BubbleSort::avaliaClockTicksTotal(int *v, int tam, bool thread) {
	int tamanho = tam;
	//inicio da avaliação
	time(&startTime);
	t = clock();

	int i = tam;
	int trocou;
	do {
		tam--;
		trocou = 0;
		for (i = 0; i < tam; i++) {
			if (v[i] > v[i + 1]) {
				int aux = 0;
				aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				trocou = 1;
				//for(k = 0; k < j; k++)
				//    printf("%d ", v[k]);
				//printf("%d",i);
			}
		}
	} while (trocou);

	//fim da avaliação
	t = clock() - t;
	time(&endTime);
	gravaRegistroDeTicks("BubbleSort_TicksExecTotal", tamanho, thread);

}



void BubbleSort::avaliaCiclosTotal(int *v, int tam, bool thread) {

	//inicio da avaliação
	int tamanho = tam;
	ciclos = 0;

	int i = tam;
	int trocou;
	do {
		tam--;
		trocou = 0;
		for (i = 0; i < tam; i++) {
			if (v[i] > v[i + 1]) {
				int aux = 0;
				aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				trocou = 1;

				ciclos += 1;

			}
		}
	} while (trocou);


	gravaRegistroDeCiclos("BubbleSort_CiclosExecTotal", tamanho, thread);

} //*/


  /* ===========================================================================================  */




  //Algoritmo de ordenacao QuickSort
void QuickSort::executaQuick(int* v, int tam) {
	//int j = tam, k;
	if (tam <= 1)
		return;
	else {
		int x = v[0];
		int a = 1;
		int b = tam - 1;
		do {
			while ((a < tam) && (v[a] <= x))
				a++;
			while (v[b] > x)
				b--;
			if (a < b) { // faz troca
				int temp = v[a];
				v[a] = v[b];
				v[b] = temp;
				a++;
				b--;
			}
			//for(k = 0; k < j; k++)
			//    printf("%d ", v[k]);
			//printf("\n");
		} while (a <= b);
		// troca pivo
		v[0] = v[b];
		v[b] = x;
		// ordena sub-vetores restantes
		executaQuick(v, b);
		executaQuick(&v[a], tam - a);
		//for(k = 0; k < j; k++)
		//    printf("%d ", v[k]);
		//printf("\n");
	}
}



void QuickSort::avaliaTempoDeExecucaoTotal(int *v, int tam, bool thread) {

	//inicio da avaliação
	time(&startTime);
	// get ticks per second
	QueryPerformanceFrequency(&frequency);
	// start timer
	QueryPerformanceCounter(&t1);

	executaQuick(v, tam);

	//fim da avaliação
	// tempo em milisegundos
	QueryPerformanceCounter(&t2);
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
	time(&endTime);
	gravaRegistroDeTempo("QuickSort_TempoExecTotal", tam, thread);

}

void QuickSort::avaliaClockTicksTotal(int *v, int tam, bool thread) {

	//inicio da avaliação
	time(&startTime);
	t = clock();

	//int j = tam;
	if (tam <= 1)
		return;
	else {
		int x = v[0];
		int a = 1;
		int b = tam - 1;
		do {
			while ((a < tam) && (v[a] <= x))
				a++;
			while (v[b] > x)
				b--;
			if (a < b) { // faz troca
				int temp = v[a];
				v[a] = v[b];
				v[b] = temp;
				a++;
				b--;
			}
			//for(k = 0; k < j; k++)
			//    printf("%d ", v[k]);
			//printf("%d",j);
		} while (a <= b);
		// troca pivo
		v[0] = v[b];
		v[b] = x;
		// ordena sub-vetores restantes
		avaliaClockTicksTotal(v, b, thread);
		avaliaClockTicksTotal(&v[a], tam - a, thread);
		//for(k = 0; k < j; k++)
		//    printf("%d ", v[k]);
		//printf("\n");
	}

	//fim da avaliação
	t = clock() - t;
	time(&endTime);
	gravaRegistroDeTicks("QuickSort_TicksExecTotal", tam, thread);

}


void QuickSort::avaliaCiclosTotal(int *v, int tam, bool thread) {

	//inicio da avaliação
	time(&startTime);


	executaQuick(v, tam);

	//fim da avaliação
	ciclos += 1; //TODO :: isso esta errado
	time(&endTime);
	gravaRegistroDeTicks("QuickSort_CiclosExecTotal", tam, thread);

}



//*/


/* ========================================================================================= */



void MergeSort::executaMergeSort(int* v, int inicio, int fim) {
	int i, j, k, meio, *t;
	if (inicio == fim)
		return;
	//ordenacao recursiva das duas metades
	meio = (inicio + fim) / 2;
	executaMergeSort(v, inicio, meio);
	executaMergeSort(v, meio + 1, fim);
	//intercalacao no vetor temporario t
	i = inicio;
	j = meio + 1;
	k = 0;
	t = (int*)malloc(sizeof(int)*(fim - inicio + 1));
	while (i < meio + 1 || j < fim + 1) {
		if (i == meio + 1) { //i passou do final da primeira metade, pegar v[j]
			t[k] = v[j];
			j++; k++;
		}
		else if (j == fim + 1) { //j passou do final da segunda metade, pegar v[i]
			t[k] = v[i];
			i++; k++;
		}
		else if (v[i] < v[j]) { //v[i]<v[j], pegar v[i]
			t[k] = v[i];
			i++; k++;
		}
		else { //v[j]<=v[i], pegar v[j]
			t[k] = v[j];
			j++; k++;
		}
		//for(z = 0; z < tamanho; z++)
		//    printf("%d ", v[z]);
		//printf("\n");
	}
	//copia vetor intercalado para o vetor original
	for (i = inicio; i <= fim; i++)
		v[i] = t[i - inicio];
	//for(z = 0; z < tamanho; z++)
	//    printf("%d ", v[z]);
	//printf("\n");
	free(t);
}

void MergeSort::avaliaTempoDeExecucaoTotal(int* v, int inicio, int fim, int tam, bool thread) {

	//inicio da avaliação
	time(&startTime);
	// get ticks per second
	QueryPerformanceFrequency(&frequency);
	// start timer
	QueryPerformanceCounter(&t1);


	executaMergeSort(v, inicio, fim);

	//fim da avaliação
	// tempo em milisegundos
	QueryPerformanceCounter(&t2);
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
	time(&endTime);

	gravaRegistroDeTempo("MergeSort_TempoExecTotal", tam, thread);

}

void MergeSort::avaliaClockTicksTotal(int* v, int inicio, int fim, int tam, bool thread) {

	//int tamanho = tam;
	//inicio da avaliação
	time(&startTime);
	t = clock();

	executaMergeSort(v, inicio, fim);

	//fim da avaliação
	t = clock() - t;
	time(&endTime);
	gravaRegistroDeTicks("MergeSort_TicksExecTotal", tam, thread);

}

void MergeSort::avaliaCiclosTotal(int* v, int inicio, int fim, int tam, bool thread) {

	//inicio da avaliação
	//int tamanho = tam;
	ciclos = 0;

	executaMergeSort(v, inicio, fim);


	//fim da avaliação
	// TODO - avaliação de ciclos esta errada
	ciclos += 1;

	gravaRegistroDeTicks("MergeSort_CiclosExecTotal", tam, thread);

}


//*/

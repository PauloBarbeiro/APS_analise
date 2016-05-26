#pragma once

#include <iostream>
#include <time.h>
#include <thread>
#include <Windows.h>


class AlgoritmosOrdenacao
{
public:
	//AlgoritmosOrdenacao();
	//virtual ~AlgoritmosOrdenacao();

	std::string algoritmo;

	//para timestamp
	time_t startTime, endTime;
	char inicio[20], fim[20];

	//Time on Windows
	LARGE_INTEGER	frequency;        // ticks per second
	LARGE_INTEGER t1, t2;           // ticks
	double elapsedTime;

	//variáveis para clock ticks
	clock_t t;

	int ciclos;

	bool inMainThread;

	void avaliaTempoDeExecucaoTotal(int* v, int tam, bool thread);
	void avaliaClockTicksTotal(int* v, int tam, bool thread);
	void avaliaCiclosTotal(int* v, int tam, bool thread);
	//void avaliaTempoCPU(int *v, int tam, bool thread);

	//para mergesort
	void avaliaTempoDeExecucaoTotal(int* v, int inicio, int fim, int tam, bool thread);
	void avaliaClockTicksTotal(int* v, int inicio, int fim, int tam, bool thread);
	void avaliaCiclosTotal(int* v, int inicio, int fim, int tam, bool thread);
	//void avaliaTempoCPU(int* v, int inicio, int fim, int tam, bool thread);

	//virtual void avaliaTempoDeExecucaoTotal() = 0;
	void gravaRegistroDeTempo(std::string nome, int tam, bool thread);
	void gravaRegistroDeTicks(std::string nome, int tam, bool thread);
	void gravaRegistroDeCiclos(std::string nome, int tam, bool thread);

protected:
private:
};



class BubbleSort : public AlgoritmosOrdenacao {

public:

	BubbleSort() {
		algoritmo = "BubbleSort";
	}

	void avaliaTempoDeExecucaoTotal(std::vector<int> v, int tam, bool thread);
	void avaliaClockTicksTotal(std::vector<int>, int tam, bool thread);
	void avaliaCiclosTotal(std::vector<int>, int tam, bool thread);
	//void avaliaTempoCPU(int *v, int tam, bool thread);

	std::thread avaliaTempo(int* v, int tam) {
		return std::thread([=] { avaliaTempoDeExecucaoTotal(v, tam, false); });
	}

	//std::thread avaliaCPU(int* v, int tam) { return std::thread([=] { avaliaTempoCPU(v, tam, false); });	}

	std::thread avaliaTicks(int* v, int tam) {
		return std::thread([=] { avaliaClockTicksTotal(v, tam, false); });
	}

	std::thread avaliaCiclos(int* v, int tam) {
		return std::thread([=] { avaliaCiclosTotal(v, tam, false); });
	}

};//*/




class QuickSort : public AlgoritmosOrdenacao {

public:
	QuickSort() {
		algoritmo = "QuickSort";
	}

	void executaQuick(int* v, int tam);

	void avaliaTempoDeExecucaoTotal(int* v, int tam, bool thread);
	void avaliaClockTicksTotal(int* v, int tam, bool thread);
	void avaliaCiclosTotal(int* v, int tam, bool thread);
	//void avaliaTempoCPU(int *v, int tam, bool thread);

	std::thread avaliaTempo(int* v, int tam) {
		return std::thread([=] { avaliaTempoDeExecucaoTotal(v, tam, false); });
	}

	//std::thread avaliaCPU(int* v, int tam) { return std::thread([=] { avaliaTempoCPU(v, tam, false); });}

	std::thread avaliaTicks(int* v, int tam) {
		return std::thread([=] { avaliaClockTicksTotal(v, tam, false); });
	}

	std::thread avaliaCiclos(int* v, int tam) {
		return std::thread([=] { avaliaCiclosTotal(v, tam, false); });
	}

};//*/




class MergeSort : public AlgoritmosOrdenacao {

public:
	MergeSort() {
		algoritmo = "MergeSort";
	}
	void executaMergeSort(int* v, int inicio, int fim);

	void avaliaTempoDeExecucaoTotal(int* v, int inicio, int fim, int tam, bool thread);
	void avaliaClockTicksTotal(int* v, int inicio, int fim, int tam, bool thread);
	void avaliaCiclosTotal(int* v, int inicio, int fim, int tam, bool thread);
	//void avaliaTempoCPU(int* v, int inicio, int fim, int tam, bool thread);

	std::thread avaliaTempo(int* v, int inicio, int fim, int tam) {
		return std::thread([=] { avaliaTempoDeExecucaoTotal(v, inicio, fim, tam, false); });
	}

	//std::thread avaliaCPU(int* v, int inicio, int fim, int tam) { return std::thread([=] { avaliaTempoCPU(v, inicio, fim, tam, false); });}

	std::thread avaliaTicks(int* v, int inicio, int fim, int tam) {
		return std::thread([=] { avaliaClockTicksTotal(v, inicio, fim, tam, false); });
	}

	std::thread avaliaCiclos(int* v, int inicio, int fim, int tam) {
		return std::thread([=] { avaliaCiclosTotal(v, inicio, fim, tam, false); });
	}

}; //*/
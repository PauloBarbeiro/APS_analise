#include "algoritmos_ordenacao.h"

#include <iostream>
#include <fstream>

#define BILLION 1000000000L

void BubbleSort::avaliaTempoDeExecucaoTotal(int *v, int tam){
    int tamanho = tam;
    //inicio da avaliação
    time( &startTime );
    //start = mach_absolute_time();
    clock_gettime(CLOCK_MONOTONIC, &start_t);	/* mark start time */



    int i = tam;
    int trocou;
    do{
        tam--;
        trocou = 0;
        for(i = 0; i < tam; i++){
            if(v[i] > v[i + 1]){
                int aux = 0;
                aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
                trocou = 1;
                //for(k = 0; k < j; k++)
                //    printf("%d ", v[k]);
                //printf("%d",i);
            }
        }
    }while(trocou);

    //fim da avaliação
    clock_gettime(CLOCK_MONOTONIC, &end_t);	/* mark the end time */
    time( &endTime );

    diff = BILLION * (end_t.tv_sec - start_t.tv_sec) + end_t.tv_nsec - start_t.tv_nsec;
	//printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);

    gravaRegistroDeTempo("BubbleSort_TempoExecTotal", tamanho);

}

void BubbleSort::avaliaClockTicksTotal(int *v, int tam){
    int tamanho = tam;
    //inicio da avaliação
    time( &startTime );
    t = clock();

    int i = tam;
    int trocou;
    do{
        tam--;
        trocou = 0;
        for(i = 0; i < tam; i++){
            if(v[i] > v[i + 1]){
                int aux = 0;
                aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
                trocou = 1;
                //for(k = 0; k < j; k++)
                //    printf("%d ", v[k]);
                //printf("%d",i);
            }
        }
    }while(trocou);

    //fim da avaliação
    t = clock() - t;
    time( &endTime );
    gravaRegistroDeTicks("BubbleSort_TicksExecTotal", tamanho);

}

void BubbleSort::avaliaTempoCPU(int *v, int tam){
    int tamanho = tam;
    //inicio da avaliação
    time( &startTime );
    //start = mach_absolute_time();
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_t);	/* mark start time */



    int i = tam;
    int trocou;
    do{
        tam--;
        trocou = 0;
        for(i = 0; i < tam; i++){
            if(v[i] > v[i + 1]){
                int aux = 0;
                aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
                trocou = 1;
                //for(k = 0; k < j; k++)
                //    printf("%d ", v[k]);
                //printf("%d",i);
            }
        }
    }while(trocou);

    //fim da avaliação
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_t);	/* mark the end time */
    time( &endTime );

    diff = BILLION * (end_t.tv_sec - start_t.tv_sec) + end_t.tv_nsec - start_t.tv_nsec;
	//printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);

    gravaRegistroDeTempo("BubbleSort_TempoExecTotal", tamanho);

}

/* ========================================================================================= */



void BubbleSort::avaliaTempoDeExecucaoParte1(int *v, int tam){
    int tamanho = tam;
    int i = tam;
    int trocou;
    do{

        //inicio da avaliação
        time( &startTime );
        clock_gettime(CLOCK_MONOTONIC, &start_t);	/* mark start time */

        tam--;
        trocou = 0;
        for(i = 0; i < tam; i++){
            if(v[i] > v[i + 1]){
                int aux = 0;
                aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
                trocou = 1;
                //for(k = 0; k < j; k++)
                //    printf("%d ", v[k]);
                //printf("%d",i);
            }
        }

        //fim da avaliação
        clock_gettime(CLOCK_MONOTONIC, &end_t);	/* mark the end time */
        time( &endTime );

        diff = BILLION * (end_t.tv_sec - start_t.tv_sec) + end_t.tv_nsec - start_t.tv_nsec;

        gravaRegistroDeTempo("BubbleSort_TempoExecParte1", tamanho);

    }while(trocou);

}



void BubbleSort::avaliaClockTicksParte1(int *v, int tam){
    int tamanho = tam;
    int i = tam;
    int trocou;
    do{

        //inicio da avaliação
        time( &startTime );
        t = clock();

        tam--;
        trocou = 0;
        for(i = 0; i < tam; i++){
            if(v[i] > v[i + 1]){
                int aux = 0;
                aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
                trocou = 1;
                //for(k = 0; k < j; k++)
                //    printf("%d ", v[k]);
                //printf("%d",i);
            }
        }

        //fim da avaliação
        t = clock() - t;
        time( &endTime );
        gravaRegistroDeTicks("BubbleSort_TicksExecParte1", tamanho);

    }while(trocou);

}


/* ======================================================================================= */


void BubbleSort::avaliaTempoDeExecucaoParte2(int *v, int tam){
    int tamanho = tam;
    int i = tam;
    int trocou;
    do{

        tam--;
        trocou = 0;
        for(i = 0; i < tam; i++){
            if(v[i] > v[i + 1]){

                //inicio da avaliação
                time( &startTime );
                clock_gettime(CLOCK_MONOTONIC, &start_t);	/* mark start time */

                int aux = 0;
                aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
                trocou = 1;
                //for(k = 0; k < j; k++)
                //    printf("%d ", v[k]);

                //fim da avaliação
                clock_gettime(CLOCK_MONOTONIC, &end_t);	/* mark the end time */
                time( &endTime );
                diff = BILLION * (end_t.tv_sec - start_t.tv_sec) + end_t.tv_nsec - start_t.tv_nsec;
                gravaRegistroDeTempo("BubbleSort_TempoExecParte2", tamanho);

                printf("%d",i);
            }
        }

    }while(trocou);

}


void BubbleSort::avaliaClockTicksParte2(int *v, int tam){
    int tamanho = tam;
    int i = tam;
    int trocou;
    do{
        tam--;
        trocou = 0;
        for(i = 0; i < tam; i++){
            if(v[i] > v[i + 1]){

                //inicio da avaliação
                time( &startTime );
                t = clock();

                int aux = 0;
                aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
                trocou = 1;
                //for(k = 0; k < j; k++)
                //    printf("%d ", v[k]);

                //fim da avaliação
                t = clock() - t;
                time( &endTime );
                gravaRegistroDeTicks("BubbleSort_TicksExecParte2", tamanho);

                //printf("%d",i);
            }
        }

    }while(trocou);

}



void BubbleSort::gravaRegistroDeTempo(std::string nome, int tam){

    strftime(inicio, 20, "%Y-%m-%d %H:%M:%S", localtime(&startTime));
    strftime(fim, 20, "%Y-%m-%d %H:%M:%S", localtime(&endTime));

    std::string textFileName = nome+".txt";

    std::ofstream textFile;

    textFile.open(textFileName, std::ios::app);
    textFile << "algoritmo:" << algoritmo << "|tamanho:" << tam << "|inicio:" << inicio << "|fim:" << fim << "|duracao(nanosec):" << (long long unsigned int) diff /*<< "|duracao(seg):" << (float)(end_t.tv_nsec - start_t.tv_nsec)/BILLION*/ << std::endl;
    textFile.close();

}

void BubbleSort::gravaRegistroDeTicks(std::string nome, int tam){

    strftime(inicio, 20, "%Y-%m-%d %H:%M:%S", localtime(&startTime));
    strftime(fim, 20, "%Y-%m-%d %H:%M:%S", localtime(&endTime));

    std::string textFileName = nome+".txt";

    std::ofstream textFile;

    textFile.open(textFileName, std::ios::app);
    textFile << "algoritmo:" << algoritmo << "|tamanho:" << tam << "|inicio:" << inicio << "|fim:" << fim << "|clockticks:" << t  << std::endl;
    textFile.close();

}



/*  ##################################################################################################
    ##################################################################################################
    ##################################################################################################
    ##################################################################################################
*/





//Algoritmo de ordenacao QuickSort
void QuickSort::executaQuick(int* v, int tam){
    int j = tam, k;
    if (tam <= 1)
        return;
    else {
        int x = v[0];
        int a = 1;
        int b = tam-1;
        do{
            while((a < tam) && (v[a] <= x))
                a++;
            while(v[b] > x)
                b--;
            if(a < b){ // faz troca
                int temp = v[a];
                v[a] = v[b];
                v[b] = temp;
                a++;
                b--;
            }
            //for(k = 0; k < j; k++)
            //    printf("%d ", v[k]);
            //printf("\n");
        }while(a <= b);
        // troca pivo
        v[0] = v[b];
        v[b] = x;
        // ordena sub-vetores restantes
        executaQuick(v, b);
        executaQuick(&v[a], tam-a);
        //for(k = 0; k < j; k++)
        //    printf("%d ", v[k]);
        //printf("\n");
    }
}



void QuickSort::avaliaTempoDeExecucaoTotal(int *v, int tam){

    //inicio da avaliação
    time( &startTime );
    clock_gettime(CLOCK_MONOTONIC, &start_t);	/* mark start time */

    executaQuick(v, tam);

    //fim da avaliação
    clock_gettime(CLOCK_MONOTONIC, &end_t);	/* mark the end time */
    time( &endTime );
    diff = BILLION * (end_t.tv_sec - start_t.tv_sec) + end_t.tv_nsec - start_t.tv_nsec;
    gravaRegistroDeTempo("QuickSort_TempoExecTotal", tam);

}

void QuickSort::avaliaClockTicksTotal(int *v, int tam){

    //inicio da avaliação
    time( &startTime );
    t = clock();

    int j = tam;
    if (tam <= 1)
        return;
    else {
        int x = v[0];
        int a = 1;
        int b = tam-1;
        do{
            while((a < tam) && (v[a] <= x))
                a++;
            while(v[b] > x)
                b--;
            if(a < b){ // faz troca
                int temp = v[a];
                v[a] = v[b];
                v[b] = temp;
                a++;
                b--;
            }
            //for(k = 0; k < j; k++)
            //    printf("%d ", v[k]);
            //printf("%d",j);
        }while(a <= b);
        // troca pivo
        v[0] = v[b];
        v[b] = x;
        // ordena sub-vetores restantes
        avaliaClockTicksTotal(v, b);
        avaliaClockTicksTotal(&v[a], tam-a);
        //for(k = 0; k < j; k++)
        //    printf("%d ", v[k]);
        //printf("\n");
    }

    //fim da avaliação
    t = clock() - t;
    time( &endTime );
    gravaRegistroDeTicks("QuickSort_TicksExecTotal", tam);

}



/* ========================================================================================= */



void QuickSort::avaliaTempoDeExecucaoParte1(int *v, int tam){
    int i = tam, k;
    int trocou;
    do{

        //inicio da avaliação
        time( &startTime );
        clock_gettime(CLOCK_MONOTONIC, &start_t);	/* mark start time */

        tam--;
        trocou = 0;
        for(i = 0; i < tam; i++){
            if(v[i] > v[i + 1]){
                int aux = 0;
                aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
                trocou = 1;
                //for(k = 0; k < j; k++)
                //    printf("%d ", v[k]);
                //printf("%d",i);
            }
        }

        //fim da avaliação
        clock_gettime(CLOCK_MONOTONIC, &end_t);	/* mark the end time */
        time( &endTime );
        diff = BILLION * (end_t.tv_sec - start_t.tv_sec) + end_t.tv_nsec - start_t.tv_nsec;
        gravaRegistroDeTempo("BubbleSort_TempoExecParte1", tam);

    }while(trocou);

}



void QuickSort::avaliaClockTicksParte1(int *v, int tam){

    int i = tam, k;
    int trocou;
    do{

        //inicio da avaliação
        time( &startTime );
        t = clock();

        tam--;
        trocou = 0;
        for(i = 0; i < tam; i++){
            if(v[i] > v[i + 1]){
                int aux = 0;
                aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
                trocou = 1;
                //for(k = 0; k < j; k++)
                //    printf("%d ", v[k]);
                //printf("%d",i);
            }
        }

        //fim da avaliação
        t = clock() - t;
        time( &endTime );
        gravaRegistroDeTicks("BubbleSort_TicksExecParte1", tam);

    }while(trocou);

}


/* ======================================================================================= */


void QuickSort::avaliaTempoDeExecucaoParte2(int *v, int tam){

    int i, j = tam, k;
    int trocou;
    do{

        tam--;
        trocou = 0;
        for(i = 0; i < tam; i++){
            if(v[i] > v[i + 1]){

                //inicio da avaliação
                time( &startTime );
                clock_gettime(CLOCK_MONOTONIC, &start_t);	/* mark start time */

                int aux = 0;
                aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
                trocou = 1;
                //for(k = 0; k < j; k++)
                //    printf("%d ", v[k]);

                //fim da avaliação
                clock_gettime(CLOCK_MONOTONIC, &end_t);	/* mark the end time */
                time( &endTime );
                diff = BILLION * (end_t.tv_sec - start_t.tv_sec) + end_t.tv_nsec - start_t.tv_nsec;
                gravaRegistroDeTempo("BubbleSort_TempoExecParte2", tam);

                //printf("%d",i);
            }
        }

    }while(trocou);

}


void QuickSort::avaliaClockTicksParte2(int *v, int tam){

    int i = tam, k;
    int trocou;
    do{
        tam--;
        trocou = 0;
        for(i = 0; i < tam; i++){
            if(v[i] > v[i + 1]){

                //inicio da avaliação
                time( &startTime );
                t = clock();

                int aux = 0;
                aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
                trocou = 1;
                //for(k = 0; k < j; k++)
                //    printf("%d ", v[k]);

                //fim da avaliação
                t = clock() - t;
                time( &endTime );
                gravaRegistroDeTicks("BubbleSort_TicksExecParte2", tam);

                //printf("%d",i);
            }
        }

    }while(trocou);

}



void QuickSort::gravaRegistroDeTempo(std::string nome, int tam){

    strftime(inicio, 20, "%Y-%m-%d %H:%M:%S", localtime(&startTime));
    strftime(fim, 20, "%Y-%m-%d %H:%M:%S", localtime(&endTime));

    std::string textFileName = nome+".txt";

    std::ofstream textFile;

    textFile.open(textFileName, std::ios::app);
    textFile << "algoritmo:" << algoritmo << "|tamanho:" << tam << "|inicio:" << inicio << "|fim:" << fim << "|duracao(nanosec):" << (long long unsigned int) diff << std::endl;
    textFile.close();

}

void QuickSort::gravaRegistroDeTicks(std::string nome, int tam){

    strftime(inicio, 20, "%Y-%m-%d %H:%M:%S", localtime(&startTime));
    strftime(fim, 20, "%Y-%m-%d %H:%M:%S", localtime(&endTime));

    std::string textFileName = nome+".txt";

    std::ofstream textFile;

    textFile.open(textFileName, std::ios::app);
    textFile << "algoritmo:" << algoritmo << "|tamanho:" << tam << "|inicio:" << inicio << "|fim:" << fim << "|clockticks:" << t  << std::endl;
    textFile.close();

}

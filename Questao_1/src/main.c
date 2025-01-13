#include "./functions/hanoi.h"

int main(){
    Vertice grafo[CONFIGURACAO_MAXIMA];
    Distancia distancia[CONFIGURACAO_MAXIMA];

    int matrizAdj[CONFIGURACAO_MAXIMA][CONFIGURACAO_MAXIMA];

    gerarConfiguracoes(grafo);
    gerarMatrizAdjacencia(grafo, matrizAdj);
    exibir_config(grafo);

    int inicial, final;
    printf("Digite o índice da configuração inicial (0 a %d): ", CONFIGURACAO_MAXIMA - 1);
    scanf("%d", &inicial);
    printf("Digite o índice da configuração final (0 a %d): ", CONFIGURACAO_MAXIMA - 1);
    scanf("%d", &final);

    clock_t inicio, fim;

    inicio = clock();
    dijkstra(inicial,matrizAdj,distancia);
    fim = clock();

    exibeDistancia(distancia);
    
    menorCaminho(inicial,final,distancia);

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    
    printf("Tempo do algoritmo de dijkstra: %f segundos\n", tempo);
    return 0;
}
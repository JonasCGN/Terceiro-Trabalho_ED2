#include "./functions/hanoi.h"

int main()
{
    Vertice grafo[CONFIGURACAO_MAXIMA];
    int matrizAdj[CONFIGURACAO_MAXIMA][CONFIGURACAO_MAXIMA];

    gerarConfiguracoes(grafo, matrizAdj);
    exibir_config(grafo);

    int inicial, final;
    printf("Digite o índice da configuração inicial (0 a %d): ", CONFIGURACAO_MAXIMA - 1);
    scanf("%d", &inicial);
    printf("Digite o índice da configuração final (0 a %d): ", CONFIGURACAO_MAXIMA - 1);
    scanf("%d", &final);

    int distancias[CONFIGURACAO_MAXIMA];
    int predecessor[CONFIGURACAO_MAXIMA];

      clock_t inicio, fim;
      inicio = clock();
      djcastra(inicial, matrizAdj, distancias, predecessor);
      fim = clock();

      exibir_caminho(inicial, final, distancias, predecessor);

      double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    

    printf("Tempo do algoritmo de dijkshtra: %f segundos\n", tempo);
    return 0;
}
#include "./functions/bellman.h"

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
    int antecessor[CONFIGURACAO_MAXIMA];

      clock_t inicio, fim;
      inicio = clock();
      fordMooreBellman(inicial, matrizAdj, distancias, antecessor);
      fim = clock();

      exibir_caminho(inicial, final, distancias, antecessor);

      double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    

    printf("Tempo do algoritmo de dijkshtra: %f segundos\n", tempo);
    return 0;
}
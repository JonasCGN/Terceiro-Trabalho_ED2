#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

#define NUM_DISCOS 4                      // Número de discos
#define NUM_PINOS 3                       // Número de pinos
#define CONFIGURACAO_MAXIMA 3 * 3 * 3 * 3// NUM_PINOS ^ NUM_DISCOS (número total de configurações possíveis)
#define INFINITO INT_MAX

typedef struct{
    int configuracao[NUM_DISCOS];
} Vertice;

int movimentoValido(Vertice vertice1, Vertice vertice2);
void gerarConfiguracoes(Vertice *grafo, int matrizAdj[][CONFIGURACAO_MAXIMA]);
void fordMooreBellman(int inicio,  int matrizAdj[CONFIGURACAO_MAXIMA][CONFIGURACAO_MAXIMA], int *distancias, int *predecessor);
void exibir_caminho(int inicio, int fim, int *distancias, int *predecessor);
void exibir_config(Vertice *vetice);
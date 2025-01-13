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

typedef struct {
    int id;
    int distancia;
    int predecessor;
} Distancia;

int movimentoValido(Vertice vertice1, Vertice vertice2);
void gerarConfiguracoes(Vertice *grafo);
void gerarMatrizAdjacencia(Vertice *grafo, int matrizAdj[][CONFIGURACAO_MAXIMA]);

void exibir_config(Vertice *vetice);
void exibeVertice(Vertice vertice);

void dijkstra(int ini, int vertice[CONFIGURACAO_MAXIMA][CONFIGURACAO_MAXIMA],Distancia *distancia);
void menorCaminho(int ini, int fim, Distancia *distancia);
void exibeDistancia(Distancia *distancia);
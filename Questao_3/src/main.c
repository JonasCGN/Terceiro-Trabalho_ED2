#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define QTD_VERTICE 8
#define RAND_CAMINHO 101

typedef struct grafo{
	int vertice[QTD_VERTICE];
	float arestas[QTD_VERTICE][QTD_VERTICE];
}Grafo;

typedef struct {
    int id;
    float distancia;
    int predecessor;
} Distancia;

void exibirVertice(int id,Grafo *grafo){
	for(int i=0;i<QTD_VERTICE;i++){
		printf("[%d] - [%d] = %f\n",id,i,(*grafo).arestas[id][i]);
	}
}

void exibirGrafo(Grafo *grafo) {
    for (int i = 0; i < QTD_VERTICE; i++) {
        printf("Caminho %d\n", i);
        exibirVertice(i, grafo);
    }
}

void exibeInfoDistancia(Distancia distancia){
	printf("Vertice atual: %d\n", distancia.id);
	printf("Distancia: %f\n", distancia.distancia);
	printf("Predecessor: %d\n", distancia.predecessor);
}

void exibeDistancia(Distancia *distancia){
	for(int i=0;i<QTD_VERTICE;i++){
		printf("Vertice: %d\n",i);
		exibeInfoDistancia(distancia[i]);
	}
}

void iniciarGrafo(Grafo *grafo){
	for(int id=0;id<QTD_VERTICE;id++){
		grafo->vertice[id] = id;
		for(int aresta =0;aresta < QTD_VERTICE;aresta++)
			grafo->arestas[id][aresta] = 0.0;
	}
}

void criandoGrafo(Grafo *grafo){
	for(int id=0;id<QTD_VERTICE;id++){
		for(int aresta =id + 1;aresta < QTD_VERTICE;aresta++){
			float confiabilidade = ((float)(rand() % RAND_CAMINHO) / 100);
			grafo->arestas[id][aresta] = confiabilidade;
			grafo->arestas[aresta][id] = confiabilidade;
		}
	}
}

void atualizaDistancia(Distancia *distancia, Grafo grafo, int destino_atual, int destino_pos) {
    distancia[destino_pos].id = destino_pos;
    distancia[destino_pos].predecessor = destino_atual;

    if ((int)distancia[destino_pos].distancia == -2) {
        distancia[destino_pos].distancia = grafo.arestas[destino_atual][destino_pos];
    } else {
        distancia[destino_pos].distancia = distancia[destino_atual].distancia * grafo.arestas[destino_atual][destino_pos];
        // distancia[destino_pos].distancia *= grafo.arestas[destino_atual][destino_pos];
	}
}

void dijkstra(int ini, Grafo *grafo,Distancia *distancia){
	for (int i = 0; i < QTD_VERTICE; i++){
		distancia[i].id = i;
		distancia[i].distancia = -2;
		distancia[i].predecessor = -2;
	}
	distancia[ini].distancia = 1;

	for(int destino_atual = 0; destino_atual < QTD_VERTICE;destino_atual++){
		for(int destino_pos = 0;destino_pos < QTD_VERTICE;destino_pos++){

			if(destino_atual != destino_pos){
				float comp1 = distancia[destino_atual].distancia;
				float comp2 = (*grafo).arestas[destino_atual][destino_pos];
				float comp3 = distancia[destino_pos].distancia;

				if(comp1 * comp2 > comp3){
					atualizaDistancia(distancia,*grafo,destino_atual,destino_pos);
				}

			}

		}
	}
}

void menorCaminho(int ini, int fim, Distancia *distancia) {
	if((ini < QTD_VERTICE && fim < QTD_VERTICE)){
		int caminho[QTD_VERTICE];
		int pos = 0;
		int atual = fim;

		while (atual != ini && atual != -2) {
			caminho[pos++] = atual;
			atual = distancia[atual].predecessor;
		}

		if (atual == ini) {
			caminho[pos++] = ini;
		}

		printf("Menor caminho de %d para %d: ", ini, fim);
		for (int i = pos - 1; i >= 0; i--) {
			printf("%d", caminho[i]);
			if (i > 0) {
				printf(" -> ");
			}
		}
		printf("\n");
	}else{
		printf("Impossivel formar caminho\n");
	}
}

int main(){
	srand((unsigned int)2);

	Grafo grafo;
	Distancia distancia[QTD_VERTICE];
	int ini=0,fim=7;

	iniciarGrafo(&grafo);
	criandoGrafo(&grafo);

	exibirGrafo(&grafo);

	// printf("Digite o numero de inicio:");
	// scanf("%d",&ini);
	// printf("Digite o numero de fim:");
	// scanf("%d",&fim);

	dijkstra(ini,&grafo, distancia);
	// exibeDistancia(distancia);
	
	menorCaminho(ini,fim,distancia);
	return 0;
}
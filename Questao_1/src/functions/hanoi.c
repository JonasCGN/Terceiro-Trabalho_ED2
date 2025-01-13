#include "./hanoi.h"

int verificaConfiguracoes(Vertice vertice1, Vertice vertice2, int *indiceDiferente) {
    int verifica = 1;
    int diferenca = 0;

    for (int i = 0; i < NUM_DISCOS; i++) {
        if (vertice1.configuracao[i] != vertice2.configuracao[i]) {
          (diferenca)++;
          if (diferenca == 1) {
            *indiceDiferente = i;
          } else {
            verifica = 0;
          }
        }
    }

    return verifica;
}

int verificaRegra(Vertice vertice1, Vertice vertice2, int indiceDiferente) {
	int verifica = 1;

	if (indiceDiferente != -1) {
		for (int i = 0; i < indiceDiferente; i++) {
			if (vertice1.configuracao[i] == vertice1.configuracao[indiceDiferente] ||
				vertice2.configuracao[i] == vertice2.configuracao[indiceDiferente]) {
				verifica = 0;
			}
		}
	}

	return verifica;
}

int movimentoValido(Vertice vertice1, Vertice vertice2) {
	int indiceDiferente = -1;

	int diferenca = verificaConfiguracoes(vertice1, vertice2, &indiceDiferente);

	if (diferenca) {
		diferenca = verificaRegra(vertice1, vertice2, indiceDiferente);
	}

	return diferenca;
}

void gerarConfiguracoes(Vertice *grafo) {
    for (int indiceAtual = 0; indiceAtual < CONFIGURACAO_MAXIMA; indiceAtual++) {
        int numeroAtribuido = indiceAtual;
		
        for (int disco = 0; disco < NUM_DISCOS; disco++) {
            grafo[indiceAtual].configuracao[disco] = numeroAtribuido % NUM_PINOS + 1;
            numeroAtribuido /= NUM_PINOS;
        }
    }
}

void gerarMatrizAdjacencia(Vertice *grafo, int matrizAdj[][CONFIGURACAO_MAXIMA]) {
    for (int i = 0; i < CONFIGURACAO_MAXIMA; i++) {
        for (int j = 0; j < CONFIGURACAO_MAXIMA; j++) {
            if (movimentoValido(grafo[i], grafo[j])) {
                matrizAdj[i][j] = 1;
            }else {
                matrizAdj[i][j] = 0;
            }
        }
    }
}


void exibir_config(Vertice *vertice) {
	for (int config_atual = 0; config_atual < CONFIGURACAO_MAXIMA; ++config_atual) {
	    printf("vertex %d: ", config_atual);
		exibeVertice(vertice[config_atual]);
		printf("\n");
	}
}

void exibeVertice(Vertice vertice){
	for (int disco_atual = 0; disco_atual < NUM_DISCOS; disco_atual++)
		printf("%d ", vertice.configuracao[disco_atual]);
}

void atualizaDistancia(Distancia *distancia, int grafo[CONFIGURACAO_MAXIMA][CONFIGURACAO_MAXIMA], int destino_atual, int destino_pos) {
    distancia[destino_pos].id = destino_pos;
    distancia[destino_pos].predecessor = destino_atual;
	distancia[destino_pos].distancia = distancia[destino_atual].distancia + grafo[destino_atual][destino_pos];
}

void dijkstra(int ini, int grafo[CONFIGURACAO_MAXIMA][CONFIGURACAO_MAXIMA], Distancia *distancia) {
    int visitados[CONFIGURACAO_MAXIMA] = {0}; // Indica se o nó foi visitado

    for (int i = 0; i < CONFIGURACAO_MAXIMA; i++) {
        distancia[i].id = i;
        distancia[i].distancia = INFINITO;
        distancia[i].predecessor = -1;
    }
    distancia[ini].distancia = 0;
    distancia[ini].predecessor = ini;

	int config_menor;
  	int config_atual = 0;

    do{
		config_menor = -1;

		for(int i = 0; i < CONFIGURACAO_MAXIMA - 1; i++){
			if (!visitados[i] && (config_menor == -1 || distancia[i].distancia < distancia[config_menor].distancia))
				config_menor = i;
		}

		if (!(config_menor == -1 || distancia[config_menor].distancia == INFINITO)){
			visitados[config_menor] = 1;

			for (int v = 0; v < CONFIGURACAO_MAXIMA; v++){
				if (!visitados[v] && grafo[config_menor][v] && 
					distancia[config_menor].distancia != INFINITO && 
					distancia[config_menor].distancia + grafo[config_menor][v] < distancia[v].distancia){
					atualizaDistancia(distancia,grafo,config_menor,v);
				}
			}
		}
			
		config_atual++;

	}while(config_atual < CONFIGURACAO_MAXIMA - 1 && config_menor != -1);
}

void menorCaminho(int ini, int fim, Distancia *distancia) {
	if((ini < CONFIGURACAO_MAXIMA && fim < CONFIGURACAO_MAXIMA)){
		int caminho[CONFIGURACAO_MAXIMA];
		int pos = 0;
		int atual = fim;

		while (atual != ini && atual != -1) {
			caminho[pos++] = atual;
			atual = distancia[atual].predecessor;
		}

		if (atual == ini) {
			caminho[pos++] = ini;
		}

		printf("Menor caminho de %d para %d: ", ini, fim);
		for (int i = pos - 1; i >= 0; i--) {
			printf("%d", caminho[i]);
			// exibeVertice(vertice[caminho[i]]);
			if (i > 0) {
				printf(" -> ");
			}
		}
		printf("\n");
	}else{
		printf("Não é possível encontrar um caminho de %d para %d.\n", ini, fim);
	}
}

void exibeInfoDistancia(Distancia distancia){
	printf("Vertice atual: %d\n", distancia.id);
	printf("Distancia: %d\n", distancia.distancia);
	printf("Predecessor: %d\n", distancia.predecessor);
}

void exibeDistancia(Distancia *distancia){
	for(int i=0;i<CONFIGURACAO_MAXIMA;i++){
		printf("Vertice: %d\n",i);
		exibeInfoDistancia(distancia[i]);
	}
}
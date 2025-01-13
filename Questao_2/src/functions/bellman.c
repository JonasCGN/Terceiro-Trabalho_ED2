#include "./bellman.h"

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
            if(movimentoValido(grafo[i], grafo[j])) {
                matrizAdj[i][j] = 1;
            } else {
                matrizAdj[i][j] = 0;
            }
        }
    }
}

void fordMooreBellman(int inicio, int matrizAdj[CONFIGURACAO_MAXIMA][CONFIGURACAO_MAXIMA], int distancia[], int antessesor[]){
    for (int indiceVertice = 0; indiceVertice < CONFIGURACAO_MAXIMA; indiceVertice++)
        antessesor[indiceVertice] = -1;

    for (int verticeAtual = 0; verticeAtual < CONFIGURACAO_MAXIMA; verticeAtual++)
        distancia[verticeAtual] = INFINITO;
    distancia[inicio] = 0;

    int isUpdated = 1;
    for (int i = 0; i < CONFIGURACAO_MAXIMA - 1 && isUpdated; ++i){
        isUpdated = 0;
		
        for (int j = 0; j < CONFIGURACAO_MAXIMA; ++j){
            if (distancia[j] != INFINITO){
                for (int k = 0; k < CONFIGURACAO_MAXIMA; k++){
					if (matrizAdj[j][k] != 0 && distancia[j] + matrizAdj[j][k] < distancia[k]){
						distancia[k] = distancia[j] + matrizAdj[j][k];
						antessesor[k] = j;
						isUpdated = 1;
					}
				}
			}
		}
    }

}

void exibir_caminho(int inicio, int fim, int *distancias, int *predecessor) {

	if (distancias[fim] == INFINITO) {
		printf("Não há caminho acessível de %d para %d.\n", inicio, fim);
	} else {

		printf("Menor caminho de %d para %d: ",inicio, fim);
		int caminho[CONFIGURACAO_MAXIMA];
		int indice = 0;
		int atual = fim;

		while (atual != -1) {
			caminho[indice++] = atual;
			atual = predecessor[atual];
		}

		for (int caminhoIndice = indice - 1; caminhoIndice >= 0; caminhoIndice--) {
			printf("%d", caminho[caminhoIndice]);
			if (caminhoIndice > 0)
				printf(" -> ");
		}
		printf("\n");
	}

}

void exibir_config(Vertice *vetice) {
	for (int config_atual = 0; config_atual < CONFIGURACAO_MAXIMA; ++config_atual) {
	    printf("vertex %d: ", config_atual);
		for (int disco_atual = 0; disco_atual < NUM_DISCOS; disco_atual++)
			printf("%d ", vetice[config_atual].configuracao[disco_atual]);
		printf("\n");
	}
}

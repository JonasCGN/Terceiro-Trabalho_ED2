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

void gerarConfiguracoes(Vertice *grafo, int matrizAdj[][CONFIGURACAO_MAXIMA]) {
	for (int indiceConfiguracao = 0; indiceConfiguracao < CONFIGURACAO_MAXIMA; indiceConfiguracao++)
		for (int indiceVizinho = 0; indiceVizinho < CONFIGURACAO_MAXIMA; indiceVizinho++)
			matrizAdj[indiceConfiguracao][indiceVizinho] = 0;

	int disco, numero_atribuido;
	for (int indiceConfiguracao = 0; indiceConfiguracao < CONFIGURACAO_MAXIMA; indiceConfiguracao++) {
		numero_atribuido = indiceConfiguracao;
		for (disco = 0; disco < NUM_DISCOS; disco++) {
			grafo[indiceConfiguracao].configuracao[disco] = numero_atribuido % NUM_PINOS + 1;
			numero_atribuido /= NUM_PINOS;
		}
	}

	for (int indiceAtual = 0; indiceAtual < CONFIGURACAO_MAXIMA; indiceAtual++)
		for (int indiceVizinho = 0; indiceVizinho < CONFIGURACAO_MAXIMA; indiceVizinho++)
			if (movimentoValido(grafo[indiceAtual], grafo[indiceVizinho]))
				matrizAdj[indiceAtual][indiceVizinho] = 1;
			else
				matrizAdj[indiceAtual][indiceVizinho] = 0;
}

void djcastra(int inicio, int matrizAdj[CONFIGURACAO_MAXIMA][CONFIGURACAO_MAXIMA], int *distancias, int *predecessor) {
	int visitados[CONFIGURACAO_MAXIMA];

	for (int configuracao_atual = 0; configuracao_atual < CONFIGURACAO_MAXIMA; configuracao_atual++) {
		distancias[configuracao_atual] = INFINITO;
		visitados[configuracao_atual] = 0;
		predecessor[configuracao_atual] = -1;
	}
	distancias[inicio] = 0;

	int vertice_menor_distancia;
	int configuracao_atual = 0;
	do {
		vertice_menor_distancia = -1;

		for (int i = 0; i < CONFIGURACAO_MAXIMA - 1; i++)
			if (!visitados[i] && (vertice_menor_distancia == -1 || distancias[i] < distancias[vertice_menor_distancia]))
				vertice_menor_distancia = i;

		if (!(vertice_menor_distancia == -1 || distancias[vertice_menor_distancia] == INFINITO)) {
			visitados[vertice_menor_distancia] = 1;

			for (int v = 0; v < CONFIGURACAO_MAXIMA; v++) {
				if (!visitados[v] && matrizAdj[vertice_menor_distancia][v] &&
					distancias[vertice_menor_distancia] != INFINITO &&
					distancias[vertice_menor_distancia] + matrizAdj[vertice_menor_distancia][v] < distancias[v]) {
					distancias[v] = distancias[vertice_menor_distancia] + matrizAdj[vertice_menor_distancia][v];
					predecessor[v] = vertice_menor_distancia;
				}
			}
		}

		configuracao_atual++;
	} while (configuracao_atual < CONFIGURACAO_MAXIMA - 1 && vertice_menor_distancia != -1);
}

void exibir_caminho(int inicio, int fim, int *distancias, int *predecessor) {
	if (distancias[fim] == INFINITO) {
		printf("Não há caminho acessível de %d para %d.\n", inicio, fim);
	} else {
		printf("Menor caminho de %d para %d: %d\n", inicio, fim, distancias[fim]);

		printf("Caminho: ");
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

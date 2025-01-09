#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define QTD_FUNC 1000
#define QTD_POSICAO_A 101
#define QTD_POSICAO_B 150

int numChar(char letra){
	return letra - '0';
}

typedef struct funcionario{
	char matricula[7];
	char funcao[20];
	char nome[50];
	float salario;
}Funcionario;

typedef struct tabHash{
	int hash[QTD_POSICAO_B];
	Funcionario funcionarios[QTD_POSICAO_B];
}TabHash;

void  inicializaTabelaHash(TabHash *tabHash,int tamanho){
	for(int i=0;i<tamanho;i++){
		tabHash->hash[i] = -1;
	}
}

void geraFuncionarios(Funcionario *funcionarios){
	char *funcoes[10] = {
		"pedreiro","assistente","secretario","servente","padeiro",
		"limpeza","conzinheiro","tecnico em ti","diretor","dev"
	};
	
	for(int i=0;i<QTD_FUNC;i++){
		sprintf(funcionarios[i].matricula,"%06d",i+1);
		sprintf(funcionarios[i].nome,"func%d",i);
		strcpy(funcionarios[i].funcao,funcoes[rand() % 10]);
		funcionarios[i].salario = (float)(rand() % 10000);
	}
}

void exibirInfo(Funcionario funcionario){
	printf("------------------------------------\n");
	printf("Matricula: %s\n",funcionario.matricula);
	printf("Nome: %s\n",funcionario.nome);
	printf("Funcao: %s\n",funcionario.funcao);
	printf("Salario: %.2f\n",funcionario.salario);
	printf("------------------------------------\n");
}

void exibirFuncionarios(Funcionario *funcionario,int tamanho){
	for(int i=0;i<tamanho;i++){
		exibirInfo(funcionario[i]);
	}
}

void rotacaoDoisDigito(char *palavra){
	char p1=palavra[4],p2=palavra[5];

	char temp[6];

	for(int i=0,j=2;i<4;i++,j++){
		temp[j] = palavra[i];
	}
	
	temp[0] = p1;
	temp[1] = p2;

	strcpy(palavra,	temp);
}

int colisaoA(int resto,char *palavra){
	int num = numChar(palavra[0]);

	if((!num))
		num = 1;

	return (resto + num);
}

int colisaoResolverA(TabHash *tab,Funcionario funcionario,char *palavra,int hash,int tamanho,int *inseriu){
	int quant=0;

	if(hash < tamanho){
		if(tab->hash[hash] == -1){
			tab->funcionarios[hash] = funcionario;
			tab->hash[hash] = hash;
			*inseriu = 1;
		}else{
			quant += 1 + colisaoResolverA(tab,funcionario,palavra,colisaoA(hash,palavra),tamanho,inseriu);
		}
	}

	return quant;
}

// 	 Função Hashing: rotação de 2 dígitos para a esquerda depois extrai o 2o, 4o e 6o dígitos e obtenha o resto
// da divisão pelo tamanho do vetor destino. As colisões devem ser tratadas somando ao resto da divisão o
// primeiro dígito da matrícula.
int funcaoHashingA(TabHash *tab,Funcionario funcionario,int tamanho){
	char temp[6];
	int quant = 0,inseriu = 0;

	strcpy(temp,funcionario.matricula);
	rotacaoDoisDigito(temp);

	int posicao = atoi((char[]){temp[1], temp[3], temp[5],'\0'}) % tamanho;

	quant = colisaoResolverA(tab,funcionario,temp,posicao,tamanho,&inseriu);

	if(!inseriu){
		tab->funcionarios[posicao] = funcionario;
		tab->hash[posicao] = posicao;
	}

	return quant;
}

int foldShift(char *palavra){
	return (atoi((char[]){palavra[0],palavra[2],palavra[5]}) + 
		atoi((char[]){palavra[1],palavra[3],palavra[4]}));	
}

int colisaoB(int num){
	return num + 7;
}

// int funcaoHashingB(TabHash *tab,Funcionario funcionario,int tamanho){
	// 	(b) Função Hashing: fole shift com 3 dígitos da seguinte forma: o 1o, 3 e 6o; 2o, 4o e 5o, depois obtenha o
	// resto da divisão do resultado pelo tamanho do vetor destino. As colisões devem ser realizadas somando
	// 7 ao valor obtido.
	// return foldShift(funcionario.matricula) % tamanho;
// }

void testeA(Funcionario *funcionarios,int tamanho){
	TabHash tabela;
	int quant = 0;
	clock_t tempo_efetivar_hash = 0;

	inicializaTabelaHash(&tabela,tamanho);

	printf("Quantidade de posição %d\n", tamanho);
	for(int i=0;i < QTD_FUNC;i++){
		clock_t inicio = clock();
		
		quant += funcaoHashingA(&tabela,funcionarios[i],tamanho);

		clock_t fim = clock();
		tempo_efetivar_hash += (fim - inicio);
	}
	
	printf("Tempo para efetivar: %f\n", (double) tempo_efetivar_hash / CLOCKS_PER_SEC);
	printf("Total Colisao: %d\n\n",quant);
}

int main(){
	Funcionario funcionarios[QTD_FUNC];
	
	geraFuncionarios(funcionarios);
	// exibirFuncionarios(funcionarios);

	testeA(funcionarios,QTD_POSICAO_A);
	testeA(funcionarios,QTD_POSICAO_B);

	return 0;
}
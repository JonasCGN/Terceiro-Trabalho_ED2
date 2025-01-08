#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define QTD_FUNC 1000
#define QTD_POSICAO_A 101
// #define QTD_POSICAO_B 150

int numChar(char letra){
	return letra - '0';
}

typedef struct funcionario{
	char matricula[7];
	char funcao[20];
	char nome[50];
	float salario;
}Funcionario;

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

	strcpy(palavra,temp);
}

int colisaoA(int resto,char *palavra){
	return resto + numChar(palavra[0]);
}

int funcaoHashingA(char *palavra,int tamanho){
	char temp[6];
	// 	 Função Hashing: rotação de 2 dígitos para a esquerda depois extrai o 2o, 4o e 6o dígitos e obtenha o resto
	// da divisão pelo tamanho do vetor destino. As colisões devem ser tratadas somando ao resto da divisão o
	// primeiro dígito da matrícula.
	strcpy(temp,palavra);
	rotacaoDoisDigito(temp);
	
	return atoi((char[]){temp[1], temp[3], temp[5]}) % tamanho;
}

int foldShift(char *palavra,int tamanho){
	return (atoi((char[]){palavra[0],palavra[2],palavra[5]}) + 
		atoi((char[]){palavra[1],palavra[3],palavra[4]}));	
}

void colisaoB(int num){
	return num + 7;
}

int funcaoHashingB(char *palavra,int tamanho){
	// 	(b) Função Hashing: fole shift com 3 dígitos da seguinte forma: o 1o, 3 e 6o; 2o, 4o e 5o, depois obtenha o
	// resto da divisão do resultado pelo tamanho do vetor destino. As colisões devem ser realizadas somando
	// 7 ao valor obtido.
	return foldShift(palavra,tamanho) % tamanho;
}

int main(){
	Funcionario funcionarios[QTD_FUNC];
	
	geraFuncionarios(funcionarios);
	// exibirFuncionarios(funcionarios);

	exibirInfo(funcionarios[0]);
	printf("%d\n",funcaoHashingA(funcionarios[0].matricula,QTD_POSICAO_A));
	exibirInfo(funcionarios[0]);

	return 0;
}
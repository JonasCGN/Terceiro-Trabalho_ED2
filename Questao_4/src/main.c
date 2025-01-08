#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define QTD_FUNC 1000
#define QTD_POSICAO 101
// #define QTD_POSICAO 150

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

void exibirFuncionarios(Funcionario *funcionario){
	for(int i=0;i<QTD_POSICAO;i++){
		exibirInfo(funcionario[i]);
	}
}

void rotacaoDoisDigito(char *palavra){
	char p1=palavra[4],p2=palavra[5];

	char temp[3];

	temp[0] = palavra[2];
	palavra[2] = palavra[0];

	temp[1] = palavra[3];
	palavra[3] = palavra[1];

	temp[2] = palavra[4];
	palavra[4] = temp[0];

	palavra[5] = temp[1];

	palavra[0] = p1;
	palavra[1] = p2;
}

void colisaoA(){

}

int funcaoHashingA(char *palavra){
	// 	 Função Hashing: rotação de 2 dígitos para a esquerda depois extrai o 2o, 4o e 6o dígitos e obtenha o resto
	// da divisão pelo tamanho do vetor destino. As colisões devem ser tratadas somando ao resto da divisão o
	// primeiro dígito da matrícula.
	rotacaoDoisDigito(palavra);

	return atoi((char[]){palavra[1], palavra[3], palavra[5]}) % QTD_POSICAO;

}

// void foldShifit(char *palavra){

// }

void colisaoB(){
	
}

void funcaoHashingB(){
	// 	(b) Função Hashing: fole shift com 3 dígitos da seguinte forma: o 1o, 3 e 6o; 2o, 4o e 5o, depois obtenha o
	// resto da divisão do resultado pelo tamanho do vetor destino. As colisões devem ser realizadas somando
	// 7 ao valor obtido.
}

int main(){
	Funcionario funcionarios[QTD_FUNC];
	
	geraFuncionarios(funcionarios);
	// exibirFuncionarios(funcionarios);

	exibirInfo(funcionarios[0]);
	printf("%d",funcaoHashingA(funcionarios[0].matricula));
	exibirInfo(funcionarios[0]);

	return 0;
}
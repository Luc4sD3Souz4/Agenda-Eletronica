#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>
#include <conio.h>

#define clear() puts("\x1B[2J")
#define MAX_AGENDA 50

#include "imprimirMenu.h"

typedef struct {
	char nome[50];
	int idade, numero, id;
} registro;

void criaContato(registro r[], int *tamanho) {
	int indice = *tamanho;
	int idade, numero, id;
	char nome[50];
	
	system("cls");
	puts("\t\t\t#####################=====----");
	printf("\t\t\t#\n");
	printf("\t\t\t# Nome: ");
	scanf("%s", nome);
	printf("\t\t\t#\n");
	printf("\t\t\t# Idade: ");
	scanf("%d", &idade);
	printf("\t\t\t#\n");
	printf("\t\t\t# Telefone: ");
	scanf("%d", &numero);
	printf("\t\t\t#\n");
	puts("\t\t\t#####################=====----");
	strcpy(r[indice].nome, nome);
	r[indice].idade  = idade;
	r[indice].numero = numero;
	id = indice;

	*tamanho = *tamanho + 1;	
}

void listaContatos(registro r[], int *tamanho) {
	int tam = *tamanho;
	printf("\n");
	printf("\t#################################################################\n");
	printf("\t#                                                               #\n");
	printf("\t#                       LISTA DE CONTATOS                       #\n");
	printf("\t#                                                               :\n");
	printf("\t# ID\tNome\t\tIdade\t\tNúmero de Telefone      .\n");
	printf("\t#                                                               .\n");
	
	int i;
												   
	for(i = 0; i < tam; i++) {
		printf("\t# %d\t%s\t\t%d\t\t%d\n", i, r[i].nome, r[i].idade, r[i].numero);
		printf("\t#\n");
	}
	printf("\t#                                                               .\n");
	printf("\t#################################################################\n");
}

void deletarContatos(registro r[], int *tamanho) {
	int indice, i, tama, result;
	system("cls");
	
	printf("\t\tLista de contatos, escolha um para ser excluido\n");
	listaContatos(r, tamanho);
	printf ("\n\n\t\tInforme o ID do contato para deletar: ");
    scanf ("%d", &indice);
	
	if (r[indice].idade == 0) {
	    do {
	    	system("cls");
	    	printf("\t\tLista de contatos, escolha um para ser excluido\n");
			listaContatos(r, tamanho);
			printf("\t\t\nID inexistente! Tente novamente: ");
			scanf ("%d", &indice);
		} while (r[indice].idade == 0);
	}
	
	for (i = indice; i < *tamanho-1; i++) {
		r[i].idade = r[i+1].idade;
		r[i].numero = r[i+1].numero;
		strcpy(r[i].nome,r[i+1].nome);
	}
	
	r[i].idade = 0;
	r[i].numero = 0;
	memset(r[i].nome, 0, sizeof(r[i].nome));
	
	*tamanho = *tamanho - 1;
	system("pause");
}

void pesquisa(registro r[]){
	system("cls");
	int indice;
	printf ("\t\t\tInforme o ID que deseja pesquisar: ");
    scanf ("%d", &indice);
    if (r[indice].idade == 0) {
	    do {
	    	system("cls");
			printf("\t\t\tID inexistente! Tente novamente: ");
			scanf ("%d", &indice);
		} while (r[indice].idade == 0);
	}
	printf("\nContato %d\n\n", indice);
	puts("ID\tNome\t\tIdade\t\tNumero de Telefone\n");
	printf("%d\t%s\t\t%d\t\t%d\n\n\n", indice, r[indice].nome, r[indice].idade, r[indice].numero);
	system("pause");
}
void editar(registro r[], int *tamanho){
	system("cls");
	int indice,idade, numero;
	char nome [50];
	
	listaContatos(r, tamanho);
	printf ("\n\t\t\tInforme o ID que deseja editar: ");
    scanf ("%d", &indice);
    if (r[indice].idade == 0) {
	    do {
	    	system("cls");
			printf("\t\t\tID inexistente! Tente novamente: ");
			scanf ("%d", &indice);
		} while (r[indice].idade == 0);
	}
	
	printf("\nInforme o novo nome: ");
	scanf("%s", nome);
	printf("\nInforme a nova idade: ");
	scanf("%d",&idade);
	printf("\nInforme o novo número: ");
	scanf("%d",&numero);
	
	strcpy(r[indice].nome,nome);
	r[indice].idade = idade;
	r[indice].numero = numero;
	
	printf("\nContato %d\n\n", indice);
	puts("ID\tNome\t\tIdade\t\tNumero de Telefone\n");
	printf("%d\t%s\t\t%d\t\t%d\n\n\n", indice, r[indice].nome, r[indice].idade, r[indice].numero);
	system("pause");
}
void processaOpcao(int opcao, registro r[], int *tamanho) {
	switch(opcao) {
		case '1':
			criaContato(r, tamanho);
			break;
		case '2':
			system("cls");
			listaContatos(r, tamanho);
			break;
		case '3':
			deletarContatos(r, tamanho);
			break;
		case '4':
			pesquisa(r);
			break;
		case '5':
			editar(r, tamanho);
			break;
		case 's':
			puts("\nEncerrando...\n");
			break;
		default:
			puts("\n\t\t\tOpção inválida!\n");
			break;
	}
}

int main() {
	FILE *arquivo;
	char nome_arquivo[] = "agenda.bin";
	char op;
						
	setlocale (LC_ALL, "Portuguese");
			
	registro agenda[MAX_AGENDA];

	int tamanho = 0;
	// lê o arquivo e carrega seu conteúdo para o vetor "agenda", se existir
	arquivo = fopen(nome_arquivo, "rb");
	if (arquivo != NULL) {
		fread(&tamanho, sizeof(int), 1, arquivo);
		fread(agenda, sizeof(registro), MAX_AGENDA, arquivo);
		fclose(arquivo);
	}

	do {
		system("cls");
		imprimeMenu();
		op = tolower(getchar());		
		processaOpcao(op, agenda, &tamanho);		
		fflush(stdin); // limpa o buffer do teclado (para remover lixos)		
		printf("\n\t\t\tPressione enter para continuar\n");
		getchar();		
	   } while (op != 's');

	// grava o arquivo, com o conteúdo do vetor, ao sair

	arquivo = fopen(nome_arquivo, "wb");
	fwrite(&tamanho, sizeof(int), 1, arquivo);	
	fwrite(agenda, sizeof(registro), MAX_AGENDA, arquivo);
	fclose(arquivo);

	return 0;
}

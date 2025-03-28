#include <stdio.h>
#include <locale.h>
// Compatibilidade com Windows e Mac/Linux
#ifdef _WIN32
#include <windows.h> // Caso o sistema seja Windows
#else
#include <unistd.h> // Caso o sistema seja MacOS/Linux
#endif

void mostrarMenu() {
	printf("1. Criar lista\n");
	printf("2. Cadastrar disciplina\n");
	printf("3. Mostrar disciplinas\n");
	printf("4. Cadastrar aluno\n");
	printf("5. Mostrar alunos\n");
	printf("6. Remover aluno\n");
	printf("7. Remover disciplina\n");
	printf("8. Créditos\n");
	printf("9. Sair\n");
}

// cpClear significa aqui "Cross Platform Clear", para que o programa funcione bem no Windows, MacOS e Linux.
void cpClear() { 
	#ifdef _WIN32
        system("cls");  
    #else
        system("clear"); 
    #endif
}

int main() {
	setlocale(LC_ALL, 0);
	
	while(1) {
		mostrarMenu();
		printf("\nEscolha uma opção: ");
		int opcao;
		scanf("%d", &opcao);
		fflush(stdin);
		
		switch(opcao) {
			case 1:
				static int criado = 0; // Para inicializar vari�veis dentro do switch-case, é necessário ou criar um escopo ou usar variável estática. Preferi usar static.
				if (!criado) { // Para não deixar criar a lista duas vezes
						// lógica
					}
					else {
						printf("Erro: lista já foi criada\n");
					}
				break;
			case 2:
				if (criado) { // Todos os cases que envolvem manipular a lista tem essa lógica, para que só possa manipular a lista se ela já tiver sido criada.
						// lógica
					}
					else {
						printf("\nErro: lista ainda não foi criada\n");
					}
				break;
			case 3:
				if (criado) { 
						// lógica
					}
					else {
						printf("\nErro: lista ainda não foi criada\n");
					}
				break;
			case 4:
				if (criado) { 
						// lógica
					}
					else {
						printf("\nErro: lista ainda não foi criada\n");
					}
				break;
			case 5:
				if (criado) { 
						// lógica
					}
					else {
						printf("\nErro: lista ainda não foi criada\n");
					}
				break;
			case 6:
				if (criado) { 
						// lógica
					}
					else {
						printf("\nErro: lista ainda não foi criada\n");
					}
				break;
			case 7:
				if (criado) { 
						// lógica
					}
					else {
						printf("\nErro: lista ainda não foi criada\n");
					}
				break;
			case 8:
				printf("Exibindo créditos. DEIXAR POR ÚLTIMO FALANDO DO CÓDIGO, \nNÃO ESQUECER DESSA PARTE!");
				break;
			case 9:
				printf("Encerrando programa.\n\n");
				return 0;
			default:
				printf("Valor inválido. Tente novamente.\n\n");
				break;
		}
	}
	
	getchar();
	return 0;
}

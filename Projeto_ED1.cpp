#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
// Compatibilidade com Windows e Mac/Linux
#ifdef _WIN32
#include <windows.h> // Caso o sistema seja Windows
#else
#include <unistd.h> // Caso o sistema seja MacOS/Linux
#endif

#define MAX 60

typedef struct disciplina { 
	/*
	coloquei disciplina como um struct pra talvez a gnt tentar criar um array de disciplinas prévio, mas isso não é necessário
	os dados podem ficar no node, o que acham?
	*/
	int id;
	char nome[50];
	double nota;

} _disciplina; 

typedef struct node {

	_disciplina disciplina;
	struct node *prox;	

} _node;

typedef _node* L_lista;

typedef struct aluno {
	
	int RGM;
	char nome[50];
	L_lista *disciplinas; 

} _aluno;

typedef struct S_lista {

	_aluno alunos[MAX];
	int n;

} S_lista;

// Protótipos de funções vão aqui
S_lista criar();
void continuar();
void mostrarDisciplinas();
void mostrarAlunos();
void mostrarMenu();
void cpClear();

int main() {
	setlocale(LC_ALL, 0);
	int opcao;
	S_lista alunos;

	do {
		mostrarMenu();
		printf("\nEscolha uma opção: ");
		
		scanf("%d", &opcao);
		fflush(stdin);
		
		switch(opcao) {
			case 1:
				static int criado = 0; // Para inicializar vari�veis dentro do switch-case, é necessário ou criar um escopo ou usar variável estática. Preferi usar static.
				if (!criado) { // Para não deixar criar a lista duas vezes
						alunos = criar();
						criado = 1;// lógica
					}
					else {
						printf("Erro: lista já foi criada\n");
					}
				continuar();
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
					mostrarDisciplinas();
					continuar();
				break;
			case 4:
					mostrarAlunos();
					continuar();
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
	} while(opcao != 9);
	
	getchar();
	return 0;
}

// cpClear significa aqui "Cross Platform Clear", para que o programa funcione bem no Windows, MacOS e Linux.
void cpClear() { 
	#ifdef _WIN32
        system("cls");  
    #else
        system("clear"); 
    #endif
}

void mostrarMenu() {
	printf("1. Criar lista\n"); //remover criar lista
	printf("2. Inserir novo aluno\n"); //->informa qual aluno->inserir disciplina na lista de dsicplinas do aluno
	printf("3. Mostrar disciplinas\n"); 
	printf("4. Mostrar alunos\n");
	printf("5. Matricular aluno em disciplinas\n");//cadastra aluno, pede pra inserir disciplinas ate o usuario terminar
	printf("6. Remover aluno\n");
	printf("7. Remover disciplina\n");
	printf("8. Créditos\n");
	printf("9. Sair\n");
}

S_lista criar() {

    S_lista lista;

    lista.n = -1;

	printf("\nLista foi criada\n");
    return lista;

}

_node * criarNode() {

	_node *n = (_node*) malloc(sizeof(_node));

	if (n) {
		n->prox = NULL;
		return n;
	}

	printf("falha na alocação de memória\n");
	return NULL;

}

//função buscar disciplina

int inserirDisciplina(L_lista *disciplinas, _disciplina nova_disciplina) {
	
	_node *novo_node = criarNode();
	if (novo_node == NULL)
	{
		return -1;
	}

	
	novo_node->disciplina = nova_disciplina;

	// se a lista estiver vazia
	// insere no inicio da lista
	// se não estiver vazia, novo_node->prox aponta pro valor anteriormente no inicio da lista
	// o inicio da lista se torna novo_node;

	if (*disciplinas == NULL) {
		*disciplinas = novo_node;
		return 0;
	} 

	novo_node->prox = *disciplinas;
	*disciplinas = novo_node;
	
	return 0;

}

int limparLista(L_lista *lista)
{
	_node *temp; // cria ponteiro temporario para um node

	while (*lista != NULL){ // até chegar no final da lista

		temp = *lista; //o ponteiro agora aponta para o primeiro da lista
		*lista = temp->prox; // a cabeça da lista agora é o proximo node na lista
		free(temp); // libera o node anterior
		
	}
	return 0;
	
}

int exibirDisciplinasAluno(L_lista *lista)
{
	 // cria ponteiro temporario para um node
	int id;
	char *nome;
	double nota;

	_node *c = *lista; //c de current, vai para o primeiro node na lista
	
	printf("\nDISCIPLINAS: \n");
	printf("\n--------------------------------------------------\n");

	while (c != NULL){ // até chegar no final da lista
		
		//coleta os dados da disciplina
		id = c->disciplina.id; 
		nome = c->disciplina.nome;
		nota = c->disciplina.nota;

		//imprime os dados da disciplina
		printf("id: %i\n", id);
		printf("nome: %s\n", nome);
		printf("nota: %.1f\n", nota);

		//vai para o proximo node
		c = c->prox;
		printf("\n--------------------------------------------------\n");
	}
	return 0;
	
}

void mostrarDisciplinas() {
	FILE *arquivo;
	arquivo = fopen("disciplinas.txt", "r");

	if (!arquivo) {
		printf("\nFalha ao abrir o arquivo de disciplinas\n");
	}

	char c;
	while ((c = fgetc(arquivo)) != EOF) {
		putchar(c);
	}
	fclose(arquivo);
}

void mostrarAlunos() {
	FILE *arquivo;
	arquivo = fopen("alunos.txt", "r");

	if (!arquivo) {
		printf("\nFalha ao abrir o arquivo de alunos\n");
	}

	char c;
	while ((c = fgetc(arquivo)) != EOF) {
		putchar(c);
	}
	fclose(arquivo);
}

/*
_aluno novo_aluno()
{

	novo aluno, tem que alocar memoria para a lista de disciplinas, e inicializar ela como vazia
	tb inserir o aluno de forma ordenada na lista, em ordem de RGM se a lista(de alunos) não estiver vazia

	
		pensei em duas formas de implementar isso, 1. podemos inserir toda a logica relacionada a criar um novo aluno aqui
		por exemplo pedir o input do RGM e Nome e em seguida usar o RGM pra posicionar o aluno ordenadamente na lista
		(a busca binária pra inserir o RGM no indice correto da lista seria uma função separada)

		ou colocar como parametro os dados que vão ser inseridos pro novo aluno e essa função vai ter apenas o processo de 
		inicializar a lista disciplinas alocar memória etc

		mas acho q faz mais sentido colocar td relacionado a inserir o aluno nessa função, com uma função separada pra descobrir o indice
		pra inserir ordenadamente o aluno na lista

	
}

*/

void continuar(){
	printf("\nAperte 'ENTER' para continuar\n");
	getchar();
}
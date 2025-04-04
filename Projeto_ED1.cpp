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

	-BM
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
	
	int rgm; // DEVE SER UMA STRING!!! IMPORTANTE!!
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
void mostrarMenu();
void cpClear();
int inserirAluno(S_lista *lista, int rgm, char nome[]);
void cadastrarAlunos(S_lista *lista);
void mostrarAlunos(S_lista lista);

int main() {
	setlocale(LC_ALL, 0);
	int opcao;
	_aluno Aluno;
	S_lista alunos;

	do {
		mostrarMenu();
		printf("\nEscolha uma opção: ");
		
		scanf("%d", &opcao);
		fflush(stdin);
		
		switch(opcao) {
			case 1:
				static int criado = 0; // Para inicializar variáveis dentro do switch-case, é necessário ou criar um escopo ou usar variável estática. Preferi usar static.
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
						cadastrarAlunos(&alunos);							
					}
					else {
						printf("\nErro: lista ainda não foi criada\n");
					}
				continuar();
				break;
			case 3:
					mostrarDisciplinas();
					continuar();
				break;
			case 4:
				if (criado) { 
					mostrarAlunos(alunos);
				}
				else {
					printf("\nErro: lista ainda não foi criada\n");
				}
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

int isVazia(S_lista *lista) {
	return (lista->n == -1);
}

void mostrarMenu() {
	printf("1. Criar lista\n"); //remover criar lista
	printf("2. Inserir novo aluno\n"); //->cadastra aluno com dados, pede para inserir disciplinas na lista de disciplinas do aluno até o usuario terminal
	printf("3. Mostrar disciplinas\n"); 
	printf("4. Mostrar alunos\n");
	printf("5. Matricular aluno em disciplinas\n");//pede o RGM do aluno -> pede os dados da disciplina -> insere a disciplina
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

	printf("\nfalha na alocação de memória\n");
	return NULL;

}

/*
Essa função coleta os dados para criar uma disciplina que será passada como argumento na função inserir disciplina.

N.B.: ESTA FUNÇÃO ESTÁ INCOMPLETA, ela vai funcionar por hora mas idealmente a função coletará o ID da disciplina
e preencherá o nome a partir dele, também vai oferecer mostrar a lista de disciplinas através do disciplinas.txt que 
pedro criou

-BM
*/
_disciplina coletarDisciplina()
{

	_disciplina nova_disciplina;
	
	printf("Informe o ID da disciplina: ");
	scanf("%d", &nova_disciplina.id);
	getchar();

	//placeholder
	scanf("Informe o nome da disciplina: ");
	scanf("%49[^\n]", nova_disciplina.nome);

	printf("Informe a nota do aluno para a disciplina: ");
	scanf("%f", &nova_disciplina.nota);
	
	return nova_disciplina;

}

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

	if (*lista == NULL) {
		return -1;
	}
	 // cria ponteiro temporario para um node
	int id;
	char *nome;
	double nota;

	_node *p = *lista; //aponta para o primeiro node na lista
	
	printf("\nDISCIPLINAS: \n");
	printf("\n--------------------------------------------------\n");

	while (p != NULL){ // contanto que o node atual exista, ou seja, até chegar ao final da lista
		
		//coleta os dados da disciplina
		id = p->disciplina.id; 
		nome = p->disciplina.nome;
		nota = p->disciplina.nota;

		//imprime os dados da disciplina
		printf("id: %i\n", id);
		printf("nome: %s\n", nome);
		printf("nota: %.1f\n", nota);

		//vai para o proximo node
		p = p->prox;
		printf("\n--------------------------------------------------\n");
	}
	return 0;
	
}

int inserirAluno(S_lista *lista, int rgm, char nome[]) {
    if (lista->n >= MAX - 1) {
        printf("Lista de alunos cheia!\n");
        return 0;
    }

    //verificaça se ja foi registrado um aluno com esse RGM
    for (int i = 0; i <= lista->n; i++) {
        if (lista->alunos[i].rgm == rgm) {
            printf("Erro: RGM %d já cadastrado!\n", rgm);
            return 0;
        }
    }
    //verificação da posição correta para inserir o aluno mediante a ordem do seu RGM
	
    int pos = 0;
	while (pos <= lista->n && lista->alunos[pos].rgm < rgm) {
        pos++;
    }

    //desloca os alunos para a direita na lista abrindo espaço para outro
    for (int i = lista->n+1; i > pos; i--) {
        lista->alunos[i] = lista->alunos[i-1];
    }
    
    lista->alunos[pos].rgm = rgm; //insere o aluno na posição correta
    strcpy(lista->alunos[pos].nome, nome); //copia o nome digitado para a estrutura Aluno
    lista->n++;// aumenta a quantidade de alunos cadastrados
    return 1;
}

//função para cadastrar mais de um aluno por vez
void cadastrarAlunos(S_lista *lista) {
    int n;
    printf("Quantos alunos deseja cadastrar? (Máx: %d): ", MAX);
    scanf("%d", &n);
    getchar();
    //verifica se a quantidade de alunos a ser cadastrada é menor que o MAX
    if (n <= 0 || n > MAX - (lista->n+1)) {
        printf("Número inválido de alunos!\n");
        return;
    }
    //coleta os dados dos alunos
    for (int i = 0; i < n; i++) {
        int rgm;
        char nome[50];
        printf("Digite o RGM do aluno %d: ", i + 1);
        scanf("%d", &rgm);
        getchar();
        printf("Digite o nome do aluno: ");
		scanf("%[^\n]s", nome);
		fflush(stdin);
		// ADICIONAR CADASTRO DE DISCIPLINAS! IMPORTANTE!!!!!!!!!!!!!!!!!
		//TODO: um switch case no "Informe o ID da disciplina" também dando a opção de (apertar {caractere} para ver a lista de disciplinas)


        if (!inserirAluno(lista, rgm, nome)) {
            i--; //se inserir um mesmo RGM ocasionando erro, repete a tentativa
        }
    }
}

void mostrarAlunos(S_lista lista) {
    if (lista.n == -1) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    printf("\nLista de Alunos:\n");
    for (int i = 0; i <= lista.n; i++) {
        printf("RGM: %d - Nome: %s\n", lista.alunos[i].rgm, lista.alunos[i].nome);
    }
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


/*
obs: se futuramente no projeto fomos implementar a opção de deletar um node da lista, 
precisariamos de uma função para relinkar os ponteiros pra não deixar o restante da lista orfã.

essa função retorna um ponteiro para um node, podendo ser usada para acessar o node diretamente dessa forma.

N.B.: Para verificar redundância na lista e evitar inserção de disciplinas duplicadas por exemplo,
a função pode ser simplesmente chamada dessa forma: if (buscarDisciplinaAluno(&lista, id) != NULL)

TODO: futuramente inserir isso na logica de inserir nova disciplina para aluno

-BM
*/

_node *buscarDisciplinaAluno(L_lista *lista, int id)
{

	if (*lista == NULL) {
		return NULL;
	}

	_node *p = *lista; //aponta para o primeiro node na lista
	

	while (p != NULL){ // contanto que o node atual exista, ou seja, até chegar ao final da lista
		
		if (id == p->disciplina.id)
		{
			return p; //se a disciplina foi encontrada, retorna o ponteiro para a disciplina;
		}

		//vai para o proximo node
		p = p->prox;

	}
	
	return NULL;
	
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

		-BM

	
}

*/

void continuar(){
	printf("\nAperte 'ENTER' para continuar\n");
	getchar();
}
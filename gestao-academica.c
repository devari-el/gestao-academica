#include <stdio.h>
#include <string.h>

struct Curso{	
	int id;
	char nome[30]; //Nome do curso
	char nivel[8]; //Tecnico ou Superior
	int duracao; //Duracao em anos
	char grade_disciplinas[3][30];
};

struct Curso cursos[2] ={
	{1, "ADS", "Superior", 3, {"IHC", "ALP", "LHW"}},
	{2, "AGRO", "Tecnico", 2, {"ADM", "PT_BR", "CME"}}
};

struct Disciplina{	
	char nome [30]; //Nome da disciplina
	int carga_horario; //Em horas
};

struct Aluno{
	int id;
	char nome [50]; //Nome aluno
	char curso[30]; //Curso em que está matriculado
	char disciplinas [3][30]; //Disciplinas que está cursando
};

struct Aluno alunos[10];

struct disciplinasMatriculadas{	
	char nome[30];	
};

void exibirAlunos(){

	int numAlunos = sizeof(alunos) / sizeof(alunos[0]);

	if(alunos[0].id != 1){

		printf("\nNao ha alunos matriculados!\n");

	}else{

		for(int i = 0; i < numAlunos; i++){

			if(alunos[i].id == 0){
				break;
			}
			printf("\n\nID: %d\nNOME: %s\nCURSO: %s", 
			alunos[i].id,
			alunos[i].nome,
			alunos[i].curso);
			printf("\nDISCIPLINAS:\n");
			for(int l = 0; l < 3; l++){
				printf("\t\t%s\n", alunos[i].disciplinas[l]);
			}
		}
	}
}

void exibirCursos(){
	printf("\n%s", cursos[0].nome);
	printf("\n%s", cursos[1].nome);
	printf("\n");
}

void cadAluno(){
	
	int i = 0;
	int id_curso;
	
	for (i = 0; i < 10; i++){
		
		if(strlen(alunos[i].nome) == 0){
			alunos[i].id = i + 1;
			break;
		}
		
	}
	
	printf("\nDigite o nome do aluno: ");
	getchar();
	fgets(alunos[i].nome, 50, stdin);
	alunos[i].nome[strcspn(alunos[i].nome, "\n")] = 0;

	int numCursos = sizeof(cursos)/ sizeof(cursos[0]);

	printf("\nDigite para qual curso deseja cadastrar o aluno:\n\n");

	for (int j = 0; j < numCursos; j++){ //for p/ printar todos os cursos disponíveis

		printf("[%d]%s\n", cursos[j].id, cursos[j].nome);

	}
	scanf("%d", &id_curso);
	id_curso -= 1;

	strcpy(alunos[i].curso, cursos[id_curso].nome);

	for(int k = 0; k < 3; k++){ //for p/ definir disciplinas a partir do curso escolhido

		strcpy(alunos[i].disciplinas[k], cursos[id_curso].grade_disciplinas[k]);

	}

	printf("\nAluno cadastrado com sucesso!\n\n");
	printf("ID: %d\n", alunos[i].id);
	printf("NOME: %s\n", alunos[i].nome);
	printf("CURSO: %s\n", alunos[i].curso);
	printf("DISCIPLINAS:\n");
		for(int l = 0; l < 3; l++){
			printf("\t\t%s\n", alunos[i].disciplinas[l]);
		}
}

void iniciarArrayAlunos(){
	for(int i = 0; i < 10; i++){
		alunos[i].id = 0;
		strcpy(alunos[i].curso, "");
		strcpy(alunos[i].nome, "");
	}
}

void menuPrincipal(){
	
	int option = 0;
	
	do{
		printf("\n========== GESTAO ACADEMICA ==========\n\n");
		printf("[1] CADASTRAR ALUNO\n");
		printf("[2] EXIBIR CURSOS\n");
		printf("[3] LANCAR NOTA OU FREQ.\n");
		printf("[4] RELATORIO ALUNO\n");
		printf("[5] SAIR\n");
		printf("\n======================================\n");
		printf("Digite a opcao desejada... ");
		scanf("%d", &option);
		
		switch(option){
			case 1:
				cadAluno();
				break;

			case 2:
				exibirCursos();
				break;

			case 3:
				printf("lancando");
				break;

			case 4:
				printf("relatorio");
				break;
				
			case 5:
				printf("\nObrigado por utilizar este sistema :)\n");
				break;

			default:
				printf("\nOpcao invalida!\n");
		}
	}while(option != 5);
}

int main (void){

	iniciarArrayAlunos();

	menuPrincipal();
	
	return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct Disciplina {
    char nome[10];    
    float notas[3];
    int carga_horaria; 
    int frequencia;
};

struct Curso {    
    int id;
    char nome[30];
    char nivel[8]; 
    int duracao; 
    struct Disciplina grade_curricular[3];
};

struct Curso cursos[2] = {
    {1, "ADS", "Superior", 3, {
        {"IHC", {0, 0, 0}, 80, 0},
        {"ALP", {0, 0, 0}, 80, 0}, 
        {"LHW", {0, 0, 0}, 40, 0}
    }},
    {2, "AGRO", "Tecnico", 2, {
        {"ADM", {0, 0, 0}, 60, 0},
        {"PT_BR", {0, 0, 0}, 60, 0}, 
        {"CME", {0, 0, 0}, 30, 0}
    }}
};

struct Aluno {
    int id;
    char nome[50];
    struct Curso *curso;
};

struct Aluno alunos[10] = {0};

#define NUM_ALUNOS (sizeof(alunos) / sizeof(alunos[0]))
#define NUM_CURSOS (sizeof(cursos) / sizeof(cursos[0]))
#define NUM_DISCIPLINAS (sizeof(cursos[0].grade_curricular) / sizeof(cursos[0].grade_curricular[0]))
#define NUM_NOTAS (sizeof(cursos[0].grade_curricular[0].notas) / sizeof(cursos[0].grade_curricular[0].notas[0]))

void exibirCursos() {
    printf("\nCursos disponiveis:\n");
    for (int i = 0; i < NUM_CURSOS; i++) {
        printf("[%d] %s (%s)\n", cursos[i].id, cursos[i].nome, cursos[i].nivel);
    }
}

void exibirAlunos() {
    int encontrou = 0;
    printf("\nLista de Alunos:\n");
    for (int i = 0; i < NUM_ALUNOS; i++) {
        if (alunos[i].id != 0) {
            encontrou = 1;
            printf("\nID: %d\nNOME: %s\nCURSO: %s\nDISCIPLINAS:\n", alunos[i].id, alunos[i].nome, alunos[i].curso->nome);
            for (int j = 0; j < NUM_DISCIPLINAS; j++) {
                printf("\t- %s\n", alunos[i].curso->grade_curricular[j].nome);
            }
        }
    }
    if (!encontrou) {
        printf("\nNao ha alunos matriculados!\n");
    }
}

void cadAluno() {
    int i, id_curso;
    for (i = 0; i < NUM_ALUNOS; i++) {
        if (alunos[i].id == 0) {
            alunos[i].id = i + 1;
            break;
        }
    }
    if (i == NUM_ALUNOS) {
        printf("\nLimite de alunos atingido!\n");
        return;
    }

    printf("\nDigite o nome do aluno: ");
    getchar();
    fgets(alunos[i].nome, 50, stdin);
    alunos[i].nome[strcspn(alunos[i].nome, "\n")] = 0;

    exibirCursos();
    printf("\nDigite o ID do curso para matricula: ");
    scanf("%d", &id_curso);

    for (int j = 0; j < NUM_CURSOS; j++) {
        if (cursos[j].id == id_curso) {
            alunos[i].curso = &cursos[j];
            printf("\nAluno cadastrado com sucesso!\n");
            return;
        }
    }
    printf("\nCurso nao encontrado! Cadastro cancelado.\n");
    alunos[i].id = 0;
}

void buscarIdAluno(int aluno_buscado, bool *encontrado){
    *encontrado = false;
    for (int i = 0; i < NUM_ALUNOS; i++){
        if(aluno_buscado == alunos[i].id){
            printf("\nAluno selecionado: %s\n\n", alunos[i].nome);
            *encontrado = true;
            return;
        }
    }
    printf("\nAluno nao encontrado!\n");
}

void lancarNotaFrequencia() {
    int id_aluno;
    bool aluno_encontrado = false;

    exibirAlunos();

    printf("\nDigite o ID do aluno que deseja lancar a Nota/Freq: ");
    scanf("%d", &id_aluno);

    buscarIdAluno(id_aluno, &aluno_encontrado);
    if (!aluno_encontrado) return;

    printf("Escolha a disciplina:\n");
    for (int i = 0; i < NUM_DISCIPLINAS; i++) {
        printf("[%d] %s\n", i, alunos[id_aluno - 1].curso->grade_curricular[i].nome);
    }
    int opcaoEscolhida;
	printf("Opcao:");
    scanf("%d", &opcaoEscolhida);
    
    printf("\nLancar:\n[1] NOTA\n[2] FREQUENCIA\nOpcao:");
    int escolha;
    scanf("%d", &escolha);

    if (escolha == 1) {
        for (int i = 0; i < NUM_NOTAS; i++) {
            printf("Nota %d: ", i + 1);
            scanf("%f", &alunos[id_aluno - 1].curso->grade_curricular[opcaoEscolhida].notas[i]);
        }
    } else if (escolha == 2) {
        printf("Frequencia em horas: ");
        scanf("%d", &alunos[id_aluno - 1].curso->grade_curricular[opcaoEscolhida].frequencia);
    }
}

void relatorioAluno(){
    int id_aluno;
    bool aluno_encontrado = false;

    exibirAlunos();

    printf("\nDigite o ID do aluno que deseja obter o relatorio: ");
    scanf("%d", &id_aluno);

    buscarIdAluno(id_aluno, &aluno_encontrado);
    if (!aluno_encontrado) return;	

	id_aluno -= 1;

	printf("\nID: %d\nNome: %s\nCurso: %s\nNivel: %s\nDuracao: %d anos\n\nRelatorio Geral:",
	alunos[id_aluno].id,
	alunos[id_aluno].nome,
	alunos[id_aluno].curso->nome,
	alunos[id_aluno].curso->nivel,
	alunos[id_aluno].curso->duracao);

	float media = 0;
	float percentualFrequencia = 0;

	for(int i = 0; i < NUM_DISCIPLINAS; i++){
		media = 0;
		printf("\n\n%s:", alunos[id_aluno].curso->grade_curricular[i].nome);
		for(int j = 0; j < NUM_NOTAS; j++){
			printf("\n\tNota %d: %.2f", i + 1, alunos[id_aluno].curso->grade_curricular[i].notas[j]);
			media += alunos[id_aluno].curso->grade_curricular[i].notas[j];
		}
		printf("\n\tMedia: %.2f", media/NUM_NOTAS);
		printf("\n\nCarga horaria total da Disciplina: %d horas", 
		alunos[id_aluno].curso->grade_curricular[i].carga_horaria);
		printf("\nCarga horario cursada pelo aluno: %d horas",
		alunos[id_aluno].curso->grade_curricular[i].frequencia);
		percentualFrequencia = (double)alunos[id_aluno].curso->grade_curricular[i].frequencia
		/(double)alunos[id_aluno].curso->grade_curricular[i].carga_horaria
		*100;
		printf("\nPercentual frequencia: %.2f%%", percentualFrequencia);

		if(media < 6 || percentualFrequencia < 75){
			printf("\nStatus: REPROVADO");
		}else{
			printf("\nStatus: APROVADO");
		}
	}
	printf("\n");
}

void menuPrincipal() {
    int option;
    do {
        printf("\n[1] Cadastrar Aluno\n[2] Exibir Cursos\n[3] Lancar Nota ou Frequencia\n[4] Relatorio Aluno\n[5] Sair\nOpcao: ");
        scanf("%d", &option);
        if (option == 1) cadAluno();
        else if (option == 2) exibirCursos();
        else if (option == 3) lancarNotaFrequencia();
		else if (option == 4) relatorioAluno();
		else if (option < 1 || option > 5){
			printf("\nDigite uma opcao valida!\n");
		}
    } while(option != 5);

	printf("\nObrigado por utilizar o sistema!\n");
}

int main() {

    menuPrincipal();
    return 0;
}
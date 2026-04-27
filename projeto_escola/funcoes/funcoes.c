#include <stdio.h>
#include "funcoes.h"
#include <string.h>
#include "util.h"

void listarDisciplinasAlunos(Disciplina disciplinas[],int qnt_disciplinas,Professor professores[],int qnt_professores) {
    int codigo;

    printf("Digite o codigo da disciplina que deseja listar as informacoes: ");
    scanf("%d", &codigo);
    limpar_buffer();

    Disciplina *disciplina = NULL;

    for (int i = 0; i < qnt_disciplinas; i++) {
        if (disciplinas[i].codigo == codigo) {
            disciplina = &disciplinas[i];
            break;
        }
    }

    if (disciplina == NULL) {
        printf("Disciplina nao encontrada.\n");
        return;
    }

    printf("\nCodigo: %d\n", disciplina->codigo);
    printf("Nome: %s\n", disciplina->nome);
    printf("Semestre: %d\n", disciplina->semestre);

    Professor *prof = NULL;

    for (int i = 0; i < qnt_professores; i++) {
        if (professores[i].matricula == disciplina->professor.matricula) {
            prof = &professores[i];
            break;
        }
    }

    if (prof != NULL) {
        printf("Professor: %s\n", prof->nome);
    } else {
        printf("Professor: nao encontrado\n");
    }

    if (disciplina->qnt_alunos == 0) {
        printf("Nenhum aluno matriculado nesta disciplina.\n");
        return;
    }

    printf("Alunos matriculados:\n");

    for (int i = 0; i < disciplina->qnt_alunos; i++) {
        printf("- %s\n", disciplina->alunos[i].nome);
    }
}
//função excluir disciplina
void excluirDisciplina(Disciplina disciplinas[], int *qnt_disciplinas) {
    if (*qnt_disciplinas == 0) {
        printf("Nenhuma disciplina cadastrada.\n");
        return;
    }

    int codigo;
    printf("Digite o codigo da disciplina a ser excluida: ");
    scanf("%d", &codigo);

    int encontrado = 0;
    for (int i = 0; i < *qnt_disciplinas; i++) {
        if (disciplinas[i].codigo == codigo) {
            encontrado = 1;
            for (int j = i; j < *qnt_disciplinas - 1; j++) {
                disciplinas[j] = disciplinas[j + 1];
            }
            (*qnt_disciplinas)--;
            printf("Disciplina excluida com sucesso.\n");
            break;
        }
    }
    if (!encontrado) {
        printf("Disciplina nao encontrada.\n");
    }
}
// função adicionar aluno a disciplina
void adicionarAlunoDisciplina(Disciplina disciplinas[], int qnt_disciplinas, Aluno alunos[], int qnt_alunos) {
    if (qnt_disciplinas == 0) {
        printf("Nenhuma disciplina cadastrada.\n");
        return;
    }
    if (qnt_alunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    int codigo_disciplina;
    unsigned long long matricula_aluno;

    printf("Digite o codigo da disciplina: ");
    scanf("%d", &codigo_disciplina);
    printf("Digite a matricula do aluno: ");
    scanf("%llu", &matricula_aluno);

    Disciplina *disciplina = NULL;
    for (int i = 0; i < qnt_disciplinas; i++) {
        if (disciplinas[i].codigo == codigo_disciplina) {
            disciplina = &disciplinas[i];
            break;
        }
    }
    if (disciplina == NULL) {
        printf("Disciplina nao encontrada.\n");
        return;
    }

    Aluno *aluno = NULL;
    for (int i = 0; i < qnt_alunos; i++) {
        if (alunos[i].matricula == matricula_aluno) {
            aluno = &alunos[i];
            break;
        }
    }
    if (aluno == NULL) {
        printf("Aluno nao encontrado.\n");
        return;
    }

    if (disciplina->qnt_alunos >= 100) {
    printf("Limite de alunos na disciplina atingido.\n");
    return;
}

// VERIFICAR DUPLICADO
for (int i = 0; i < disciplina->qnt_alunos; i++) {
    if (disciplina->alunos[i].matricula == matricula_aluno) {
        printf("Aluno ja esta cadastrado nesta disciplina.\n");
        return;
    }
}

disciplina->alunos[disciplina->qnt_alunos++] = *aluno;
printf("Aluno incluido na disciplina com sucesso.\n");
}
// função excluir aluno da disciplina
void excluirAlunoDisciplina(Disciplina disciplinas[], int qnt_disciplinas, Aluno alunos[], int qnt_alunos) {
    if (qnt_disciplinas == 0) {
        printf("Nenhuma disciplina cadastrada.\n");
        return;
    }
    if (qnt_alunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    int codigo_disciplina;
    unsigned long long matricula_aluno;

    printf("Digite o codigo da disciplina: ");
    scanf("%d", &codigo_disciplina);
    printf("Digite a matricula do aluno: ");
    scanf("%llu", &matricula_aluno);

    Disciplina *disciplina = NULL;
    for (int i = 0; i < qnt_disciplinas; i++) {
        if (disciplinas[i].codigo == codigo_disciplina) {
            disciplina = &disciplinas[i];
            break;
        }
    }
    if (disciplina == NULL) {
        printf("Disciplina nao encontrada.\n");
        return;
    }

    int aluno_index = -1;
    for (int i = 0; i < disciplina->qnt_alunos; i++) {
        if (disciplina->alunos[i].matricula == matricula_aluno) {
            aluno_index = i;
            break;
        }
    }
    if (aluno_index == -1) {
        printf("Aluno nao encontrado na disciplina.\n");
        return;
    }

    for (int j = aluno_index; j < disciplina->qnt_alunos - 1; j++) {
        disciplina->alunos[j] = disciplina->alunos[j + 1];
    }
    disciplina->qnt_alunos--;
    printf("Aluno excluido da disciplina com sucesso.\n");
}
// função cadastrar disciplina
void cadastrarDisciplina(
    Disciplina disciplinas[],
    int *qnt_disciplinas,
    int max_disciplinas,
    Professor professores[],
    int qnt_professores
) {
    if (*qnt_disciplinas >= max_disciplinas) {
        printf("Limite de disciplinas atingido.\n");
        return;
    }

    Disciplina nova_disciplina;

    printf("Digite o nome da disciplina: ");
    fgets(nova_disciplina.nome, sizeof(nova_disciplina.nome), stdin);
    nova_disciplina.nome[strcspn(nova_disciplina.nome, "\n")] = '\0';

    if (strlen(nova_disciplina.nome) == 0) {
        printf("Nome invalido.\n");
        return;
    }

    printf("Digite o codigo da disciplina: ");
    scanf("%d", &nova_disciplina.codigo);
    limpar_buffer();

    printf("Digite o semestre da disciplina: ");
    scanf("%d", &nova_disciplina.semestre);
    limpar_buffer();

    unsigned long long matricula_prof;

    printf("Digite a matricula do professor da disciplina: ");
    scanf("%llu", &matricula_prof);
    limpar_buffer();

    Professor *prof_encontrado = NULL;

    for (int i = 0; i < qnt_professores; i++) {
        if (professores[i].matricula == matricula_prof) {
            prof_encontrado = &professores[i];
            break;
        }
    }

    if (prof_encontrado == NULL) {
        printf("Professor nao encontrado.\n");
        return;
    }

    nova_disciplina.professor = *prof_encontrado;
    nova_disciplina.qnt_alunos = 0;

    disciplinas[*qnt_disciplinas] = nova_disciplina;
    (*qnt_disciplinas)++;

    printf("Disciplina cadastrada com sucesso.\n");
}

void listarDisciplinas(Disciplina disciplinas[], int qnt_disciplinas, Professor professores[], int qnt_professores) {
    if (qnt_disciplinas == 0) {
        printf("Nenhuma disciplina cadastrada.\n");
        return;
    }

    printf("\t--Listar Disciplinas--\n");
    for (int i = 0; i < qnt_disciplinas; i++) {
        Disciplina *disciplina = &disciplinas[i];

        printf("Codigo: %d\n", disciplina->codigo);
        printf("Nome: %s\n", disciplina->nome);
        printf("Semestre: %d\n", disciplina->semestre);

        //Pesquisar professor da disciplina
        Professor *prof = NULL;
        for (int j = 0; j < qnt_professores; j++) {
            if (professores[j].matricula == disciplina->professor.matricula) {
                prof = &professores[j];
                break;
            }
        }

        if (prof != NULL) {
            printf("Professor: %s\n", prof->nome);
        } else {
            printf("Professor: nao encontrado\n");
        }

        printf("\n------------------------------\n");
    }
}
//funcao atualizar disciplina
void atualizarDisciplina(Disciplina disciplinas[], int qnt_disciplinas, Professor professores[], int qnt_professores) {
    printf("Digite o codigo da disciplina a ser atualizada: ");
    int codigo;
    scanf("%d", &codigo);
    Disciplina *disciplina = NULL;
    for (int i = 0; i < qnt_disciplinas; i++) {
        if (disciplinas[i].codigo == codigo) {
            disciplina = &disciplinas[i];
            break;
        }
    }
    if (disciplina == NULL) {
        printf("Disciplina nao encontrada.\n");
        return;
    }

    printf("Digite o novo dado a ser atualizado:\n");
    printf("1 - Nome\n");
    printf("2 - Semestre\n");
    printf("3 - Professor\n");
    int opcao;
    scanf("%d", &opcao);
    switch (opcao) {
        case 1:
            printf("Digite o novo nome: ");
            limpar_buffer();
            fgets(disciplina->nome, sizeof(disciplina->nome), stdin);
            disciplina->nome[strcspn(disciplina->nome, "\n")] = '\0';
            break;
        case 2:
            printf("Digite o novo semestre: ");
            scanf("%d", &disciplina->semestre);
            break;
        case 3:
            printf("Digite a matricula do novo professor: ");
            unsigned long long matricula_professor;
            scanf("%llu", &matricula_professor);
            limpar_buffer();

            Professor *professor = NULL;
            for (int i = 0; i < qnt_professores; i++) {
                if (professores[i].matricula == matricula_professor) {
                    professor = &professores[i];
                    break;
                }
            }
            if (professor == NULL) {
                printf("Professor nao encontrado.\n");
                return;
            }
            disciplina->professor = *professor;
            break;
        default:
            printf("Opcao invalida.\n");
    }
    printf("Disciplina atualizada com sucesso.\n");
}

void listarDisciplinasLotadas(Disciplina disciplinas[], int qnt_disciplinas) {
    if (qnt_disciplinas == 0) {
        printf("Nenhuma disciplina cadastrada.\n");
        return;
    }

    printf("\t--Listar Disciplinas Lotadas (3 ou mais alunos)--\n");
    int encontradas = 0;

    for (int i = 0; i < qnt_disciplinas; i++) {
        if (disciplinas[i].qnt_alunos >= 3) {
            encontradas = 1;
            printf("Codigo: %d\n", disciplinas[i].codigo);
            printf("Nome: %s\n", disciplinas[i].nome);
            printf("Semestre: %d\n", disciplinas[i].semestre);
            printf("Quantidade de Alunos: %d\n", disciplinas[i].qnt_alunos);
            printf("\n------------------------------\n");
        }
    }

    if (!encontradas) {
        printf("Nenhuma disciplina lotada encontrada.\n");
    }
}
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "funcoes/funcoes.h"
#include "funcoes/funcoesAluno.h"
#include "funcoes/funcoesProfessor.h"
#include "funcoes/util.h"

#define MAX_ALUNOS 5

int main(void) {
    int opcao, sair = 0;
    int qnt_alunos = 0, qnt_professores = 0, qnt_disciplinas = 0;

    Aluno alunos[MAX_ALUNOS];
    Professor *professores = NULL;
    Disciplina *disciplinas = NULL;

    while (!sair) {
        printf("\n\t--PROJETO ESCOLA--\n");
        printf("1 - Aluno\n");
        printf("2 - Professor\n");
        printf("3 - Disciplina\n");
        printf("4 - Lista de pessoas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            limpar_buffer();
            printf("Entrada invalida.\n");
            continue;
        }

        limpar_buffer();

        switch (opcao) {

        case 1: {
            int sairAluno = 0;

            while (!sairAluno) {
                int opcaoAluno;

                printf("\n\t--MODULO ALUNO--\n");
                printf("1 - Voltar\n");
                printf("2 - Cadastrar Aluno\n");
                printf("3 - Listar Alunos\n");
                printf("4 - Excluir Aluno\n");
                printf("5 - Atualizar Aluno\n");
                printf("Escolha uma opcao: ");

                scanf("%d", &opcaoAluno);
                limpar_buffer();

                switch (opcaoAluno) {
                case 1:
                    sairAluno = 1;
                    break;

                case 2:
                    cadastrarAluno(alunos, &qnt_alunos, MAX_ALUNOS);
                    break;

                case 3: {
                    int escolhaListagem;

                    printf("Qual tipo de listagem deseja?\n");
                    printf("1 - Listar alunos\n");
                    printf("2 - Listar alunos por sexo\n");
                    printf("3 - Listar alunos por idade\n");
                    printf("4 - Listar alunos por nome\n");
                    printf("5 - Listar alunos matriculados em 3 ou mais disciplinas\n");

                    scanf("%d", &escolhaListagem);
                    limpar_buffer();

                    switch (escolhaListagem) {
                    case 1: listarAlunos(alunos, qnt_alunos); break;
                    case 2: listarAlunosPorSexo(alunos, qnt_alunos); break;
                    case 3: listarAlunosPorIdade(alunos, qnt_alunos); break;
                    case 4: listarAlunosPorNome(alunos, qnt_alunos); break;
                    case 5: listarAlunosEm3Disciplinas(alunos, qnt_alunos, disciplinas, qnt_disciplinas); break;
                    default: printf("Entrada invalida.\n");
                    }

                    break;
                }

                case 4:
                    excluirAluno(alunos, &qnt_alunos);
                    break;

                case 5:
                    atualizarAluno(alunos, qnt_alunos);
                    break;

                default:
                    printf("Entrada invalida.\n");
                }
            }
            break;
        }

        case 2: {
            int sairProfessor = 0;

            while (!sairProfessor) {
                int opcaoProfessor;

                printf("\n\t--MODULO PROFESSOR--\n");
                printf("1 - Voltar\n");
                printf("2 - Cadastrar Professor\n");
                printf("3 - Listar Professores\n");
                printf("4 - Excluir Professor\n");
                printf("5 - Atualizar Professor\n");
                printf("Escolha uma opcao: ");

                scanf("%d", &opcaoProfessor);
                limpar_buffer();

                switch (opcaoProfessor) {
                case 1:
                    sairProfessor = 1;
                    break;

                case 2:
                    professores = realloc(professores,
                        sizeof(Professor) * (qnt_professores + 1));

                    if (professores == NULL) {
                        printf("Erro ao alocar memoria.\n");
                        break;
                    }

                    cadastrarProfessor(professores, &qnt_professores);
                    break;

                case 3: {
                    int escolhaListagem;

                    printf("Qual tipo de listagem deseja?\n");
                    printf("1 - Listar professores\n");
                    printf("2 - Listar professores por sexo\n");
                    printf("3 - Listar professores por idade\n");
                    printf("4 - Listar professores por nome\n");

                    scanf("%d", &escolhaListagem);
                    limpar_buffer();

                    switch (escolhaListagem) {
                    case 1: listarProfessores(professores, qnt_professores); break;
                    case 2: listarProfessoresPorSexo(professores, qnt_professores); break;
                    case 3: listarProfessoresPorIdade(professores, qnt_professores); break;
                    case 4: listarProfessoresPorNome(professores, qnt_professores); break;
                    default: printf("Entrada invalida.\n");
                    }

                    break;
                }

                case 4:
                    excluirProfessor(professores, &qnt_professores);
                    break;

                case 5:
                    atualizarProfessor(professores, qnt_professores);
                    break;

                default:
                    printf("Entrada invalida.\n");
                }
            }
            break;
        }

        case 3: {
            int sairDisciplina = 0;

            while (!sairDisciplina) {
                int opcaoDisciplina;

                printf("\n\t--MODULO DISCIPLINAS--\n");
                printf("1 - Voltar\n");
                printf("2 - Cadastrar Disciplina\n");
                printf("3 - Listar Disciplinas\n");
                printf("4 - Excluir Disciplina\n");
                printf("5 - Incluir aluno na disciplina\n");
                printf("6 - Excluir aluno da disciplina\n");
                printf("7 - Atualizar disciplina\n");
                printf("Escolha uma opcao: ");

                scanf("%d", &opcaoDisciplina);
                limpar_buffer();

                switch (opcaoDisciplina) {
                case 1:
                    sairDisciplina = 1;
                    break;

                case 2:
                    disciplinas = realloc(disciplinas,
                        sizeof(Disciplina) * (qnt_disciplinas + 1));

                    if (disciplinas == NULL) {
                        printf("Erro ao alocar memoria.\n");
                        break;
                    }

                    cadastrarDisciplina(disciplinas,&qnt_disciplinas,100,professores,qnt_professores);
                    break;

                case 3: {
                    int escolhaListagem;

                    printf("Qual tipo de listagem deseja?\n");
                    printf("1 - Listar disciplinas\n");
                    printf("2 - Listar disciplina e nome dos alunos\n");

                    scanf("%d", &escolhaListagem);
                    limpar_buffer();

                    if (escolhaListagem == 1)
                        listarDisciplinas(disciplinas, qnt_disciplinas, professores, qnt_professores);
                    else if (escolhaListagem == 2)
                        listarDisciplinasAlunos(disciplinas, qnt_disciplinas, professores, qnt_professores);
                    else
                        printf("Entrada invalida.\n");

                    break;
                }

                case 4:
                    excluirDisciplina(disciplinas, &qnt_disciplinas);
                    break;

                case 5:
                    adicionarAlunoDisciplina(disciplinas, qnt_disciplinas, alunos, qnt_alunos);
                    break;

                case 6:
                    excluirAlunoDisciplina(disciplinas, qnt_disciplinas, alunos, qnt_alunos);
                    break;

                case 7:
                    atualizarDisciplina(disciplinas, qnt_disciplinas, professores, qnt_professores);
                    break;

                default:
                    printf("Entrada invalida.\n");
                }
            }
            break;
        }

        case 4: {
            int escolhaListagem;

            printf("Selecione o tipo de listagem das pessoas:\n");
            printf("1 - Pesquisa de alunos e professores por nome\n");
            printf("★ 2 - Aniversariante do Mes ★\n");

            scanf("%d", &escolhaListagem);
            limpar_buffer();

            if (escolhaListagem == 1)
                listarPessoasStrg(alunos, qnt_alunos, professores, qnt_professores);
            else if (escolhaListagem == 2)
                listarAniversariantes(alunos, qnt_alunos, professores, qnt_professores);
            else
                printf("Opcao invalida.\n");

            break;
        }

        case 0:
            sair = 1;
            break;

        default:
            printf("Entrada invalida.\n");
        }
    }

    free(professores);
    free(disciplinas);

    return 0;
}
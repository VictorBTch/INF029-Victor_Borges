#include <stdio.h>
#include "funcoes.h"
#include <string.h>
#include "util.h"

//funcao listar alunos
void listarAlunos(Aluno alunos[], int qnt_alunos) {
    if (qnt_alunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    printf("\t--Listar Alunos--\n");
    for (int i = 0; i < qnt_alunos; i++) {
        Aluno *aluno = &alunos[i];
        printf("\nMatricula: %llu\n", aluno->matricula);
        printf("Nome: %s\n", aluno->nome);
        printf("Data de Nascimento: %02d/%02d/%04d\n",
               aluno->data_nascimento.dia,
               aluno->data_nascimento.mes,
               aluno->data_nascimento.ano);
        printf("Idade: %d\n", aluno->idade);
        printf("CPF: %s\n", aluno->CPF);
        printf("Sexo: %c\n", aluno->sexo);
        printf("\n------------------------------\n");
    }
}

//funcao atualizar aluno
void atualizarAluno(Aluno alunos[], int qnt_alunos) {
    printf("Digite o aluno que deseja atualizar (matricula): ");
    unsigned long long matricula;
    scanf("%llu", &matricula);
    Aluno *aluno = NULL;
    for (int i = 0; i < qnt_alunos; i++) {
        if (alunos[i].matricula == matricula) {
            aluno = &alunos[i];
            break;
        }
    }
    if (aluno == NULL) {
        printf("Aluno nao encontrado.\n");
        return;
    }

    printf("Digite o novo dado a ser atualizado:\n");
    printf("1 - Nome\n");
    printf("2 - Data de nascimento\n");
    printf("3 - CPF\n");
    printf("4 - Sexo\n");
    int opcao;
    scanf("%d", &opcao);
    switch (opcao) {
        case 1:
            printf("Digite o novo nome: ");
            limpar_buffer();
            fgets(aluno->nome, sizeof(aluno->nome), stdin);
            aluno->nome[strcspn(aluno->nome, "\n")] = '\0';
            break;
        case 2:
            printf("Digite a nova data de nascimento (dd mm aaaa): ");
            printf("Dia: ");
            scanf("%d", &aluno->data_nascimento.dia);
            printf("Mes: ");
            scanf("%d", &aluno->data_nascimento.mes);
            printf("Ano: ");
            scanf("%d", &aluno->data_nascimento.ano);
            aluno->idade = 2026 - aluno->data_nascimento.ano;
            break;
        case 3:
            printf("Digite o novo CPF: ");
            scanf("%s", aluno->CPF);
            break;
        case 4:
            printf("Digite o novo sexo (M/F): ");
            scanf(" %c", &aluno->sexo);
            break;
        printf("Aluno atualizado com sucesso.\n");
            default:
            printf("Opcao invalida.\n");    
    }
}

//função excluir aluno
void excluirAluno(Aluno alunos[], int *qnt_alunos) {    
    if (*qnt_alunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    unsigned long long matricula;
    printf("Digite a matricula do aluno a ser excluido: ");
    scanf("%llu", &matricula);

    int encontrado = 0;
    for (int i = 0; i < *qnt_alunos; i++) {
        if (alunos[i].matricula == matricula) {
            encontrado = 1;
            for (int j = i; j < *qnt_alunos - 1; j++) {
                alunos[j] = alunos[j + 1];
            }
            (*qnt_alunos)--;
            printf("Aluno excluido com sucesso.\n");
            break;
        }
    }
    if (!encontrado) {
        printf("Aluno nao encontrado.\n");
    }
}
// função cadastrar aluno
int cadastrarAluno(Aluno alunos[], int *qnt_alunos, int max_alunos) {
    if (*qnt_alunos >= max_alunos) {
        printf("Limite de alunos atingido.\n");
        return 0;
    }

    Aluno novo_aluno;

    printf("Digite a matricula do aluno: ");
    scanf("%llu", &novo_aluno.matricula);
    limpar_buffer();

    if (novo_aluno.matricula == 0) {
        printf("Matricula invalida.\n");
        return 0;
    }

    // VERIFICA DUPLICADO
    for (int i = 0; i < *qnt_alunos; i++) {
        if (alunos[i].matricula == novo_aluno.matricula) {
            printf("Matricula ja cadastrada.\n");
            return 0;
        }
    }

    printf("Digite o nome do aluno: ");
    fgets(novo_aluno.nome, sizeof(novo_aluno.nome), stdin);
    novo_aluno.nome[strcspn(novo_aluno.nome, "\n")] = '\0';

    if (strlen(novo_aluno.nome) == 0) {
        printf("Nome invalido.\n");
        return 0;
    }

    printf("Digite a data de nascimento do aluno:\n");
    printf("Dia: ");
    scanf("%d", &novo_aluno.data_nascimento.dia);
    printf("Mes: ");
    scanf("%d", &novo_aluno.data_nascimento.mes);
    printf("Ano: ");
    scanf("%d", &novo_aluno.data_nascimento.ano);
    limpar_buffer();

    novo_aluno.idade = 2026 - novo_aluno.data_nascimento.ano;

    if (novo_aluno.data_nascimento.dia < 1 ||
        novo_aluno.data_nascimento.dia > 31 ||
        novo_aluno.data_nascimento.mes < 1 ||
        novo_aluno.data_nascimento.mes > 12 ||
        novo_aluno.data_nascimento.ano < 1900 ||
        novo_aluno.data_nascimento.ano > 2026) {
        printf("Data invalida.\n");
        return 0;
    }

    printf("Digite o CPF (11 digitos): ");
    scanf("%11s", novo_aluno.CPF);
    limpar_buffer();

    if (strlen(novo_aluno.CPF) != 11) {
        printf("CPF invalido. Deve conter exatamente 11 digitos.\n");
        return 0;
    }

    printf("Digite o sexo do aluno (M/F): ");
    scanf(" %c", &novo_aluno.sexo);

    if (novo_aluno.sexo == 'm') {
        novo_aluno.sexo = 'M';
    } else if (novo_aluno.sexo == 'f') {
        novo_aluno.sexo = 'F';
    }

    if (novo_aluno.sexo != 'M' && novo_aluno.sexo != 'F') {
        printf("Sexo invalido. Digite 'M' ou 'F'.\n");
        limpar_buffer();
        return 0;
    }

    alunos[*qnt_alunos] = novo_aluno;
    (*qnt_alunos)++;

    printf("Aluno cadastrado com sucesso.\n");
    return 1;
}

void listarAlunosPorSexo(Aluno alunos[], int qnt_alunos) {
    if (qnt_alunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    char sexo;

    printf("Digite o sexo para filtrar (M/F): ");
    scanf(" %c", &sexo);
    limpar_buffer();

    if (sexo == 'm') sexo = 'M';
    else if (sexo == 'f') sexo = 'F';

    if (sexo != 'M' && sexo != 'F') {
        printf("Sexo invalido. Digite 'M' ou 'F'.\n");
        return;
    }

    printf("\t--Listar Alunos por Sexo (%c)--\n", sexo);

    int encontrados = 0;

    for (int i = 0; i < qnt_alunos; i++) {
        if (alunos[i].sexo == sexo) {
            encontrados = 1;

            printf("\nMatricula: %llu\n", alunos[i].matricula);
            printf("Nome: %s\n", alunos[i].nome);
            printf("Data de Nascimento: %02d/%02d/%04d\n",
                   alunos[i].data_nascimento.dia,
                   alunos[i].data_nascimento.mes,
                   alunos[i].data_nascimento.ano);
            printf("Idade: %d\n", alunos[i].idade);
            printf("CPF: %s\n", alunos[i].CPF);
            printf("Sexo: %c\n", alunos[i].sexo);
            printf("\n------------------------------\n");
        }
    }

    if (!encontrados) {
        printf("Nenhum aluno encontrado com sexo %c.\n", sexo);
    }
}
void listarAlunosPorIdade(Aluno alunos[], int qnt_alunos) {
    if (qnt_alunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    Aluno ordenados[qnt_alunos];

    for (int i = 0; i < qnt_alunos; i++) {
        ordenados[i] = alunos[i];
    }

    for (int i = 0; i < qnt_alunos - 1; i++) {
        for (int j = 0; j < qnt_alunos - i - 1; j++) {
            if (ordenados[j].idade < ordenados[j + 1].idade) {
                Aluno temp = ordenados[j];
                ordenados[j] = ordenados[j + 1];
                ordenados[j + 1] = temp;
            }
        }
    }

    printf("\t--Listar Alunos por Idade (Decrescente)--\n");

    for (int i = 0; i < qnt_alunos; i++) {
        printf("\nMatricula: %llu\n", ordenados[i].matricula);
        printf("Nome: %s\n", ordenados[i].nome);
        printf("Data de Nascimento: %02d/%02d/%04d\n",
               ordenados[i].data_nascimento.dia,
               ordenados[i].data_nascimento.mes,
               ordenados[i].data_nascimento.ano);
        printf("Idade: %d\n", ordenados[i].idade);
        printf("CPF: %s\n", ordenados[i].CPF);
        printf("Sexo: %c\n", ordenados[i].sexo);
        printf("\n------------------------------\n");
    }
}

void listarAlunosPorNome(Aluno alunos[], int qnt_alunos) {
    if (qnt_alunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    Aluno ordenados[qnt_alunos];

    for (int i = 0; i < qnt_alunos; i++) {
        ordenados[i] = alunos[i];
    }

    for (int i = 0; i < qnt_alunos - 1; i++) {
        for (int j = 0; j < qnt_alunos - i - 1; j++) {
            if (strcmp(ordenados[j].nome, ordenados[j + 1].nome) > 0) {
                Aluno temp = ordenados[j];
                ordenados[j] = ordenados[j + 1];
                ordenados[j + 1] = temp;
            }
        }
    }

    printf("\t--Listar Alunos por Nome (A-Z)--\n");

    for (int i = 0; i < qnt_alunos; i++) {
        printf("\nMatricula: %llu\n", ordenados[i].matricula);
        printf("Nome: %s\n", ordenados[i].nome);
        printf("Data de Nascimento: %02d/%02d/%04d\n",
               ordenados[i].data_nascimento.dia,
               ordenados[i].data_nascimento.mes,
               ordenados[i].data_nascimento.ano);
        printf("Idade: %d\n", ordenados[i].idade);
        printf("CPF: %s\n", ordenados[i].CPF);
        printf("Sexo: %c\n", ordenados[i].sexo);
        printf("\n------------------------------\n");
    }
}

void listarAlunosEm3Disciplinas(Aluno alunos[], int qnt_alunos, Disciplina disciplinas[], int qnt_disciplinas) {
    if (qnt_alunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
       return;
    }
    if (qnt_disciplinas == 0) {
        printf("Nenhuma disciplina cadastrada.\n");
        return;
    }  
    printf("\t--Listar Alunos Matriculados em 3 ou Mais Disciplinas--\n");
    int encontrados = 0;
    for(int i = 0; i < qnt_alunos; i++) {
        int contador = 0;
        for (int j = 0; j < qnt_disciplinas; j++) {
            for (int k = 0; k < disciplinas[j].qnt_alunos; k++) {
                if (disciplinas[j].alunos[k].matricula == alunos[i].matricula) {
                    contador++;
                    break;
                }
            }
        }
        if (contador >= 3) {
            encontrados = 1;
            printf("\nMatricula: %llu\n", alunos[i].matricula);
            printf("Nome: %s\n", alunos[i].nome);
            printf("Data de Nascimento: %02d/%02d/%04d\n",
                   alunos[i].data_nascimento.dia,
                   alunos[i].data_nascimento.mes,
                   alunos[i].data_nascimento.ano);
            printf("Idade: %d\n", alunos[i].idade);
            printf("CPF: %s\n", alunos[i].CPF);
            printf("Sexo: %c\n", alunos[i].sexo);
            printf("\n------------------------------\n");
        }
    }
    if (!encontrados) {
        printf("Nenhum aluno encontrado matriculado em 3 ou mais disciplinas.\n");
    }
} 
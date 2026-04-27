#include <stdio.h>
#include "funcoes.h"
#include "../structs.h"
#include <string.h>
#include "util.h"

//função listar professores
void listarProfessores(Professor professores[], int qnt_professores) {
    if (qnt_professores == 0) {
        printf("Nenhum professor cadastrado.\n");
        return;
    }

    printf("\t--Listar Professores--\n");
    for (int i = 0; i < qnt_professores; i++) {
        Professor *professor = &professores[i];
        printf("\nMatricula: %llu\n", professor->matricula);
        printf("Nome: %s\n", professor->nome);
        printf("Data de Nascimento: %02d/%02d/%04d\n",
               professor->data_nascimento.dia,
               professor->data_nascimento.mes,
               professor->data_nascimento.ano);
        printf("Idade: %d\n", professor->idade);
        printf("CPF: %s\n", professor->CPF);
        printf("Sexo: %c\n", professor->sexo);
        printf("\n------------------------------\n");
    }
}

//função excluir professor
void excluirProfessor(Professor professores[], int *qnt_professores) {
    if (*qnt_professores == 0) {
        printf("Nenhum professor cadastrado.\n");
        return;
    }

    unsigned long long matricula;
    printf("Digite a matricula do professor a ser excluido: ");
    scanf("%llu", &matricula);

    int encontrado = 0;
    for (int i = 0; i < *qnt_professores; i++) {
        if (professores[i].matricula == matricula) {
            encontrado = 1;
            for (int j = i; j < *qnt_professores - 1; j++) {
                professores[j] = professores[j + 1];
            }
            (*qnt_professores)--;
            printf("Professor excluido com sucesso.\n");
            break;
        }
    }
    if (!encontrado) {
        printf("Professor nao encontrado.\n");
    }
}

//função atualizar professor
void atualizarProfessor(Professor professores[], int qnt_professores) {
    printf("Digite o professor que deseja atualizar (matricula): ");
    unsigned long long matricula;
    scanf("%llu", &matricula);
    Professor *professor = NULL;
    for (int i = 0; i < qnt_professores; i++)   {
        if (professores[i].matricula == matricula) {
            professor = &professores[i];
            break;
        }
    }
    if (professor == NULL) {
        printf("Professor nao encontrado.\n");
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
            fgets(professor->nome, sizeof(professor->nome), stdin);
            professor->nome[strcspn(professor->nome, "\n")] = '\0';
            break;
        case 2:
            printf("Digite a nova idade: ");
            scanf("%d", &professor->idade);
            break;
        case 3:
            printf("Digite a nova data de nascimento (dd mm aaaa): ");
            printf("Dia: ");
            scanf("%d", &professor->data_nascimento.dia);
            printf("Mes: ");
            scanf("%d", &professor->data_nascimento.mes);
            printf("Ano: ");
            scanf("%d", &professor->data_nascimento.ano);
            professor->idade = 2026 - professor->data_nascimento.ano;      
            break;
        case 4:
            printf("Digite o novo CPF: ");
            scanf("%s", professor->CPF);
            break;
        case 5:
            printf("Digite o novo sexo (M/F): ");
            scanf(" %c", &professor->sexo);
            break;
        printf("Professor atualizado com sucesso.\n");
        default:
            printf("Opcao invalida.\n");
}
}
//função cadastrar professor
void cadastrarProfessor(Professor professores[], int *qnt_professores) {
    Professor novo_professor;

    printf("Digite a matricula do professor: ");
    scanf("%llu", &novo_professor.matricula);
    limpar_buffer();
    
    // VERIFICA DUPLICADO
    for (int i = 0; i < *qnt_professores; i++) {
        if (professores[i].matricula == novo_professor.matricula) {
            printf("Matricula ja cadastrada.\n");
            return;
        }
    }
    printf("Nome: ");
    fgets(novo_professor.nome, sizeof(novo_professor.nome), stdin);
    novo_professor.nome[strcspn(novo_professor.nome, "\n")] = '\0';

    printf("Digite o sexo do professor (M/F): ");
    scanf(" %c", &novo_professor.sexo);
    limpar_buffer();

    if (novo_professor.sexo == 'm') novo_professor.sexo = 'M';
    else if (novo_professor.sexo == 'f') novo_professor.sexo = 'F';

    if (novo_professor.sexo != 'M' && novo_professor.sexo != 'F') {
        printf("Sexo invalido.\n");
        return;
    }

    printf("Digite a data de nascimento (dd mm aaaa):\n");
    printf("Dia: ");
    scanf("%d", &novo_professor.data_nascimento.dia);
    printf("Mes: ");
    scanf("%d", &novo_professor.data_nascimento.mes);
    printf("Ano: ");
    scanf("%d", &novo_professor.data_nascimento.ano);
    limpar_buffer();

    novo_professor.idade = 2026 - novo_professor.data_nascimento.ano;
        if (novo_professor.data_nascimento.dia < 1 ||
            novo_professor.data_nascimento.dia > 31 ||
            novo_professor.data_nascimento.mes < 1 ||
            novo_professor.data_nascimento.mes > 12 ||
            novo_professor.data_nascimento.ano < 1900 ||
            novo_professor.data_nascimento.ano > 2026) {
        printf("Data invalida.\n");
        return;
    }
    printf("Digite o CPF (11 digitos): ");
    scanf("%11s", novo_professor.CPF);
    limpar_buffer();

    if (strlen(novo_professor.CPF) != 11) {
        printf("CPF invalido.\n");
        return;
    }

    professores[*qnt_professores] = novo_professor;
    (*qnt_professores)++;

    printf("Professor cadastrado com sucesso.\n");
}

void listarProfessoresPorSexo(Professor professores[], int qnt_professores) {
    if (qnt_professores == 0) {
        printf("Nenhum professor cadastrado.\n");
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

    printf("\t--Listar Professores por Sexo (%c)--\n", sexo);

    int encontrados = 0;

    for (int i = 0; i < qnt_professores; i++) {
        if (professores[i].sexo == sexo) {
            encontrados = 1;

            printf("\nMatricula: %llu\n", professores[i].matricula);
            printf("Nome: %s\n", professores[i].nome);
            printf("Data de Nascimento: %02d/%02d/%04d\n",
                   professores[i].data_nascimento.dia,
                   professores[i].data_nascimento.mes,
                   professores[i].data_nascimento.ano);
            printf("Idade: %d\n", professores[i].idade);
            printf("CPF: %s\n", professores[i].CPF);
            printf("Sexo: %c\n", professores[i].sexo);
            printf("\n------------------------------\n");
        }
    }

    if (!encontrados) {
        printf("Nenhum professor encontrado com sexo %c.\n", sexo);
    }
}

void listarProfessoresPorIdade(Professor professores[], int qnt_professores) {
    if (qnt_professores == 0) {
        printf("Nenhum professor cadastrado.\n");
        return;
    }

    Professor ordenados[qnt_professores];

    for (int i = 0; i < qnt_professores; i++) {
        ordenados[i] = professores[i];
    }

    for (int i = 0; i < qnt_professores - 1; i++) {
        for (int j = 0; j < qnt_professores - i - 1; j++) {
            if (ordenados[j].idade < ordenados[j + 1].idade) {
                Professor temp = ordenados[j];
                ordenados[j] = ordenados[j + 1];
                ordenados[j + 1] = temp;
            }
        }
    }

    printf("\t--Listar Professores por Idade (Decrescente)--\n");

    for (int i = 0; i < qnt_professores; i++) {
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

void listarProfessoresPorNome(Professor professores[], int qnt_professores) {
    if (qnt_professores == 0) {
        printf("Nenhum professor cadastrado.\n");
        return;
    }

    Professor ordenados[qnt_professores];

    for (int i = 0; i < qnt_professores; i++) {
        ordenados[i] = professores[i];
    }

    for (int i = 0; i < qnt_professores - 1; i++) {
        for (int j = 0; j < qnt_professores - i - 1; j++) {
            if (strcmp(ordenados[j].nome, ordenados[j + 1].nome) > 0) {
                Professor temp = ordenados[j];
                ordenados[j] = ordenados[j + 1];
                ordenados[j + 1] = temp;
            }
        }
    }

    printf("\t--Listar Professores por Nome (A-Z)--\n");

    for (int i = 0; i < qnt_professores; i++) {
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
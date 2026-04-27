#include <stdio.h>
#include "funcoes.h"
#include <string.h>

void limpar_buffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void listarAniversariantes(Aluno alunos[], int qnt_alunos, Professor professores[], int qnt_professores) {
    if (qnt_alunos == 0 && qnt_professores == 0) {
        printf("Nenhum aluno ou professor cadastrado.\n");
        return;
    }

    int mes_atual;
    printf("Digite o mes atual (1-12): ");
    if (scanf("%d", &mes_atual) != 1 || mes_atual < 1 || mes_atual > 12) {
        limpar_buffer();
        printf("Mes invalido. Digite um valor entre 1 e 12.\n");
        return;
    }
    limpar_buffer();

   printf(">>> ★ Aniversariante do Mes (%d)★ <<<\n", mes_atual);

    int encontrados = 0;

    for (int i = 0; i < qnt_alunos; i++) {
        if (alunos[i].data_nascimento.mes == mes_atual) {
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

    for (int i = 0; i < qnt_professores; i++) {
        if (professores[i].data_nascimento.mes == mes_atual) {
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
        printf("Nenhum aniversariante encontrado no mes %d.\n", mes_atual);
    }
}

#include <ctype.h>
#include <string.h>

void listarPessoasStrg(Aluno alunos[], int qnt_alunos,Professor professores[], int qnt_professores) {
    if (qnt_alunos == 0 && qnt_professores == 0) {
        printf("Nenhum aluno ou professor cadastrado.\n");
        return;
    }

    char filtro[50];

    printf("\t--Buscar Pessoas por Nome--\n");
    printf("Digite no minimo 3 letras para buscar: ");

    fgets(filtro, sizeof(filtro), stdin);
    filtro[strcspn(filtro, "\n")] = '\0';

    if (strlen(filtro) < 3) {
        printf("Digite pelo menos 3 letras.\n");
        return;
    }

    int encontrados = 0;

    printf("\n--- Alunos Encontrados ---\n");

    for (int i = 0; i < qnt_alunos; i++) {
        int j = 0;
        int k = 0;

        while (alunos[i].nome[j] != '\0' && filtro[k] != '\0') {
            if (tolower(alunos[i].nome[j]) == tolower(filtro[k])) {
                k++;
            }
            j++;
        }

        if (filtro[k] == '\0') {
            encontrados = 1;
            printf("Aluno: %s | Matricula: %llu\n",
                   alunos[i].nome,
                   alunos[i].matricula);
        }
    }

    printf("\n--- Professores Encontrados ---\n");

    for (int i = 0; i < qnt_professores; i++) {
        int j = 0;
        int k = 0;

        while (professores[i].nome[j] != '\0' && filtro[k] != '\0') {
            if (tolower(professores[i].nome[j]) == tolower(filtro[k])) {
                k++;
            }
            j++;
        }

        if (filtro[k] == '\0') {
            encontrados = 1;
            printf("Professor: %s | Matricula: %llu\n",
                   professores[i].nome,
                   professores[i].matricula);
        }
    }

    if (!encontrados) {
        printf("\nNenhuma pessoa encontrada com \"%s\" no nome.\n", filtro);
    }
}
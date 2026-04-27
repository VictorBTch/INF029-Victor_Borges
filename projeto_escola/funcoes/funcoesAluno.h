#ifndef FUNCOESALUNO_H
#define FUNCOESALUNO_H

#include "../structs.h"

void listarAlunos(Aluno alunos[], int qnt_alunos);

void excluirAluno(Aluno alunos[], int *qnt_alunos);

void atualizarAluno(Aluno alunos[], int qnt_alunos);

int cadastrarAluno(Aluno alunos[], int *qnt_alunos, int max_alunos);

void listarAlunosPorSexo(Aluno alunos[], int qnt_alunos);

void listarAlunosPorIdade(Aluno alunos[], int qnt_alunos);

void listarAlunosPorNome(Aluno alunos[], int qnt_alunos);

void listarAlunosEm3Disciplinas(Aluno alunos[], int qnt_alunos, Disciplina disciplinas[], int qnt_disciplinas);
#endif // FUNCOESALUNO_H
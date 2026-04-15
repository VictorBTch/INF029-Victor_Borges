#ifndef FUNCOES_H
#define FUNCOES_H

#include "../structs.h"

void listarDisciplinasAlunos(Disciplina disciplinas[],int qnt_disciplinas,Professor professores[],int qnt_professores);

void excluirDisciplina(Disciplina disciplinas[], int *qnt_disciplinas);

void excluirAlunoDisciplina(Disciplina disciplinas[], int qnt_disciplinas, Aluno alunos[], int qnt_alunos);

void adicionarAlunoDisciplina(Disciplina disciplinas[], int qnt_disciplinas, Aluno alunos[], int qnt_alunos);

void cadastrarDisciplina(Disciplina disciplinas[],int *qnt_disciplinas,int max_disciplinas,Professor professores[],int qnt_professores);

void listarDisciplinas(Disciplina disciplinas[], int qnt_disciplinas, Professor professores[], int qnt_professores);

void atualizarDisciplina(Disciplina disciplinas[], int qnt_disciplinas, Professor professores[], int qnt_professores);

void listarDisciplinasLotadas(Disciplina disciplinas[], int qnt_disciplinas);   
#endif // FUNCOES_H

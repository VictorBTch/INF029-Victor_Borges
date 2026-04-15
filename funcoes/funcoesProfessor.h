#ifndef FUNCOESPROFESSOR_H
#define FUNCOESPROFESSOR_H

#include "../structs.h"



void excluirProfessor(Professor professores[], int *qnt_professores);

void atualizarProfessor(Professor professores[], int qnt_professores);

void cadastrarProfessor(Professor professores[], int *qnt_professores);

void listarProfessoresPorSexo(Professor professores[], int qnt_professores);

void listarProfessoresPorIdade(Professor professores[], int qnt_professores);

void listarProfessoresPorNome(Professor professores[], int qnt_professores);

void listarProfessores(Professor professores[], int qnt_professores);

#endif // FUNCOESPROFESSOR_H

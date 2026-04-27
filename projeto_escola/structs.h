#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Data {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct Aluno {
    char nome[50];
    int idade;
    unsigned long long matricula;
    Data data_nascimento;
    char CPF[12]; // CPF com 11 dígitos + caractere nulo
    char sexo; // 'M' para masculino, 'F' para feminino
} Aluno;

typedef struct Professor {
    char nome[50];
    int idade;
    unsigned long long matricula;
    Data data_nascimento;
    char CPF[12]; // CPF com 11 dígitos + caractere nulo
    char sexo; // 'M' para masculino, 'F' para feminino
} Professor;

typedef struct Disciplina {
    char nome[50];
    int codigo;
    Professor professor;
    int semestre;
    Aluno alunos[100]; // Lista de alunos matriculados na disciplina
    int qnt_alunos; // Quantidade de alunos matriculados
} Disciplina;
#endif // STRUCTS_H

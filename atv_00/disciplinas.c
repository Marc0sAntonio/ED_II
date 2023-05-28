#include <stdio.h>
#include <stdlib.h>

struct disciplina{
    int _cod; // não pode ser repetido, é o parametro de organização da arv
    char _nome_disciplina[40];
    int _bloco; //deve ser menor que a quatidade de blocos do curso
    int _carga_horaria; //multiplo do numerod e semanas da disciplina
};
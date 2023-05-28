#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "curso.h"
#include "disciplinas.h"


struct curso{
    int _cod;
    char _nome_curso[50];
    int _qtd_blocos;
    int _qtd_seman;
    Disciplina *_arv_disciplinas;
    Curso *dir;
    Curso *esq;
};

int Busca_cod_curso(Curso *raizCursos, int cod_curso)
{   int achou = 0;
    if(raizCursos != NULL)
    {
        if(raizCursos->_cod == cod_curso)
            achou = 1;
        else if (raizCursos->_cod < cod_curso)
            achou = Busca_cod_curso(raizCursos->dir, cod_curso);
        else
            achou = Busca_cod_curso(raizCursos->esq, cod_curso);
    }   
    return achou;
}

int Cria_cod_unico(Curso *raizCursos) {
    srand(time(NULL));
    int cod_curso = 0;
    do
        cod_curso = rand() % 10000;
    while (Busca_cod_curso(raizCursos, cod_curso));

    return (cod_curso);
}


void cria_arv_cursos(Curso **raizCurso) {

    Cria_curso(&(*raizCurso), "Pão", 5, 25);
    Cria_curso(&(*raizCurso), "sistemas", 2, 10);
    Cria_curso(&(*raizCurso), "biologia", 8, 15);
    Cria_curso(&(*raizCurso), "catarro", 3, 15);

}

void Cria_curso(Curso **raizCursos, char *nome_curso, int qtd_blocos, int qtd_seman)
{
    Curso* Novo = (Curso *) malloc(sizeof(Curso));
    
    Novo->_qtd_blocos = qtd_blocos;
    Novo->_qtd_seman = qtd_seman;
    strcpy(Novo->_nome_curso, nome_curso);
    Novo->_cod = Cria_cod_unico((*raizCursos)); 
    Novo->dir = NULL;
    Novo->esq = NULL;
    
    Insere_curso(&(*raizCursos), Novo); 
}

void Insere_curso(Curso** raizCursos, Curso* Novo)
{
    if ((*raizCursos) == NULL) 
        *raizCursos = Novo;
    else {
        if (Novo->_cod < (*raizCursos)->_cod) 
            Insere_curso(&((*raizCursos)->esq), Novo);
        else 
            Insere_curso(&((*raizCursos)->dir), Novo);
    }
}

void Imprime_cursos_crescente(Curso *raizCursos)
{
    if (raizCursos != NULL)
    {
        Imprime_cursos_crescente(raizCursos->esq);
        printf("\n================================");
        printf("Código do curso: %d\n", raizCursos->_cod);
        printf("Nome do curso: %s\n", raizCursos->_nome_curso);
        printf("Quantidade de blocos: %d\n", raizCursos->_qtd_blocos);
        printf("Quantidade de semanas: %d\n", raizCursos->_qtd_seman);
        printf("\n================================");
        Imprime_cursos_crescente(raizCursos->dir);
    }
}







// (1) Imprimir a árvore de cursos em ordem crescente pelo código do curso;
// (2) Imprimir os dados de um curso dado o código do mesmo;
// (3) Imprimir todos os cursos com a mesma quantidade de blocos, onde o usuário informe a quantidade 
// de blocos;
// (4) Imprimir a árvore de disciplinas em ordem crescente pelo código das disciplinas dado o código do 
// curso;
// (5) Imprimir os dados de uma disciplina dado o código dela e do curso ao qual ela pertence;
// (6) Imprimir as disciplinas de um determinado bloco de um curso, dado o bloco e o código do curso;
// (7) Imprimir todas as disciplinas de um determinado curso com a mesma carga horária, onde o código 
// do curso e a carga horária devem ser informadas pelo usuário;
// (8) Excluir uma disciplina dado o código da disciplina e o código do curso;
// (9) Excluir um curso dado o código do mesmo, desde que não tenha nenhuma disciplina cadastrada para 
// aquele curso
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arv_AVL.h"

#define MULT_NUM_SEM = 15

struct disciplina{
    int _cod; // não pode ser repetido, é o parametro de organização da arv
    char _nome_disciplina[40];
    int _bloco; //deve ser menor que a quatidade de blocos do curso
    int _carga_horaria; //multiplo do numerod e semanas da disciplina
    Disciplina *esq;
    Disciplina *dir;
    int altura;
};

struct curso{
    int _cod;
    char _nome_curso[50];
    int _qtd_blocos;
    int _qtd_seman;
    Disciplina *_arv_disciplinas;
    Curso *dir;
    Curso *esq;
    int altura;
};

Curso *Busca_cod_curso(Curso *raizCursos, int cod_curso) 
{
    if (raizCursos == NULL || raizCursos->_cod == cod_curso) {
        return raizCursos;
    }

    if (cod_curso < raizCursos->_cod) {
        return Busca_cod_curso(raizCursos->esq, cod_curso);
    } else {
        return Busca_cod_curso(raizCursos->dir, cod_curso);
    }
}

int Cria_cod_unico_curso(Curso *raizCursos) 
{
    int cod_curso = 0;
    srand(time(NULL));
    do
        cod_curso = rand() % 100000;
    while (Busca_cod_curso(raizCursos, cod_curso));

    return (cod_curso);
}

//balanceamento
void Rotacao_esq_curso(Curso **raizCursos) {
    Curso *aux, *filho;

    aux = (*raizCursos)->dir;
    filho = aux->esq;
    aux->esq = *raizCursos;
    (*raizCursos)->dir = filho;
    AtualizaAlturaCurso(raizCursos);
    AtualizaAlturaCurso(&aux);

    *raizCursos = aux; 
}

void Rotacao_dir_curso(Curso **raizCursos) {
    Curso *aux, *filho;

    aux = (*raizCursos)->esq;
    filho = aux->dir;
    aux->dir = *raizCursos;
    (*raizCursos)->esq = filho;
    Atualiza_altura_curso(raizCursos);
    Atualiza_altura_curso(&aux);

    *raizCursos = aux;
}

int Altura_no_curso(Curso *curso) {
    int h;
    if (curso) {
        h = curso->altura;
    }
    else {
        h = -1;
    }
    return (h);
}

int Fb_curso(Curso *curso) {
    if (curso) {
        return (Altura_no_curso(curso->esq) - Altura_no_curso(curso->dir));
    }
    else {
        return 0;
    }
}

void Atualiza_altura_curso(Curso **raizCursos) {
    (*raizCursos)->altura = Calcula_altura_curso(*raizCursos);
}

int Calcula_altura_curso(Curso *raizCursos) {
    int esq, dir, h;

    if (raizCursos == NULL) {
        h = -1;
    }
    else {
        esq = Calcula_altura_curso(raizCursos->esq);
        dir = Calcula_altura_curso(raizCursos->dir);

        if (esq > dir) {
            h = esq + 1;
        }
        else {
            h = dir + 1;
        }
    }

    return (h);
}

void Balanceia_cursos(Curso **raizCursos) {
    int fb;
    fb = Fb_curso(*raizCursos);

    if (fb == -2) {
        if (Fb_curso((*raizCursos)->dir) > 0) 
            Rotacao_dir_curso(&((*raizCursos)->dir));
        Rotacao_esq_curso(raizCursos);
    }else if (fb == 2) {
        if (Fb_curso((*raizCursos)->esq) < 0) 
            Rotacao_esq_curso(&((*raizCursos)->esq));
        Rotacao_dir_curso(raizCursos);
    }
}


void InsereCurso(Curso **raizCursos, Curso *Novo) {
    if ((*raizCursos) == NULL) {
        *raizCursos = Novo;
    }
    else {
        if (Novo->_cod < (*raizCursos)->_cod) 
            InsereCurso(&((*raizCursos)->esq), Novo);
        else 
            InsereCurso(&((*raizCursos)->dir), Novo);
    }

    Balancear_cursos(raizCursos);
    Atualiza_altura_curso(raizCursos);
}



void Cria_curso(Curso **raizCursos,int cod_curso, char *nome_curso, int qtd_blocos, int qtd_semanas) {
    Curso* Novo = (Curso *) malloc(sizeof(Curso));

    Novo->_cod = cod_curso;
    strcpy(Novo->_nome_curso, nome_curso);
    Novo->_qtd_blocos = qtd_blocos;
    Novo->_qtd_seman = qtd_semanas;
    Novo->_arv_disciplinas = NULL;
    Novo->dir = NULL;
    Novo->esq = NULL;
    Novo->altura = 0;

    Insere_curso(&(*raizCursos), Novo);
}



void Cria_arv_cursos(Curso **raizCurso) {
    inserirCurso(&(*raizCurso), Cria_cod_unico_curso(*raizCurso), "Pão", 5, 25);
    inserirCurso(&(*raizCurso), Cria_cod_unico_curso(*raizCurso), "sistemas", 5, 15);
    inserirCurso(&(*raizCurso), Cria_cod_unico_curso(*raizCurso), "biologia", 8, 15);
    inserirCurso(&(*raizCurso), Cria_cod_unico_curso(*raizCurso), "Oraoci", 3, 15);
    inserirCurso(&(*raizCurso), Cria_cod_unico_curso(*raizCurso), "biologia", 4, 15);
}

void Imprime_cursos_crescente(Curso *raizCursos)
{
    if (raizCursos != NULL)
    {
        Imprime_cursos_crescente(raizCursos->esq);
        printf("\n================================\n");
        printf("Codigo do curso: %d\n", raizCursos->_cod);
        printf("Nome do curso: %s\n", raizCursos->_nome_curso);
        printf("Quantidade de blocos: %d\n", raizCursos->_qtd_blocos);
        printf("Quantidade de semanas: %d\n", raizCursos->_qtd_seman);
        printf("\n================================\n");
        Imprime_cursos_crescente(raizCursos->dir);
    }
}

void Imprime_por_cod(Curso *raizCursos, int cod) // como o codigo é unico, não preciso procurar toda a arvore
{
    if(raizCursos != NULL)
    {   Curso *aux;
        aux = Busca_cod_curso(raizCursos, cod);
        if(aux != NULL)
        {   printf("\n================================\n");
            printf("Codigo do curso: %d\n", aux->_cod);
            printf("Nome do curso: %s\n", aux->_nome_curso);
            printf("Quantidade de blocos: %d\n", aux->_qtd_blocos);
            printf("Quantidade de semanas: %d\n", aux->_qtd_seman);
            printf("\n================================\n");
        }
        else printf("Curso não encontrado!\n");
    }
}

void Imprime_cursos_bloco(Curso *raizCursos, int blocos) // como o codigo é unico, não preciso procurar toda a arvore
{
    if(raizCursos != NULL)
    {   
        Imprime_cursos_bloco(raizCursos->esq, blocos);
        if(raizCursos->_qtd_blocos == blocos)
        {
            printf("\n================================\n");
            printf("Codigo do curso: %d\n", raizCursos->_cod);
            printf("Nome do curso: %s\n", raizCursos->_nome_curso);
            printf("Quantidade de blocos: %d\n", raizCursos->_qtd_blocos);
            printf("Quantidade de semanas: %d\n", raizCursos->_qtd_seman);
            printf("\n================================\n");
        }
        Imprime_cursos_bloco(raizCursos->dir, blocos);
    }
}


Disciplina *Busca_cod_disc(Disciplina *raizDisciplinas, int cod)
{   
    if (raizDisciplinas == NULL || raizDisciplinas->_cod == cod)
        return raizDisciplinas;
    if(cod < raizDisciplinas->_cod)
        return Busca_cod_disc(raizDisciplinas->esq, cod);
    else
        return Busca_cod_disc(raizDisciplinas->dir, cod);
}


int Cria_cod_unico_disc(Disciplina *raizDisciplinas) 
{
    int cod_disc = 0;
    do
        cod_disc = rand() % 100000;
    while (Busca_cod_disc(raizDisciplinas, cod_disc));

    return cod_disc;
}

/// 
void Cria_arv_disc(Curso** raizCursos, int cod_curso)
{
    for(int i = 0; i < 10; i++)
    {
        inserirDisciplina(*raizCursos, &((*raizCursos)->_arv_disciplinas), Cria_cod_unico_disc((*raizCursos)->_arv_disciplinas), "Estrutura de Dados II", 4, 60);
    }
}


void Imprimir_disc_em_ordem(Disciplina* raizDisciplinas) {
    if (raizDisciplinas != NULL) {
        Imprimir_disc_em_ordem(raizDisciplinas->esq);
        printf("\nCódigo: %d, Nome: %s, Bloco: %d\n", raizDisciplinas->_cod, raizDisciplinas->_nome_disciplina, raizDisciplinas->_bloco);
        Imprimir_disc_em_ordem(raizDisciplinas->dir);
    }
}

void Imprimir_disc_em_ordem_curso(Curso* raizCursos, int cod_curso) {
    Curso* meu_curso = Busca_cod_curso(raizCursos, cod_curso);

    if (meu_curso != NULL) {
        Disciplina* raizDisciplinas = meu_curso->_arv_disciplinas;

        if (raizDisciplinas != NULL) 
            Imprimir_disc_em_ordem(raizDisciplinas);
        else 
            printf("\nNão há disciplinas cadastradas para o curso %d.\n", cod_curso);
    } else 
        printf("\nO curso com código %d não foi encontrado.\n", cod_curso);
}

void Imprime_dados_disc(Disciplina* minha_disciplina)
{  
    if (minha_disciplina != NULL) {
        printf("\n================================\n");
        printf("Código: %d\n", minha_disciplina->_cod);
        printf("Nome: %s\n", minha_disciplina->_nome_disciplina);
        printf("Carga horária: %d horas\n", minha_disciplina->_carga_horaria);
        printf("Bloco: %d\n", minha_disciplina->_bloco);
        printf("\n================================\n");
    }
}

void Imprimir_disc_por_cod(Curso* raizCursos, int cod_curso, int cod_disc) 
{
    if(raizCursos != NULL)
    {
        Curso* meu_curso = Busca_cod_curso(raizCursos, cod_curso);

        if (meu_curso != NULL) {
            Disciplina* raizDisciplinas = meu_curso->_arv_disciplinas;

            if (raizDisciplinas != NULL) {
                Disciplina* minha_disc = Busca_cod_disc(raizDisciplinas, cod_disc);
                Imprime_dados_disc(minha_disc);
            } else 
                printf("\nNão há disciplinas cadastradas para o curso %d.\n", cod_curso);
        } else 
            printf("\nO curso com código %d não foi encontrado.\n", cod_curso);
    }else
        printf("\nLista de cursos vazia!\n");
}

void Imprime_dados_disc_bloco(Disciplina *minha_disciplina, int bloco)
{   
    if(minha_disciplina != NULL)
    {
        Imprime_dados_disc_bloco(minha_disciplina->esq, bloco);
        if(minha_disciplina->_bloco == bloco)
        {
            printf("\n================================\n");
            printf("Código: %d\n", minha_disciplina->_cod);
            printf("Nome: %s\n", minha_disciplina->_nome_disciplina);
            printf("Carga horária: %d horas\n", minha_disciplina->_carga_horaria);
            printf("Bloco: %d\n", minha_disciplina->_bloco);
            printf("\n================================\n");
        }
        Imprime_dados_disc_bloco(minha_disciplina->dir, bloco);
    }
}

void Imprime_disc_do_bloco(Curso* raizCursos, int cod_curso, int bloco)
{
    if(raizCursos != NULL)
    {
        Curso* meu_curso = Busca_cod_curso(raizCursos, cod_curso);

        if(meu_curso != NULL)
            Imprime_dados_disc_bloco(meu_curso->_arv_disciplinas, bloco);
        else
            printf("\nO curso com código %d não foi encontrado.\n", cod_curso);
    }else
        printf("\nLista de cursos vazia!\n");
}



void Imprime_dados_disc_horas(Disciplina *minha_disciplina, int carga_horaria)
{   
    Imprime_dados_disc_horas(minha_disciplina->esq, carga_horaria);
    if(minha_disciplina->_carga_horaria == carga_horaria)
    {
        printf("\n================================\n");
        printf("Código: %d\n", minha_disciplina->_cod);
        printf("Nome: %s\n", minha_disciplina->_nome_disciplina);
        printf("Carga horária: %d horas\n", minha_disciplina->_carga_horaria);
        printf("Bloco: %d\n", minha_disciplina->_bloco);
        printf("\n================================\n");
    }
        Imprime_dados_disc_horas(minha_disciplina->dir, carga_horaria);   
}

void Imprime_disc_por_horas(Curso* raizCursos, int cod_curso, int carga_horaria)
{
    if(raizCursos != NULL)
    {
        Curso* meu_curso = Busca_cod_curso(raizCursos, cod_curso);

        if(meu_curso != NULL)
            Imprime_dados_disc_horas(meu_curso->_arv_disciplinas, carga_horaria);
        else
            printf("\nO curso com código %d não foi encontrado.\n", cod_curso);
    }else
        printf("\nLista de cursos vazia!\n");
}


Disciplina* encontrarMinimo_disc(Disciplina* raizDisciplinas) {
    if (raizDisciplinas->esq == NULL) {
        return raizDisciplinas;
    }
    return encontrarMinimo_disc(raizDisciplinas->esq);
}

void Excluir_disciplina_Aux(Disciplina** raizDisciplinas, int cod_disciplina)
{   
    //tem que balancear depois
    int excluiu = 0;
    if(*raizDisciplinas != NULL)
    {
        if((*raizDisciplinas)->_cod == cod_disciplina)
        {
            if((*raizDisciplinas)->esq == NULL && (*raizDisciplinas)->dir == NULL)
            {
                free(*raizDisciplinas);
                *raizDisciplinas = NULL;
                excluiu = 1;
            }else if((*raizDisciplinas)->esq == NULL)
            {
                Disciplina* aux = *raizDisciplinas;
                *raizDisciplinas = (*raizDisciplinas)->dir;
                free(aux);
                excluiu = 1;
            }else if((*raizDisciplinas)->dir == NULL)
            {
                Disciplina* aux = *raizDisciplinas;
                *raizDisciplinas = (*raizDisciplinas)->esq;
                free(aux);
                excluiu = 1;
            }else
            {
                Disciplina* aux = encontrarMinimo_disc((*raizDisciplinas)->dir);
                (*raizDisciplinas)->_cod = aux->_cod;
                Excluir_disciplina_Aux(&(*raizDisciplinas)->dir, aux->_cod);
                excluiu = 1;
            }
        }else if((*raizDisciplinas)->_cod > cod_disciplina)
            Excluir_disciplina_Aux(&(*raizDisciplinas)->esq, cod_disciplina);
        else
            Excluir_disciplina_Aux(&(*raizDisciplinas)->dir, cod_disciplina);
    }
    if(excluiu)
    {
        (*raizDisciplinas)->altura = Max(Altura_disciplina((*raizDisciplinas)->esq), Altura_disciplina((*raizDisciplinas)->dir)) + 1;
        int balanco = Fator_bal_disciplina(*raizDisciplinas);
        if(balanco > 1 && Fator_bal_disciplina((*raizDisciplinas)->esq) >= 0)
            Rotacao_dir_disciplina(raizDisciplinas);
        if(balanco > 1 && Fator_bal_disciplina((*raizDisciplinas)->esq) < 0)
        {
            Rotacao_esq_disciplina(&(*raizDisciplinas)->esq);
            Rotacao_dir_disciplina(raizDisciplinas);
        }
        if(balanco < -1 && Fator_bal_disciplina((*raizDisciplinas)->dir) <= 0)
            Rotacao_esq_disciplina(raizDisciplinas);
        if(balanco < -1 && Fator_bal_disciplina((*raizDisciplinas)->dir) > 0)
        {
            Rotacao_dir_disciplina(&(*raizDisciplinas)->dir);
            Rotacao_esq_disciplina(raizDisciplinas);
        }
        
    }
}

void Excluir_disciplina(Curso** raizCursos, int cod_disciplina, int cod_curso)
{
    if(raizCursos != NULL)
    {
        if(*raizCursos != NULL)
        {
            int excluiu = 0;
            Curso* meu_curso = Busca_cod_curso(raizCursos, cod_curso);
            if(meu_curso)
            {
                Disciplina* minha_disciplina = Busca_cod_disc(meu_curso->_arv_disciplinas, cod_disciplina);
                if(minha_disciplina)
                {
                    Excluir_disciplina_Aux(&meu_curso->_arv_disciplinas, cod_disciplina);
                    excluiu = 1;
                }else   
                    printf("\nDisciplina não encontrada!\n");
            }else   
                printf("\nCurso não encontrado!\n");
            if(excluiu)
                printf("\nDisciplina excluída com sucesso!\n");
        }else
            printf("\nLista de cursos vazia!\n");
    }else
        printf("\nLista de cursos vazia!\n");
}


void Excluir_curso_Aux(Curso** raizCursos, int cod_curso)
{   
    //tem que balancear depois
    int excluiu = 0;
    if(*raizCursos != NULL)
    {
        if((*raizCursos)->_cod == cod_curso)
        {
            if((*raizCursos)->esq == NULL && (*raizCursos)->dir == NULL)
            {
                free(*raizCursos);
                *raizCursos = NULL;
                excluiu = 1;
            }else if((*raizCursos)->esq == NULL)
            {
                Curso* aux = *raizCursos;
                *raizCursos = (*raizCursos)->dir;
                free(aux);
                excluiu = 1;
            }else if((*raizCursos)->dir == NULL)
            {
                Curso* aux = *raizCursos;
                *raizCursos = (*raizCursos)->esq;
                free(aux);
                excluiu = 1;
            }else
            {
                Curso* aux = encontrarMinimo_curso((*raizCursos)->dir);
                (*raizCursos)->_cod = aux->_cod;
                Excluir_curso_Aux(&(*raizCursos)->dir, aux->_cod);
                excluiu = 1;
            }
        }else if((*raizCursos)->_cod > cod_curso)
            Excluir_curso_Aux(&(*raizCursos)->esq, cod_curso);
        else
            Excluir_curso_Aux(&(*raizCursos)->dir, cod_curso);
    }
    if(excluiu)
    {
        (*raizCursos)->altura = Max(Altura_curso((*raizCursos)->esq), Altura_curso((*raizCursos)->dir)) + 1;
        int balanco = Fator_bal_curso(*raizCursos);
        if(balanco > 1 && Fator_bal_curso((*raizCursos)->esq) >= 0)
            Rotacao_dir_curso(raizCursos);
        if(balanco > 1 && Fator_bal_curso((*raizCursos)->esq) < 0)
        {
            Rotacao_esq_curso(&(*raizCursos)->esq);
            Rotacao_dir_curso(raizCursos);
        }
        if(balanco < -1 && Fator_bal_curso((*raizCursos)->dir) <= 0)
            Rotacao_esq_curso(raizCursos);
        if(balanco < -1 && Fator_bal_curso((*raizCursos)->dir) > 0)
        {
            Rotacao_dir_curso(&(*raizCursos)->dir);
            Rotacao_esq_curso(raizCursos);
        }

    }
}

void Excluir_curso(Curso** raizCursos, int cod_curso)
{
    if(raizCursos != NULL)
    {
        if(*raizCursos != NULL)
        {
            int excluiu = 0;
            Curso* meu_curso = Busca_cod_curso(raizCursos, cod_curso);
            if(meu_curso)
            {
                Excluir_disciplinas(&meu_curso->_arv_disciplinas);
                Excluir_curso_Aux(raizCursos, cod_curso);
                excluiu = 1;
            }else   
                printf("\nCurso não encontrado!\n");
            if(excluiu)
                printf("\nCurso excluído com sucesso!\n");
        }else
            printf("\nLista de cursos vazia!\n");
    }else
        printf("\nLista de cursos vazia!\n");
}

/*
if(raizCursos != NULL)
    {
        if(*raizDisciplinas != NULL)
        {
            int excluiu = 0;
            Curso* meu_curso = Busca_cod_curso(raizCursos, cod_curso);
            if(meu_curso)
            {
                Disciplina* minha_disciplina = Busca_cod_disc(meu_curso->_arv_disciplinas, cod_disciplina);
                if(minha_disciplina)
                {
                    
            }else   
                printf("\nCurso não encontrado!\n");
        }
    }*/







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
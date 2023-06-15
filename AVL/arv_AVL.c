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

//balanceament
void Rotacao_esq_curso(Curso **raizCursos) {
    Curso *aux, *filho;

    aux = (*raizCursos)->dir;
    filho = aux->esq;
    aux->esq = *raizCursos;
    (*raizCursos)->dir = filho;
    Atualiza_altura_curso(raizCursos);
    Atualiza_altura_curso(&aux);

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
    int alt;
    if (curso) 
        alt = curso->altura;
    else 
        alt = -1;
    return (alt);
}

int Fb_curso(Curso *curso) {
    if (curso)
        return (Altura_no_curso(curso->esq) - Altura_no_curso(curso->dir));
    else 
        return 0;
}

void Atualiza_altura_curso(Curso **raizCursos) {
    (*raizCursos)->altura = Calcula_altura_curso(*raizCursos);
}

int Calcula_altura_curso(Curso *raizCursos) {
    int alt, esq, dir;

    if (raizCursos == NULL) {
        alt = -1;
    }
    else {
        esq = Calcula_altura_curso(raizCursos->esq);
        dir = Calcula_altura_curso(raizCursos->dir);

        if (esq > dir) {
            alt = esq + 1;
        }
        else {
            alt = dir + 1;
        }
    }

    return (alt);
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

    Balanceia_cursos(raizCursos);
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

    InsereCurso(&(*raizCursos), Novo);
}



void Cria_arv_cursos(Curso **raizCurso) {
    Cria_curso(&(*raizCurso), Cria_cod_unico_curso(*raizCurso), "Pão", 5, 25);
    Cria_curso(&(*raizCurso), Cria_cod_unico_curso(*raizCurso), "sistemas", 5, 15);
    Cria_curso(&(*raizCurso), Cria_cod_unico_curso(*raizCurso), "biologia", 8, 15);
    Cria_curso(&(*raizCurso), Cria_cod_unico_curso(*raizCurso), "Oraoci", 3, 15);
    Cria_curso(&(*raizCurso), Cria_cod_unico_curso(*raizCurso), "biologia", 4, 15);
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


int Eh_folha_curso(Curso *raizCursos) {
    int EhFolha = 0;
    if (raizCursos->esq == NULL && raizCursos->dir == NULL) {
        EhFolha = 1;
    }

    return (EhFolha);
}

int Dois_filhos_curso(Curso *raizCursos) {
    int DoisFilhos = 0;
    if (raizCursos->esq != NULL && raizCursos->dir != NULL) {
        DoisFilhos = 1;
    }

    return (DoisFilhos);
}

Curso* Maior_esq_curso(Curso *raizCursos) {
    if (raizCursos->dir != NULL) {
        return Maior_esq_curso(raizCursos->dir);
    }
    else {
        return raizCursos;
    }
}

Curso* Curso_filho(Curso *raizCursos) {
    if (raizCursos->esq != NULL) {
        return (raizCursos->esq);
    }
    else {
        return (raizCursos->dir);
    }
}

void Excluir_curso(Curso **raizCursos, int CodCurso) {
    int removeu = 1;

    if ((*raizCursos) != NULL) {
        Curso *Aux, *Filho;

        if ((*raizCursos)->_cod == CodCurso) {
            if ((*raizCursos)->_arv_disciplinas != NULL) {
                removeu = 0;
                printf("\nO curso possui disciplinas cadastradas!\n");
            }
            else {
                if (Eh_folha_curso(*raizCursos)) {
                    Aux = (*raizCursos);
                    (*raizCursos) = NULL;
                }
                else if (Dois_filhos_curso(*raizCursos)) {
                    Filho = Maior_esq_curso(*raizCursos);
                    Aux = (*raizCursos);
                    Filho->dir = (*raizCursos)->dir;
                    (*raizCursos) = (*raizCursos)->esq;
                }
                else {
                    Filho = Curso_filho(*raizCursos);
                    Aux = (*raizCursos);
                    (*raizCursos) = Filho;
                }
                free(Aux);
                removeu = 0;
                printf("\nCurso removido com sucesso!\n");
            } 
        }
        else if ((*raizCursos)->_cod > CodCurso) {
            Excluir_curso(&((*raizCursos)->esq), CodCurso);
        }
        else {
            Excluir_curso(&((*raizCursos)->dir), CodCurso);    
        }
    }
    
    if (removeu == 0 && (*raizCursos) != NULL) {
        Balanceia_cursos(raizCursos);
        Atualiza_altura_curso(raizCursos);
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


//balanceament
void Rotacao_esq_disciplina(Disciplina **raizDisc) {
    Disciplina *aux, *filho;

    aux = (*raizDisc)->dir;
    filho = aux->esq;
    aux->esq = *raizDisc;
    (*raizDisc)->dir = filho;
    Atualiza_altura_disc(raizDisc);
    Atualiza_altura_disc(&aux);

    *raizDisc = aux; 
}

void Rotacao_dir_disciplina(Disciplina **raizDisc) {
    Disciplina *aux, *filho;

    aux = (*raizDisc)->esq;
    filho = aux->dir;
    aux->dir = *raizDisc;
    (*raizDisc)->esq = filho;
    Atualiza_altura_disc(raizDisc);
    Atualiza_altura_disc(&aux);

    *raizDisc = aux;
}

int Altura_no_disciplina(Disciplina *disciplina) {
    int alt;
    if (disciplina) 
        alt = disciplina->altura;
    else 
        alt = -1;
    return (alt);
}

int Fb_disc(Disciplina *disciplina) {
    if (disciplina)
        return (Altura_no_disciplina(disciplina->esq) - Altura_no_disciplina(disciplina->dir));
    else 
        return 0;
}

void Atualiza_altura_disc(Disciplina **raizDisc) {
    (*raizDisc)->altura = Calcula_altura_disc(*raizDisc);
}

int Calcula_altura_disc(Disciplina *raizDisc) {
    int alt, esq, dir;

    if (raizDisc == NULL) {
        alt = -1;
    }
    else {
        esq = Calcula_altura_disc(raizDisc->esq);
        dir = Calcula_altura_disc(raizDisc->dir);

        if (esq > dir) {
            alt = esq + 1;
        }
        else {
            alt = dir + 1;
        }
    }

    return (alt);
}

void Balanceia_disc(Disciplina **raizDisc) {
    int fb;
    fb = Fb_disc(*raizDisc);

    if (fb == -2) {
        if (Fb_disc((*raizDisc)->dir) > 0) 
            Rotacao_dir_disciplina(&((*raizDisc)->dir));
        Rotacao_esq_disciplina(raizDisc);
    }else if (fb == 2) {
        if (Fb_disc((*raizDisc)->esq) < 0) 
            Rotacao_esq_disciplina(&((*raizDisc)->esq));
        Rotacao_dir_disciplina(raizDisc);
    }
}


void Insere_disc(Disciplina **raizDisc, Disciplina *Novo) {
    if ((*raizDisc) == NULL) {
        *raizDisc = Novo;
    }
    else {
        if (Novo->_cod < (*raizDisc)->_cod) 
            Insere_disc(&((*raizDisc)->esq), Novo);
        else 
            Insere_disc(&((*raizDisc)->dir), Novo);
    }

    Balanceia_disc(raizDisc);
    Atualiza_altura_disc(raizDisc);
}



void Cria_disciplina(int cod_curso, Disciplina **raizDisc, int cod_disc, char *nome, int bloco, int carga_h) {


        Disciplina *Nova = (Disciplina *)malloc(sizeof(Disciplina));

        if (Busca_cod_disc(*raizDisc, cod_disc) != NULL) {
            Nova->_cod = Cria_cod_unico_disc(*raizDisc);
        }
        else Nova->_cod = cod_disc;

        strcpy(Nova->_nome_disciplina, nome);
        Nova->_bloco = bloco;
        Nova->_carga_horaria = carga_h;
        Nova->esq = NULL;
        Nova->dir = NULL;
        Nova->altura = 0;

        Insere_disc(&(*raizDisc), Nova);
        printf("\nDisciplina criada com sucesso!\n");
}


void Cria_arv_disc(Curso** raizCursos, int cod_curso)
{
    Curso *meu_curso = Busca_cod_curso(*raizCursos, cod_curso);
    for(int i = 0; i < 10; i++){
        Cria_disciplina(cod_curso, &(meu_curso->_arv_disciplinas), i + 1, "Estrutura de Dados II", 4, 60);
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
///AQUIIIII

int Eh_folha_disc(Disciplina *raizDisc) {
    int EhFolha = 0;
    if (raizDisc->esq == NULL && raizDisc->dir == NULL) {
        EhFolha = 1;
    }

    return (EhFolha);
}

int Dois_filhos_disc(Disciplina *raizDisc) {
    int DoisFilhos = 0;
    if (raizDisc->esq != NULL && raizDisc->dir != NULL) {
        DoisFilhos = 1;
    }

    return (DoisFilhos);
}

Disciplina* Maior_esq_disc(Disciplina *raizDisc) {
    if (raizDisc->dir != NULL) {
        return Maior_esq_disc(raizDisc->dir);
    }
    else {
        return raizDisc;
    }
}

Disciplina* Disc_filho(Disciplina *raizDisc) {
    if (raizDisc->esq != NULL) {
        return (raizDisc->esq);
    }
    else {
        return (raizDisc->dir);
    }
}

void Excluir_disc_Aux(Disciplina** raizDisc, int CodDisciplina, int *removeu)
{
    if((*raizDisc)->_cod == CodDisciplina)
    {
        Disciplina *Aux, *Filho;
        if (Eh_folha_disc(*raizDisc)) {
            Aux = (*raizDisc);
            (*raizDisc) = NULL;
        }
        else if (Dois_filhos_disc(*raizDisc)) {
            Filho = Maior_esq_disc(*raizDisc);
            Aux = (*raizDisc);
            Filho->dir = (*raizDisc)->dir;
            (*raizDisc) = (*raizDisc)->esq;
        }
        else {
            Filho = Disc_filho(*raizDisc);
            Aux = (*raizDisc);
            (*raizDisc) = Filho;
        }
            free(Aux);
            *removeu = 0;
            printf("\nDisciplina removida com sucesso!\n");
    }else if(CodDisciplina > (*raizDisc)->_cod)
        Excluir_disc_Aux(&((*raizDisc)->dir), CodDisciplina, removeu);
    else
        Excluir_disc_Aux(&((*raizDisc)->esq), CodDisciplina, removeu);
}

void Excluir_disc(Curso **raizCursos, int CodCurso, int CodDisciplina) {
    int removeu = 1;

    if ((*raizCursos) != NULL) {

        if ((*raizCursos)->_cod == CodCurso) {
            if ((*raizCursos)->_arv_disciplinas != NULL)
                Excluir_disc_Aux(&((*raizCursos)->_arv_disciplinas), CodDisciplina, &removeu);
        }
        else if ((*raizCursos)->_cod > CodCurso) 
            Excluir_disc(&((*raizCursos)->esq), CodCurso, CodDisciplina);
        else 
            Excluir_disc(&((*raizCursos)->dir), CodCurso, CodDisciplina);    
    }
    
    if (removeu == 0 && (*raizCursos)->_arv_disciplinas != NULL) {
        Balanceia_disc(&((*raizCursos)->_arv_disciplinas));
        Atualiza_altura_disc(&((*raizCursos)->_arv_disciplinas));
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
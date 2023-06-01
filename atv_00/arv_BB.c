#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arv_BB.h"

#define MULT_NUM_SEM = 15

struct disciplina{
    int _cod; // não pode ser repetido, é o parametro de organização da arv
    char _nome_disciplina[40];
    int _bloco; //deve ser menor que a quatidade de blocos do curso
    int _carga_horaria; //multiplo do numerod e semanas da disciplina
    Disciplina *esq;
    Disciplina *dir;
};

struct curso{
    int _cod;
    char _nome_curso[50];
    int _qtd_blocos;
    int _qtd_seman;
    Disciplina *_arv_disciplinas;
    Curso *dir;
    Curso *esq;
};

Curso *Busca_cod_curso(Curso *raizCursos, int cod) 
{
    if (raizCursos == NULL || raizCursos->_cod == cod) {
        return raizCursos;
    }

    if (cod < raizCursos->_cod) {
        return Busca_cod_curso(raizCursos->esq, cod);
    } else {
        return Busca_cod_curso(raizCursos->dir, cod);
    }
}

int Cria_cod_unico(Curso *raizCursos) 
{
    int cod_curso = 0;
    srand(time(NULL));
    do
        cod_curso = rand() % 10000;
    while (Busca_cod_curso(raizCursos, cod_curso));

    return (cod_curso);
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

void Cria_curso(Curso **raizCursos, char *nome_curso, int qtd_blocos, int qtd_seman)
{
    Curso* Novo = (Curso *) malloc(sizeof(Curso));
    
    Novo->_qtd_blocos = qtd_blocos;
    Novo->_qtd_seman = qtd_seman;
    strcpy(Novo->_nome_curso, nome_curso);
    Novo->_cod = Cria_cod_unico((*raizCursos)); 
    Novo->dir = NULL;
    Novo->esq = NULL;
    Novo->_arv_disciplinas = NULL;
    
    Insere_curso(&(*raizCursos), Novo); 
    
}
//ctrl b
void Cria_arv_cursos(Curso **raizCurso) {

    Cria_curso(&(*raizCurso), "Pão", 5, 25);
    Cria_curso(&(*raizCurso), "sistemas", 5, 15);
    Cria_curso(&(*raizCurso), "biologia", 8, 15);
    Cria_curso(&(*raizCurso), "catarro", 3, 15);
    Cria_curso(&(*raizCurso), "biologia", 4, 15);
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
        printf("\n================================");
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
            printf("\n================================");
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
            printf("\n================================");
        }
        Imprime_cursos_bloco(raizCursos->dir, blocos);
    }
}




Disciplina *Busca_cod_disc(Disciplina *raizDisciplinas, int cod)
{   
    if (raizDisciplinas == NULL || raizDisciplinas->_cod == cod)
        return raizDisciplinas;
    if(cod == raizDisciplinas->_cod)
        return raizDisciplinas;
    else if(cod < raizDisciplinas->_cod)
        Busca_cod_disc(raizDisciplinas->esq, cod);
    else 
        Busca_cod_disc(raizDisciplinas->esq, cod);
}

int Cria_cod_unico_disc(Disciplina *raizDisciplinas) 
{
    int cod_disc = 0;
    srand(time(NULL));
    do
        cod_disc = rand() % 100000;
    while (Busca_cod_disc(raizDisciplinas, cod_disc));

    return cod_disc;
}

void Inserir_disciplina_aux(Disciplina** raizDisciplinas, Disciplina* novaDisciplina)
{

   if (*raizDisciplinas == NULL) {
        *raizDisciplinas = novaDisciplina;
    } else {
        if (novaDisciplina->_cod < (*raizDisciplinas)->_cod) 
            Inserir_disciplina_aux(&((*raizDisciplinas)->esq), novaDisciplina);
        else 
            Inserir_disciplina_aux(&((*raizDisciplinas)->dir), novaDisciplina);
    }
}

void Insere_disc(Curso *meu_curso, Disciplina** raizDisciplinas, char *nome, int bloco, int carga_h)
{
    if(bloco < meu_curso->_qtd_blocos)
    {
        if((carga_h % meu_curso->_qtd_seman) == 0)
        {
            Disciplina *Nova = (Disciplina *)malloc(sizeof(Disciplina));

            Nova->_cod = Cria_cod_unico_disc(*raizDisciplinas);
            strcpy(Nova->_nome_disciplina, nome);
            Nova->_bloco = bloco;
            Nova->_carga_horaria = carga_h;
            Nova->esq = NULL;
            Nova->dir = NULL;

            Inserir_disciplina_aux(raizDisciplinas, Nova);

        }else
            printf("\nA carga horária selecionada não é multipla do numero de semanas do curso!\n");
    }else
        printf("\nNumero de blocos selecionado é maior que a quantidade de blocos do curso!\n");
}

void Cria_arv_disc(Curso** raizCursos, int cod_curso) {
    if (raizCursos != NULL){
        Curso* meu_curso = Busca_cod_curso(*raizCursos, cod_curso);
        if (meu_curso != NULL) {
            Insere_disc(meu_curso, &(meu_curso->_arv_disciplinas), "Estrutura de Dados II", 4, 60);
        }else 
            printf("\ncurso não encontrado!\n");
        
    }
}

void Imprimir_disc_em_ordem(Disciplina* raizDisciplinas) {
    if (raizDisciplinas != NULL) {
        Imprimir_disc_em_ordem(raizDisciplinas->esq);
        printf("Código: %d, Nome: %s\n", raizDisciplinas->_cod, raizDisciplinas->_nome_disciplina);
        Imprimir_disc_em_ordem(raizDisciplinas->dir);
    }
}

void Imprimir_disc_em_ordem_curso(Curso* raizCursos, int cod_curso) {
    Curso* meu_curso = Busca_cod_curso(raizCursos, cod_curso);

    if (meu_curso != NULL) {
        Disciplina* raizDisciplinas = meu_curso->_arv_disciplinas;

        if (raizDisciplinas != NULL) {
            Imprimir_disc_em_ordem(raizDisciplinas);
        } else {
            printf("Não há disciplinas cadastradas para o curso %d.\n", cod_curso);
        }
    } else {
        printf("O curso com código %d não foi encontrado.\n", cod_curso);
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
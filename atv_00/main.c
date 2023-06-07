#include <stdio.h>
#include <stdlib.h>
#include "arv_BB.h"
#include <time.h>


int main() {
    srand(time(NULL));
    int cod_curso = 0,cod_disc = 0, bloco = 0;
    Curso *raizCursos;
    //Disciplina *raizDisciplinas = NULL;
    raizCursos = NULL;

    Cria_arv_cursos(&raizCursos);
    Imprime_cursos_crescente(raizCursos);
    
    printf("Codigo para buscar o curso: ");
    scanf("%d", &cod_curso);
    Imprime_por_cod(raizCursos, cod_curso);

    printf("Bloco para buscar o cursos: ");
    scanf("%d", &bloco);
    Imprime_cursos_bloco(raizCursos, bloco);


    printf("\n\nCodigo do curso que deseja inserir a disciplina: ");
    scanf("%d", &cod_curso);
    Cria_arv_disc(&raizCursos, cod_curso);
    Imprimir_disc_em_ordem_curso(raizCursos, cod_curso);  


    printf("\nDigite o codigo do curso da disciplina que deseja ver as informações: ");
    scanf("%d", &cod_curso);
    printf("\nAgora digite o codigo da disciplina: ");
    scanf("%d", &cod_disc);
    Imprimir_disc_por_cod(raizCursos, cod_curso, cod_disc);


    printf("\nDigite o codigo do curso que deseja ver as disciplinas do bloco: ");
    scanf("%d", &cod_curso);
    printf("\nDigite o bloco que deseja ver as disciplias: ");
    scanf("%d", &bloco);
    Imprime_disc_do_bloco(raizCursos, cod_curso, bloco);
    

    return 0;
}

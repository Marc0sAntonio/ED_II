#include <stdio.h>
#include <stdlib.h>
#include "arv_BB.h"

int main() {
    int cod = 0, bloco = 0;
    Curso *raizCursos;
    //Disciplina *raizDisciplinas = NULL;
    raizCursos = NULL;

    Cria_arv_cursos(&raizCursos);
    Imprime_cursos_crescente(raizCursos);
    
    printf("Codigo para buscar o curso: ");
    scanf("%d", &cod);
    Imprime_por_cod(raizCursos, cod);
    printf("Bloco para buscar o cursos: ");
    scanf("%d", &bloco);
    Imprime_cursos_bloco(raizCursos, bloco);
    
    printf("\n\nCodigo do curso que deseja inserir a disciplina: ");
    scanf("%d", &cod);
    Cria_arv_disc(&(raizCursos), cod);

    //Cria_arv_disc(&(raizCursos), cod);
    //oi
    //imprimirDisciplinas(raizCursos); 
    Imprimir_disc_em_ordem_curso(raizCursos, cod);


    return 0;
}

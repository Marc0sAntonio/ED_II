#include <stdio.h>
#include <stdlib.h>
#include "curso.h"

int main() {
    Curso *raizCurso;
    raizCurso = NULL;

    cria_arv_cursos(&raizCurso);
    Imprime_cursos_crescente(raizCurso);

    return 0;
}

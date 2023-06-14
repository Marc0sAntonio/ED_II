#include <stdio.h>
#include <stdlib.h>
#include "arv_AVL.h"
#include <time.h>

void exibirMenu() {
    printf("\n===== MENU =====\n");
    printf("1. Imprimir todos os cursos em ordem crescente\n");
    printf("2. Buscar curso por código\n");
    printf("3. Imprimir cursos de um bloco\n");
    printf("4. Inserir disciplina em um curso\n");
    printf("5. Imprimir informações de uma disciplina\n");
    printf("6. Imprimir disciplinas de um bloco\n");
    printf("7. Imprimir disciplinas com mesma carga horária\n");
    printf("8. Excluir disciplina de um curso\n");
    printf("9. Excluir um curso\n");
    printf("0. Sair\n");
    printf("================\n");
    printf("Digite sua opção: ");
}

int main() {
    srand(time(NULL));
    int cod_curso = 0, cod_disc = 0, bloco = 0, carga_h = 0;
    Curso *raizCursos;
    raizCursos = NULL;

    Cria_arv_cursos(&raizCursos);

    int opcao = -1;
    while (opcao != 0) {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\n=== Cursos em Ordem Crescente ===\n");
                Imprime_cursos_crescente(raizCursos);
                break;
            case 2:
                printf("\n=== Buscar Curso por Código ===\n");
                printf("Informe o código do curso: ");
                scanf("%d", &cod_curso);
                printf("\nCurso encontrado:\n");
                Imprime_por_cod(raizCursos, cod_curso);
                break;
            case 3:
                printf("\n=== Cursos de um Bloco ===\n");
                printf("Informe o bloco: ");
                scanf("%d", &bloco);
                printf("\nCursos do bloco %d:\n", bloco);
                Imprime_cursos_bloco(raizCursos, bloco);
                break;
            case 4:
                printf("\n=== Inserir Disciplina em um Curso ===\n");
                printf("Informe o código do curso: ");
                scanf("%d", &cod_curso);
                Cria_arv_disc(&raizCursos, cod_curso);
                printf("\nDisciplinas do curso após inserção:\n");
                Imprimir_disc_em_ordem_curso(raizCursos, cod_curso);
                break;
            case 5:
                printf("\n=== Informações de uma Disciplina ===\n");
                printf("Informe o código do curso: ");
                scanf("%d", &cod_curso);
                printf("Informe o código da disciplina: ");
                scanf("%d", &cod_disc);
                printf("\nInformações da disciplina:\n");
                Imprimir_disc_por_cod(raizCursos, cod_curso, cod_disc);
                break;
            case 6:
                printf("\n=== Disciplinas de um Bloco ===\n");
                printf("Informe o código do curso: ");
                scanf("%d", &cod_curso);
                printf("Informe o bloco: ");
                scanf("%d", &bloco);
                printf("\nDisciplinas do bloco %d do curso %d:\n", bloco, cod_curso);
                Imprime_disc_do_bloco(raizCursos, cod_curso, bloco);
                break;
            case 7:
                printf("\n=== Disciplinas com Mesma Carga Horária ===\n");
                printf("Informe o código do curso: ");
                scanf("%d", &cod_curso);
                printf("Informe a carga horária: ");
                scanf("%d", &carga_h);
                printf("\nDisciplinas do curso %d com carga horária %d:\n", cod_curso, carga_h);
                Imprime_disc_por_horas(raizCursos, cod_curso, carga_h);
                break;
            case 8:
                printf("\n=== Excluir Disciplina de um Curso ===\n");
                printf("Informe o código do curso: ");
                scanf("%d", &cod_curso);
                printf("Informe o código da disciplina: ");
                scanf("%d", &cod_disc);
                Excluir_disciplina_por_cod(&raizCursos, cod_curso, cod_disc);
                printf("\nDisciplinas do curso após a remoção:\n");
                Imprimir_disc_em_ordem_curso(raizCursos, cod_curso);
                break;
            case 9:
                printf("\n=== Excluir um Curso ===\n");
                printf("Informe o código do curso: ");
                scanf("%d", &cod_curso);
                Excluir_curso(&raizCursos, cod_curso);
            case 0:
                printf("\nSaindo do programa...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                break;
        }
    }

    return 0;
}

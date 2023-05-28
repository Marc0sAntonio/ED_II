typedef struct curso Curso;

int Busca_cod_curso(Curso *raizCursos, int cod_curso);

int Cria_cod_unico(Curso *raizCursos);

void cria_arv_cursos(Curso **raizCurso);

void Cria_curso(Curso **raizCursos, char *nome_curso, int qtd_blocos, int qtd_seman);

void Insere_curso(Curso** raizCursos, Curso* Novo);

void Imprime_cursos_crescente(Curso *raizCursos);
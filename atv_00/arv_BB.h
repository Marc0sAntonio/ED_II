typedef struct disciplina Disciplina;

typedef struct curso Curso;


/*

int Busca_cod_curso(Curso *raizCursos, int cod_curso); 
*/
Curso *Busca_cod_curso(Curso *raizCursos, int cod);

int Cria_cod_unico_curso(Curso *raizCursos);

void Insere_curso(Curso** raizCursos, Curso* Novo);

void Cria_curso(Curso **raizCursos, char *nome_curso, int qtd_blocos, int qtd_seman);

void Cria_arv_cursos(Curso **raizCurso);

void Imprime_cursos_crescente(Curso *raizCursos);

void Imprime_por_cod(Curso *raizCursos, int cod);

void Imprime_cursos_bloco(Curso *raizCursos, int blocos);


Disciplina *Busca_cod_disc(Disciplina *raizDisciplinas, int cod);

int Cria_cod_unico_disc(Disciplina *raizDisciplinas); 

void Inserir_disciplina_aux(Disciplina** raizDisciplinas, Disciplina* novaDisciplina);

void Insere_disc(Curso *meu_curso, Disciplina** raizDisciplinas, char *nome, int bloco, int carga_h);

void Cria_arv_disc(Curso** raizCursos, int cod_curso);


void Imprimir_disc_em_ordem(Disciplina* raizDisciplinas);

void Imprimir_disc_em_ordem_curso(Curso* raizCursos, int cod_curso);
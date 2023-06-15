typedef struct disciplina Disciplina;

typedef struct curso Curso;

// Curso

Curso *Busca_cod_curso(Curso *raizCursos, int cod);

int Cria_cod_unico_curso(Curso *raizCursos);

void Rotacao_esq_curso(Curso **raizCursos);

void Rotacao_dir_curso(Curso **raizCursos);

int Altura_no_curso(Curso *curso);

int Fb_curso(Curso *curso);

void Atualiza_altura_curso(Curso **raizCursos);

int Calcula_altura_curso(Curso *raizCursos);

void Balanceia_cursos(Curso **raizCursos);

void InsereCurso(Curso **raizCursos, Curso *Novo);

void Cria_curso(Curso **raizCursos,int cod_curso, char *nome_curso, int qtd_blocos, int qtd_semanas);

void Cria_arv_cursos(Curso **raizCurso);

void Imprime_cursos_crescente(Curso *raizCursos);

void Imprime_por_cod(Curso *raizCursos, int cod);

void Imprime_cursos_bloco(Curso *raizCursos, int blocos);

int Eh_folha_curso(Curso *raizCursos);

int Dois_filhos_curso(Curso *raizCursos);

Curso* Maior_esq_curso(Curso *raizCursos);

Curso* Curso_filho(Curso *raizCursos);

void Excluir_curso(Curso **raizCursos, int CodCurso);


// Disciplina

Disciplina *Busca_cod_disc(Disciplina *raizDisciplinas, int cod);

int Cria_cod_unico_disc(Disciplina *raizDisciplinas);

void Rotacao_esq_disciplina(Disciplina **raizDisc);

void Rotacao_dir_disciplina(Disciplina **raizDisc);

int Altura_no_disciplina(Disciplina *disciplina);

int Fb_disc(Disciplina *disciplina);

void Atualiza_altura_disc(Disciplina **raizDisc);

int Calcula_altura_disc(Disciplina *raizDisc);

void Balanceia_disc(Disciplina **raizDisc);

void Insere_disc(Disciplina **raizDisc, Disciplina *Novo);

void Cria_disciplina(int cod_curso, Disciplina **raizDisc, int cod_disc, char *nome, int bloco, int carga_h);

void Cria_arv_disc(Curso** raizCursos, int cod_curso);

void Imprimir_disc_em_ordem(Disciplina* raizDisciplinas);

void Imprimir_disc_em_ordem_curso(Curso* raizCursos, int cod_curso);

void Imprime_dados_disc(Disciplina* minha_disciplina);

void Imprimir_disc_por_cod(Curso* raizCursos, int cod_curso, int cod_disc);

void Imprime_dados_disc_bloco(Disciplina *minha_disciplina, int bloco);

void Imprime_disc_do_bloco(Curso* raizCursos, int cod_curso, int bloco);

void Imprime_dados_disc_horas(Disciplina *minha_disciplina, int carga_horaria);

void Imprime_disc_por_horas(Curso* raizCursos, int cod_curso, int carga_horaria);

int Eh_folha_disc(Disciplina *raizDisc);

int Dois_filhos_disc(Disciplina *raizDisc);

Disciplina* Maior_esq_disc(Disciplina *raizDisc);

Disciplina* Disc_filho(Disciplina *raizDisc);

void Excluir_disc_Aux(Disciplina** raizDisc, int CodDisciplina, int *removeu);

void Excluir_disc(Curso **raizDisc, int CodCurso, int CodDisciplina);
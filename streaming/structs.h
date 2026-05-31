#ifndef STRUCTS_H
#define STRUCTS_H

#define MAX_NOME       100
#define MAX_EMAIL       80
#define MAX_TITULO     100
#define MAX_GENERO      40
#define MAX_URL        150
#define MAX_FAVORITOS   50

/* ─── Registro: Video ─────────────────────────────────────── */
typedef struct {
    int  id;
    char titulo[MAX_TITULO];
    char genero[MAX_GENERO];
    int  ano;
    float duracao_min;
    char url[MAX_URL];
    int  ativo;   /* 0 = removido logicamente (não usado na exclusão por cópia, mas mantido por clareza) */
} Video;

/* ─── Registro: Usuario ───────────────────────────────────── */
typedef struct {
    int  id;
    char nome[MAX_NOME];
    char email[MAX_EMAIL];
    int  favoritos[MAX_FAVORITOS];   /* vetor de IDs de vídeos favoritados */
    int  qtd_favoritos;
    int  ativo;
} Usuario;

#endif /* STRUCTS_H */
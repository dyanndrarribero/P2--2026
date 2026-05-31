#ifndef USUARIOS_H
#define USUARIOS_H

#include "structs.h"

/* ── Escrita ─────────────────────────────────────────────── */
void cadastrar_usuario(void);
void atualizar_usuario(void);

/* ── Leitura ──────────────────────────────────────────────── */
void listar_usuarios(void);
void buscar_usuario_por_id(void);

/* ── Remoção ──────────────────────────────────────────────── */
void remover_usuario(void);

/* ── Favoritos ────────────────────────────────────────────── */
void gerenciar_favoritos(void);

/* ── Relatório ────────────────────────────────────────────── */
void relatorio_usuarios_favoritos(void);

/* ── Auxiliares (usadas internamente e por videos.c) ─────── */
int  proximo_id_usuario(void);
int  buscar_usuario_struct(int id, Usuario *u);

#endif /* USUARIOS_H */
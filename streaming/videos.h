#ifndef VIDEOS_H
#define VIDEOS_H

#include "structs.h"

/* ── Escrita ─────────────────────────────────────────────── */
void cadastrar_video(void);
void atualizar_video(void);

/* ── Leitura ──────────────────────────────────────────────── */
void listar_videos(void);
void buscar_video_por_id(void);

/* ── Remoção ──────────────────────────────────────────────── */
void remover_video(void);

/* ── Auxiliares (usadas internamente e por usuarios.c) ────── */
int  proximo_id_video(void);
int  buscar_video_struct(int id, Video *v);

#endif /* VIDEOS_H */
/*
 * videos.c  –  CRUD completo de Vídeos
 * Parte de: [Colega]
 *
 * Responsabilidades:
 *   - Cadastro, atualização, leitura e remoção de vídeos
 *   - Funções auxiliares usadas por usuarios.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "videos.h"

#define ARQ_VIDEOS     "videos.bin"
#define ARQ_TEMP_V     "videos_temp.bin"

/* ═══════════════════════════════════════════════════════════
 *  AUXILIARES
 * ═══════════════════════════════════════════════════════════ */

int proximo_id_video(void) {
    FILE *fp = fopen(ARQ_VIDEOS, "rb");
    if (!fp) return 1;
    int maior = 0;
    Video v;
    while (fread(&v, sizeof(Video), 1, fp) == 1)
        if (v.id > maior) maior = v.id;
    fclose(fp);
    return maior + 1;
}

int buscar_video_struct(int id, Video *v) {
    FILE *fp = fopen(ARQ_VIDEOS, "rb");
    if (!fp) return 0;
    while (fread(v, sizeof(Video), 1, fp) == 1) {
        if (v->id == id) { fclose(fp); return 1; }
    }
    fclose(fp);
    return 0;
}

static void linha_v(void) {
    printf("─────────────────────────────────────────────────────\n");
}

/* ═══════════════════════════════════════════════════════════
 *  CADASTRO
 * ═══════════════════════════════════════════════════════════ */
void cadastrar_video(void) {
    Video v;
    memset(&v, 0, sizeof(Video));
    v.id    = proximo_id_video();
    v.ativo = 1;

    printf("\n┌─ CADASTRO DE VÍDEO ─────────────────────────────────\n");
    printf("│ Novo ID gerado automaticamente: %d\n", v.id);

    printf("│ Título  : ");
    scanf(" %[^\n]", v.titulo);

    printf("│ Gênero  : ");
    scanf(" %[^\n]", v.genero);

    printf("│ Ano     : ");
    scanf("%d", &v.ano);

    printf("│ Duração (min): ");
    scanf("%f", &v.duracao_min);

    printf("│ URL     : ");
    scanf(" %[^\n]", v.url);

    FILE *fp = fopen(ARQ_VIDEOS, "ab");
    if (!fp) { perror("Erro ao abrir arquivo de vídeos"); return; }
    fwrite(&v, sizeof(Video), 1, fp);
    fclose(fp);

    printf("└ Vídeo #%d cadastrado com sucesso!\n", v.id);
}

/* ═══════════════════════════════════════════════════════════
 *  ATUALIZAÇÃO
 * ═══════════════════════════════════════════════════════════ */
void atualizar_video(void) {
    int id;
    printf("\n┌─ ATUALIZAR VÍDEO ───────────────────────────────────\n");
    printf("│ ID do vídeo a atualizar: ");
    scanf("%d", &id);

    FILE *fp = fopen(ARQ_VIDEOS, "r+b");
    if (!fp) { printf("└ Arquivo de vídeos não encontrado.\n"); return; }

    Video v;
    int encontrado = 0;
    long pos;

    while ((pos = ftell(fp)), fread(&v, sizeof(Video), 1, fp) == 1) {
        if (v.id == id) {
            printf("│ Vídeo encontrado: \"%s\"\n", v.titulo);

            char buf[MAX_TITULO];
            printf("│ Novo título (Enter para manter): ");
            scanf(" %[^\n]", buf);
            if (strlen(buf) > 0) strncpy(v.titulo, buf, MAX_TITULO - 1);

            printf("│ Novo gênero (Enter para manter): ");
            scanf(" %[^\n]", buf);
            if (strlen(buf) > 0) strncpy(v.genero, buf, MAX_GENERO - 1);

            printf("│ Novo ano (0 para manter): ");
            int ano; scanf("%d", &ano);
            if (ano != 0) v.ano = ano;

            printf("│ Nova duração em min (0 para manter): ");
            float dur; scanf("%f", &dur);
            if (dur > 0) v.duracao_min = dur;

            fseek(fp, pos, SEEK_SET);
            fwrite(&v, sizeof(Video), 1, fp);
            encontrado = 1;
            break;
        }
    }
    fclose(fp);

    if (encontrado) printf("└ Vídeo #%d atualizado!\n", id);
    else            printf("└ Vídeo #%d não encontrado.\n", id);
}

/* ═══════════════════════════════════════════════════════════
 *  LISTAR TODOS
 * ═══════════════════════════════════════════════════════════ */
void listar_videos(void) {
    FILE *fp = fopen(ARQ_VIDEOS, "rb");
    if (!fp) { printf("\n Nenhum vídeo cadastrado ainda.\n"); return; }

    printf("\n");
    linha_v();
    printf(" %-5s %-35s %-20s %-6s %s\n",
           "ID", "Título", "Gênero", "Ano", "Duração");
    linha_v();

    Video v;
    int total = 0;
    while (fread(&v, sizeof(Video), 1, fp) == 1) {
        printf(" %-5d %-35s %-20s %-6d %.0f min\n",
               v.id, v.titulo, v.genero, v.ano, v.duracao_min);
        total++;
    }
    fclose(fp);
    linha_v();
    printf(" Total: %d vídeo(s)\n\n", total);
}

/* ═══════════════════════════════════════════════════════════
 *  BUSCAR POR ID
 * ═══════════════════════════════════════════════════════════ */
void buscar_video_por_id(void) {
    int id;
    printf("\n ID do vídeo: ");
    scanf("%d", &id);

    Video v;
    if (!buscar_video_struct(id, &v)) {
        printf(" Vídeo #%d não encontrado.\n", id);
        return;
    }

    printf("\n");
    linha_v();
    printf(" ID      : %d\n", v.id);
    printf(" Título  : %s\n", v.titulo);
    printf(" Gênero  : %s\n", v.genero);
    printf(" Ano     : %d\n", v.ano);
    printf(" Duração : %.0f min\n", v.duracao_min);
    printf(" URL     : %s\n", v.url);
    linha_v();
}

/* ═══════════════════════════════════════════════════════════
 *  REMOÇÃO
 * ═══════════════════════════════════════════════════════════ */
void remover_video(void) {
    int id;
    printf("\n┌─ REMOVER VÍDEO ─────────────────────────────────────\n");
    printf("│ ID do vídeo a remover: ");
    scanf("%d", &id);

    FILE *fp    = fopen(ARQ_VIDEOS,   "rb");
    FILE *ftemp = fopen(ARQ_TEMP_V,   "wb");

    if (!fp || !ftemp) {
        perror("Erro ao abrir arquivos");
        if (fp)    fclose(fp);
        if (ftemp) fclose(ftemp);
        return;
    }

    Video v;
    int encontrado = 0;
    while (fread(&v, sizeof(Video), 1, fp) == 1) {
        if (v.id == id) { encontrado = 1; }
        else            { fwrite(&v, sizeof(Video), 1, ftemp); }
    }

    fclose(fp);
    fclose(ftemp);

    if (!encontrado) {
        remove(ARQ_TEMP_V);
        printf("└ Vídeo #%d não encontrado.\n", id);
        return;
    }

    if (remove(ARQ_VIDEOS) != 0)        { perror("Erro ao remover arquivo antigo"); return; }
    if (rename(ARQ_TEMP_V, ARQ_VIDEOS) != 0) { perror("Erro ao renomear temporário");   return; }

    printf("└ Vídeo #%d removido com sucesso!\n", id);
}
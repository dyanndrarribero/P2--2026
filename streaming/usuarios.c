/*
 * usuarios.c  –  CRUD completo de Usuários
 * Parte de: Dyanndra
 *
 * Responsabilidades:
 *   - Cadastro, atualização, leitura e remoção de usuários
 *   - Gerenciamento do vetor de favoritos (IDs de vídeos)
 *   - Relatório: todos os usuários com nomes dos vídeos favoritados
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "usuarios.h"
#include "videos.h"

#define ARQ_USUARIOS   "usuarios.bin"
#define ARQ_TEMP       "usuarios_temp.bin"

/* ═══════════════════════════════════════════════════════════
 *  AUXILIARES INTERNAS
 * ═══════════════════════════════════════════════════════════ */

/* Retorna o maior ID presente + 1, ou 1 se o arquivo estiver vazio */
int proximo_id_usuario(void) {
    FILE *fp = fopen(ARQ_USUARIOS, "rb");
    if (!fp) return 1;

    int maior = 0;
    Usuario u;
    while (fread(&u, sizeof(Usuario), 1, fp) == 1) {
        if (u.id > maior) maior = u.id;
    }
    fclose(fp);
    return maior + 1;
}

/* Preenche *u com o registro do ID pedido.
   Retorna 1 se encontrou, 0 caso contrário. */
int buscar_usuario_struct(int id, Usuario *u) {
    FILE *fp = fopen(ARQ_USUARIOS, "rb");
    if (!fp) return 0;

    while (fread(u, sizeof(Usuario), 1, fp) == 1) {
        if (u->id == id) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

/* Imprime uma linha de separação decorativa */
static void linha(void) {
    printf("─────────────────────────────────────────────────────\n");
}

/* ═══════════════════════════════════════════════════════════
 *  ESCRITA  –  CADASTRO
 * ═══════════════════════════════════════════════════════════ */
void cadastrar_usuario(void) {
    Usuario u;
    memset(&u, 0, sizeof(Usuario));

    u.id            = proximo_id_usuario();
    u.qtd_favoritos = 0;
    u.ativo         = 1;

    printf("\n┌─ CADASTRO DE USUÁRIO ───────────────────────────────\n");
    printf("│ Novo ID gerado automaticamente: %d\n", u.id);

    printf("│ Nome  : ");
    scanf(" %[^\n]", u.nome);

    printf("│ E-mail: ");
    scanf(" %[^\n]", u.email);

    FILE *fp = fopen(ARQ_USUARIOS, "ab");
    if (!fp) {
        perror("Erro ao abrir arquivo de usuários");
        return;
    }
    fwrite(&u, sizeof(Usuario), 1, fp);
    fclose(fp);

    printf("└ Usuário #%d cadastrado com sucesso!\n", u.id);
}

/* ═══════════════════════════════════════════════════════════
 *  ESCRITA  –  ATUALIZAÇÃO
 * ═══════════════════════════════════════════════════════════ */
void atualizar_usuario(void) {
    int id;
    printf("\n┌─ ATUALIZAR USUÁRIO ─────────────────────────────────\n");
    printf("│ ID do usuário a atualizar: ");
    scanf("%d", &id);

    FILE *fp = fopen(ARQ_USUARIOS, "r+b");
    if (!fp) {
        printf("└ Arquivo de usuários não encontrado.\n");
        return;
    }

    Usuario u;
    int encontrado = 0;
    long pos;

    while ((pos = ftell(fp)), fread(&u, sizeof(Usuario), 1, fp) == 1) {
        if (u.id == id) {
            printf("│ Usuário encontrado: %s <%s>\n", u.nome, u.email);
            printf("│ Novo nome (Enter para manter): ");
            char buf[MAX_NOME];
            scanf(" %[^\n]", buf);
            if (strlen(buf) > 0) strncpy(u.nome, buf, MAX_NOME - 1);

            printf("│ Novo e-mail (Enter para manter): ");
            char buf2[MAX_EMAIL];
            scanf(" %[^\n]", buf2);
            if (strlen(buf2) > 0) strncpy(u.email, buf2, MAX_EMAIL - 1);

            fseek(fp, pos, SEEK_SET);
            fwrite(&u, sizeof(Usuario), 1, fp);
            encontrado = 1;
            break;
        }
    }

    fclose(fp);
    if (encontrado)
        printf("└ Usuário #%d atualizado com sucesso!\n", id);
    else
        printf("└ Usuário #%d não encontrado.\n", id);
}

/* ═══════════════════════════════════════════════════════════
 *  LEITURA  –  LISTAR TODOS
 * ═══════════════════════════════════════════════════════════ */
void listar_usuarios(void) {
    FILE *fp = fopen(ARQ_USUARIOS, "rb");
    if (!fp) {
        printf("\n Nenhum usuário cadastrado ainda.\n");
        return;
    }

    printf("\n");
    linha();
    printf(" %-5s %-30s %-35s %s\n", "ID", "Nome", "E-mail", "Favoritos");
    linha();

    Usuario u;
    int total = 0;
    while (fread(&u, sizeof(Usuario), 1, fp) == 1) {
        printf(" %-5d %-30s %-35s %d vídeo(s)\n",
               u.id, u.nome, u.email, u.qtd_favoritos);
        total++;
    }
    fclose(fp);

    linha();
    printf(" Total: %d usuário(s)\n\n", total);
}

/* ═══════════════════════════════════════════════════════════
 *  LEITURA  –  BUSCAR POR ID
 * ═══════════════════════════════════════════════════════════ */
void buscar_usuario_por_id(void) {
    int id;
    printf("\n ID do usuário: ");
    scanf("%d", &id);

    Usuario u;
    if (!buscar_usuario_struct(id, &u)) {
        printf(" Usuário #%d não encontrado.\n", id);
        return;
    }

    printf("\n");
    linha();
    printf(" ID    : %d\n", u.id);
    printf(" Nome  : %s\n", u.nome);
    printf(" E-mail: %s\n", u.email);
    printf(" Favoritos (%d): ", u.qtd_favoritos);
    for (int i = 0; i < u.qtd_favoritos; i++) {
        printf("%d", u.favoritos[i]);
        if (i < u.qtd_favoritos - 1) printf(", ");
    }
    printf("\n");
    linha();
}

/* ═══════════════════════════════════════════════════════════
 *  REMOÇÃO  –  cria novo arquivo sem o registro excluído
 * ═══════════════════════════════════════════════════════════ */
void remover_usuario(void) {
    int id;
    printf("\n┌─ REMOVER USUÁRIO ───────────────────────────────────\n");
    printf("│ ID do usuário a remover: ");
    scanf("%d", &id);

    FILE *fp    = fopen(ARQ_USUARIOS, "rb");
    FILE *ftemp = fopen(ARQ_TEMP,     "wb");

    if (!fp || !ftemp) {
        perror("Erro ao abrir arquivos");
        if (fp)    fclose(fp);
        if (ftemp) fclose(ftemp);
        return;
    }

    Usuario u;
    int encontrado = 0;

    while (fread(&u, sizeof(Usuario), 1, fp) == 1) {
        if (u.id == id) {
            encontrado = 1;           /* pula – não copia para o novo arquivo */
        } else {
            fwrite(&u, sizeof(Usuario), 1, ftemp);
        }
    }

    fclose(fp);
    fclose(ftemp);

    if (!encontrado) {
        remove(ARQ_TEMP);
        printf("└ Usuário #%d não encontrado.\n", id);
        return;
    }

    /* Substitui o arquivo antigo pelo novo */
    if (remove(ARQ_USUARIOS) != 0) {
        perror("Erro ao remover arquivo antigo");
        return;
    }
    if (rename(ARQ_TEMP, ARQ_USUARIOS) != 0) {
        perror("Erro ao renomear arquivo temporário");
        return;
    }

    printf("└ Usuário #%d removido com sucesso!\n", id);
}

/* ═══════════════════════════════════════════════════════════
 *  FAVORITOS  –  adicionar / remover vídeo da lista
 * ═══════════════════════════════════════════════════════════ */
void gerenciar_favoritos(void) {
    printf("\n┌─ GERENCIAR FAVORITOS ───────────────────────────────\n");
    printf("│ ID do usuário : ");
    int uid; scanf("%d", &uid);

    printf("│ [1] Adicionar favorito  [2] Remover favorito\n│ Opção: ");
    int op; scanf("%d", &op);

    printf("│ ID do vídeo   : ");
    int vid; scanf("%d", &vid);

    /* Verifica se o vídeo existe */
    Video v;
    if (!buscar_video_struct(vid, &v)) {
        printf("└ Vídeo #%d não existe no sistema.\n", vid);
        return;
    }

    FILE *fp = fopen(ARQ_USUARIOS, "r+b");
    if (!fp) {
        printf("└ Arquivo de usuários não encontrado.\n");
        return;
    }

    Usuario u;
    int encontrado = 0;
    long pos;

    while ((pos = ftell(fp)), fread(&u, sizeof(Usuario), 1, fp) == 1) {
        if (u.id == uid) {
            encontrado = 1;

            if (op == 1) {
                /* Adicionar */
                if (u.qtd_favoritos >= MAX_FAVORITOS) {
                    printf("└ Lista de favoritos cheia (máx %d).\n", MAX_FAVORITOS);
                    fclose(fp);
                    return;
                }
                /* Verifica duplicata */
                for (int i = 0; i < u.qtd_favoritos; i++) {
                    if (u.favoritos[i] == vid) {
                        printf("└ Vídeo #%d já está nos favoritos.\n", vid);
                        fclose(fp);
                        return;
                    }
                }
                u.favoritos[u.qtd_favoritos++] = vid;
                printf("│ Vídeo \"%s\" adicionado aos favoritos!\n", v.titulo);

            } else if (op == 2) {
                /* Remover */
                int achou = 0;
                for (int i = 0; i < u.qtd_favoritos; i++) {
                    if (u.favoritos[i] == vid) {
                        /* Desloca os elementos à esquerda */
                        for (int j = i; j < u.qtd_favoritos - 1; j++)
                            u.favoritos[j] = u.favoritos[j + 1];
                        u.qtd_favoritos--;
                        achou = 1;
                        break;
                    }
                }
                if (!achou) {
                    printf("└ Vídeo #%d não está nos favoritos desse usuário.\n", vid);
                    fclose(fp);
                    return;
                }
                printf("│ Vídeo removido dos favoritos.\n");
            }

            fseek(fp, pos, SEEK_SET);
            fwrite(&u, sizeof(Usuario), 1, fp);
            break;
        }
    }

    fclose(fp);

    if (!encontrado)
        printf("└ Usuário #%d não encontrado.\n", uid);
    else
        printf("└ Operação concluída!\n");
}

/* ═══════════════════════════════════════════════════════════
 *  RELATÓRIO  –  usuários com nomes dos vídeos favoritados
 * ═══════════════════════════════════════════════════════════ */
void relatorio_usuarios_favoritos(void) {
    FILE *fp = fopen(ARQ_USUARIOS, "rb");
    if (!fp) {
        printf("\n Nenhum usuário cadastrado.\n");
        return;
    }

    printf("\n");
    printf("╔═════════════════════════════════════════════════════╗\n");
    printf("║     RELATÓRIO: USUÁRIOS E SEUS VÍDEOS FAVORITOS     ║\n");
    printf("╚═════════════════════════════════════════════════════╝\n");

    Usuario u;
    int total_usuarios = 0;

    while (fread(&u, sizeof(Usuario), 1, fp) == 1) {
        total_usuarios++;
        printf("\n  👤 #%d — %s (%s)\n", u.id, u.nome, u.email);

        if (u.qtd_favoritos == 0) {
            printf("      (nenhum vídeo favoritado)\n");
        } else {
            for (int i = 0; i < u.qtd_favoritos; i++) {
                Video v;
                if (buscar_video_struct(u.favoritos[i], &v)) {
                    printf("      ▶ [%d] %s  (%s, %d)  – %.0f min\n",
                           v.id, v.titulo, v.genero, v.ano, v.duracao_min);
                } else {
                    printf("      ▶ [%d] <vídeo removido ou não encontrado>\n",
                           u.favoritos[i]);
                }
            }
        }
        linha();
    }

    fclose(fp);
    printf(" Total de usuários no relatório: %d\n\n", total_usuarios);
}
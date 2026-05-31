/*
 * main.c  –  Menu principal do sistema de streaming
 * Parte de: [Colega]
 */

#include <stdio.h>
#include <stdlib.h>

#include "usuarios.h"
#include "videos.h"

static void limpar_tela(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

static void cabecalho(void) {
    printf("╔═════════════════════════════════════════════════════╗\n");
    printf("║          🎬  SISTEMA DE STREAMING  🎬               ║\n");
    printf("╚═════════════════════════════════════════════════════╝\n\n");
}

static void menu_videos(void) {
    int op;
    do {
        limpar_tela();
        cabecalho();
        printf(" ── MENU VÍDEOS ─────────────────────────────────────\n");
        printf("  1. Cadastrar vídeo\n");
        printf("  2. Atualizar vídeo\n");
        printf("  3. Listar todos os vídeos\n");
        printf("  4. Buscar vídeo por ID\n");
        printf("  5. Remover vídeo\n");
        printf("  0. Voltar\n");
        printf(" ────────────────────────────────────────────────────\n");
        printf("  Opção: ");
        scanf("%d", &op);

        switch (op) {
            case 1: cadastrar_video();       break;
            case 2: atualizar_video();       break;
            case 3: listar_videos();         break;
            case 4: buscar_video_por_id();   break;
            case 5: remover_video();         break;
            case 0: break;
            default: printf(" Opção inválida.\n");
        }

        if (op != 0) {
            printf("\n Pressione Enter para continuar...");
            getchar(); getchar();
        }
    } while (op != 0);
}

static void menu_usuarios(void) {
    int op;
    do {
        limpar_tela();
        cabecalho();
        printf(" ── MENU USUÁRIOS ───────────────────────────────────\n");
        printf("  1. Cadastrar usuário\n");
        printf("  2. Atualizar usuário\n");
        printf("  3. Listar todos os usuários\n");
        printf("  4. Buscar usuário por ID\n");
        printf("  5. Remover usuário\n");
        printf("  6. Gerenciar favoritos\n");
        printf("  0. Voltar\n");
        printf(" ────────────────────────────────────────────────────\n");
        printf("  Opção: ");
        scanf("%d", &op);

        switch (op) {
            case 1: cadastrar_usuario();     break;
            case 2: atualizar_usuario();     break;
            case 3: listar_usuarios();       break;
            case 4: buscar_usuario_por_id(); break;
            case 5: remover_usuario();       break;
            case 6: gerenciar_favoritos();   break;
            case 0: break;
            default: printf(" Opção inválida.\n");
        }

        if (op != 0) {
            printf("\n Pressione Enter para continuar...");
            getchar(); getchar();
        }
    } while (op != 0);
}

static void menu_relatorios(void) {
    int op;
    do {
        limpar_tela();
        cabecalho();
        printf(" ── RELATÓRIOS ──────────────────────────────────────\n");
        printf("  1. Usuários com seus vídeos favoritos\n");
        printf("  2. Todos os vídeos cadastrados\n");
        printf("  0. Voltar\n");
        printf(" ────────────────────────────────────────────────────\n");
        printf("  Opção: ");
        scanf("%d", &op);

        switch (op) {
            case 1: relatorio_usuarios_favoritos(); break;
            case 2: listar_videos();                break;
            case 0: break;
            default: printf(" Opção inválida.\n");
        }

        if (op != 0) {
            printf("\n Pressione Enter para continuar...");
            getchar(); getchar();
        }
    } while (op != 0);
}

int main(void) {
    int op;
    do {
        limpar_tela();
        cabecalho();
        printf(" ── MENU PRINCIPAL ──────────────────────────────────\n");
        printf("  1. Vídeos\n");
        printf("  2. Usuários\n");
        printf("  3. Relatórios\n");
        printf("  0. Sair\n");
        printf(" ────────────────────────────────────────────────────\n");
        printf("  Opção: ");
        scanf("%d", &op);

        switch (op) {
            case 1: menu_videos();     break;
            case 2: menu_usuarios();   break;
            case 3: menu_relatorios(); break;
            case 0: printf("\n Encerrando o sistema. Até logo!\n\n"); break;
            default: printf(" Opção inválida.\n");
                     getchar(); getchar();
        }
    } while (op != 0);

    return 0;
}
// 1 Questão 

#include <stdio.h>
#include <string.h>

struct Produto {
    int id;
    char descricao[20];
    int qtdEstoque;
    float vlrUnit;
};

int buscaSequencialDesc(struct Produto v[], int tam, char x[]) {
    int i;
    for (i = 0; i < tam; i++) {
        if (strcmp(v[i].descricao, x) == 0) {
            return i;
        }
    }
    return -1;
}


// 2 Questão
#include <stdio.h>

struct Venda {
    int id;
    int qtdProdutosVendidos;
    int idsProdutos[5];
    int qtdsVendidas[5];
};

int buscaBinariaId(struct Venda v[], int tam, int x) {
    int ini = 0, fim = tam - 1, meio;
    while (ini <= fim) {
        meio = (ini + fim) / 2;
        if (v[meio].id == x) {
            return meio;
        } else if (v[meio].id < x) {
            ini = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return -1;
}

// 3 Questão
#include <stdio.h>
#include <string.h>

struct Produto {
    int id;
    char descricao[20];
    int qtdEstoque;
    float vlrUnit;
};

int buscaSequencialDesc(struct Produto v[], int tam, char x[]) {
    int i;
    for (i = 0; i < tam; i++) {
        if (strcmp(v[i].descricao, x) == 0) {
            return i;
        }
    }
    return -1;
}

int alteraProduto(struct Produto v[], int tam) {
    char desc[20];
    char resp;
    int pos;

    printf("Digite a descricao do produto: ");
    scanf("%s", desc);

    pos = buscaSequencialDesc(v, tam, desc);
    if (pos == -1) {
        return 0;
    }

    printf("Deseja alterar a descricao? (s/n): ");
    scanf(" %c", &resp);
    if (resp == 's' || resp == 'S') {
        printf("Nova descricao: ");
        scanf("%s", v[pos].descricao);
    }

    printf("Deseja alterar a qtdEstoque? (s/n): ");
    scanf(" %c", &resp);
    if (resp == 's' || resp == 'S') {
        printf("Nova qtdEstoque: ");
        scanf("%d", &v[pos].qtdEstoque);
    }

    printf("Deseja alterar o vlrUnit? (s/n): ");
    scanf(" %c", &resp);
    if (resp == 's' || resp == 'S') {
        printf("Novo vlrUnit: ");
        scanf("%f", &v[pos].vlrUnit);
    }

    return 1;
}

// 4 Questão
#include <stdio.h>
#include <string.h>

struct Produto {
    int id;
    char descricao[20];
    int qtdEstoque;
    float vlrUnit;
};

struct Venda {
    int id;
    int qtdProdutosVendidos;
    int idsProdutos[5];
    int qtdsVendidas[5];
};

int buscaSequencialDesc(struct Produto v[], int tam, char x[]) {
    int i;
    for (i = 0; i < tam; i++) {
        if (strcmp(v[i].descricao, x) == 0) {
            return i;
        }
    }
    return -1;
}

int buscaBinariaId(struct Venda v[], int tam, int x) {
    int ini = 0, fim = tam - 1, meio;
    while (ini <= fim) {
        meio = (ini + fim) / 2;
        if (v[meio].id == x) {
            return meio;
        } else if (v[meio].id < x) {
            ini = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return -1;
}

void venda(struct Produto vp[], int tamProd, struct Venda vv[], int tamVendas) {
    struct Venda novaVenda;
    int i, pos, qtdProd, qtd;
    char desc[20];

    do {
        printf("Digite o id da venda: ");
        scanf("%d", &novaVenda.id);
        if (buscaBinariaId(vv, tamVendas, novaVenda.id) != -1) {
            printf("ID ja cadastrado. Tente novamente.\n");
        }
    } while (buscaBinariaId(vv, tamVendas, novaVenda.id) != -1);

    do {
        printf("Quantidade de produtos diferentes (1-5): ");
        scanf("%d", &qtdProd);
    } while (qtdProd < 1 || qtdProd > 5);

    novaVenda.qtdProdutosVendidos = qtdProd;

    for (i = 0; i < qtdProd; i++) {
        do {
            printf("Descricao do produto %d: ", i + 1);
            scanf("%s", desc);
            pos = buscaSequencialDesc(vp, tamProd, desc);
            if (pos == -1) {
                printf("Produto nao encontrado.\n");
            } else if (vp[pos].qtdEstoque == 0) {
                printf("Produto sem estoque disponivel.\n");
                pos = -1;
            }
        } while (pos == -1);

        novaVenda.idsProdutos[i] = vp[pos].id;

        do {
            printf("Quantidade (1 a %d): ", vp[pos].qtdEstoque);
            scanf("%d", &qtd);
        } while (qtd < 1 || qtd > vp[pos].qtdEstoque);

        novaVenda.qtdsVendidas[i] = qtd;
        vp[pos].qtdEstoque -= qtd;
    }

    vv[tamVendas] = novaVenda;
}

// 5 Questão 
#include <stdio.h>

struct Produto {
    int id;
    char descricao[20];
    int qtdEstoque;
    float vlrUnit;
};

struct Venda {
    int id;
    int qtdProdutosVendidos;
    int idsProdutos[5];
    int qtdsVendidas[5];
};

void relatorio(struct Produto vp[], int tamProd, struct Venda vv[], int tamVendas) {
    int i, j, k, pos;
    float vlrTotal, totalGeral;

    for (i = 0; i < tamVendas; i++) {
        if (vv[i].qtdProdutosVendidos > 2) {
            printf("+-------------------------------------------+\n");
            printf("| V E N D A  N.%03d                          |\n", vv[i].id);
            printf("+-------------------------------------------+\n");
            printf("+QTD| D E S C R I C A O  |VLR UNIT|VLR TOTAL|\n");
            printf("+---+--------------------+--------+---------+\n");

            totalGeral = 0;

            for (j = 0; j < vv[i].qtdProdutosVendidos; j++) {
                pos = -1;
                for (k = 0; k < tamProd; k++) {
                    if (vp[k].id == vv[i].idsProdutos[j]) {
                        pos = k;
                        break;
                    }
                }
                if (pos != -1) {
                    vlrTotal = vp[pos].vlrUnit * vv[i].qtdsVendidas[j];
                    totalGeral += vlrTotal;
                    printf("|%3d|%-20s|%8.2f|%9.2f|\n",
                        vv[i].qtdsVendidas[j],
                        vp[pos].descricao,
                        vp[pos].vlrUnit,
                        vlrTotal);
                }
            }

            for (j = vv[i].qtdProdutosVendidos; j < 5; j++) {
                printf("|   |                    |        |         |\n");
            }

            printf("+---+--------------------+--------+---------+\n");
            printf("|   |Total Geral         |        |%9.2f|\n", totalGeral);
            printf("+---+--------------------+--------+---------+\n\n");
        }
    }
}
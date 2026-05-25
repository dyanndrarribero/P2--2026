#include <stdio.h>
#include <string.h>

#define NUM_ESTADOS 26

typedef struct {
    char nome[50];
    int num_veiculos;
    int num_acidentes;
} Estado;

/* (a) Procedimento para coletar dados de um estado */
void coletarDados(Estado cadastro[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("\n--- Estado %d ---\n", i + 1);
        printf("Nome do estado: ");
        scanf(" %[^\n]", cadastro[i].nome);
        printf("Numero de veiculos (2007): ");
        scanf("%d", &cadastro[i].num_veiculos);
        printf("Numero de acidentes (2007): ");
        scanf("%d", &cadastro[i].num_acidentes);
    }
}

/* (b) Procedimento para encontrar maior e menor numero de acidentes */
void maiorMenorAcidentes(Estado cadastro[], int n, int *indMaior, int *indMenor) {
    int i;
    *indMaior = 0;
    *indMenor = 0;
    for (i = 1; i < n; i++) {
        if (cadastro[i].num_acidentes > cadastro[*indMaior].num_acidentes)
            *indMaior = i;
        if (cadastro[i].num_acidentes < cadastro[*indMenor].num_acidentes)
            *indMenor = i;
    }
}

/* (c) Funcao para calcular percentual de veiculos envolvidos em acidentes */
float percentualAcidentes(Estado cadastro[], int indice) {
    if (cadastro[indice].num_veiculos == 0)
        return 0.0;
    return (float)cadastro[indice].num_acidentes / cadastro[indice].num_veiculos * 100.0;
}

/* (d) Funcao para calcular media de acidentes no pais */
float mediaAcidentes(Estado cadastro[], int n) {
    int i;
    float soma = 0;
    for (i = 0; i < n; i++)
        soma += cadastro[i].num_acidentes;
    return soma / n;
}

/* (e) Procedimento para exibir estados acima da media */
void estadosAcimaMedia(Estado cadastro[], int n, float media) {
    int i;
    printf("\nEstados com numero de acidentes acima da media (%.2f):\n", media);
    for (i = 0; i < n; i++) {
        if (cadastro[i].num_acidentes > media)
            printf("  - %s: %d acidentes\n", cadastro[i].nome, cadastro[i].num_acidentes);
    }
}

int main() {
    Estado cadastro[NUM_ESTADOS];
    int indMaior, indMenor, i;
    float media;

    printf("=== Pesquisa de Acidentes de Transito nos Estados Brasileiros ===\n");

    /* (a) Coleta de dados */
    coletarDados(cadastro, NUM_ESTADOS);

    /* (b) Maior e menor numero de acidentes */
    maiorMenorAcidentes(cadastro, NUM_ESTADOS, &indMaior, &indMenor);
    printf("\n--- Maior e Menor Numero de Acidentes ---\n");
    printf("Maior: %s com %d acidentes\n", cadastro[indMaior].nome, cadastro[indMaior].num_acidentes);
    printf("Menor: %s com %d acidentes\n", cadastro[indMenor].nome, cadastro[indMenor].num_acidentes);

    /* (c) Percentual por estado */
    printf("\n--- Percentual de Veiculos Envolvidos em Acidentes por Estado ---\n");
    for (i = 0; i < NUM_ESTADOS; i++) {
        printf("%-20s: %.4f%%\n", cadastro[i].nome, percentualAcidentes(cadastro, i));
    }

    /* (d) Media nacional */
    media = mediaAcidentes(cadastro, NUM_ESTADOS);
    printf("\n--- Media de Acidentes no Pais ---\n");
    printf("Media: %.2f acidentes\n", media);

    /* (e) Estados acima da media */
    estadosAcimaMedia(cadastro, NUM_ESTADOS, media);

    return 0;
}

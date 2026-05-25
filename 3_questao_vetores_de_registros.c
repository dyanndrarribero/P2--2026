#include <stdio.h>
#include <string.h>

#define MAX_CONTAS 100

typedef struct {
    int num_conta;
    char nome[80];
    char cpf[15];
    char telefone[20];
    float saldo;
} Conta;

typedef struct {
    Conta contas[MAX_CONTAS];
    int total;
} Cadastro;

/* (a) Funcao de busca: retorna posicao, -1 se vazio, -2 se nao encontrado */
int buscarConta(Cadastro *cad, int num_conta) {
    if (cad->total == 0)
        return -1;
    int i;
    for (i = 0; i < cad->total; i++) {
        if (cad->contas[i].num_conta == num_conta)
            return i;
    }
    return -2;
}

/* (b) Procedimento para cadastrar nova conta */
void cadastrarConta(Cadastro *cad, int num_conta) {
    if (cad->total >= MAX_CONTAS) {
        printf("Cadastro cheio! Nao e possivel adicionar mais contas.\n");
        return;
    }

    int pos = buscarConta(cad, num_conta);
    if (pos >= 0) {
        printf("Erro: numero de conta %d ja cadastrado!\n", num_conta);
        return;
    }

    int idx = cad->total;
    cad->contas[idx].num_conta = num_conta;

    printf("Nome do titular: ");
    scanf(" %[^\n]", cad->contas[idx].nome);
    printf("CPF: ");
    scanf(" %[^\n]", cad->contas[idx].cpf);
    printf("Telefone de contato: ");
    scanf(" %[^\n]", cad->contas[idx].telefone);
    cad->contas[idx].saldo = 0.0;

    cad->total++;
    printf("Conta %d cadastrada com sucesso!\n", num_conta);
}

/* (c) Procedimento para consultar saldo */
void consultarSaldo(Cadastro *cad, int num_conta) {
    int pos = buscarConta(cad, num_conta);
    if (pos == -1 || pos == -2) {
        printf("Conta %d nao esta cadastrada.\n", num_conta);
        return;
    }
    printf("Saldo da conta %d (%s): R$ %.2f\n",
           num_conta, cad->contas[pos].nome, cad->contas[pos].saldo);
}

/* (d) Procedimento para deposito */
void depositar(Cadastro *cad, int num_conta) {
    int pos = buscarConta(cad, num_conta);
    if (pos == -1 || pos == -2) {
        printf("Conta %d nao esta cadastrada.\n", num_conta);
        return;
    }
    float valor;
    printf("Valor do deposito: R$ ");
    scanf("%f", &valor);
    if (valor <= 0) {
        printf("Valor invalido.\n");
        return;
    }
    cad->contas[pos].saldo += valor;
    printf("Deposito de R$ %.2f realizado. Novo saldo: R$ %.2f\n",
           valor, cad->contas[pos].saldo);
}

/* (e) Procedimento para saque */
void sacar(Cadastro *cad, int num_conta) {
    int pos = buscarConta(cad, num_conta);
    if (pos == -1 || pos == -2) {
        printf("Conta %d nao esta cadastrada.\n", num_conta);
        return;
    }
    float valor;
    printf("Valor do saque: R$ ");
    scanf("%f", &valor);
    if (valor <= 0) {
        printf("Valor invalido.\n");
        return;
    }
    if (valor > cad->contas[pos].saldo) {
        printf("Saldo insuficiente. Saldo atual: R$ %.2f\n", cad->contas[pos].saldo);
        return;
    }
    cad->contas[pos].saldo -= valor;
    printf("Saque de R$ %.2f realizado. Novo saldo: R$ %.2f\n",
           valor, cad->contas[pos].saldo);
}

/* (f) Procedimento para exibir todas as contas de um cadastro */
void exibirContas(Cadastro *cad, const char *tipo) {
    int i;
    printf("\n--- Contas de %s ---\n", tipo);
    if (cad->total == 0) {
        printf("Nenhuma conta cadastrada.\n");
        return;
    }
    for (i = 0; i < cad->total; i++) {
        printf("Conta: %-6d | Titular: %-30s | Telefone: %s\n",
               cad->contas[i].num_conta,
               cad->contas[i].nome,
               cad->contas[i].telefone);
    }
}

void exibirMenu() {
    printf("\n========= BANCO DINHEIRO CERTO =========\n");
    printf("Escolha o tipo de conta:\n");
    printf("  1 - Conta Corrente\n");
    printf("  2 - Conta Poupanca\n");
    printf("  0 - Sair\n");
    printf("Opcao: ");
}

void exibirMenuOperacao() {
    printf("\n--- Operacoes ---\n");
    printf("  1 - Cadastrar conta\n");
    printf("  2 - Consultar saldo\n");
    printf("  3 - Depositar\n");
    printf("  4 - Sacar\n");
    printf("  5 - Listar todas as contas\n");
    printf("  0 - Voltar\n");
    printf("Opcao: ");
}

int main() {
    Cadastro corrente, poupanca;
    corrente.total = 0;
    poupanca.total = 0;

    int opcaoTipo, opcaoOp, num_conta;
    Cadastro *cad;
    const char *tipoCad;

    do {
        exibirMenu();
        scanf("%d", &opcaoTipo);

        if (opcaoTipo == 0) break;

        if (opcaoTipo == 1) {
            cad = &corrente;
            tipoCad = "Conta Corrente";
        } else if (opcaoTipo == 2) {
            cad = &poupanca;
            tipoCad = "Conta Poupanca";
        } else {
            printf("Opcao invalida.\n");
            continue;
        }

        do {
            exibirMenuOperacao();
            scanf("%d", &opcaoOp);

            switch (opcaoOp) {
                case 1:
                    printf("Numero da nova conta: ");
                    scanf("%d", &num_conta);
                    cadastrarConta(cad, num_conta);
                    break;
                case 2:
                    printf("Numero da conta: ");
                    scanf("%d", &num_conta);
                    consultarSaldo(cad, num_conta);
                    break;
                case 3:
                    printf("Numero da conta: ");
                    scanf("%d", &num_conta);
                    depositar(cad, num_conta);
                    break;
                case 4:
                    printf("Numero da conta: ");
                    scanf("%d", &num_conta);
                    sacar(cad, num_conta);
                    break;
                case 5:
                    exibirContas(cad, tipoCad);
                    break;
                case 0:
                    break;
                default:
                    printf("Opcao invalida.\n");
            }
        } while (opcaoOp != 0);

    } while (opcaoTipo != 0);

    printf("\nSistema encerrado. Obrigado!\n");
    return 0;
}

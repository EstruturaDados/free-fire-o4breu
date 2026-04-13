#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ================================================
   SISTEMA DE INVENTÁRIO + TORRE DE FUGA
   Mochila: Vetor + Lista Encadeada
   Torre  : Bubble Sort | Insertion Sort | Selection Sort
            Busca Binária | Contador de Comparações
   ================================================ */

#define MAX_ITENS  10
#define MAX_COMP   20

/* ================================================
   STRUCTS
   ================================================ */

/* Item da mochila */
typedef struct {
    char nome[30];
    char tipo[20];
    int  quantidade;
} Item;

/* Nó da lista encadeada */
typedef struct No {
    Item      dados;
    struct No *proximo;
} No;

/* Componente da torre de fuga */
typedef struct {
    char nome[30];
    char tipo[20];
    int  prioridade; /* 1 (baixa) a 10 (alta) */
} Componente;

/* ================================================
   VARIÁVEIS GLOBAIS
   ================================================ */

/* --- Mochila --- */
Item mochila[MAX_ITENS];
int  totalVetor = 0;
No  *listaHead  = NULL;
int  totalLista = 0;
int  comparacoes = 0;

/* --- Torre --- */
Componente torre[MAX_COMP];
int  totalComp    = 0;
int  tordeOrdenada = 0; /* Flag: 1 = ordenada por nome (busca binária liberada) */
long compBubble    = 0;
long compInsertion = 0;
long compSelection = 0;
long compBusca     = 0;

/* ================================================
   UTILITÁRIOS
   ================================================ */

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* ================================================
   MOCHILA — VETOR
   ================================================ */

void listarVetor() {
    printf("\n╔══════════════════════════════════════════════════╗\n");
    printf("║      🎒 MOCHILA (VETOR)  %2d/%2d itens             ║\n",
           totalVetor, MAX_ITENS);
    printf("╠════╦══════════════════════════╦════════════╦═════╣\n");
    printf("║ Nº ║ NOME                     ║ TIPO       ║ QTD ║\n");
    printf("╠════╬══════════════════════════╬════════════╬═════╣\n");
    if (totalVetor == 0)
        printf("║              [ Mochila vazia! ]                  ║\n");
    for (int i = 0; i < totalVetor; i++)
        printf("║ %2d ║ %-24s ║ %-10s ║ %3d ║\n",
               i+1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    printf("╚════╩══════════════════════════╩════════════╩═════╝\n\n");
}

void inserirItemVetor() {
    printf("\n[ CADASTRAR ITEM - VETOR ]\n");
    if (totalVetor >= MAX_ITENS) { printf("⚠ Vetor cheio!\n"); return; }

    Item novo;
    printf("Nome      : "); scanf(" %29[^\n]", novo.nome);
    for (int i = 0; i < totalVetor; i++)
        if (strcasecmp(mochila[i].nome, novo.nome) == 0) {
            printf("⚠ Já existe!\n"); return;
        }
    printf("Tipo      : "); scanf(" %19[^\n]", novo.tipo);
    printf("Quantidade: "); scanf("%d", &novo.quantidade);
    if (novo.quantidade <= 0) { printf("⚠ Quantidade inválida!\n"); return; }

    mochila[totalVetor++] = novo;
    printf("✔ '%s' adicionado!\n", novo.nome);
    listarVetor();
}

void removerItemVetor() {
    printf("\n[ REMOVER ITEM - VETOR ]\n");
    if (totalVetor == 0) { printf("⚠ Vetor vazio!\n"); return; }

    char nome[30];
    printf("Nome: "); scanf(" %29[^\n]", nome);

    int pos = -1;
    for (int i = 0; i < totalVetor; i++)
        if (strcasecmp(mochila[i].nome, nome) == 0) { pos = i; break; }

    if (pos == -1) { printf("⚠ Não encontrado.\n"); return; }
    for (int i = pos; i < totalVetor - 1; i++) mochila[i] = mochila[i+1];
    totalVetor--;
    printf("✔ Removido!\n");
    listarVetor();
}

void ordenarVetor() {
    for (int i = 0; i < totalVetor - 1; i++)
        for (int j = 0; j < totalVetor - i - 1; j++)
            if (strcasecmp(mochila[j].nome, mochila[j+1].nome) > 0) {
                Item t = mochila[j]; mochila[j] = mochila[j+1]; mochila[j+1] = t;
            }
    printf("✔ Vetor ordenado por nome!\n");
    listarVetor();
}

void buscarSequencialVetor() {
    printf("\n[ BUSCA SEQUENCIAL - VETOR ]\n");
    if (totalVetor == 0) { printf("⚠ Vazio!\n"); return; }
    char nome[30]; printf("Nome: "); scanf(" %29[^\n]", nome);
    comparacoes = 0;
    for (int i = 0; i < totalVetor; i++) {
        comparacoes++;
        if (strcasecmp(mochila[i].nome, nome) == 0) {
            printf("✔ Encontrado na posição %d | Comparações: %d\n",
                   i+1, comparacoes);
            printf("  Tipo: %s | Qtd: %d\n\n",
                   mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }
    printf("⚠ Não encontrado. Comparações: %d\n", comparacoes);
}

void buscarBinariaVetor() {
    printf("\n[ BUSCA BINÁRIA - VETOR ]\n");
    printf("  ⚠ Ordene antes para resultado correto!\n");
    if (totalVetor == 0) { printf("⚠ Vazio!\n"); return; }
    char nome[30]; printf("Nome: "); scanf(" %29[^\n]", nome);
    comparacoes = 0;
    int ini = 0, fim = totalVetor - 1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2; comparacoes++;
        int cmp = strcasecmp(mochila[meio].nome, nome);
        if (cmp == 0) {
            printf("✔ Encontrado na posição %d | Comparações: %d\n",
                   meio+1, comparacoes);
            printf("  Tipo: %s | Qtd: %d\n\n",
                   mochila[meio].tipo, mochila[meio].quantidade);
            return;
        }
        if (cmp < 0) ini = meio + 1; else fim = meio - 1;
    }
    printf("⚠ Não encontrado. Comparações: %d\n", comparacoes);
}

/* ================================================
   MOCHILA — LISTA ENCADEADA
   ================================================ */

void listarLista() {
    printf("\n╔══════════════════════════════════════════════════╗\n");
    printf("║    🔗 MOCHILA (LISTA ENCADEADA) %2d itens         ║\n", totalLista);
    printf("╠════╦══════════════════════════╦════════════╦═════╣\n");
    printf("║ Nº ║ NOME                     ║ TIPO       ║ QTD ║\n");
    printf("╠════╬══════════════════════════╬════════════╬═════╣\n");
    if (!listaHead) printf("║              [ Lista vazia! ]                    ║\n");
    No *a = listaHead; int n = 1;
    while (a) {
        printf("║ %2d ║ %-24s ║ %-10s ║ %3d ║\n",
               n++, a->dados.nome, a->dados.tipo, a->dados.quantidade);
        a = a->proximo;
    }
    printf("╚════╩══════════════════════════╩════════════╩═════╝\n\n");
}

void inserirItemLista() {
    printf("\n[ CADASTRAR ITEM - LISTA ]\n");
    if (totalLista >= MAX_ITENS) { printf("⚠ Limite atingido!\n"); return; }

    Item novo;
    printf("Nome      : "); scanf(" %29[^\n]", novo.nome);
    No *a = listaHead;
    while (a) {
        if (strcasecmp(a->dados.nome, novo.nome) == 0) {
            printf("⚠ Já existe!\n"); return;
        }
        a = a->proximo;
    }
    printf("Tipo      : "); scanf(" %19[^\n]", novo.tipo);
    printf("Quantidade: "); scanf("%d", &novo.quantidade);
    if (novo.quantidade <= 0) { printf("⚠ Inválido!\n"); return; }

    No *novoNo = (No*)malloc(sizeof(No));
    if (!novoNo) { printf("⚠ Erro de memória!\n"); return; }
    novoNo->dados = novo; novoNo->proximo = NULL;

    if (!listaHead) { listaHead = novoNo; }
    else {
        No *fim = listaHead;
        while (fim->proximo) fim = fim->proximo;
        fim->proximo = novoNo;
    }
    totalLista++;
    printf("✔ '%s' adicionado!\n", novo.nome);
    listarLista();
}

void removerItemLista() {
    printf("\n[ REMOVER ITEM - LISTA ]\n");
    if (!listaHead) { printf("⚠ Lista vazia!\n"); return; }
    char nome[30]; printf("Nome: "); scanf(" %29[^\n]", nome);
    No *at = listaHead, *ant = NULL;
    while (at && strcasecmp(at->dados.nome, nome) != 0) {
        ant = at; at = at->proximo;
    }
    if (!at) { printf("⚠ Não encontrado.\n"); return; }
    if (!ant) listaHead = at->proximo;
    else ant->proximo = at->proximo;
    free(at); totalLista--;
    printf("✔ Removido!\n");
    listarLista();
}

void buscarSequencialLista() {
    printf("\n[ BUSCA SEQUENCIAL - LISTA ]\n");
    if (!listaHead) { printf("⚠ Vazia!\n"); return; }
    char nome[30]; printf("Nome: "); scanf(" %29[^\n]", nome);
    comparacoes = 0; No *a = listaHead; int pos = 1;
    while (a) {
        comparacoes++;
        if (strcasecmp(a->dados.nome, nome) == 0) {
            printf("✔ Encontrado na posição %d | Comparações: %d\n",
                   pos, comparacoes);
            printf("  Tipo: %s | Qtd: %d\n\n",
                   a->dados.tipo, a->dados.quantidade);
            return;
        }
        a = a->proximo; pos++;
    }
    printf("⚠ Não encontrado. Comparações: %d\n", comparacoes);
}

/* ================================================
   TORRE DE FUGA — COMPONENTES
   ================================================ */

void mostrarTorre() {
    printf("\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║       🏗  COMPONENTES DA TORRE  (%2d/%2d)                  ║\n",
           totalComp, MAX_COMP);
    printf("╠════╦══════════════════╦══════════════╦══════════════════╣\n");
    printf("║ Nº ║ NOME             ║ TIPO         ║ PRIORIDADE       ║\n");
    printf("╠════╬══════════════════╬══════════════╬══════════════════╣\n");
    if (totalComp == 0)
        printf("║           [ Nenhum componente cadastrado! ]              ║\n");
    for (int i = 0; i < totalComp; i++) {
        char barra[11] = "          ";
        for (int b = 0; b < torre[i].prioridade && b < 10; b++) barra[b] = '*';
        printf("║ %2d ║ %-16s ║ %-12s ║ %2d [%-10s] ║\n",
               i+1, torre[i].nome, torre[i].tipo, torre[i].prioridade, barra);
    }
    printf("╚════╩══════════════════╩══════════════╩══════════════════╝\n\n");
}

void cadastrarComponente() {
    printf("\n[ CADASTRAR COMPONENTE DA TORRE ]\n");
    if (totalComp >= MAX_COMP) { printf("⚠ Torre cheia!\n"); return; }

    Componente novo;
    printf("Nome        : "); fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    for (int i = 0; i < totalComp; i++)
        if (strcasecmp(torre[i].nome, novo.nome) == 0) {
            printf("⚠ Já cadastrado!\n"); return;
        }

    printf("Tipo        : "); fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Prioridade (1-10): "); scanf("%d", &novo.prioridade); limparBuffer();
    if (novo.prioridade < 1 || novo.prioridade > 10) {
        printf("⚠ Prioridade deve ser entre 1 e 10!\n"); return;
    }

    torre[totalComp++] = novo;
    tordeOrdenada = 0; /* nova inserção invalida ordenação anterior */
    printf("✔ '%s' adicionado à torre!\n", novo.nome);
    mostrarTorre();
}

/* Bubble Sort por nome — exibindo comparações e tempo */
void bubbleSortNome() {
    compBubble = 0;
    clock_t ini = clock();

    for (int i = 0; i < totalComp - 1; i++)
        for (int j = 0; j < totalComp - i - 1; j++) {
            compBubble++;
            if (strcasecmp(torre[j].nome, torre[j+1].nome) > 0) {
                Componente t = torre[j]; torre[j] = torre[j+1]; torre[j+1] = t;
            }
        }

    double ms = (double)(clock() - ini) / CLOCKS_PER_SEC * 1000.0;
    tordeOrdenada = 1; /* ordenado por nome: busca binária liberada */

    printf("\n📊 Bubble Sort por NOME:\n");
    printf("   Comparações : %ld\n", compBubble);
    printf("   Tempo       : %.4f ms\n", ms);
    mostrarTorre();
}

/* Insertion Sort por tipo */
void insertionSortTipo() {
    compInsertion = 0;
    clock_t ini = clock();

    for (int i = 1; i < totalComp; i++) {
        Componente chave = torre[i]; int j = i - 1;
        while (j >= 0 && (compInsertion++, strcasecmp(torre[j].tipo, chave.tipo) > 0)) {
            torre[j+1] = torre[j]; j--;
        }
        torre[j+1] = chave;
    }

    double ms = (double)(clock() - ini) / CLOCKS_PER_SEC * 1000.0;
    tordeOrdenada = 0; /* não ordenado por nome: bloqueia busca binária */

    printf("\n📊 Insertion Sort por TIPO:\n");
    printf("   Comparações : %ld\n", compInsertion);
    printf("   Tempo       : %.4f ms\n", ms);
    mostrarTorre();
}

/* Selection Sort por prioridade */
void selectionSortPrioridade() {
    compSelection = 0;
    clock_t ini = clock();

    for (int i = 0; i < totalComp - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < totalComp; j++) {
            compSelection++;
            if (torre[j].prioridade < torre[minIdx].prioridade) minIdx = j;
        }
        if (minIdx != i) {
            Componente t = torre[i]; torre[i] = torre[minIdx]; torre[minIdx] = t;
        }
    }

    double ms = (double)(clock() - ini) / CLOCKS_PER_SEC * 1000.0;
    tordeOrdenada = 0;

    printf("\n📊 Selection Sort por PRIORIDADE:\n");
    printf("   Comparações : %ld\n", compSelection);
    printf("   Tempo       : %.4f ms\n", ms);
    mostrarTorre();
}

/* Busca binária por nome (exige Bubble Sort aplicado antes) */
void buscaBinariaTorre() {
    printf("\n[ 🔑 BUSCA BINÁRIA - COMPONENTE-CHAVE DA TORRE ]\n");

    if (!tordeOrdenada) {
        printf("⚠ Execute o Bubble Sort por nome antes da busca binária!\n");
        return;
    }
    if (totalComp == 0) { printf("⚠ Torre vazia!\n"); return; }

    char nome[30];
    printf("Nome do componente-chave: "); fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    compBusca = 0;
    int ini = 0, fim = totalComp - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2; compBusca++;
        int cmp = strcasecmp(torre[meio].nome, nome);
        if (cmp == 0) {
            printf("\n🔑 COMPONENTE-CHAVE ENCONTRADO!\n");
            printf("╔══════════════════════════════════════╗\n");
            printf("║ Nome      : %-24s║\n", torre[meio].nome);
            printf("║ Tipo      : %-24s║\n", torre[meio].tipo);
            printf("║ Prioridade: %-24d║\n", torre[meio].prioridade);
            printf("╚══════════════════════════════════════╝\n");
            printf("🔍 Comparações: %ld | Posição: %d\n\n", compBusca, meio+1);
            printf("✅ Torre de fuga DESBLOQUEADA! Missão concluída!\n\n");
            return;
        }
        if (cmp < 0) ini = meio + 1; else fim = meio - 1;
    }
    printf("⚠ Componente-chave '%s' não encontrado. Comparações: %ld\n",
           nome, compBusca);
    printf("🚨 Torre não pode ser ativada sem o componente-chave!\n\n");
}

/* Painel comparativo de desempenho dos algoritmos */
void painelDesempenho() {
    printf("\n╔══════════════════════════════════════════════╗\n");
    printf("║        📊 PAINEL DE DESEMPENHO               ║\n");
    printf("╠══════════════════╦═══════════════╦═══════════╣\n");
    printf("║ Algoritmo        ║ Comparações   ║ Critério  ║\n");
    printf("╠══════════════════╬═══════════════╬═══════════╣\n");
    printf("║ Bubble Sort      ║ %13ld ║ Nome      ║\n", compBubble);
    printf("║ Insertion Sort   ║ %13ld ║ Tipo      ║\n", compInsertion);
    printf("║ Selection Sort   ║ %13ld ║ Prioridade║\n", compSelection);
    printf("║ Busca Binária    ║ %13ld ║ Nome      ║\n", compBusca);
    printf("╚══════════════════╩═══════════════╩═══════════╝\n\n");
}

/* ================================================
   MENUS
   ================================================ */

void menuVetor() {
    int op;
    do {
        printf("\n╔══════════════════════════════╗\n");
        printf("║    📦 MENU - VETOR           ║\n");
        printf("╠══════════════════════════════╣\n");
        printf("║ 1. Inserir item              ║\n");
        printf("║ 2. Remover item              ║\n");
        printf("║ 3. Listar itens              ║\n");
        printf("║ 4. Ordenar (Bubble Sort)     ║\n");
        printf("║ 5. Busca sequencial          ║\n");
        printf("║ 6. Busca binária             ║\n");
        printf("║ 0. Voltar                    ║\n");
        printf("╚══════════════════════════════╝\n");
        printf("Opção: "); scanf("%d", &op); limparBuffer();
        switch (op) {
            case 1: inserirItemVetor();      break;
            case 2: removerItemVetor();      break;
            case 3: listarVetor();           break;
            case 4: ordenarVetor();          break;
            case 5: buscarSequencialVetor(); break;
            case 6: buscarBinariaVetor();    break;
            case 0: break;
            default: printf("⚠ Inválido!\n");
        }
    } while (op != 0);
}

void menuLista() {
    int op;
    do {
        printf("\n╔══════════════════════════════╗\n");
        printf("║  🔗 MENU - LISTA ENCADEADA   ║\n");
        printf("╠══════════════════════════════╣\n");
        printf("║ 1. Inserir item              ║\n");
        printf("║ 2. Remover item              ║\n");
        printf("║ 3. Listar itens              ║\n");
        printf("║ 4. Busca sequencial          ║\n");
        printf("║ 0. Voltar                    ║\n");
        printf("╚══════════════════════════════╝\n");
        printf("Opção: "); scanf("%d", &op); limparBuffer();
        switch (op) {
            case 1: inserirItemLista();      break;
            case 2: removerItemLista();      break;
            case 3: listarLista();           break;
            case 4: buscarSequencialLista(); break;
            case 0: break;
            default: printf("⚠ Inválido!\n");
        }
    } while (op != 0);
}

void menuTorre() {
    int op;
    do {
        printf("\n╔══════════════════════════════════╗\n");
        printf("║  🏗  MENU - TORRE DE FUGA        ║\n");
        printf("╠══════════════════════════════════╣\n");
        printf("║ 1. Cadastrar componente          ║\n");
        printf("║ 2. Listar componentes            ║\n");
        printf("║ 3. Bubble Sort   (por nome)      ║\n");
        printf("║ 4. Insertion Sort (por tipo)     ║\n");
        printf("║ 5. Selection Sort (por prior.)   ║\n");
        printf("║ 6. 🔑 Busca binária (chave)      ║\n");
        printf("║ 7. 📊 Painel de desempenho       ║\n");
        printf("║ 0. Voltar                        ║\n");
        printf("╚══════════════════════════════════╝\n");
        printf("Opção: "); scanf("%d", &op); limparBuffer();
        switch (op) {
            case 1: cadastrarComponente();   break;
            case 2: mostrarTorre();          break;
            case 3: bubbleSortNome();        break;
            case 4: insertionSortTipo();     break;
            case 5: selectionSortPrioridade(); break;
            case 6: buscaBinariaTorre();     break;
            case 7: painelDesempenho();      break;
            case 0: break;
            default: printf("⚠ Inválido!\n");
        }
    } while (op != 0);
}

/* ================================================
   MAIN
   ================================================ */
int main() {
    int op;

    printf("\n══════════════════════════════════════════════\n");
    printf("  🧟 SOBREVIVENTE v3.0 — MISSÃO FINAL\n");
    printf("  Mochila (Vetor + Lista) | Torre de Fuga\n");
    printf("══════════════════════════════════════════════\n");

    do {
        printf("\n╔══════════════════════════════════╗\n");
        printf("║         MENU PRINCIPAL           ║\n");
        printf("╠══════════════════════════════════╣\n");
        printf("║ 1. 📦 Mochila com Vetor          ║\n");
        printf("║ 2. 🔗 Mochila com Lista          ║\n");
        printf("║ 3. 🏗  Torre de Fuga             ║\n");
        printf("║ 0. 🚪 Sair                       ║\n");
        printf("╚══════════════════════════════════╝\n");
        printf("Opção: "); scanf("%d", &op); limparBuffer();

        switch (op) {
            case 1: menuVetor(); break;
            case 2: menuLista(); break;
            case 3: menuTorre(); break;
            case 0: printf("\n🔒 Missão encerrada. Até a próxima!\n\n"); break;
            default: printf("⚠ Inválido!\n");
        }
    } while (op != 0);

    /* Libera memória da lista encadeada */
    No *a = listaHead;
    while (a) { No *t = a; a = a->proximo; free(t); }

    return 0;
}

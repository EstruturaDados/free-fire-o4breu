#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================================================
   SISTEMA DE INVENTÁRIO - MOCHILA DO SOBREVIVENTE
   Implementação paralela: Vetor + Lista Encadeada
   ================================================ */

#define MAX_ITENS 10

/* --- Struct Item: dados do item da mochila --- */
typedef struct {
    char nome[30];
    char tipo[20];
    int  quantidade;
} Item;

/* --- Struct No: nó da lista encadeada --- */
typedef struct No {
    Item     dados;
    struct No *proximo;
} No;

/* ================================================
   VARIÁVEIS GLOBAIS
   ================================================ */
Item mochila[MAX_ITENS]; /* Vetor de itens                  */
int  totalVetor = 0;     /* Contador de itens no vetor      */
No  *listaHead  = NULL;  /* Ponteiro para o início da lista  */
int  totalLista = 0;     /* Contador de itens na lista       */
int  comparacoes = 0;    /* Contador de comparações de busca */

/* ================================================
   FUNÇÕES AUXILIARES
   ================================================ */

/* Limpa o buffer do teclado para evitar leituras erradas */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Pausa e aguarda o jogador pressionar Enter */
void pausar() {
    printf("\nPressione Enter para continuar...");
    limparBuffer();
    getchar();
}

/* ================================================
   OPERAÇÕES COM VETOR (LISTA SEQUENCIAL)
   ================================================ */

/* Lista todos os itens armazenados no vetor */
void listarVetor() {
    printf("\n╔══════════════════════════════════════════════════╗\n");
    printf("║         🎒 MOCHILA (VETOR) - %2d/%2d itens          ║\n",
           totalVetor, MAX_ITENS);
    printf("╚══════════════════════════════════════════════════╝\n");

    if (totalVetor == 0) {
        printf("  [ Mochila vazia! ]\n\n");
        return;
    }

    printf("  %-4s %-28s %-12s %s\n", "Nº", "NOME", "TIPO", "QTD");
    printf("  %-4s %-28s %-12s %s\n", "--", "----", "----", "---");
    for (int i = 0; i < totalVetor; i++) {
        printf("  %-4d %-28s %-12s %d\n",
               i + 1,
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
    printf("\n");
}

/* Insere um novo item no vetor, impedindo duplicatas */
void inserirItemVetor() {
    printf("\n[ CADASTRAR ITEM - VETOR ]\n");

    if (totalVetor >= MAX_ITENS) {
        printf("⚠ Mochila (vetor) cheia!\n");
        return;
    }

    Item novo;
    printf("Nome      : "); scanf(" %29[^\n]", novo.nome);

    /* Verifica duplicata */
    for (int i = 0; i < totalVetor; i++) {
        if (strcasecmp(mochila[i].nome, novo.nome) == 0) {
            printf("⚠ Item '%s' já existe no vetor!\n", novo.nome);
            return;
        }
    }

    printf("Tipo      : "); scanf(" %19[^\n]", novo.tipo);
    printf("Quantidade: "); scanf("%d", &novo.quantidade);

    if (novo.quantidade <= 0) {
        printf("⚠ Quantidade deve ser maior que zero!\n");
        return;
    }

    mochila[totalVetor++] = novo;
    printf("✔ '%s' adicionado ao vetor!\n", novo.nome);
    listarVetor();
}

/* Remove item do vetor pelo nome, deslocando os seguintes */
void removerItemVetor() {
    printf("\n[ REMOVER ITEM - VETOR ]\n");

    if (totalVetor == 0) { printf("⚠ Vetor vazio!\n"); return; }

    char nome[30];
    printf("Nome do item: "); scanf(" %29[^\n]", nome);

    int pos = -1;
    for (int i = 0; i < totalVetor; i++) {
        if (strcasecmp(mochila[i].nome, nome) == 0) { pos = i; break; }
    }

    if (pos == -1) { printf("⚠ Item não encontrado.\n"); return; }

    /* Desloca elementos para preencher o espaço removido */
    for (int i = pos; i < totalVetor - 1; i++)
        mochila[i] = mochila[i + 1];

    totalVetor--;
    printf("✔ '%s' removido do vetor!\n", nome);
    listarVetor();
}

/* Ordena o vetor por nome usando Bubble Sort */
void ordenarVetor() {
    printf("\n[ ORDENANDO VETOR por nome (Bubble Sort)... ]\n");

    for (int i = 0; i < totalVetor - 1; i++) {
        for (int j = 0; j < totalVetor - i - 1; j++) {
            /* Troca se o item atual vem depois do próximo alfabeticamente */
            if (strcasecmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                Item temp      = mochila[j];
                mochila[j]     = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }

    printf("✔ Vetor ordenado!\n");
    listarVetor();
}

/* Busca sequencial no vetor: percorre posição a posição */
void buscarSequencialVetor() {
    printf("\n[ BUSCA SEQUENCIAL - VETOR ]\n");

    if (totalVetor == 0) { printf("⚠ Vetor vazio!\n"); return; }

    char nome[30];
    printf("Nome do item: "); scanf(" %29[^\n]", nome);

    comparacoes = 0;

    for (int i = 0; i < totalVetor; i++) {
        comparacoes++;
        if (strcasecmp(mochila[i].nome, nome) == 0) {
            printf("\n✔ Item encontrado (posição %d):\n", i + 1);
            printf("  Nome      : %s\n", mochila[i].nome);
            printf("  Tipo      : %s\n", mochila[i].tipo);
            printf("  Quantidade: %d\n", mochila[i].quantidade);
            printf("  🔍 Comparações realizadas: %d\n\n", comparacoes);
            return;
        }
    }

    printf("⚠ Item não encontrado. Comparações: %d\n", comparacoes);
}

/* Busca binária no vetor (exige ordenação prévia) */
void buscarBinariaVetor() {
    printf("\n[ BUSCA BINÁRIA - VETOR ]\n");
    printf("  ⚠ Certifique-se de ter ordenado antes!\n");

    if (totalVetor == 0) { printf("⚠ Vetor vazio!\n"); return; }

    char nome[30];
    printf("Nome do item: "); scanf(" %29[^\n]", nome);

    comparacoes = 0;
    int inicio = 0, fim = totalVetor - 1, meio;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        comparacoes++;

        int cmp = strcasecmp(mochila[meio].nome, nome);

        if (cmp == 0) {
            printf("\n✔ Item encontrado (posição %d):\n", meio + 1);
            printf("  Nome      : %s\n", mochila[meio].nome);
            printf("  Tipo      : %s\n", mochila[meio].tipo);
            printf("  Quantidade: %d\n", mochila[meio].quantidade);
            printf("  🔍 Comparações realizadas: %d\n\n", comparacoes);
            return;
        } else if (cmp < 0) {
            inicio = meio + 1; /* Item está na metade direita */
        } else {
            fim = meio - 1;    /* Item está na metade esquerda */
        }
    }

    printf("⚠ Item não encontrado. Comparações: %d\n", comparacoes);
}

/* ================================================
   OPERAÇÕES COM LISTA ENCADEADA
   ================================================ */

/* Lista todos os nós da lista encadeada */
void listarLista() {
    printf("\n╔══════════════════════════════════════════════════╗\n");
    printf("║      🔗 MOCHILA (LISTA ENCADEADA) - %2d itens      ║\n",
           totalLista);
    printf("╚══════════════════════════════════════════════════╝\n");

    if (listaHead == NULL) {
        printf("  [ Lista vazia! ]\n\n");
        return;
    }

    printf("  %-4s %-28s %-12s %s\n", "Nº", "NOME", "TIPO", "QTD");
    printf("  %-4s %-28s %-12s %s\n", "--", "----", "----", "---");

    No *atual = listaHead;
    int num = 1;

    /* Percorre encadeamento até o fim (NULL) */
    while (atual != NULL) {
        printf("  %-4d %-28s %-12s %d\n",
               num++,
               atual->dados.nome,
               atual->dados.tipo,
               atual->dados.quantidade);
        atual = atual->proximo;
    }
    printf("\n");
}

/* Insere novo nó no final da lista encadeada */
void inserirItemLista() {
    printf("\n[ CADASTRAR ITEM - LISTA ENCADEADA ]\n");

    if (totalLista >= MAX_ITENS) {
        printf("⚠ Limite de itens atingido!\n");
        return;
    }

    Item novo;
    printf("Nome      : "); scanf(" %29[^\n]", novo.nome);

    /* Verifica duplicata percorrendo a lista */
    No *atual = listaHead;
    while (atual != NULL) {
        if (strcasecmp(atual->dados.nome, novo.nome) == 0) {
            printf("⚠ Item '%s' já existe na lista!\n", novo.nome);
            return;
        }
        atual = atual->proximo;
    }

    printf("Tipo      : "); scanf(" %19[^\n]", novo.tipo);
    printf("Quantidade: "); scanf("%d", &novo.quantidade);

    if (novo.quantidade <= 0) {
        printf("⚠ Quantidade deve ser maior que zero!\n");
        return;
    }

    /* Aloca novo nó dinamicamente */
    No *novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) { printf("⚠ Erro de memória!\n"); return; }

    novoNo->dados    = novo;
    novoNo->proximo  = NULL;

    /* Insere no final da lista */
    if (listaHead == NULL) {
        listaHead = novoNo;
    } else {
        No *fim = listaHead;
        while (fim->proximo != NULL) fim = fim->proximo;
        fim->proximo = novoNo;
    }

    totalLista++;
    printf("✔ '%s' adicionado à lista!\n", novo.nome);
    listarLista();
}

/* Remove nó da lista pelo nome, ajustando ponteiros */
void removerItemLista() {
    printf("\n[ REMOVER ITEM - LISTA ENCADEADA ]\n");

    if (listaHead == NULL) { printf("⚠ Lista vazia!\n"); return; }

    char nome[30];
    printf("Nome do item: "); scanf(" %29[^\n]", nome);

    No *atual   = listaHead;
    No *anterior = NULL;

    /* Percorre a lista procurando o nó */
    while (atual != NULL && strcasecmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual    = atual->proximo;
    }

    if (atual == NULL) { printf("⚠ Item não encontrado.\n"); return; }

    /* Ajusta ponteiros para "pular" o nó removido */
    if (anterior == NULL)
        listaHead = atual->proximo;   /* Era o primeiro nó */
    else
        anterior->proximo = atual->proximo;

    free(atual); /* Libera a memória alocada */
    totalLista--;
    printf("✔ '%s' removido da lista!\n", nome);
    listarLista();
}

/* Busca sequencial na lista encadeada */
void buscarSequencialLista() {
    printf("\n[ BUSCA SEQUENCIAL - LISTA ENCADEADA ]\n");

    if (listaHead == NULL) { printf("⚠ Lista vazia!\n"); return; }

    char nome[30];
    printf("Nome do item: "); scanf(" %29[^\n]", nome);

    comparacoes = 0;
    No *atual = listaHead;
    int pos = 1;

    while (atual != NULL) {
        comparacoes++;
        if (strcasecmp(atual->dados.nome, nome) == 0) {
            printf("\n✔ Item encontrado (posição %d):\n", pos);
            printf("  Nome      : %s\n", atual->dados.nome);
            printf("  Tipo      : %s\n", atual->dados.tipo);
            printf("  Quantidade: %d\n", atual->dados.quantidade);
            printf("  🔍 Comparações realizadas: %d\n\n", comparacoes);
            return;
        }
        atual = atual->proximo;
        pos++;
    }

    printf("⚠ Item não encontrado. Comparações: %d\n", comparacoes);
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
        printf("Opção: "); scanf("%d", &op);

        switch (op) {
            case 1: inserirItemVetor();       break;
            case 2: removerItemVetor();       break;
            case 3: listarVetor();            break;
            case 4: ordenarVetor();           break;
            case 5: buscarSequencialVetor();  break;
            case 6: buscarBinariaVetor();     break;
            case 0: break;
            default: printf("⚠ Opção inválida!\n");
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
        printf("Opção: "); scanf("%d", &op);

        switch (op) {
            case 1: inserirItemLista();      break;
            case 2: removerItemLista();      break;
            case 3: listarLista();           break;
            case 4: buscarSequencialLista(); break;
            case 0: break;
            default: printf("⚠ Opção inválida!\n");
        }
    } while (op != 0);
}

/* ================================================
   MAIN: Menu principal com escolha de estrutura
   ================================================ */
int main() {
    int op;

    printf("\n══════════════════════════════════════════\n");
    printf("  🧟 INVENTÁRIO DO SOBREVIVENTE v2.0\n");
    printf("  Vetor (sequencial) vs Lista Encadeada\n");
    printf("══════════════════════════════════════════\n");

    do {
        printf("\n╔══════════════════════════════╗\n");
        printf("║      ESCOLHA A ESTRUTURA     ║\n");
        printf("╠══════════════════════════════╣\n");
        printf("║ 1. 📦 Mochila com Vetor      ║\n");
        printf("║ 2. 🔗 Mochila com Lista      ║\n");
        printf("║ 0. 🚪 Sair                   ║\n");
        printf("╚══════════════════════════════╝\n");
        printf("Opção: "); scanf("%d", &op);

        switch (op) {
            case 1: menuVetor(); break;
            case 2: menuLista(); break;
            case 0: printf("\n🔒 Até a próxima, sobrevivente!\n\n"); break;
            default: printf("⚠ Opção inválida!\n");
        }
    } while (op != 0);

    /* Libera todos os nós da lista antes de encerrar */
    No *atual = listaHead;
    while (atual != NULL) {
        No *temp = atual;
        atual = atual->proximo;
        free(temp);
    }

    return 0;
}

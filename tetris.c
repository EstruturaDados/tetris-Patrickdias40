#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define stng 30
#define MAX 5

typedef struct {
    char peca[stng];
    int id;
}Peca;

typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
}filaTetris;

int filaCheia(filaTetris *f) {
    return  f->total == MAX;
}
int filaVazia(filaTetris *f) {
    return  f->total == 0;
}

void limpar() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void removeEnter(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

void menu(filaTetris *f, int opcao);
void inicializaFila(filaTetris *f);
void inserePeca(filaTetris *f, Peca p);
void removePeca(filaTetris *f, Peca *p);
void visualizar(filaTetris *f);
void gerarPecas(filaTetris *f);


int main() {
    int opcao;
    filaTetris f;
    inicializaFila(&f);

    do {
        printf("\n=== MENU ===\n");
        printf("1 para gerar as pecas\n");
        printf("2 para alterar uma peca:\n");
        printf("3 para Visualizar as pecas:\n");
        printf("4 para fechar o programa:\n");

        printf("\nEscolha:");
        scanf("%d", &opcao);
        limpar();

        menu(&f, opcao);
    } while (opcao < 4);

    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha


    return 0;
}

void menu(filaTetris *f, int opcao) {
    switch (opcao) {
        case 1:
            gerarPecas(f);
            break;
        
        case 2:
            Peca removida;
            removePeca(f, &removida);
            printf("Peça removida: %s (ID %d)\n", removida.peca, removida.id);
            break;

        case 3:
            visualizar(f);
            break;

        case 4:
            printf("\n-----Fechando Programa-----\n");
            break;

        default:
            printf("\n-- ERRO: Opcao Invalida --\n");
            break;
        }
}

void inicializaFila(filaTetris *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total= 0;
}

void inserePeca(filaTetris *f, Peca p) {
    if(filaCheia(f)) {
        printf("Lista Cheia, Nao é possivel inserir mais pecas!!");
        return;
    }
    
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

void removePeca(filaTetris *f, Peca *p) {
    if(filaVazia(f)) {
        printf("Lista Vazia, Nao é possivel remover mais pecas!!");
        return;
    }
    
    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
    //para nao deixar a lista faltando, quando excluir uma ja cria outra
    gerarPecas(f);
}

void visualizar(filaTetris *f) {
    if(filaVazia(f)) {
        printf("Lista Vazia, Nao é possivel visualizar!!");
        return;
    }
    printf("\n----- Fila -----\n");
    for(int i = 0, idx = f->inicio; i< f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%s, %d]", f->itens[idx].peca, f->itens[idx].id);
    }
}

void gerarPecas(filaTetris *f) {
    static int contadorID = 1;

    while (!filaCheia(f)) {
        Peca pecaNova;

        printf("Digite o nome da peça: ");
        fgets(pecaNova.peca, stng, stdin);
        removeEnter(pecaNova.peca);

        pecaNova.id = contadorID++;
        inserePeca(f, pecaNova);
    }

    printf("Fila completa!\n");
}
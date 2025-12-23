#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define stng 30
#define MAX 5
#define Pilha 3

//fila que define as pecas que o usuraio possui
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

//pilha que define as pecas reservas do usuario possui
typedef struct {
    char pecaRes[stng];
    int id;
} PecaRes;
typedef struct {
    PecaRes itens[Pilha];
    int topo;
} PilhaRes;

//Funcoes expecificas da fila que define as pecas que o usuraio possui
int filaCheia(filaTetris *f) {
    return  f->total == MAX;
}
int filaVazia(filaTetris *f) {
    return  f->total == 0;
}

//Funcoes expecificas da pilha que define as pecas reservas do usuario possui
void inicializaPilha(PilhaRes *p) {
    p->topo = -1;
}
int pilhaVazia(PilhaRes *p) {
    return p->topo == -1;
}
int pilhaCheia(PilhaRes *p) {
    return p->topo == Pilha - 1;
}

void limpar() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void removeEnter(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

void menu(PilhaRes *p, filaTetris *f, int opcao);

//Funcoes expecificas da fila que define as pecas que o usuraio possui
void inicializaFila(filaTetris *f);
void inserePeca(filaTetris *f, Peca p);
void removePeca(filaTetris *f);
void visualizar(filaTetris *f);
void gerarPecas(filaTetris *f);

//Funcoes expecificas da pilha que define as pecas reservas do usuario possui
void alterarPeca(PilhaRes *p, filaTetris *f);
void adcPecaRes(PilhaRes *p, PecaRes Nova);
void rmvPecaRes(PilhaRes *p, PecaRes *remover);
void visualizarPecasRes(PilhaRes *p);

int main() {
    int opcao;
    filaTetris f;
    PilhaRes p;
    inicializaFila(&f);
    inicializaPilha(&p);

    do {
        printf("\n=== MENU ===\n");
        printf("1 para gerar as pecas na lista\n");
        printf("2 para alterar uma peca:\n");
        printf("3 para Visualizar as pecas:\n");
        printf("4 para adicionar uma peca reserva na fila:\n");
        printf("5 para visualizar as pecas reservas:\n");
        printf("6 para remover uma peca reserva:\n");
        printf("7 para fechar o programa:\n");

        printf("\nEscolha:");
        scanf("%d", &opcao);
        limpar();

        menu(&p, &f, opcao);
    } while (opcao < 7);


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

void menu(PilhaRes *p, filaTetris *f, int opcao) {
    switch (opcao) {
        case 1:
            gerarPecas(f);
            break;
        
        case 2:
            removePeca(f);
            break;

        case 3:
            visualizar(f);
            break;

        case 4:
            alterarPeca(p, f);
            break;

        case 5:
            visualizarPecasRes(p);
            break;

        case 6:
            PecaRes remover;
            rmvPecaRes(p, &remover);
            break;

        case 7:
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
        printf("\nLista Cheia, Nao é possivel inserir mais pecas\n!!");
        return;
    }
    
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}
void removePeca(filaTetris *f) {
    Peca removida;
    if(filaVazia(f)) {
        printf("\nLista Vazia, Nao é possivel remover mais pecas\n!!");
        return;
    }
    
    removida  = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
    printf("Peça removida: %s (ID %d)\n", removida.peca, removida.id);
    //para nao deixar a lista faltando, quando excluir uma em sequencia cria outra
    gerarPecas(f);
}
void visualizar(filaTetris *f) {
    if(filaVazia(f)) {
        printf("\nLista Vazia, Nao é possivel visualizar!!\n");
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

void adcPecaRes(PilhaRes *p, PecaRes Nova) {
    if (pilhaCheia(p)) {
        printf("\nPilha cheia, nao é possivel adici onar pecas reservas!!\n");
        return;
    }
    p->topo++;
    p->itens[p->topo] = Nova;
}
void alterarPeca(PilhaRes *p, filaTetris *f) {
    PecaRes Alterar;
    static int contadorIdPilha = 1;
    if(filaVazia(f)) {
        printf("\nLista Vazia, Nao é possivel remover mais pecas!!\n");
        return;
    }
    printf("\nIra guardar a primeira peca\n");
    strcpy(Alterar.pecaRes, f->itens[f->inicio].peca);

    //Defini o id da pecaRes e incrementa
    Alterar.id = contadorIdPilha++;
    adcPecaRes(p, Alterar);
    removePeca(f);
}
void rmvPecaRes(PilhaRes *p, PecaRes *remover) {
    if(pilhaVazia(p)) {
        printf("\nPilha vazia, nao existe pecas reservas para remover!!\n");
        return;
    }
    *remover = p->itens[p->topo];
    printf("\nPeca Utilizada:\n");
    printf("[%d, %s]\n", remover->id, remover->pecaRes);
    p->topo--;
}
void visualizarPecasRes(PilhaRes *p) {
    if(pilhaVazia(p)){
        printf("\nPilha vazia, nao existe pecas reservas para visualizar!!\n");
        return;
    }
    printf("\nPilha PECAS RESERVAS(topo -> base):\n");

    for(int i = p->topo; i >= 0; i--) {
        printf("[%d, %s]\n", p->itens[i].id, p->itens[i].pecaRes);
    }
}
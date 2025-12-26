#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define stng 30
#define MAX 5
#define Pilha 3

static int contadorIDfila = 1;

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

//------ Fila ------
void inicializaFila(filaTetris *f);
void gerarPecas(filaTetris *f);
void inserePeca(filaTetris *f, Peca p);
void visualizar(filaTetris *f);
Peca rmutilizarPeca(filaTetris *f);


//------ Pilha ------
void inicializaPilha(PilhaRes *p);
void adcPecaRes(PilhaRes *p, PecaRes Nova);
void visualizarPecasRes(PilhaRes *p);
PecaRes rmPecaRes(PilhaRes *p);
PecaRes rmutilizarPecaRes(PilhaRes *p);

//Funcoes para troca de itens entre a fila e pilha
void alterarPRes(PilhaRes *p, filaTetris *f);
void alterarPFilaExIn(PilhaRes *p, filaTetris *f);
void alterarPFilaTroca(PilhaRes *p, filaTetris *f);

int main() {
    int opcao;
    filaTetris f;
    PilhaRes p;
    inicializaFila(&f);
    inicializaPilha(&p);

    printf("---- JOGO INICIALIZADO ----");
    gerarPecas(&f);

    do {
        printf("\n=== MENU ===\n");
        printf("1 - para gerar as pecas na lista\n");
        printf("2 - para utilizar uma peca:\n");
        printf("3 - para Visualizar as pecas:\n");
        printf("4 - para adicionar uma peca reserva na fila:\n");
        printf("5 - para trocar as pecas reserva para a fila:\n");
        printf("6 - para visualizar as pecas reservas:\n");
        printf("7 - para remover uma peca reserva:\n");
        printf("8 - para guardar peca em reserva:\n");
        printf("9 - para visualizar todas as pecas:\n");
        printf("10 - para fechar o programa:\n");

        printf("\nEscolha:");
        scanf("%d", &opcao);
        limpar();

        menu(&p, &f, opcao);
    } while (opcao < 10);


    return 0;
}

void menu(PilhaRes *p, filaTetris *f, int opcao) {
    switch (opcao) {
        case 1:
            gerarPecas(f);
            break;
        
        case 2:
            rmutilizarPeca(f);
            gerarPecas(f);
            break;

        case 3:
            visualizar(f);
            break;

        case 4:
            alterarPFilaExIn(p, f);
            gerarPecas(f);
            break;
        
        case 5:
            alterarPFilaTroca(p, f);
            break;
            
        case 6:
            visualizarPecasRes(p);
            break;

        case 7:
            rmutilizarPecaRes(p);
            break;

        case 8:
            alterarPRes(p, f);
            break;

        case 9:
            visualizar(f);
            visualizarPecasRes(p);
            break;

        case 10:
            printf("\n-----Fechando Programa-----\n");
            break;

        default:
            printf("\n-- ERRO: Opcao Invalida --\n");
            break;
        }
}

//------ Fila ------
void inicializaFila(filaTetris *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total= 0;
}
void gerarPecas(filaTetris *f) {
    printf("\n------- Gerando pecas novas -------\n");
    while (!filaCheia(f)) {
        Peca pecaNova;

        printf("Digite o nome da peça: ");
        fgets(pecaNova.peca, stng, stdin);
        removeEnter(pecaNova.peca);

        pecaNova.id = contadorIDfila++;
        inserePeca(f, pecaNova);
    }

    printf("\nFila completa - Pecas geradas!\n");
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
//Remove peca da lista(como se fosse utiliza de fato)
Peca rmutilizarPeca(filaTetris *f) {
    Peca removida = {0};
    if(filaVazia(f)) {
        printf("\nLista Vazia, Nao é possivel remover mais pecas!!\n");
        return removida;
    }
    
    removida  = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
    printf("Peça removida: %s (ID %d)\n", removida.peca, removida.id);
    return removida;
}

//------ Pilha ------
void inicializaPilha(PilhaRes *p) {
    p->topo = -1;
}
void adcPecaRes(PilhaRes *p, PecaRes Nova) {
    if (pilhaCheia(p)) {
        printf("\nPilha cheia, nao é possivel adici onar pecas reservas!!\n");
        return;
    }
    p->topo++;
    p->itens[p->topo] = Nova;
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
PecaRes rmPecaRes(PilhaRes *p) {
    PecaRes rehabilitaPeca = {0};
    if(pilhaVazia(p)) {
        printf("\nPilha Vazia, Nao é possivel executar a acao!!\n");
        return rehabilitaPeca;
    }
    
    rehabilitaPeca = p->itens[p->topo];
    p->topo--;
    
    return rehabilitaPeca;
}
//Remove peca da lista(como se fosse utiliza de fato)
PecaRes rmutilizarPecaRes(PilhaRes *p) {
    PecaRes removida = {0};
    if(pilhaVazia(p)) {
        printf("\nPilha Vazia, Nao é possivel remover pecas!!\n");
        return removida;
    }
    
    removida  = p->itens[p->topo];
    p->topo--;
    printf("Peça removida: %s (ID %d)\n", removida.pecaRes, removida.id);
    return removida;
}

//----Funcoes para troca de itens entre a fila e pilha --------
void alterarPRes(PilhaRes *p, filaTetris *f) {
    static int contadorIdPilha = 1;
    if(filaVazia(f)) {
        printf("\nLista Vazia, Nao é possivel remover mais pecas!!\n");
        return;
    }
    if(pilhaCheia(p)) {
        printf("\nPilha Reserva esta cheia nao é possivel adicionar mais pecas!!\n");
        return;
    }
    printf("\nIra guardar a primeira peca\n");
 
    Peca pecaExtraida = rmutilizarPeca(f);

    PecaRes novaRes;
    novaRes.id = contadorIdPilha++;
    strcpy(novaRes.pecaRes, pecaExtraida.peca);

    adcPecaRes(p, novaRes);

    printf("\nA peca [%s] foi movida para a reserva (ID Reserva: %d)\n", pecaExtraida.peca, novaRes.id);
}
//funcao que tira da pilha e insere na fila(Minha Logica faz mais sentido)
void alterarPFilaExIn(PilhaRes *p, filaTetris *f) {
    if(filaVazia(f)) {
        printf("\nLista Vazia, Nao é possivel executar acao!!\n");
        return;
    }
    if(pilhaVazia(p)) {
        printf("\nPilha Reserva esta vazia nao é possivel executar a acao\n");
        return;
    }

    while (p->topo >= 0 && !filaCheia(f)) {
        printf("\nIra voltar as pecas para a pilha:\n");
    
        PecaRes pecaResExtraida = rmPecaRes(p);
        
        Peca novaPeca;
        novaPeca.id = contadorIDfila++;
        strcpy(novaPeca.peca, pecaResExtraida.pecaRes);

        inserePeca(f, novaPeca);

        printf("\nA peca [%s] foi movida para a fila (ID: %d)\n", pecaResExtraida.pecaRes, novaPeca.id);
    }
}

void alterarPFilaTroca(PilhaRes *p, filaTetris *f) {

    if (f->total < 3) {
        printf("\nFila precisa de pelo menos 3 peças.\n");
        return;
    }
    if (pilhaVazia(p)) {
        printf("\nPilha Vazia, nao e possivel executar acao.\n");
        return;
    }

    int qtdPilha = p->topo + 1;
    int qtdFila  = f->total;

    int qtdTroca = qtdPilha;
    if (qtdTroca > qtdFila) {
        printf("Erro:");
        return;
    }

    for (int i = 0; i < qtdTroca; i++) {
        int idxFila = (f->inicio + i) % MAX;

        char temp[stng];
        strcpy(temp, f->itens[idxFila].peca);

        strcpy(f->itens[idxFila].peca, p->itens[p->topo - i].pecaRes);
        strcpy(p->itens[p->topo - i].pecaRes, temp);
    }
    printf("\nPecas trocada com sucesso para a fila\n");
}
#include <stdio.h>

#define TAM 5   // tamanho da fila circular

// ---------------------------
//  STRUCT DA PEÇA
// ---------------------------
typedef struct {
    char tipo;
    int id;
} Peca;


// ---------------------------
//  VARIÁVEIS DA FILA
// ---------------------------
Peca fila[TAM];
int frente = 0;
int tras = 0;
int quantidade = 0;
int proximoID = 1;
int indiceTipo = 0;  // controla qual tipo vem a seguir


// ---------------------------
//  GERAR PEÇA AUTOMÁTICA SEM rand()
// ---------------------------
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};

    Peca p;
    p.tipo = tipos[indiceTipo];
    p.id = proximoID++;

    indiceTipo = (indiceTipo + 1) % 4; // gira entre 0-3 para gerar I O T L repetidamente

    return p;
}


// ---------------------------
//  VERIFICAR FILA
// ---------------------------
int filaVazia() { return quantidade == 0; }
int filaCheia() { return quantidade == TAM; }


// ---------------------------
//  INSERIR (ENQUEUE)
// ---------------------------
void enqueue(Peca p) {
    if (filaCheia()) {
        printf("❌ Fila cheia! Não é possível inserir.\n");
        return;
    }

    fila[tras] = p;
    tras = (tras + 1) % TAM;
    quantidade++;
}


// ---------------------------
//  REMOVER (DEQUEUE)
// ---------------------------
Peca dequeue() {
    Peca removida = {'X', -1};

    if (filaVazia()) {
        printf("❌ Fila vazia! Nada para remover.\n");
        return removida;
    }

    removida = fila[frente];
    frente = (frente + 1) % TAM;
    quantidade--;

    return removida;
}


// ---------------------------
//  MOSTRAR FILA
// ---------------------------
void mostrarFila() {
    printf("\n📦 FILA ATUAL:\n");

    if (filaVazia()) {
        printf("   (vazia)\n\n");
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        int idx = (frente + i) % TAM;
        printf("   [%d] Tipo: %c | ID: %d\n", i, fila[idx].tipo, fila[idx].id);
    }
    printf("\n");
}


// ---------------------------
//  INICIALIZAR FILA COM 5 PEÇAS
// ---------------------------
void inicializarFila() {
    for (int i = 0; i < TAM; i++) {
        enqueue(gerarPeca());
    }
}


// ---------------------------
//  PROGRAMA PRINCIPAL
// ---------------------------
int main() {
    inicializarFila();

    int opcao;

    do {
        printf("🎮 DESAFIO TETRIS STACK – Nível Novato\n");
        printf("-------------------------------------\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça manualmente (enqueue)\n");
        printf("3 - Visualizar fila\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            Peca jogada = dequeue();
            if (jogada.id != -1) {
                printf("🧱 Peça jogada -> Tipo: %c | ID: %d\n", jogada.tipo, jogada.id);

                // insere automaticamente outra no final
                Peca nova = gerarPeca();
                enqueue(nova);
                printf("➕ Nova peça criada -> Tipo: %c | ID: %d\n", nova.tipo, nova.id);
            }
            mostrarFila();
        }
        else if (opcao == 2) {
            if (!filaCheia()) {
                Peca nova = gerarPeca();
                enqueue(nova);
                printf("➕ Peça inserida -> Tipo: %c | ID: %d\n", nova.tipo, nova.id);
            } else {
                printf("❌ Fila cheia.\n");
            }
            mostrarFila();
        }
        else if (opcao == 3) {
            mostrarFila();
        }
        else if (opcao != 0) {
            printf("❌ Opção inválida!\n");
        }

    } while (opcao != 0);

    printf("\n👋 Encerrando...\n");
    return 0;
}


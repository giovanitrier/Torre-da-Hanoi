#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#else
void gotoxy(int x, int y) {
    printf("\033[%d;%df", y, x);
    fflush(stdout);
}
#endif

typedef struct {
    int tam;
    int topo;
    int *array;
} Haste;

Haste* criar_haste(int tam) {
    Haste* hs = (Haste*)malloc(sizeof(Haste));
    hs->tam = tam;
    hs->topo = -1;
    hs->array = (int*)malloc(hs->tam * sizeof(int));
    return hs;
}

void gotoxy(int x, int y) {
#ifdef _WIN32
    COORD p = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
#else
    printf("\033[%d;%df", y, x);
    fflush(stdout);
#endif
}

int vazia(Haste* hs) {
    return hs->topo == -1;
}

int cheia(Haste* hs) {
    return hs->topo == hs->tam - 1;
}

void empilhar(Haste* hs, int item) {
    if (cheia(hs)) {
        printf("Erro: Pilha cheia.\n");
        return;
    }
    hs->array[++hs->topo] = item;
}

int desempilhar(Haste* hs) {
    if (vazia(hs)) {
        printf("Erro: Pilha vazia.\n");
        return -1;
    }
    return hs->array[hs->topo--];
}

void mover_disco(Haste* origem, Haste* destino) {
    int disco = desempilhar(origem);
    empilhar(destino, disco);
}

void hanoi(int num_discos, Haste* origem, Haste* auxiliar, Haste* destino) {
    if (num_discos == 1) {
        mover_disco(origem, destino);
        return;
    }
    hanoi(num_discos - 1, origem, destino, auxiliar);
    mover_disco(origem, destino);
    hanoi(num_discos - 1, auxiliar, origem, destino);
}

void imprimir_hastes(Haste* A, Haste* B, Haste* C) {
    gotoxy(1, 6);
    printf("Haste A");
    int i;
    for (i = A->topo; i >= 0; i--) {
        gotoxy(2, 5 - i);
        printf("%d ", A->array[i]);
    }
    gotoxy(8, 6);
    printf("Haste B");
    for (i = B->topo; i >= 0; i--) {
        gotoxy(10, 5 - i);
        printf("%d ", B->array[i]);
    }
    gotoxy(16, 6);
    printf("Haste C");
    for (i = C->topo; i >= 0; i--) {
        gotoxy(18, 5 - i);
        printf("%d ", C->array[i]);
    }
    printf("\n");
}

int main() {
    char opcao;
    char movimento;
    Haste* A, * B, * C;

    A = criar_haste(5);
    B = criar_haste(5);
    C = criar_haste(5);

    empilhar(A, 5);
    empilhar(A, 4);
    empilhar(A, 3);
    empilhar(A, 2);
    empilhar(A, 1);

#ifdef _WIN32
    system("CLS");
#else
    printf("\033[2J");
    printf("\033[H");
#endif
    printf("\n----- Menu -----\n");
    printf("1 - Modo Manual\n");
    printf("2 - Modo Automatico\n");
    printf("3 - Sair\n");
    printf("Escolha uma opcao> ");
    scanf(" %c", &opcao);

    clock_t inicio, fim;
    double tempo;

    switch (opcao) {
    case '1':
        inicio = clock();
        while (!vazia(A) || !vazia(B) || !vazia(C)) {
#ifdef _WIN32
            system("cls");
#else
            printf("\033[2J");
            printf("\033[H");
#endif
            imprimir_hastes(A, B, C);
            gotoxy(0, 7);
            printf("Escolha o proximo movimento:\n");
            printf("1 - Mover disco da haste A para a haste B\n");
            printf("2 - Mover disco da haste A para a haste C\n");
            printf("3 - Mover disco da haste B para a haste A\n");
            printf("4 - Mover disco da haste B para a haste C\n");
            printf("5 - Mover disco da haste C para a haste A\n");
            printf("6 - Mover disco da haste C para a haste B\n");
            printf("\n");

            fim = clock();
            tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            gotoxy(26, 6);
            printf("Tempo: %.1f s", tempo);
            gotoxy(0, 16);
            scanf(" %c", &movimento);

            switch (movimento) {
            case '1':
                if (!vazia(A) && (vazia(B) || A->array[A->topo] < B->array[B->topo]))
                    mover_disco(A, B);
                else
                    printf("Movimento invalido.\n");
                Sleep(150);
                break;
            case '2':
                if (!vazia(A) && (vazia(C) || A->array[A->topo] < C->array[C->topo]))
                    mover_disco(A, C);
                else
                    printf("Movimento invalido.\n");
                Sleep(150);
                break;
            case '3':
                if (!vazia(B) && (vazia(A) || B->array[B->topo] < A->array[A->topo]))
                    mover_disco(B, A);
                else
                    printf("Movimento invalido.\n");
                Sleep(150);
                break;
            case '4':
                if (!vazia(B) && (vazia(C) || B->array[B->topo] < C->array[C->topo]))
                    mover_disco(B, C);
                else
                    printf("Movimento invalido.\n");
                Sleep(150);
                break;
            case '5':
                if (!vazia(C) && (vazia(A) || C->array[C->topo] < A->array[A->topo]))
                    mover_disco(C, A);
                else
                    printf("Movimento invalido.\n");
                Sleep(150);
                break;
            case '6':
                if (!vazia(C) && (vazia(B) || C->array[C->topo] < B->array[B->topo]))
                    mover_disco(C, B);
                else
                    printf("Movimento invalido.\n");
                Sleep(150);
                break;
            default:
                printf("Opcao invalida.\n");
                break;
            }
        }
        break;
    case '2':
        inicio = clock();
        hanoi(5, A, B, C);
        fim = clock();
        tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("Tempo de execucao: %.1f segundos\n", tempo);
        break;
    case '3':
        printf("Saindo...\n");
        break;
    default:
        printf("Opcao invalida.\n");
        break;
    }

    free(A->array);
    free(A);
    free(B->array);
    free(B);
    free(C->array);
    free(C);

    return 0;
}

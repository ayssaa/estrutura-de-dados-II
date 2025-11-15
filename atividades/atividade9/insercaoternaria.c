#include <stdlib.h>
#include <stdio.h>

// Função que encontra posição de inserção usando busca ternaria
int buscaPosicaoTernaria(int vet[], int inicio, int fim, int chave) {
    while (inicio <= fim) {
        int terco = (fim - inicio) / 3;
        int m1 = inicio + terco;
        int m2 = fim - terco;

        if (chave < vet[m1]) {
            fim = m1 - 1; // está no primeiro terço
        }
        else if (chave > vet[m2]) {
            inicio = m2 + 1; // está no último terço
        }
        else {
            // está no terço do meio
            inicio = m1 + 1;
            fim = m2 - 1;
        }
    }
    return inicio; // posição onde deve ser inserido
}

void main() {
    int vet[3] = {2, 3, 1};
    int n = 3;
    int aux;
    
    printf("Vetor desordenado: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
    
    // Inserção ternaria
    for (int i = 1; i < n; i++) {
        aux = vet[i];
        int j = i - 1;

        // busca posição com busca ternária
        int pos = buscaPosicaoTernaria(vet, 0, j, aux);

        // move os elementos pra direita
        while (j >= pos) {
            vet[j + 1] = vet[j];
            j--;
        }

        // insere na posição certa
        vet[pos] = aux;
    } 
    
    printf("Vetor ordenado: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
}

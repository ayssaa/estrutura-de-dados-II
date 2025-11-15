#include <stdlib.h>
#include <stdio.h>

// Função que encontra a posição de inserção usando busca binária
int buscaPosicao(int vet[], int inicio, int fim, int chave) {
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        if (chave < vet[meio]) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }
    return inicio; // posição onde o elemento deve ser inserido
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
    
    // Inserçao binaria
    for (int i = 1; i < n; i++) {
        aux = vet[i];
        int j = i - 1;

        // encontra a posição de inserção usando busca binaria
        int pos = buscaPosicao(vet, 0, j, aux);

        // desloca os elementos maiores para a direita
        while (j >= pos) {
            vet[j + 1] = vet[j];
            j--;
        }

        // insere o elemento na posição correta
        vet[pos] = aux;
    } 
    
    printf("Vetor ordenado: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
}

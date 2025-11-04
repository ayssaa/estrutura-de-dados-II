#include <stdio.h>
#include <stdlib.h>

void main() {
    // Implementando o algoritmo Bolha
    
    int vet[3] = {2, 3, 1};
    int n = 3;
    int aux;

    for (int i = n-1; i >= 1; i--) {
        for (int j = 0; j < i; j++) {
            if (vet[j] > vet[j+1]) {
                // troca
                aux = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = aux;
            }
        }
    }

    // Exibe vetor ordenado
    printf("Vetor ordenado: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", vet[i]);
    }

    printf("\n");
}

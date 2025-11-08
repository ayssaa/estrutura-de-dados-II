#include <stdio.h>
#include <stdlib.h>

void main() {
    // Implementando o algoritmo Bolha com parada
    
    int vet[3] = {2, 3, 1};
    int n = 3;
    int indice = n-1; // indice = n-1
    int aux;
    int mudou = 1;
    int j;
    
    // Exibe vetor desordenado
    printf("Vetor desordenado: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", vet[i]);
    }

    printf("\n");
    
    while(mudou) {
        j = 1;
        mudou = 0;
        
        while(j<n) {
            if(vet[j-1] > vet[j]) {
                // troca
                aux = vet[j-1];
                vet[j-1] = vet[j];
                vet[j] = aux;
                mudou = 1;
            }
            indice = j;
            j = j+1;
        }
        n = indice;
    }
    
    
    // Exibe vetor ordenado
    n = 3; // ajeitando a variavel para seu valor original
    printf("Vetor ordenado: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", vet[i]);
    }

    printf("\n");
}

#include <stdlib.h>
#include <stdio.h>

int main() {
    int vet[3] = {2, 3, 1};
    int n = 3;
    int aux;
    
    printf("Vetor desordenado: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
    
    for (int i = 1; i < n; i++) {
        aux = vet[i];
        int j = i - 1;
        
        while (j >= 0 && aux < vet[j]) {
            vet[j+1] = vet[j];
            j--;
        }
        
        vet[j+1] = aux;
    } 
    
    printf("Vetor ordenado: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
    
    return 0;
}

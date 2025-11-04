# include <stdlib.h>
# include <stdio.h>

void main() {
    // Implementando Inserção direta
    int vet[3] = {2, 3, 1};
    int n = 3;
    int aux;
    
    // Exibe vetor desordenado
    printf("Vetor ordenado: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", vet[i]);
    }

    printf("\n");
    
    for(int i = 1; i < (n-1); i++) {
        aux = vet[i];
        int j = (i-1);
        
        while(j >= 0 && aux < vet[j]) {
            vet[j+1] = vet[j];
            j = j-1;
        }
        
        if(j != (i-1)) {
            vet[j+1] = aux;
        }
    } 
    
    // Exibe vetor ordenado
    printf("Vetor ordenado: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", vet[i]);
    }

    printf("\n");
    
}

# include <stdio.h>
# include <stdlib.h>
# include <time.h> // biblioteca para medir tempo

// Seleção

void main() {
    int vetor[5] = {2, 3, 1, 5, 4};
    int n = 5; // tamanho do vetor
    int comparacoes = 0;
    int trocas = 0;

    clock_t inicio, fim; // variáveis para armazenar o tempo
    double tempo_execucao;

    inicio = clock(); // marca o tempo inicial

    // imprime o vetor antes de ordenar
    for(int i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    for(int i = 0; i < n; i++){
        int menor = i;

        for(int j = i+1; j < n; j++) {
            comparacoes += 1;
            if(vetor[j] < vetor[menor]) {
                menor = j;
            }
        }

        if(i != menor){
            int auxiliar = vetor[i];
            vetor[i] = vetor[menor];
            vetor[menor] = auxiliar;
            trocas += 1;
        }
    }

    fim = clock(); // marca o tempo final

    // calcula tempo de execução em segundos
    tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    // imprime o vetor depois de ordenar
    for(int i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }

    printf("\nComparações: %d\nTrocas: %d", comparacoes, trocas);
    printf("Tempo de execução: %.6f segundos\n", tempo_execucao);
}
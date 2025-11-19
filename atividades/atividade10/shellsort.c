# include <stdio.h>
# include <stdlib.h>
# include <time.h> // biblioteca para medir tempo

// ShellSort

void main() {
    int vetor[5] = {2, 3, 1, 5, 4};
    int n = 5; // tamanho do vetor
    int h = 1;

    int comparacoes = 0;
    int trocas = 0;

    clock_t inicio, fim; 
    double tempo_execucao;

    // imprime o vetor antes de ordenar
    for(int i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    inicio = clock(); // marca o tempo inicial

    while(h < n) {
        h = (3*h) + 1;
    }

    while(h > 1) {
        h = h/3;
        for(int i = h; i < n; i++) {
            int auxiliar = vetor[i];
            int j = i - h;

            comparacoes += 1;

            while(j >= 0 && auxiliar < vetor[j]) {
                vetor[j + h] = vetor[j];
                j = j - h;

                trocas += 1;
                comparacoes += 1;
            }
            vetor[j+h] = auxiliar;
            comparacoes += 1;
        }
    }

    fim = clock(); // marca o tempo final
    tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    // imprime o vetor depois de ordenar
    for(int i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }

    printf("\nComparações: %d\nTrocas: %d", comparacoes, trocas);
    // Professor coloquei esses valores pra ficar melhor na saída, ainda to entendendo como usa a biblioteca de tempo :)
    printf("Tempo de execução: %.6f segundos (%.3f ms)\n", tempo_execucao, tempo_execucao * 1000);
}
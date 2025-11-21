# include <stdio.h>
# include <stdlib.h>

/*

Algoritmo Heap Sort
-> Contabilizar o número de comparações, trocas e o tempo de execução.

*/

// Função que cria a heap (max-heap)
void criaHeap(int V[], int inicio, int final) {
    int auxiliar = V[inicio]; // guarda o pai
    int j = inicio * 2 + 1;   // filho à esquerda

    while (j <= final) {
        // Verifica se há filho à direita e se ele é maior
        if (j < final && V[j] < V[j + 1]) {
            j = j + 1; // vai para o maior filho
        }

        // Se o filho for maior que o pai
        if (auxiliar < V[j]) {
            V[inicio] = V[j];   // filho sobe
            inicio = j;         // novo pai
            j = 2 * inicio + 1; // próximo filho
        } else {
            j = final + 1;      // sai do loop
        }
    }

    // Antigo pai ocupa o lugar do último filho analisado
    V[inicio] = auxiliar;
}

// Função Heap Sort
void heapSort(int V[], int N) {
    int i, auxiliar;

    // criando a heap
    for (i = (N - 1) / 2; i >= 0; i--) {
        criaHeap(V, i, N - 1);
    }

    // Reconstrói a heap ordenando o vetor
    for (i = N - 1; i >= 1; i--) {
        auxiliar = V[0];
        V[0] = V[i];
        V[i] = auxiliar;
        criaHeap(V, 0, i - 1);
    }
}

void main() {
    int V[] = {1, 4, 2, 3, 7, 6, 5};
    int N = 7;

    printf("Vetor original:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", V[i]);
    }

    heapSort(V, N);

    printf("\n\nVetor ordenado:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", V[i]);
    }
}

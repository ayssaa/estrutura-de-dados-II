// busca binária com recursividade
// Incluindo bibliotecas
# include <stdio.h>
# include <stdlib.h>

int buscaBinaria(int vetor[], int ini, int fim, int chave) {
    if (ini > fim) {
        return -1; // caso base: não achei :(
    }

    int meio = (ini + fim) / 2;

    if (vetor[meio] == chave) {
        return meio; // achei!
    } 
    else if (vetor[meio] < chave) {
        // busca na metade direita
        return buscaBinaria(vetor, meio + 1, fim, chave);
    } 
    else {
        // busca na metade esquerda
        return buscaBinaria(vetor, ini, meio - 1, chave);
    }
}

void main() {
    int lista[10] = {1, 2, 3, 4 , 5, 6, 7, 8, 9, 10};
    int chave;

    printf("Olá! Qual número você quer buscar? ");
    scanf("%d", &chave);

    int indice = buscaBinaria(lista, 0, 10, chave);

    // saída :)
    
    if (indice == -1) {
        printf("Valor não encontrado!\n");
    }
    else {
        printf("Valor %d encontrado no índice %d da lista!\n", chave, indice);
    }
}
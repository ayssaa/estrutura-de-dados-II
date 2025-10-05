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
    // transformando lista.txt em um vetor:
    FILE *arquivo = fopen("lista.txt", "r");

    if(arquivo == NULL) {
        printf("Erro ao abrir o arquivo!");
    }

    int lista[500];
    int quantidade_lida = 0;

    while (quantidade_lida < 500) {
        fscanf(arquivo, "%d", &lista[quantidade_lida]);
        quantidade_lida += 1;
    }

    fclose(arquivo);

    // o vetor lista não está ordenado, então vamos ordena-lo!
    for (int i = 0; i < quantidade_lida - 1; i++) {
        for (int j = 0; j < quantidade_lida - i - 1; j++) {
            if (lista[j] > lista[j + 1]) {
                int temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }

    // agora o vetor está ordenado e podemos fazer uma busca binária
    int chave;
    printf("Olá! Qual número você quer buscar? ");
    scanf("%d", &chave);

    int indice = buscaBinaria(lista, 0, 500, chave);

    // saída :)
    FILE *indices = fopen("indices.txt", "w");
    if(indices == NULL) {
        printf("Erro ao abrir o arquivo!");
    }

    if (indice == -1) {
        printf("Valor não encontrado!\n");
        fprintf(indices, "Valor %d não foi encontrado no arquivo\n", chave);
    }
    else {
        printf("Valor encontrado!\n");
        fprintf(indices, "Valor %d encontrado no índice %d da lista!!! :D\n", chave, indice);
    }
}
// Incluindo Bibliotecas
# include <stdio.h>
# include <stdlib.h>


// Função que realiza uma busca sequencial
int buscaSequencial(int v[], int chave) {
    // percorre a lista
    for (int i=0; i < 3; i++) {
        if (v[i] == chave) {
            return i;
        }
    }
    return -1;
}


void main() {
    int lista[3]; // criando a lista
    int procurado; // criando o procurado
   
    // Solicitando os dados para preenchimento da lista
    printf("Digite os valores da lista:\n");
    for(int i = 0; i < 3; i++) {
        printf("Valor %d: ", i+1);
        scanf("%d", &lista[i]);
    }
   
    // Solicitando valor procurado
    printf("Digite o valor que você deseja procurar: ");
    scanf("%d", &procurado);
   
    // Chamada de Função
    int resultado = buscaSequencial(lista, procurado);
   
    // Saída
    if (resultado != -1) {
        printf("Achei! Está no índice %d!", resultado);
    }
    else {
        printf("Valor não encontrado");
    }
   
}

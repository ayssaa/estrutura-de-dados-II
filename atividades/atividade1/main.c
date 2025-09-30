// Incluindo Bibliotecas
# include <stdio.h>
# include <stdlib.h>

void main() {
    // Abrindo/Criando meus arquivos
    FILE *lista = fopen("lista.txt", "r"); // arquivo com a lista de dados numéricos
    FILE *indices = fopen("indices.txt", "w"); // arquivo de saída com os respectivos índices 
    
    // verificando erros...
    if(lista == NULL || indices == NULL) {
        printf("Erro ao abrir os arquivos.\n");
    }
    
    // Lendo a lista.txt
    int vetor[250];   // vetor fixo para 250 números
    int quantidade_lida = 0;
    while (quantidade_lida < 250) {
        fscanf(lista, "%d", &vetor[quantidade_lida]);
        quantidade_lida += 1;
    }
   
    // Solicitando a chave desejada
    int chave;
    printf("Digite o valor que você deseja procurar: ");
    scanf("%d", &chave);
    
    
    // Procurando chave e escrevendo índices... 
    int qnt_chaves = 0;
    fprintf(indices, "Indices: ");
    for (int i = 0; i < 250; i++) {
        if (vetor[i] == chave) {
            fprintf(indices, "%d ", i); // grava o índice no arquivo
            qnt_chaves += 1;
        }
    }
    
    // Saída
    fclose(lista);
    fclose(indices);
    
    printf("Busca concluida! Encontrei o valor '%d' %d vezes! Veja os índices em 'indices.txt'.\n", chave, qnt_chaves);
}


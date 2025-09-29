// Incluindo Bibliotecas
# include <stdio.h>
# include <stdlib.h>

void main() {
    // Abrindo/Criando meus arquivos
    FILE *lista = fopen("lista.txt", "r"); // arquivo com a lista de dados numéricos
    FILE *indices = fopen("saida.txt", "w"); // arquivo de saída com os respectivos índices 
    
    // verificando erros...
    if(lista == NULL || indices == NULL) {
        printf("Erro ao abrir os arquivos.\n");
    }
    
    // Lendo a lista.txt
    int vetor[250];   // vetor fixo para 250 números
    int quantidade_lida = 0;

    while (quantidade_lida < 250) {
        fscanf(vetor, "%d", &vetor[quantidade_lida]);
        quantidade_lida++;
    }
   
    // Solicitando a chave desejada
    int chave;
    printf("Digite o valor que você deseja procurar: ");
    scanf("%d", &chave);
    
    
    // Procurando chave e escrevendo índices... 
    int qnt_chaves = 0;
    fprintf(indices, "Indices: ");
    for (int i=0; i < 250; i++) {
        if (vetor[i] == chave) {
            fprintf(indices, "%d ", i); // grava o índice no arquivo
            qnt_chaves += 1;
        }
    }
    fprintf(indices, "\n");
    
    // Saída
    fclose(lista);
    fclose(indices);
    printf("Busca concluida! Veja o resultado em 'indices.txt'.\n");
}



// Codigo gpt
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *fin  = fopen("lista.txt", "r");   // arquivo de entrada
    FILE *fout = fopen("saida.txt", "w");   // arquivo de saída

    if (!fin || !fout) {
        printf("Erro ao abrir arquivos.\n");
        return 1;
    }

    int v[250];   // vetor fixo para 250 números
    int n = 0;

    // lê 250 números (um por linha)
    while (n < 250 && fscanf(fin, "%d", &v[n]) == 1) {
        n++;
    }

    int chave;
    printf("Digite o valor que deseja procurar: ");
    scanf("%d", &chave);

    int indices[250];
    int qtd = 0;

    // busca sequencial
    for (int i = 0; i < n; i++) {
        if (v[i] == chave) {
            indices[qtd++] = i;  // índice 0-based
        }
    }

    // escreve resultado no arquivo de saída
    fprintf(fout, "Ocorrencias: %d\n", qtd);
    if (qtd > 0) {
        fprintf(fout, "Indices: ");
        for (int i = 0; i < qtd; i++) {
            fprintf(fout, "%d%s", indices[i], (i+1<qtd) ? " " : "\n");
        }
    }

    fclose(fin);
    fclose(fout);

    printf("Busca concluida! Veja o resultado em 'saida.txt'.\n");
    return 0;
}

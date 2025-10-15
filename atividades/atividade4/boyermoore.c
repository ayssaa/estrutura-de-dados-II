// Incluindo bibliotecas
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define alfabeto 256  // tabela ASCII estendida

void main() {
    char texto[100] = "abcbcbabacbcaacbabacaba";
    char padrao[50];

    printf("Digite o padrão que você deseja buscar: ");
    scanf("%s", padrao);

    // implementando a busca boyer moore
    int comparacoes = 0;
    int indice = -1;
    int achou = 0;
    int n = strlen(texto); // tamanho do texto
    int m = strlen(padrao); // tamanho do padrao

    // Tabela do mau caractere
    int charuim[alfabeto];
    for (int i = 0; i < alfabeto; i++) {
        charuim[i] = -1;
    }
    for (int i = 0; i < m; i++) {
        charuim[(unsigned char)padrao[i]] = i;
    }
    
    // Busca
    int shift = 0;
    while (shift <= n - m) {
        int j = m - 1;

        // compara da direita para a esquerda
        while (j >= 0) {
            comparacoes += 1;
            if (padrao[j] == texto[shift + j]) {
                j -= 1;
            } else {
                break;
            }
        }

        if (j < 0) {
            indice = shift; // primeira ocorrência
            achou = 1;
            break; // pare na primeira; se quiser todas, remova o break
        } else {
            int next = j - charuim[(unsigned char)texto[shift + j]];
            if (next < 1) next = 1;
            shift += next;
        }
    }    

    FILE *resultados = fopen("resultados.txt", "w");
    if (resultados == NULL) {
        printf("Erro ao criar arquivo!\n");
    }

    if(achou == 0) {
        fprintf(resultados, "Não encontrei o padrão!\n");
    }
    
    else {
        fprintf(resultados, "indice = %d\ncomparacoes = %d\n", indice, comparacoes);
    }

    fclose(resultados);

    printf("Resultado está salvo em 'resultados.txt'!\n");
    printf("Tivemos um total de %d comparações!\n", comparacoes);
}

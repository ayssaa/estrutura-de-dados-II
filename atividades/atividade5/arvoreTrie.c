
/*
Oii professor! Fiz a implementação acompanhando os vídeos aula abaixo:

. https://www.youtube.com/watch?v=NqEbV5FBKmg
. https://www.youtube.com/watch?v=NDfAYZCHstI

Então ficou bem parecido, pois assisti e implementei com a mesma lógica!
*/

// Incluindo bibliotecas
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# define NUM_CHARS 256

typedef struct NoTrie {
    struct NoTrie *prox[NUM_CHARS];
    bool fim; // é ou não o fim da string
} notrie;

notrie *criarNo() {
    notrie *novono = malloc(sizeof(*novono));

    for(int i=0; i< NUM_CHARS; i++) {
        novono->prox[i] = NULL;
    }

    novono->fim = false;
    return novono;
}

bool inserirtrie(notrie **raiz, char *signedtext) {
    if(*raiz == NULL) {
        *raiz = criarNo();
    }
    
    unsigned char *text = (unsigned char *)signedtext; // resolvendo problema de índice negativo
    notrie *tmp = *raiz;
    int lenght = strlen(signedtext);

    for(int i=0; i< lenght; i++) {
        if(tmp->prox[text[i]] == NULL) {
            // cria um novo nó
            tmp->prox[text[i]] = criarNo();
        }
        tmp = tmp->prox[text[i]];
    }

    if(tmp->fim) {
        return false;
    } else {
        tmp->fim = true;
        return true;
    }
}

void imprimirRec(notrie *no, unsigned char *prefix, int lenght) {
    unsigned char newprefix[lenght+2];
    memcpy(newprefix, prefix, lenght);
    newprefix[lenght+1] = 0;
    
    if(no->fim) {
        printf("Palavra: %s\n", prefix);
    }

    for(int i=0; i< NUM_CHARS; i++) {
        if(no->prox[i] != NULL) {
            newprefix[lenght] = i;
            imprimirRec(no->prox[i], newprefix, lenght+1);
        }
    }
}

void imprimir(notrie *raiz) {
    if(raiz == NULL) {
        printf("Vazia!\n");
        return;
    }
    imprimirRec(raiz, NULL, 0);
}

bool busca(notrie *raiz, char *signedtext) {
    unsigned char *text = (unsigned char *) signedtext;
    int length = strlen(signedtext);
    notrie * tmp = raiz;
    for(int i=0; i< length; i++) {
        if(tmp->prox[text[i]] == NULL) {
            return false;
        }
        tmp = tmp->prox[text[i]];
    }
    return tmp->fim;
}


bool tem_filho(notrie *no) {
    if(no == NULL) {
        return false;
    }
    for (int i = 0; i < NUM_CHARS; i++) {
        if(no->prox[i] != NULL) {
            // tem filho
            return true;
        }
    }
    return false;
}


notrie* deletarRec(notrie *no, unsigned char *text, bool *deleted) {
    if(no == NULL) {
        return no;
    }
    
    if(*text == '\0') {
        if(no->fim) {
            no->fim = false;
            *deleted = true;

            if(tem_filho(no) == false) {
                free(no);
                no = NULL;
            }
        }
        return no;
    }

    no->prox[text[0]] = deletarRec(no->prox[text[0]], text+1, deleted);
    if(*deleted && tem_filho(no) == false && no->fim == false) {
        free(no);
        no = NULL;
    }
    return no;
}

bool deletar(notrie** raiz, char *signedtext) {
    unsigned char *text = (unsigned char *) signedtext;
    bool resultado = false;

    if(*raiz == NULL) {
        return false;
    }

    *raiz = deletarRec(*raiz, text, &resultado);
    return resultado;
}


void main() {
    notrie *raiz = NULL;

    // Inserindo na árvore
    inserirtrie(&raiz, "Ayssa");
    inserirtrie(&raiz, "Samuel");
    inserirtrie(&raiz, "Amor");
    inserirtrie(&raiz, "Apaixonada");
    inserirtrie(&raiz, "UFES");
    
    // Vendo árvore
    printf("------Palavras armazenadas------\n");
    imprimir(raiz);

    // Buscando
    printf("------Buscando palavras------\n");
    printf("search for Ayssa: %d\n", busca(raiz, "Ayssa"));
    printf("search for Samuel: %d\n", busca(raiz, "Samuel"));
    printf("search for UFES: %d\n", busca(raiz, "UFES"));

    // Removendo
    printf("-> Removendo palavras...\nPalavras removidas com sucesso! Veja as palavras armazenadas atuais:\n");
    deletar(&raiz, "UFES");
    deletar(&raiz, "Apaixonada");
    imprimir(raiz);
}

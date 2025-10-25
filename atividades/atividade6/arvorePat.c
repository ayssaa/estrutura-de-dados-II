#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NUM_CHARS 256

typedef struct NoTrie notrie;

typedef struct {
    unsigned char *trecho;
    size_t tamanho;
    notrie *filho;
} aresta;

struct NoTrie {
    aresta *arestas;
    size_t qtd_arestas;
    bool fim;
};

notrie *criarNo() {
    notrie *novono = (notrie*)calloc(1, sizeof(*novono));
    if (!novono) { perror("calloc"); exit(EXIT_FAILURE); }
    return novono;
}

unsigned char* copiarTrecho(const unsigned char *s, size_t tam) {
    unsigned char *p = (unsigned char*)malloc(tam + 1);
    if (!p) { perror("malloc"); exit(EXIT_FAILURE); }
    memcpy(p, s, tam);
    p[tam] = '\0';
    return p;
}

size_t prefixo_comum(const unsigned char *a, size_t ta, const unsigned char *b, size_t tb) {
    size_t i = 0;
    size_t limite = ta < tb ? ta : tb;
    while (i < limite && a[i] == b[i]) {
        i += 1;
    }
    return i;
}

aresta* encontrar_aresta(notrie *no, unsigned char primeira_letra) {
    for (size_t i = 0; i < no->qtd_arestas; i += 1) {
        if (no->arestas[i].trecho[0] == primeira_letra) {
            return &no->arestas[i];
        }
    }
    return NULL;
}

aresta* adicionar_aresta(notrie *no, const unsigned char *trecho, size_t tam, notrie *filho) {
    aresta *novo = (aresta*)realloc(no->arestas, (no->qtd_arestas + 1) * sizeof(aresta));
    if (!novo) { perror("realloc"); exit(EXIT_FAILURE); }
    no->arestas = novo;
    aresta *a = &no->arestas[no->qtd_arestas];
    no->qtd_arestas += 1;
    a->trecho = copiarTrecho(trecho, tam);
    a->tamanho = tam;
    a->filho = filho;
    return a;
}

void remover_aresta(notrie *no, size_t indice) {
    if (indice >= no->qtd_arestas) { return; }
    free(no->arestas[indice].trecho);
    for (size_t i = indice + 1; i < no->qtd_arestas; i += 1) {
        no->arestas[i - 1] = no->arestas[i];
    }
    no->qtd_arestas -= 1;
    if (no->qtd_arestas == 0) {
        free(no->arestas);
        no->arestas = NULL;
    } else {
        aresta *novo = (aresta*)realloc(no->arestas, no->qtd_arestas * sizeof(aresta));
        if (novo) {
            no->arestas = novo;
        }
    }
}

void fundir_unico_filho(notrie *no) {
    if (!no || no->qtd_arestas != 1) { return; }
    if (no->fim) { return; }

    aresta *a = &no->arestas[0];
    notrie *filho = a->filho;
    if (!filho || filho->qtd_arestas == 0) { return; }

    if (filho->qtd_arestas == 1 && !filho->fim) {
        aresta *filho_aresta = &filho->arestas[0];
        unsigned char *novo_trecho = (unsigned char*)malloc(a->tamanho + filho_aresta->tamanho + 1);
        if (!novo_trecho) { perror("malloc"); exit(EXIT_FAILURE); }
        memcpy(novo_trecho, a->trecho, a->tamanho);
        memcpy(novo_trecho + a->tamanho, filho_aresta->trecho, filho_aresta->tamanho);
        novo_trecho[a->tamanho + filho_aresta->tamanho] = '\0';

        free(a->trecho);
        a->trecho = novo_trecho;
        a->tamanho += filho_aresta->tamanho;

        notrie *neto = filho_aresta->filho;
        free(filho_aresta->trecho);
        free(filho->arestas);
        free(filho);

        a->filho = neto;
    }
}

bool inserirtrie(notrie **raiz, char *signedtext) {
    if (*raiz == NULL) { *raiz = criarNo(); }

    unsigned char *texto = (unsigned char*)signedtext;
    size_t tamanho = strlen(signedtext);
    notrie *atual = *raiz;

    if (tamanho == 0) {
        bool ja = atual->fim;
        atual->fim = true;
        return !ja;
    }

    while (1) {
        aresta *a = encontrar_aresta(atual, texto[0]);

        if (!a) {
            notrie *folha = criarNo();
            folha->fim = true;
            adicionar_aresta(atual, texto, tamanho, folha);
            return true;
        }

        size_t comum = prefixo_comum(texto, tamanho, a->trecho, a->tamanho);

        if (comum == a->tamanho) {
            texto += comum;
            tamanho -= comum;
            if (tamanho == 0) {
                bool ja = a->filho->fim;
                a->filho->fim = true;
                return !ja;
            }
            atual = a->filho;
            continue;
        }

        notrie *meio = criarNo();

        notrie *filho_antigo = a->filho;
        unsigned char *trecho_antigo = a->trecho;
        size_t tam_antigo = a->tamanho;

        a->trecho = copiarTrecho(trecho_antigo, comum);
        a->tamanho = comum;
        a->filho = meio;

        adicionar_aresta(meio, trecho_antigo + comum, tam_antigo - comum, filho_antigo);
        free(trecho_antigo);

        texto += comum;
        tamanho -= comum;

        if (tamanho == 0) {
            bool ja = meio->fim;
            meio->fim = true;
            return !ja;
        } else {
            notrie *folha = criarNo();
            folha->fim = true;
            adicionar_aresta(meio, texto, tamanho, folha);
            return true;
        }
    }
}

bool busca(notrie *raiz, char *signedtext) {
    if (!raiz) { return false; }

    const unsigned char *texto = (const unsigned char*)signedtext;
    size_t tamanho = strlen(signedtext);
    notrie *atual = raiz;

    while (tamanho > 0) {
        aresta *a = encontrar_aresta(atual, texto[0]);
        if (!a) { return false; }

        if (tamanho < a->tamanho) { return false; }
        if (memcmp(texto, a->trecho, a->tamanho) != 0) { return false; }

        texto += a->tamanho;
        tamanho -= a->tamanho;
        atual = a->filho;
    }
    return atual->fim;
}

bool deletarRec(notrie *no, const unsigned char *texto, size_t tamanho, bool *apagou) {
    if (!no) { return false; }

    if (tamanho == 0) {
        if (no->fim) {
            no->fim = false;
            *apagou = true;
            return true;
        }
        return false;
    }

    aresta *a = encontrar_aresta(no, texto[0]);
    if (!a) { return false; }

    if (tamanho < a->tamanho) { return false; }
    if (memcmp(texto, a->trecho, a->tamanho) != 0) { return false; }

    bool ok = deletarRec(a->filho, texto + a->tamanho, tamanho - a->tamanho, apagou);

    if (*apagou) {
        notrie *filho = a->filho;

        if (!filho->fim && filho->qtd_arestas == 0) {
            size_t indice = 0;
            for (; indice < no->qtd_arestas; indice += 1) {
                if (&no->arestas[indice] == a) { break; }
            }

            free(filho);
            remover_aresta(no, indice);

            if (!no->fim && no->qtd_arestas == 1) {
                fundir_unico_filho(no);
            }
        } else if (!filho->fim && filho->qtd_arestas == 1) {
            aresta *a_filho = &filho->arestas[0];
            unsigned char *novo_trecho = (unsigned char*)malloc(a->tamanho + a_filho->tamanho + 1);
            if (!novo_trecho) { perror("malloc"); exit(EXIT_FAILURE); }
            memcpy(novo_trecho, a->trecho, a->tamanho);
            memcpy(novo_trecho + a->tamanho, a_filho->trecho, a_filho->tamanho);
            novo_trecho[a->tamanho + a_filho->tamanho] = '\0';

            free(a->trecho);
            a->trecho = novo_trecho;
            a->tamanho += a_filho->tamanho;

            notrie *neto = a_filho->filho;
            free(a_filho->trecho);
            free(filho->arestas);
            free(filho);

            a->filho = neto;
        }
    }

    return ok;
}

bool deletar(notrie **raiz, char *signedtext) {
    if (!*raiz) { return false; }
    const unsigned char *texto = (const unsigned char*)signedtext;
    size_t tamanho = strlen(signedtext);
    bool apagou = false;

    deletarRec(*raiz, texto, tamanho, &apagou);

    if (*raiz && !(*raiz)->fim && (*raiz)->qtd_arestas == 1) {
        fundir_unico_filho(*raiz);
    }

    return apagou;
}

void imprimirRec(notrie *no, unsigned char *buffer, size_t tamanho) {
    if (!no) { return; }

    if (no->fim) {
        buffer[tamanho] = '\0';
        printf("Palavra: %s\n", buffer);
    }

    for (size_t i = 0; i < no->qtd_arestas; i += 1) {
        aresta *a = &no->arestas[i];
        memcpy(buffer + tamanho, a->trecho, a->tamanho);
        imprimirRec(a->filho, buffer, tamanho + a->tamanho);
    }
}

void imprimir(notrie *raiz) {
    if (!raiz) { printf("Vazia!\n"); return; }
    unsigned char buffer[1024];
    imprimirRec(raiz, buffer, 0);
}

void liberarTrie(notrie *no) {
    if (!no) { return; }
    for (size_t i = 0; i < no->qtd_arestas; i += 1) {
        liberarTrie(no->arestas[i].filho);
        free(no->arestas[i].trecho);
    }
    free(no->arestas);
    free(no);
}

int main(void) {
    notrie *raiz = NULL;

    inserirtrie(&raiz, "Ayssa");
    inserirtrie(&raiz, "Samuel");
    inserirtrie(&raiz, "Amor");
    inserirtrie(&raiz, "Apaixonada");
    inserirtrie(&raiz, "UFES");
    
    printf("------Palavras armazenadas------\n");
    imprimir(raiz);

    printf("------Buscando palavras------\n");
    printf("search for Ayssa: %d\n", busca(raiz, "Ayssa"));
    printf("search for Samuel: %d\n", busca(raiz, "Samuel"));
    printf("search for UFES: %d\n", busca(raiz, "UFES"));

    printf("-> Removendo palavras...\n");
    deletar(&raiz, "UFES");
    deletar(&raiz, "Apaixonada");
    imprimir(raiz);

    liberarTrie(raiz);
    return 0;
}

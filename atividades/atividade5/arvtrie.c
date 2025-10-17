// Incluindo bibliotecas
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# define NUM_CHARS 256

typedef struct TrieNode {
    struct TrieNode *children[NUM_CHARS];
    bool terminal; // é ou não o fim da string
} trieNode;

trieNode *createnode() {
    trieNode *newnode = malloc(sizeof(*newnode));

    for(int i=0; i< NUM_CHARS; i++) {
        newnode->children[i] = NULL;
    }

    newnode->terminal = false;
    returnnewnode;
}

bool trieinsert(trieNode **root, char *signedtext) {
    if(*root == NULL) {
        *root = createnode();
    }
    
    unsigned char *text = (unsigned char *)signedtext; // resolvendo problema de índice negativo
    trieNode *tmp = *root;
    int lenght = strlen(signedtext);

    for(int i=0; i< lenght; i++) {
        if(tmp->children[text[i]] == NULL) {
            // cria um novo nó
            tmp->children[text[i]] = createnode();
        }
        tmp = tmp->children[text[i]];
    }

    if(tmp->terminal) {
        return false;
    } else {
        tmp->terminal = true;
        return true;
    }
}

void printtrie_rec(trieNode *node, unsigned char *prefix, int lenght) {
    unsigned char newprefix[lenght+2];
    memcpy(newprefix, prefix, lenght);
    newprefix[lenght+1] = 0;
    
    if(node->terminal) {
        printf("Word: %s\n", prefix);
    }

    for(int i=0; i< NUM_CHARS; i++) {
        if(node->children[i] != NULL) {
            newprefix[lenght] = i;
            printtrie_rec(node->children[i], newprefix, lenght+1);
        }
    }
}

void printtrie(trieNode * root) {
    if(root == NULL) {
        printf("Trie empty!\n");
        return;
    }
    printtrie_rec(root, NULL, 0);
}

bool searchtrie(trieNode *root, char *signedtext) {
    unsigned char *text = (unsigned char *) signedtext;
    int length = strlen(signedtext);
    trieNode * tmp = root;
    for(int i=0; i< length; i++) {
        if(tmp->children[text[i]] == NULL) {
            return false;
        }
        tmp = tmp->children[text[i]];
    }
    return tmp->terminal;
}

bool node_has_children(trieNode *node) {
    if(node == NULL) {
        return false;
    }
    for (int i = 0; i < NUM_CHARS; i++) {
        if(node->children[i] != NULL) {
            // tem filho
            return true;
        }
    }
    return false;
}

trieNode* deletestr_rec(trieNode *node, unsigned char *text, bool *deleted) {
    if(node == NULL) {
        return node;
    }
    
    if(*text == '\0') {
        if(node->terminal) {
            node->terminal = false;
            *deleted = true;

            if(node_has_children(node) == false) {
                free(node);
                node = NULL;
            }
        }
        return node;
    }

    node->children[text[0]] = deletestr_rec(node->children[text[0]], text+1, deleted);
    if(*deleted && node_has_children(node) == false && node->terminal == false) {
        free(node);
        node = NULL;
    }
    return node;
}

bool deletestr(trieNode** root, char *signedtext) {
    unsigned char *text = (unsigned char *) signedtext;
    bool result = false;

    if(*root == NULL) {
        return false;
    }

    *root = deletestr_rec(*root, text, &result);
    return result;
}


void main() {
    trieNode * root = NULL;

    trieinsert(&root, "Kit");
    trieinsert(&root, "Cattle");
    trieinsert(&root, "Kin");
    trieinsert(&root, "Cat");
    trieinsert(&root, "Happy");
    printtrie(root);

    printf("search for Cattle: %d\n", searchtrie(root, "Cattle"));
    printf("search for Cat: %d\n", searchtrie(root, "Cat"));
    printf("search for Kitten: %d\n", searchtrie(root, "Kitten"));

    deletestr(&root, "Kin");
    deletestr(&root, "Cat");
    printtrie(root);

}

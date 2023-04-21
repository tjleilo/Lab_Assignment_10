#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct Trie {
    struct Trie *children[26];
    int words;
};


void insert(struct Trie *ppTrie, char *word) {
    if (ppTrie == NULL){
        return;
    }

    struct Trie *tmp = ppTrie; //Pointer to go through the trie

    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';

        if (tmp->children[index] == NULL) { // If this char at this index doesn't exist in the trie, then add
            tmp->children[index] = calloc(1, sizeof(struct Trie));
        }
        tmp = tmp->children[index]; // Moves to that index to move down the trie
    }
    tmp->words = tmp->words + 1;
}

int numberOfOccurances(struct Trie *pTrie, char *word){
    struct Trie *tmp = pTrie; //Pointer to go through the trie

    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';

        if (tmp->children[index] == NULL) {
            return 0;
        }
        tmp = tmp->children[index];
    }
    return tmp->words;
}


struct Trie * deallocateTrie(struct Trie *pTrie) {
    if (pTrie == NULL) {
        return 0;
    }
    for (int i = 0; i < 26; i++) {
        if (pTrie->children[i] != NULL) {
            deallocateTrie(pTrie->children[i]);
        }
    }
    free(pTrie);
    return NULL;
}


int main(void)
{
    //read the number of the words in the dictionary
    // parse line  by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

   struct Trie *trie = calloc(1, sizeof(struct Trie));

   for (int i=0;i<5;i++)
    {
       insert(trie, pWords[i]);
    }

   for (int i=0;i<5;i++)
    {
        printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL)
        printf("There is an error in this program\n");
    return 0;
}
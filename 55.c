#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 101

typedef struct tItem {
    char key[MAX_WORD_LEN];
    int count;
    struct tItem *prev;
    struct tItem *next;
} Item;

typedef struct tLista {
    Item *first;
    Item *last;
} Lista;

Lista * createEmptyList() {
    Lista *list = (Lista *) malloc(sizeof(Lista));
    if (list != NULL) {
        list->first = NULL;
        list->last = NULL;
    }
    return list;
}

Item * createItem(char *word) {
    Item *item = (Item *) malloc(sizeof(Item));
    if (item != NULL) {
        strcpy(item->key, word);
        item->count = 1;
        item->prev = NULL;
        item->next = NULL;
    }
    return item;
}

void freeList(Lista *list) {
    if (list == NULL) {
        return;
    }
    Item *current = list->first;
    Item *temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

Item * findItem(Lista *list, char *word) {
    Item *current = list->first;
    while (current != NULL) {
        if (strcmp(current->key, word) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void promoteItem(Lista *list, Item *item) {
    while (item->prev != NULL && item->count > item->prev->count) {
        Item *prevItem = item->prev;

        prevItem->next = item->next;
        item->prev = prevItem->prev;

        if (item->next != NULL) {
            item->next->prev = prevItem;
        }

        if (prevItem->prev != NULL) {
            prevItem->prev->next = item;
        }

        item->next = prevItem;
        prevItem->prev = item;

        if (list->first == prevItem) {
            list->first = item;
        }
        if (list->last == item) {
            list->last = prevItem;
        }
    }
}

void processSearch(Lista *list, char *word) {
    Item *foundItem = findItem(list, word);

    if (foundItem != NULL) {
        foundItem->count++;
        promoteItem(list, foundItem);
    } else {
        Item *newItem = createItem(word);
        if (newItem == NULL) {
            return;
        }

        if (list->first == NULL) {
            list->first = newItem;
            list->last = newItem;
        } else {
            list->last->next = newItem;
            newItem->prev = list->last;
            list->last = newItem;
        }
    }
}

void printList(Lista *list) {
    if (list == NULL) {
        return;
    }
    Item *current = list->first;
    while (current != NULL) {
        printf("%s [%d]\n", current->key, current->count);
        current = current->next;
    }
}

int main() {
    char word[MAX_WORD_LEN];
    Lista *list = createEmptyList();
    if (list == NULL) {
        return 1;
    }

    while (scanf("%s", word) != EOF) {
        processSearch(list, word);
    }

    printList(list);
    freeList(list);

    return 0;
}
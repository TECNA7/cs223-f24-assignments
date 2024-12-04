#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tree_node* find(const char* name, struct tree_node* root) {
    if (root == NULL) return NULL;

    int cmp = strcmp(name, root->data.name);
    if (cmp < 0) return find(name, root->left);
    else if (cmp > 0) return find(name, root->right);
    return root;
}

struct tree_node* insert(const char* name, struct tree_node* root) {
    if (root == NULL) {
        struct tree_node* node = malloc(sizeof(struct tree_node));
        if (!node) {
            fprintf(stderr, "Memory allocation failed\n");
            return NULL;
        }
        strncpy(node->data.name, name, sizeof(node->data.name) - 1);
        node->data.name[sizeof(node->data.name) - 1] = '\0';

        node->left = node->right = NULL;

        return node; 
    }

    if (strcmp(name, root->data.name) < 0) {
        root->left = insert(name, root->left);
    } else if (strcmp(name, root->data.name) > 0) {
        root->right = insert(name, root->right);
    }

    return root; 
}

void clear(struct tree_node* root) {
    if (!root) return;
    clear(root->left);
    clear(root->right);
    free(root);
}
void print_helper(struct tree_node* node, int depth, char* prefix) {
    if (node == NULL) return;
    for (int i = 0; i < depth; i++) {
        printf(" ");
    }
    if (prefix) {
        printf("%s", prefix);
    }
    printf("%s\n", node->data.name);
    print_helper(node->left, depth + 1, "l:");
    print_helper(node->right, depth + 1, "r:");
}

void print(struct tree_node* root) {
    print_helper(root, 0, NULL);  
}

void printSorted(struct tree_node* root) {
    if (root == NULL) return;

    printSorted(root->left);
    printf("%s\n", root->data.name);
    printSorted(root->right);
}

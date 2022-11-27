#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "akinator.h"

#define $CALLOC(name) if (!name) {                                                                                        \
                                fprintf(stderr, "Calloc returned null. File %s Line %d\n", __FILE__, __LINE__);           \
                                return NULL_CALLOC;                                                                       \
                      }
#define $SCAN(name) if (!name) fprintf(stderr, "Scanf return null. File %s Line %d\n", __FILE__, __LINE__);
#define $ fprintf(stderr, "I'm here. File %s Line %d\n", __FILE__, __LINE__);
#define $

int akinator (tree_t *tree)
{
        akinator_t aki = {
                .name = "Internet Genious",
                .mode = "on",
                .answ = "",
                .tree = tree,
        };

        return intro(&aki);
}

int intro (akinator_t *aki)
{
        int error = 0;

        printf("Hi, I am %s. What do you want to do?\n", aki->name);
        while (aki->mode[0]) {
                printf("Modes:\n"
                       "1 - guessing\n"
                       "2 - give defenition\n"
                       "3 - give comparison\n"
                );
                if (scanf("%s", aki->mode) > MAX_LINE_LENGTH - 1) {
                        fprintf(stderr, "Buffer was overflawed.\n");
                        return BUF_OVERFLAW;
                }
                if (!stricmp(aki->mode, "exit")) {
                        printf("Goodbye.\n");
                        return 0;
                } else if (!stricmp(aki->mode, "1")) {
                        if (!aki->tree->root->right) {
                                fprintf(stderr, "Tree is empty.");
                        }
                        if (error = guess(aki, aki->tree->root))
                                return error;
                } else if (!stricmp(aki->mode, "2")) {
                        $
                        if (!aki->tree->root->right) {
                                fprintf(stderr, "Tree is empty.");
                        }
                        if ((error = give_defenition(aki)) == NO_NAME)
                                continue;
                        else if (error)
                                return error;
                } else if (!stricmp(aki->mode, "3")) {
                        if (!aki->tree->root->right) {
                                fprintf(stderr, "Tree is empty.");
                        }
                        $
                        if ((error = give_comparison(aki)) == NO_NAME)
                                continue;
                        else if (error)
                                return error;
                } else if (!stricmp(aki->mode, "help")) {
                        printf("Commands:\n"
                               " - help\n"
                               " - exit\n"
                        );
                } else {
                        printf("Sorry, I can't understand you, try again.\n"
                               "Use help to get more information about functions\n");
                }
                free_buf(aki->mode);
                free_buf(aki->answ);
        }

        return 0;
}

void free_buf (char *buf)
{
        for (int i = 2; buf[i] != '\0'; i++)
                buf[i] = '\0';
}

int guess (akinator_t *aki, node_t *node)
{
        int cycle = 1;
        int error = 0;

        if (node->right) {
                printf("Is it %s?\n", node->data);
                while (cycle) {
                        if (scanf("%s", aki->answ) >= MAX_LINE_LENGTH - 1) {
                                fprintf(stderr, "Buffer was overflawed.\n");
                                return BUF_OVERFLAW;
                        }
                        if (!stricmp(aki->answ, "yes")) {
                                guess(aki, node->right);
                                cycle = 0;
                        } else if (!stricmp(aki->answ, "no")) {
                                guess(aki, node->left);
                                cycle = 0;
                        } else if (!stricmp(aki->answ, "exit")) {
                                return 0;
                        } else {
                                printf("I can't understand you. Try again\n");
                        }
                }
        } else {
                printf("Are you %s?\n", node->data);
                while (cycle) {
                        scanf("%s", aki->answ);
                        if (!stricmp(aki->answ, "yes")) {
                                printf("I knew that.\n");
                                cycle = 0;
                        } else if (!stricmp(aki->answ, "no")) {
                                printf("Ohhhhhh\n");
                                if ((error = add_new_hero(aki->tree, node)))
                                        return error;
                                cycle = 0;
                        } else if (!stricmp(aki->answ, "exit")) {
                                return 0;
                        } else {
                                printf("I can't understand you. Try again\n");
                        }
                }
        }

        return 0;
}

int add_new_hero (tree_t *tree, node_t *node)
{
        char *name_data = (char*) calloc(MAX_LINE_LENGTH, sizeof(char));
        $CALLOC(name_data)
        char *feature_data = (char*) calloc(MAX_LINE_LENGTH, sizeof(char));
        $CALLOC(feature_data)

        printf("Who are you?\n");
        scanf("%s", name_data);
        node->right = tree_insert(tree, node->right,       name_data);
        node->left  = tree_insert(tree, node->left, node->data);

        printf("What is the differance between %s and %s?\n", node->left->data, node->right->data);
        scanf("%s", feature_data);
        node->atr.fillcolor = "blue";
        node->data = feature_data;

        return 0;
}

int give_defenition (akinator_t *aki)
{
        char *name = (char*) calloc(MAX_NAME_LENGTH, sizeof(char));
        $CALLOC(name)

        printf("Enter name of the character to find.\n");
        if (scanf("%s", name) >= MAX_LINE_LENGTH - 1) {
                fprintf(stderr, "Buffer was overflawed.\n");
                return BUF_OVERFLAW;
        }
        $SCAN(name)
        node_t *path_nodes = (node_t*) calloc((int) aki->tree->size, sizeof(node_t));
        $CALLOC(path_nodes)
        node_t *start_node = path_nodes;
        if (find_name(aki, name, aki->tree->root, path_nodes)) {
                node_t *node = path_nodes;
                path_nodes++;
                printf("%s is ", name);
                while (node->data && node->right && path_nodes->data) {
                        if (!strcmp(node->left->data, path_nodes->data))
                                printf("not ");
                        printf("%s, ", node->data);
                        node = path_nodes;
                        path_nodes++;
                }
                if (!strcmp(node->left->data, name))
                                printf("not ");
                printf("%s, ", node->data);
                printf("\n");
        } else {
                printf("Cannot find name.\n");
                return NO_NAME;
        }

        free(start_node);
        free(name);
        return 0;
}

node_t* find_name (akinator_t *aki, char *name, node_t *node, node_t *path_node)
{
        node_t *temp_node = node;
        if (node->right && node->left) {
                *path_node = *node;
                node = find_name(aki, name, node->right, path_node + 1);
                if (node)
                        return node;
                node = find_name(aki, name, temp_node->left, path_node + 1);
                if (node)
                        return node;
        }

        if (node) {
                if (!strcmp(node->data, name)) {
                        return node;
                }
        }

        *path_node = {};
        path_node = nullptr;
        return path_node;
}

int give_comparison (akinator_t *aki)
{
        char *name_1 = (char*) calloc(MAX_NAME_LENGTH, sizeof(char));
        $CALLOC(name_1)
        char *name_2 = (char*) calloc(MAX_NAME_LENGTH, sizeof(char));
        $CALLOC(name_2)

        printf("Enter names of the characters to compare.\n");
        if (scanf("%s", name_1) >= MAX_LINE_LENGTH - 1) {
                fprintf(stderr, "Buffer was overflawed.\n");
                return BUF_OVERFLAW;
        }
        $SCAN(name_1)
        if (scanf("%s", name_2) >= MAX_LINE_LENGTH - 1) {
                fprintf(stderr, "Buffer was overflawed.\n");
                return BUF_OVERFLAW;
        }
        $SCAN(name_2)
        node_t *path_1_nodes = (node_t*) calloc((int) aki->tree->size, sizeof(node_t));
        $CALLOC(path_1_nodes)
        node_t *path_2_nodes = (node_t*) calloc((int) aki->tree->size, sizeof(node_t));
        $CALLOC(path_2_nodes)
        node_t *start_1_node = path_1_nodes;
        node_t *start_2_node = path_2_nodes;

        if (find_name(aki, name_1, aki->tree->root, path_1_nodes) && find_name(aki, name_2, aki->tree->root, path_2_nodes)) {
                node_t *node1 = path_1_nodes;
                node_t *node2 = path_2_nodes;
                path_1_nodes++;
                path_2_nodes++;
                node_t *prev_node = aki->tree->root;
                if (!strcmp(path_1_nodes->data, path_2_nodes->data)) {
                        printf("\n%s is the same as %s in ", name_1, name_2);
                }

                if (!strcmp(path_1_nodes->data, aki->tree->root->left->data) && !strcmp(path_2_nodes->data, aki->tree->root->left->data))
                                printf("not ");
                while (node1->right && node2->right && path_1_nodes->data && path_2_nodes->data) {
                        if (!strcmp(path_1_nodes->data, path_2_nodes->data)) {
                                if (node1->right && node2->right)
                                        if (!strcmp(node1->data, prev_node->left->data) && !strcmp(node1->data, node2->data))
                                                printf("not ");
                                printf("%s, ", node1->data);
                                prev_node = node1;
                                node1 = path_1_nodes;
                                node2 = path_2_nodes;
                                path_1_nodes++;
                                path_2_nodes++;
                        } else {
                                break;
                        }
                }

                if (node1->right)
                        printf("but %s is ", name_1);
                while (node1->data && node1->right && path_1_nodes->data) {
                        if (!strcmp(node1->left->data, path_1_nodes->data))
                                printf("not ");
                        printf("%s, ", node1->data);
                        node1 = path_1_nodes;
                        path_1_nodes++;
                }
                if (!strcmp(node1->left->data, name_1))
                                printf("not ");
                        printf("%s, ", node1->data);

                if (node2->right)
                        printf("and %s is ", name_2);

                while (node2->data && path_2_nodes->data) {
                        if (!strcmp(node2->left->data, path_2_nodes->data))
                                printf("not ");
                        printf("%s, ", node2->data);
                        node2 = path_2_nodes;
                        path_2_nodes++;
                }
                if (!strcmp(node2->left->data, name_2))
                                printf("not ");
                        printf("%s, ", node2->data);
                printf("\n");
        } else {
                printf("Cannot find name.\n");
                return NO_NAME;
        }

        free(start_1_node);
        free(name_1);
        free(start_2_node);
        free(name_2);
        return 0;
}

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
                                printf("Tree is empty.");
                        }
                        if (error = guess(aki, aki->tree->root))
                                return error;
                } else if (!stricmp(aki->mode, "2")) {
                        $
                        if (error = give_defenition(aki))
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
                node_t *prev_node = aki->tree->root;
                printf("%s is ", name);
                while (node) {
                        $
                        if (!path_nodes) {
                                break;
                        }
                        $
                        if (!node->left)
                                break;
                        if (!node->data) {
                                node = nullptr;
                                break;
                        }
                        $
                        $
                        printf("%s ", node->data);
                        $
                        if (node->left->data == path_nodes->data) {
                                if (!strcmp(node->left->data, path_nodes->data))
                                        printf("not ");
                        $
                        }
                        node = path_nodes;
                        $
                        path_nodes++;
                }
                printf("\n");
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

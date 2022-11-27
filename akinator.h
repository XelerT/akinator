#ifndef AKINATOR_H
#define AKINATOR_H

#include "tree.h"
#include "tree_text.h"

const char MAX_NAME_LENGTH = 42;

struct akinator_t {
        char name[MAX_NAME_LENGTH] = {};
        char mode[MAX_LINE_LENGTH] = {};
        char answ[MAX_LINE_LENGTH] = {};
        tree_t *tree = nullptr;
};

enum aki_errors {
        BUF_OVERFLAW = 0xBADBAF,
        NO_NAME      = 0xBAD4A2E
};

int akinator (tree_t *tree);
int intro (akinator_t *aki);
int guess (akinator_t *aki, node_t *node);
int add_new_hero (tree_t *tree, node_t *node);
void free_buf (char *buf);
node_t* find_name (akinator_t *aki, char *name, node_t *node, node_t *path_node);
int give_defenition (akinator_t *aki);
int give_comparison (akinator_t *aki);

#endif /*AKINATOR_H*/

#ifndef TREE_H
#define TREE_H

typedef char* elem_t;

enum tree_errors {
        NULL_TREE_PTR = 1,
        NULL_ROOT_PTR = 2,
        NULL_NODE_PTR = 4
};

enum errors {
        NULL_CALLOC = -1
};

struct graph_node_atr_t {
        const char *shape = "rectangle";
        const char *style = "rounded";
        const char *fixedsize = "false";
        const char *fillcolor = "#00b899";
        int height = 3;
        int width = 2;
        int fontsize = 30;
        int penwidth = 5;
};

struct node_t {
        node_t *left  = nullptr;
        elem_t data   = nullptr;        //???
        node_t *right = nullptr;
        size_t indx   =       0;
        int new_node  =       0;

        graph_node_atr_t atr = {};
};

struct tree_t {
        node_t *root = nullptr;
        size_t size  =       0;
};

int tree_ctor (tree_t *tree);
node_t* tree_insert (tree_t *tree, node_t *node, elem_t data);
int tree_dtor (tree_t *tree);
void free_nodes (node_t *node);

#endif /*TREE_H*/

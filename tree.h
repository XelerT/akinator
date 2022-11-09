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

struct node_t {
        node_t *left  = nullptr;
        elem_t data   = nullptr;        //???
        node_t *right = nullptr;
        int new_node  =       0;
};

struct tree_t {
        node_t *root = nullptr;
        size_t size  =       0;
};

int tree_ctor (tree_t *tree);
int tree_insert (node_t *node, elem_t data);
int tree_dtor (tree_t *tree);
void free_nodes (node_t *node);
int tree_dump (tree_t *tree, const char *file_name, const char *func, const int line,
               const char *tree_name, FILE *log, const char *img);
int tree_error (tree_t *tree);


#endif /*TREE_H*/

#include <stdio.h>
#include <assert.h>
#include "tree.h"

// #define img_path C:\Users\taran\Desktop\X course\Akinator\graph.png
// #define tree_dump(list,html_log,graph_path) list_dump(tree, __FILE__,  __PRETTY_FUNCTION__,                    \
//                                                       __LINE__, #list, html_log, #graph_path)

#define $ fprintf(stderr, "I'm here. File %s Line %d\n", __FILE__, __LINE__);

int tree_ctor (tree_t *tree)
{
        assert(tree);

        tree->root = (node_t*) calloc(1, sizeof(node_t));
        if (!tree->root)
                return NULL_CALLOC;
        tree->size = 1;
        tree->root->atr = {};

        return 0;
}

node_t* tree_insert (tree_t *tree, node_t *node, elem_t data)
{
        if (!node)
                node = (node_t*) calloc(1, sizeof(node_t));
        // if (!node)
        //         return NULL_CALLOC;

        node->atr = {};
        node->data = data;
        node->indx = tree->size;
        tree->size++;
        node->new_node = 1;

        return node;
}

int tree_dtor (tree_t *tree)
{
        if (!tree)
                return NULL_TREE_PTR;
        free_nodes(tree->root);
        // free(tree);

        return 0;
}

void free_nodes (node_t *node)
{
        assert(node);

        if (node->left) {
                assert(node);
                assert(node->left);
                free_nodes(node->left);
        }
        if (node->right) {
                free_nodes(node->right);
        }
        if (node->new_node) {
                free(node);
        }
}

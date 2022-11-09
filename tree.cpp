#include <stdio.h>
#include <assert.h>
#include "tree.h"

// #define img_path C:\Users\taran\Desktop\X course\Akinator\graph.png
// #define tree_dump(list,html_log,graph_path) list_dump(tree, __FILE__,  __PRETTY_FUNCTION__,                    \
//                                                       __LINE__, #list, html_log, #graph_path)

int tree_ctor (tree_t *tree)
{
        assert(tree);

        tree->root = (node_t*) calloc(1, sizeof(node_t));
        if (!tree->root)
                return NULL_CALLOC;
        tree->size = 0;

        return 0;
}

int tree_insert (tree_t *tree, node_t *node, elem_t data)
{
        assert(node);

        *node = (node_t*) calloc(1, sizeof(node_t));
        if (!node)
                return NULL_CALLOC;
        node->data = data;
        tree->size++;
        node->new_node = 1;

        return 0;
}

int tree_dtor (tree_t *tree)
{
        if (!tree)
                return NULL_TREE_PTR;
        free_nodes(tree->root);
        free(tree);

        return 0;
}

void free_nodes (node_t *node)
{
        // tree_dump();

        if (node->left)
                free_nodes(node->left);
        if (node->right)
                free_nodes(node->right);
        if (node->new_node) {
                free(node);
        }

        return;
}

int tree_dump (tree_t *tree, const char *file_name, const char *func, const int line,
               const char *tree_name, FILE *log, const char *img)
{
        assert(tree);
        assert(log);

        static char *tree_errors[] = {
                "Tree pointer is null.",
                "Node pointer in tree is null.",
        };

        int errors = tree_error(tree);
        fprintf(log, "<pre>\n");

        if (!errors)
                return 0;

        for (int i = 0; (errors << i) != 0; i++) {
                switch (errors & ~(~0 << i + 1)) {                                                                      //1111 1111
                case NULL_TREE_PTR:                                                                                     //1111 1100
                        fprintf(log, "<p style=\"color:red;\">%s<\/p></pre>\n", tree_errors[i]);                        //0000 0011
                        return NULL_TREE_PTR;                                                                          //&0000 1010
                case NULL_ROOT_PTR:                                                                                     //0000 0010
                        fprintf(log, "<p style=\"color:red;\">%s<\/p></pre>\n", tree_errors[i]);
                        return NULL_ROOT_PTR;
                }
        }

        fprintf(log, "</pre>\n");

        return errors;
}

int tree_error (tree_t *tree)
{
        int errors = 0;
        if (tree == nullptr) {
                errors |= NULL_TREE_PTR;
        } else {
                if (tree->root == nullptr)
                        errors |= NULL_ROOT_PTR;
        }

        return errors;
}

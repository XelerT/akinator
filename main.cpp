#include <stdio.h>
#include <assert.h>
#include "tree.h"
#include "tree_dump.h"

int main ()
{
        tree_t tree = {};
        tree_ctor(&tree);
        char root_node[] = "root?";
        tree.root->data = root_node;

        for (int i = 0; i < 3; i++) {
                if (i % 2) {
                        tree.root->left = tree_insert(&tree, tree.root->left, "fucking left node");
                        assert(tree.root->left);
                } else
                        tree.root->right = tree_insert(&tree, tree.root->right, "fucking right node");
        }

        tree_graph(&tree);
        return 0;
}

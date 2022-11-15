#include <stdio.h>
#include <assert.h>
#include "tree.h"
#include "tree_dump.h"
#include "tree_text.h"

int main ()
{
        tree_t tree = {};
        text_t text = {};
        tree_ctor(&tree);
        FILE *akitree = fopen("akitree.txt", "r");
        get_text (akitree, &text);
        replace_n (&text);
        divide_text (&text);
        size_t line_count = 0;
        get_tree(&tree, tree.root, &text, &line_count);

        tree_graph(&tree);

        akinator(&tree);
        // tree_dtor(&tree);
        return 0;
}

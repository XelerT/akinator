#include <stdio.h>
#include <assert.h>
#include "tree.h"
#include "tree_dump.h"
#include "tree_text.h"
#include "akinator.h"

#define $ fprintf(stderr, "I'm here. File %s Line %d\n", __FILE__, __LINE__);
#define $

int main ()
{
        tree_t tree = {};
        text_t text = {};
        tree_ctor(&tree);
        FILE *akitree = fopen("akitree.txt", "r");
        if (!akinator) {
                fprintf(stderr, "File pointer is null. %d\n", __LINE__);
                return NULL_FILE_PTR;
        }
        int error = 0;
        if (error = get_text (akitree, &text))
                return error;
        replace_n (&text);
        divide_text (&text);
        size_t line_count = 0;
        get_tree(&tree, tree.root, &text, &line_count);

        if (error = akinator(&tree))
                return error;
        fclose(akitree);
        FILE *output = fopen("akitree.txt", "w");
        if (!output) {
                fprintf(stderr, "File pointer is null. %d\n", __LINE__);
                return NULL_FILE_PTR;
        }
        $
        tree2text(tree.root, output, 0);
        $
        tree_graph(&tree);

        fclose(output);
        tree_dtor(&tree);
        return 0;
}

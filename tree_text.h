#ifndef TEXT_TREE_H
#define TEXT_TREE_H

#include "tree.h"

struct line_t
{
        char *ptr = nullptr;
        size_t length = 0;
};

struct text_t {
        size_t n_lines = 0;
        size_t n_chars = 0;
        char *buf = nullptr;
        line_t *lines = nullptr;
};

const int MAX_LINE_LENGTH = 512;

void get_text (FILE *input, text_t *text);
void replace_n (text_t *text);
void divide_text (text_t *text);
void get_tree (tree_t *tree, node_t *node, text_t *text, size_t *line_count);
char* get_line(char *line);
char *skip_tabs (char *line);

#endif /*TEXT_TREE_H*/

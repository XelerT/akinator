#include <stdio.h>
#include <sys\stat.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include "tree_text.h"
#define $ fprintf(stderr, "I'm here. File %s Line %d\n", __FILE__, __LINE__);
// #define $

int get_text (FILE *input, text_t *text)
{
        if (!input) {
                fprintf(stderr, "File pointer is null. File: %s | Line: %d\n", __FILE__, __LINE__);
                return NULL_FILE_PTR;
        }
        if (!text) {
                fprintf(stderr, "Text pointer is null. File: %s | Line: %d\n", __FILE__, __LINE__);
                return NULL_TEXT_PTR;
        }

        struct stat file = {};
        if (stat("akitree.txt", &file) < 0)
                return FILE_ERR;

        size_t n_chars = 0;
        char *buf = (char*) calloc(file.st_size + 1, sizeof(char));
        if (!buf) {
                fprintf(stderr, "Calloc returned NULL. %d\n", __LINE__);
                return NULL_CALLOC;
        }

        n_chars = fread(buf, sizeof(char), file.st_size, input);
        text->n_chars = n_chars;

        text->buf = buf;
        text->n_lines = file.st_size - n_chars;
        if (!n_chars) {
                fprintf(stderr, "Input file is empty.\n");
                return EMPTY_FILE;
        }
        return 0;
}

void replace_n (text_t *text)
{
        if (!text) {
                fprintf(stderr, "Text pointer is null. File: %s | Line: %d\n", __FILE__, __LINE__);
                return;
        }

        char *buf = text->buf;

        for (size_t i = 0; i < text->n_chars; i++)
                if (text->buf[i] == '\n')
                        buf[i] = '\0';
}

void divide_text (text_t *text)
{
        if (!text) {
                fprintf(stderr, "Text pointer is null. File: %s | Line: %d\n", __FILE__, __LINE__);
                return;
        }

        char *buf = text->buf;
        buf[text->n_chars + 1] = '\0';

        line_t *lines = (line_t*) calloc(text->n_lines + 1, sizeof(line_t));
        if (!lines) {
                fprintf(stderr, "Calloc returned NULL. %d\n", __LINE__);
                return;
        }
        text->lines = lines;
        for (size_t i = 0; i < text->n_lines; i++) {
                lines[i].ptr = buf;
                while (*buf != '\n' && *buf != '\0')
                        buf++;
                buf++;
                lines[i].length = buf - lines[i].ptr;
        }
}

void get_tree (tree_t *tree, node_t *node, text_t *text, size_t *line_count)
{
        assert(tree);
        assert(node);
        assert(text->lines);
        assert(text->lines->ptr);

        line_t *lines = text->lines;

        node->data = get_line((lines + *line_count)->ptr);

        if (!strrchr((lines + *line_count)->ptr, '}')) {
                (*line_count)++;
                node->right = tree_insert(tree, node->right, get_line((lines + *line_count)->ptr));
                node->left = tree_insert(tree, node->left, "adas");
                get_tree(tree, node->right, text, line_count);
                get_tree(tree, node->left, text, line_count);
                (*line_count)++;
        } else if (*line_count < text->n_lines - 1) {
                (*line_count)++;
        }
}

char* get_line(char *line)
{
        assert(line);

        char *ret_line = (char*) calloc(MAX_LINE_LENGTH, sizeof(char));
        int   n_chars  = 0;
        if (!ret_line)
                fprintf(stderr, "Null calloc ptr. %s %d\n", __FILE__, __LINE__);

        line = skip_tabs(line);
        line+= 2;
        if (!sscanf(line, "[%[^]]%n", ret_line, &n_chars))
                fprintf(stderr, "Null line ptr. %s %d\n", __FILE__, __LINE__);
        if (n_chars > MAX_LINE_LENGTH)
                fprintf(stderr, "Line in file is too long(%d chars). %s %d\n", n_chars, __FILE__, __LINE__);

        return ret_line;
}

char *skip_tabs (char *line)
{
        assert(line);

        while (isspace(*line))
                line++;
        return line;
}

int tree2text (node_t *node, FILE *output, int n_tabs)
{
        assert(node);
        assert(output);
$
        if (node->right) {
                print_tabs(output, n_tabs);
                fprintf(output, "{ [%s] \n", node->data);
                tree2text(node->right, output, n_tabs + 1);
                tree2text(node->left,  output, n_tabs + 1);
                print_tabs(output, n_tabs);
                fprintf(output, "}\n");
        } else {
                print_tabs(output, n_tabs);
                fprintf(output, "{ [%s] }\n", node->data);
        }
$
        return 0;
}

void print_tabs (FILE *output, int n_tabs)
{
        assert(output);

        for (int i = 0; i < n_tabs; i++)
                fprintf(output, "\t");
}

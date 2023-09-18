#include <assert.h>
#include <stdio.h>
#include <sys/stat.h>

#include "print.h"
#include "sort.h"
#include "process_file.h"

void line_count (struct Buffer* array, struct Lines* lines)
{
    assert (array != NULL);
    assert (array -> buffer != NULL);
    for (size_t i = 0; i < array -> size; i++)
    {
        if (array -> buffer[i] == '\n')
            lines -> line_count++;
    }
}

int get_file_size (struct File* file, struct Buffer* array)
{
    assert (file != NULL);

    struct stat st = {};

    if (stat(file -> filename, &st) == -1)
    {
        printf ("Error: could not stat the file");
        return -1;
    }

    array -> size = st.st_size;
}

void read_file_in_buffer (FILE *fp, struct Buffer* array)
{
    assert (array != NULL);
    assert (array -> buffer != NULL);

    size_t nread = fread (array -> buffer, sizeof(char), array -> size, fp);
    assert(nread == array -> size);

    fclose (fp);
}

void fill_text_and_count_line (struct Buffer* array, struct Lines* lines)
{
    assert (lines != NULL);
    assert (array != NULL);
    assert (lines -> text != NULL);
    assert (array -> buffer != NULL);

    size_t line1 = 0;
    lines -> text[line1++] = array -> buffer;

    for (int i = 0; i < array -> size; i++)
    {
        if (array -> buffer[i] == '\n')
        {
            array -> buffer[i] = '\0';
            lines -> text[line1] = &array -> buffer[i + 1];
            line1++;
        }
    }

    if (array -> size > 0 && array -> buffer[array -> size - 1] != '\n')
    {
        array -> buffer[array -> size] = '\0';
    }
}

void free_buffer (struct Buffer* array, struct Lines* lines)
{
    free (array -> buffer);
    free (lines -> text);
}

FILE* open_file(const char* filename, const char* mode)
 {
    FILE* fp = fopen(filename, mode);
    if (fp == NULL)
    {
        printf("Cannot open file '%s'.\n", filename);
        return NULL;
    }
    return fp;
}

void process_file (struct Buffer* array, struct Lines* lines)
{
    File file = {
        "Onegin.txt",
    };

    FILE *fp = fopen(file.filename, "rb");

    get_file_size (&file, array);
    array -> buffer = (char*)calloc(array -> size + 1, sizeof(char));
    read_file_in_buffer (fp, array);
    line_count (array, lines);

    lines -> text = (char**)calloc (lines -> line_count, sizeof(char*));
    fill_text_and_count_line (array, lines);
}


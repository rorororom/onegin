#include <assert.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

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

    return st.st_size;
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

void print_text_to_output(const char *outputFilename, struct Lines *lines, StringInfo *stringArray)
{
    FILE *outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Ошибка: не удалось открыть файл для записи\n");
        exit(EXIT_FAILURE);
    }

    print_text (lines, stringArray, outputFile);
    fclose (outputFile);
}


StringInfo *creat_string (struct Lines* lines)
{

    StringInfo *stringArray = (StringInfo *)calloc(lines->line_count, sizeof(StringInfo));
    if (stringArray == NULL)
    {
        perror("Ошибка выделения памяти для stringArray");
    }
    for (int i = 0; i < lines->line_count; i++)
    {
        stringArray[i].pointer = lines->text[i];
        stringArray[i].length = strlen(lines->text[i]);
    }
    return stringArray;
}

void process_sort_and_print(struct Lines *lines, StringInfo *stringArray)
{
    File file_output = {
        "output_sort.txt",
    };
    print_text_to_output(file_output.filename, lines, stringArray);

    sort_text(lines, stringArray);
    File file_output_sort = {
        "output_sort.txt",
    };
    print_text_to_output(file_output_sort.filename, lines, stringArray);

    sort_text_reverse(lines, stringArray);
    File file_output_sort_reverse = {
        "output_sort_reverse.txt",
    };
    print_text_to_output(file_output_sort_reverse.filename, lines, stringArray);
}

void process_file (struct Buffer* array, struct Lines* lines, const char* filename)
{
    File file = {
        filename,
    };

    FILE *fp = fopen(file.filename, "rb");

    get_file_size (&file, array);
    array -> buffer = (char*)calloc(array -> size + 1, sizeof(char));

    read_file_in_buffer (fp, array);
    line_count (array, lines);
    lines -> text = (char**)calloc (lines -> line_count, sizeof(char*));
    fill_text_and_count_line (array, lines);

    fclose(fp);

    size_t i = 0;

    StringInfo *stringArray  = creat_string (lines);
    StringInfo *buf = creat_string (lines);

    process_sort_and_print(lines, stringArray);
}


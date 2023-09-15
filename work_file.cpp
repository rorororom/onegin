#include <assert.h>
#include <stdio.h>
#include <sys/stat.h>

#include "print.h"
#include "sort.h"
#include "work_file.h"

void line_count (struct File* file)
{
    assert (file != NULL);
    assert (file -> buffer != NULL);
    for (size_t i = 0; i < file -> size; i++)
    {
        if (file -> buffer[i] == '\n')
            file -> line_count++;
    }
}

int get_file_size (struct File* file)
{
    assert (file != NULL);

    struct stat st = {};

    if (stat(file -> filename, &st) == -1)
    {
        printf ("Error: could not stat the file");
        return -1;
    }

    file -> size = st.st_size;
}

 void read_file_in_buffer (FILE *fp, struct File* file) // TODO: add asserts in all function
{
    assert (file != NULL);
    assert (file -> buffer != NULL);

    size_t nread = fread (file -> buffer, sizeof(char), file -> size, fp);
    assert(nread == file -> size);

    fclose (fp);
}

void fill_text_and_count_line (struct File* file)
{
    assert (file != NULL);
    assert (file -> text != NULL);
    assert (file -> buffer != NULL);

    size_t line1 = 0;
    file -> text[line1++] = file-> buffer;

    for (int i = 0; i < file -> size; i++)
    {
        if (file -> buffer[i] == '\n') // TODO: add finish \0 and check last string
        {
            file -> buffer[i] = '\0';
            file -> text[line1] = &file -> buffer[i + 1];
            line1++;
        }
    }
}

void free_fail (struct File* file)
{
    free (file -> buffer);
    free (file -> text);
}

int work_file ()
{
    File file = {
        "Onegin.txt",
        NULL,
        0,
        NULL,
        0
    };

    FILE *fp = fopen(file.filename, "rb");
    if (fp == NULL)
    {
        printf("Cannot open source file.\n");
        return 1;//enum
    }

    get_file_size (&file);
    file.buffer = (char*)calloc(file.size + 1, sizeof(char));
    read_file_in_buffer (fp, &file);
    line_count (&file);

    file.text = (char**)calloc (file.line_count, sizeof(char*));
    fill_text_and_count_line (&file);

    sort_text (&file);
    print (&file);

    print_indentation ();

    sort_text_reverse (&file);
    print (&file);

    fill_text_and_count_line (&file); // TODO:

    print_indentation ();

    print_all_text (&file);
    free_fail (&file); // TODO: RENAME destruct file
}

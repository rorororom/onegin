#include <assert.h>
#include <stdio.h>

#include "work_file.h"
#include "print.h"

void print_all_text (struct File* file)
{
    for (int i = 0; i < file -> size; i++)
    {
        if (file -> buffer[i] == '\0')
        {
            file -> buffer[i] = '\n';
        }
    }

    printf ("%s\n", file -> buffer);
}

void print_text (struct File* file)
{
    for (int i = 0; i < file -> line_count; ++i)
    {
        printf ("%s \n", file -> text[i]);
    }
}

void print (struct File* file)
{
    print_text (file);
}

void print_indentation ()
{
    for (int i = 0; i < 20; i++)
        printf ("\n");
}





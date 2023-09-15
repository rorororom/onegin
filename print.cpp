#include <assert.h>
#include <stdio.h>

#include "process_file.h"
#include "print.h"

void print_all_text (struct Buffer* array)
{
    for (int i = 0; i < array -> size; i++)
    {
        if (array -> buffer[i] == '\0')
        {
            array -> buffer[i] = '\n';
        }
    }

    printf ("%s\n", array -> buffer);
}

void print_text (struct Lines* lines)
{
    for (int i = 0; i < lines -> line_count; ++i)
    {
        printf ("%s \n", lines -> text[i]);
    }
}

void print (struct Lines* lines)
{
    print_text (lines);
}

void print_indentation ()
{
    for (int i = 0; i < 20; i++)
        printf ("\n");
}





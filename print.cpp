#include <assert.h>
#include <stdio.h>

#include "process_file.h"
#include "print.h"

void print_all_text (struct Buffer* array, FILE *outputFile)
{
    for (int i = 0; i < array -> size; i++)
    {
        if (array -> buffer[i] == '\0')
        {
            array -> buffer[i] = '\n';
        }
    }

    fprintf (outputFile, "%s\n", array -> buffer);

    for (int i = 0; i < array -> size; i++)
    {
        if (array -> buffer[i] == '\n')
        {
            array -> buffer[i] = '\0';
        }
    }
}

void print_text (struct Lines* lines, struct StringInfo* stringArray, FILE *outputFile)
{
    for (int i = 0; i < lines -> line_count; ++i)
    {
        fprintf (outputFile, "%s \n", stringArray[i].pointer);
    }
}

void print (struct Lines* lines, struct StringInfo* stringArray, FILE *outputFile)
{
    print_text (lines, stringArray, outputFile);
}

void print_indentation (FILE *outputFile)
{
    for (int i = 0; i < 20; i++)
        fprintf (outputFile, "\n");
}





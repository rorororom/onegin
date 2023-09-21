#include <stdio.h>

#include "print.h"
#include "process_file.h"
#include "sort.h"

int main (int argc, char* argv[])
{
    if (argc != 2) {
        printf("Использование: %s <имя_файла>\n", argv[0]);
        return ERROR;
    }
    //

    const char *filename = argv[1];

    setbuf (stdout, NULL);
    Lines lines = {
        NULL,
        0,
    };

    Buffer array = {
        NULL,
        0,
    };

    process_file (&array, &lines, filename);

    free_buffer (&array, &lines);
}

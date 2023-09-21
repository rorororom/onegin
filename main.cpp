#include <stdio.h>

#include "print.h"
#include "process_file.h"
#include "sort.h"

int main ()
{
    setbuf (stdout, NULL);
    Lines lines = {
        NULL,
        0,
    };

    Buffer array = {
        NULL,
        0,
    };

    process_file (&array, &lines);

    free_buffer (&array, &lines);
}

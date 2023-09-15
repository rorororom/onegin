#include <stdio.h>

#include "print.h"
#include "process_file.h"
#include "sort.h"

int main ()
{
    Lines lines = {
        NULL,
        0,
    };

    Buffer array = {
        NULL,
        0,
    };

    process_file (&array, &lines);

    sort_text (&lines);
    print (&lines);
    print_indentation ();

    sort_text_reverse (&lines);
    print (&lines);

    print_indentation ();
    print_all_text (&array);

    free_buffer (&array, &lines);
}

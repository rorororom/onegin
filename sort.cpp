#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <cctype>

#include "sort.h"
#include "process_file.h"

void sort_text (struct Lines* lines)
{
    assert (lines -> text != NULL);

    my_qsort (lines, 0, lines -> line_count - 1, compare_strings);
}

void sort_text_reverse (struct Lines* lines)
{
    assert (lines -> text != NULL);

    my_qsort (lines, 0, lines -> line_count - 1, compare_strings_reverse);
}

void my_qsort(struct Lines* lines, int left, int right, int (*compare)(const char*, const char*))
{
    assert (lines != NULL);
    assert (lines -> text!= NULL);
    assert (left >= 0);
    assert (right >= 0);

    if (left < right)
    {
        int i = left, j = right;
        char* pivot = lines -> text[(right + left) / 2];

        while (i < j)
        {
            while (compare(lines -> text[i], pivot) < 0)
            {
                i++;
            }
            while (compare(lines -> text[j], pivot) > 0)
            {
                j--;
            }
            if (i < j)
            {
                char* temp = lines -> text[i];
                lines -> text[i] = lines -> text[j];
                lines -> text[j] = temp;
            }

            i++;
            j--;
        }

        if (left < j)
        {
            my_qsort(lines, left, j, compare);
        }

        if (i < right)
        {
            my_qsort(lines, i, right, compare);
        }
    }
}

int compare_strings(const char* a, const char* b) {
    assert (a != NULL);
    assert (b != NULL);

    const char* str1 = (const char*)a;
    const char* str2 = (const char*)b;

    while (*str1 && *str2)
    {
        while (!(isalpha (*str1)))
        {
            str1++;
        }

        while (!(isalpha (*str2)))
        {
            str2++;
        }

        int cmp = compare_letters (*str1, *str2);
        if (cmp != 0) return cmp;

        str1++;
        str2++;
    }

    return compare_letters (*str1, *str2);
}

int compare_strings_reverse (const char* a, const char* b)
{
    assert (a != NULL);
    assert (b != NULL);

    const char* str1 = (const char*)a;
    const char* str2 = (const char*)b;

    const char* p1 = str1 + strlen (str1) - 1;
    const char* p2 = str2 + strlen (str2) - 1;

    while (p1 >= str1 && p2 >= str2)
    {
        while (!(isalpha (*p1)))
        {
            p1--;
            continue;
        }
        while (!(isalpha (*p2)))
        {
            p2--;
            continue;
        }
        int cmp = compare_letters (*p1, *p2);
        if (cmp != 0) return cmp;

        p1--;
        p2--;
    }

    return compare_letters (*p1, *p2);;
}

int compare_letters (char ch1, char ch2)
{
    ch1 = tolower (ch1);
    ch2 = tolower (ch2);

    if (ch1 < ch2)
    {
        return -1;
    }
    else if (ch1 > ch2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

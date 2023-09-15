#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <cctype>

#include "sort.h"
#include "work_file.h"

void sort_text (struct File* file)
{
    assert (file -> text != NULL);

    my_qsort(file, 0, file -> line_count - 1);
}

void sort_text_reverse (struct File* file)
{
    assert (file -> text != NULL);

    myQSort_reverse (file, 0, file -> line_count - 1);
}

void my_qsort(struct File *file, int left, int right)
{
    assert (file != NULL);
    assert (file -> text!= NULL);
    assert (left >= 0);
    assert (right >= 0);

    if (left < right)
    {
        int i = left, j = right;
        char* pivot = file -> text[(right + left) / 2];

        while (i < j)
        {
            while (compareStrings(file -> text[i], pivot) < 0)
            {
                i++;
            }
            while (compareStrings(file -> text[j], pivot) > 0)
            {
                j--;
            }
            if (i < j)
            {
                char* temp = file -> text[i];
                file -> text[i] = file -> text[j];
                file -> text[j] = temp;
            }

            i++;
            j--;
        }

        if (left < j)
        {
            my_qsort(file, left, j);
        }

        if (i < right)
        {
            my_qsort(file, i, right);
        }
    }
}

void myQSort_reverse(struct File* file, int left, int right)
{
    assert (file != NULL);
    assert (file->text != NULL);
    assert (left >= 0);
    assert (right >= 0);

    if (left < right)
    {
        int i = left, j = right;
        char* pivot = file -> text[(right + left) / 2];

        while (i <= j)
        {
            while (compareStrings_reverse(file -> text[i], pivot) < 0) {
                i++;
            }
            while (compareStrings_reverse(file -> text[j], pivot) > 0) {
                j--;
            }
            if (i <= j)
            {
                char* temp = file -> text[i];
                file->text[i] = file -> text[j];
                file->text[j] = temp;
                i++;
                j--;
            }
            if (i < left && j > right)
            {
                break;
            }
        }

        if (left < j)
        {
            myQSort_reverse(file, left, j);
        }
        if (i < right)
        {
            myQSort_reverse(file, i, right);
        }
    }
}

int compareStrings(const char* a, const char* b) {
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

int compareStrings_reverse (const char* a, const char* b)
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

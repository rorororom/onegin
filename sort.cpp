#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "sort.h"
#include "process_file.h"

void sort_text(struct Lines* lines, struct StringInfo* stringArray)
{
    assert(lines != NULL);
    assert(lines->text != NULL);
    assert(stringArray != NULL);
    assert(lines->line_count >= 0);

    my_qsort(lines, 0, lines->line_count - 1, compare_strings, stringArray);
}

void sort_text_reverse(struct Lines* lines, struct StringInfo* stringArray)
{
    assert(lines != NULL);
    assert(lines->text != NULL);
    assert(stringArray != NULL);
    assert(lines->line_count >= 0);

    my_qsort(lines, 0, lines->line_count - 1, compare_strings_reverse, stringArray);
}

void my_qsort(struct Lines* lines, int left, int right, int (*compare)(const void*, const void*), struct StringInfo* stringArray)
{
    assert(lines != NULL);
    assert(stringArray != NULL);
    assert(left >= 0);
    assert(right >= 0);
    assert(left <= right);

    if (left >= right)
    {
        return;
    }
    printf ("first - %d, second - %d\n", left, right);


    int i = left;
    int j = right;
    char* pivot = stringArray[(left + right) / 2].pointer;
    printf ("first - %d, second - %d\n", i, j);

    while (i <= j)
    {
        printf ("first - %d, second - %d\n", i, j);
        while (compare(stringArray[i].pointer, pivot) < 0)
        {
            i++;
            printf ("i - %d, j - %d\n", i, j);
        }
        while (compare(stringArray[j].pointer, pivot) > 0)
        {
            j--;
        }
        if (i <= j)
        {
            zamena(stringArray, i, j);
            i++;
            j--;
        }
    }

    my_qsort(lines, left, j, compare, stringArray);
    my_qsort(lines, i, right, compare, stringArray);
}


int compare_strings(const void *a, const void *b) {
    assert(a != NULL);
    assert(b != NULL);

    const struct StringInfo *srt1 = (const struct StringInfo *)a;
    const struct StringInfo *srt2 = (const struct StringInfo *)b;

    int first = 0;
    int second = 0;

    printf ("first - %d, second - %d, str1 - %s, str2 - %s\n", first, second, srt1 -> pointer, srt2 -> pointer);

    while (true)
    {
        while ((srt1 -> pointer)[first] != '\0' && isalpha((srt1 -> pointer)[first]) == 0)
        {
            printf ("first - %d, second - %d, str1 - %s, str2 - %s\n", first, second, srt1 -> pointer, srt2 -> pointer);
            first++;
        }
        while ((srt2 -> pointer)[second] != '\0' && isalpha((srt2 -> pointer)[second]) == 0)
        {
            second++;
        }
        if (tolower((srt1 -> pointer)[first]) == tolower((srt2 -> pointer)[second]) && (srt2 -> pointer)[first] != '\0')
        {
            first++;
            second++;
            continue;
        }
        break;
    }

    return tolower((srt1 -> pointer)[first]) - tolower((srt2 -> pointer)[second]);
}

int compare_strings_reverse(const void* a, const void* b) {
    assert(a != NULL);
    assert(b != NULL);

    const struct StringInfo *srt1 = (const struct StringInfo *)a;
    const struct StringInfo *srt2 = (const struct StringInfo *)b;

    int first = (srt1 -> length) - 1;
    int second = (srt2 -> length) - 1;

    while (true)
    {
        while ((first >= 0) && isalpha((srt1 -> pointer)[first]) == 0)
        {
            first--;
        }
        while ((second >= 0) && isalpha((srt2 -> pointer)[second]) == 0)
        {
            second--;
        }
        if (tolower((srt1 -> pointer)[first]) == tolower((srt2 -> pointer)[second]) && (first >= 0))
        {
            first--;
            second--;
            continue;
        }
        break;
    }

    return tolower((srt1-> pointer)[first]) - tolower((srt2 -> pointer)[second]);
}


int zamena(struct StringInfo* stringArray, int left, int right) {
    struct StringInfo temp = stringArray[left];
    stringArray[left] = stringArray[right];
    stringArray[right] = temp;
}

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

    my_qsort(0, lines->line_count - 1, compare_strings, stringArray);
}

void sort_text_reverse(struct Lines* lines, struct StringInfo* stringArray)
{
    assert(lines != NULL);
    assert(lines->text != NULL);
    assert(stringArray != NULL);
    assert(lines->line_count >= 0);

    my_qsort(0, lines->line_count - 1, compare_strings_reverse, stringArray);
}

void my_qsort(int left, int right, int (*compare)(const void*, const void*), struct StringInfo* stringArray)
{
    if (right - left <= 0)
    {
        return;
    }
    assert(stringArray != NULL);
    assert(left >= 0);
    assert(right >= 0);
    assert(left <= right);

    if (left >= right)
    {
        return;
    }


    int i = left;
    int j = right;
    StringInfo pivot = stringArray[(left + right) / 2];

    while (i < j)
    {
        while (i < right && compare(&stringArray[i], &pivot) < 0)
        {
            i++;
        }
        while (j >= 0 && compare(&stringArray[j], &pivot) > 0)
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


    my_qsort(left, j, compare, stringArray);
    my_qsort(i, right, compare, stringArray);
}


int compare_strings(const void *a, const void *b) {
    assert(a != NULL);
    assert(b != NULL);

    const struct StringInfo *srt1 = (const struct StringInfo *)a;
    const struct StringInfo *srt2 = (const struct StringInfo *)b;

    int first = 0;
    int second = 0;

    while (true)
    {
        while ((srt1 -> pointer)[first] != '\0' && isalpha((srt1 -> pointer)[first]) == 0)
        {
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

    return 0;
}

#ifndef SORT_H
#define SORT_H

void sort_text(struct Lines* lines, struct StringInfo* stringArray);
void sort_text_reverse(struct Lines* lines, struct StringInfo* stringArray);

void my_qsort(int left, int right, int (*compare)(const void*, const void*), struct StringInfo* stringArray);

int compare_strings(const void* a, const void* b);
int compare_strings_reverse(const void* a, const void* b);

int zamena (struct StringInfo* stringArray, int left, int right);

#endif // SORT_H

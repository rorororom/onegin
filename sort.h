#ifndef SORT_H
#define SORT_H

void sort_text (struct Lines* lines);
void sort_text_reverse (struct Lines* lines);

void my_qsort(struct Lines* lines, int left, int right, int (*compare)(const char*, const char*));

int compare_strings_reverse (const char* a, const char* b);
int compare_strings(const char* a, const char* b);
int compare_letters (char ch1, char ch2);

#endif // SORT_H

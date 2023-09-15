#ifndef SORT_H
#define SORT_H

void sort_text (struct File* file);
void sort_text_reverse (struct File* file);

void my_qsort(struct File* file, int left, int right);
void myQSort_reverse(struct File* file, int left, int right); // TODO: rename

int compareStrings_reverse (const char* a, const char* b);
int compareStrings(const char* a, const char* b);
int compare_letters (char ch1, char ch2);

#endif // SORT_H

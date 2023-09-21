#ifndef PRINT_H
#define PRINT_H

void print_all_text (struct Buffer* array, FILE *outputFile);
void print (struct Lines* lines, struct StringInfo* stringArray, FILE *outputFile);
void print_text (struct Lines* lines, struct StringInfo* stringArray, FILE *outputFile);
void print_indentation (FILE *outputFile);

#endif

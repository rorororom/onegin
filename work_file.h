#ifndef WORK_FILE_H
#define WORK_FILE_H

struct File {
    const char *filename;
    char *buffer; // struct buffer
    size_t size;
    char **text; // struct lines
    size_t line_count;
};

void line_count (struct File* file);
int get_file_size (struct File* file);
void read_file_in_buffer (FILE *fp, struct File* file);
void fill_text_and_count_line (struct File* file);
int work_file ();

#endif

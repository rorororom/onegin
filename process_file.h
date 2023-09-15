#ifndef WORK_FILE_H
#define WORK_FILE_H

enum eroor {
    ERROR = -1
};

struct File{
    const char *filename;
    char *buffer;
    size_t size;
    char **text;
    size_t line_count;
};

struct Buffer {
    char *buffer;
    size_t size;
};

struct Lines {
    char **text;
    size_t line_count;
};

void line_count (struct Buffer* array, struct Lines* lines);
int get_file_size (struct File* file, struct Buffer* array);
void read_file_in_buffer (FILE *fp, struct Buffer* array);
void fill_text_and_count_line (struct Buffer* array, struct Lines* lines);
void free_buffer (struct Buffer* array, struct Lines* lines);
FILE* open_file(const char* filename, const char* mode);
void process_file (struct Buffer* array, struct Lines* lines);

#endif

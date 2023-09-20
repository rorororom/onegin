#include <stdio.h>

#include "process_file.cpp"

int lof_file() {
    FILE *log_file = fopen("my_log.txt", "w");
    if (log_file == NULL) {
        perror("Не удалось открыть файл((((");
        return ERROR;
    }

    fprintf(log_file, "Файл открыт)\n");

    fclose(log_file);
    return 0;
}

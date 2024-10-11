#include <stdio.h>
#include <string.h>
#include <errno.h>

#ifndef DATABASE_FILE
#define DATABASE_FILE "database.csv"
#endif

int main(int argc, char * argv[])
{
    if (argc < 2) {
        printf("Usage: %s term\nReturn an emoji corresponding to provided term.\n", argv[0]);
        return 0;
    }

    FILE *csv_file = fopen(DATABASE_FILE, "r");
    if (!csv_file) {
        printf("Error: Could not open %s.\n", DATABASE_FILE);
        return ENOENT;
    }

    char *csv_word;
    char *emoji = NULL;

    // don't care about buffer overflows, this is a strictly personal tool
    for (char line[255]; fgets(line, sizeof(line), csv_file); ) {
        csv_word = strtok(line, ",");

        // do we have a match?
        if (strcmp(csv_word, argv[1]) == 0) {
            emoji = strtok(NULL, ",\n");
            break;
        }
    }

    fclose(csv_file);

    if (!emoji) {
        printf("No emoji found\n");
        return EAGAIN;
    }

    printf("%s\n", emoji);

    return 0;
}

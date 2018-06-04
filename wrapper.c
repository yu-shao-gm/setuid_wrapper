#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

int main (int argc, char *argv[])
{
    setuid(0);

    int i;
    size_t size;

    size = 1;
    for (i = 1; i < argc; i++) {
        size += strlen(argv[i]) + 1;
    }

    char *arguments = malloc(size);

    if (!arguments) {
        fprintf(stderr, "No memory\n");
        return 2;
    }

    size = 0;

    for (i = 1; i < argc; i++) {
        size += sprintf(arguments + size, "%s ", argv[i]);
        assert(arguments[size] == '\0');
    }

    arguments[--size] = '\0';
    system(strcat(strcat(argv[0], ".sh "), arguments));

    free(arguments);
    return 0;
}

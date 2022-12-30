#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFBUMP 1024

char ** split_line(char *line)
{
    int bufsize = BUFBUMP;
    int position = 0;
    char **tokens = malloc(sizeof(char) * bufsize);
    char *token;

    token = strtok(line, " ");

    if (!tokens) 
    {
        fprintf(stderr, "ERROR3: allocation point\n");
        exit(EXIT_FAILURE);
    }

    while (token != NULL) 
    {
        tokens[position] = token;

        ++position;

        token = strtok(NULL, " ");

        // If we have exceeded the carray, reallocate.
        if (position >= bufsize) 
        {
            bufsize += BUFBUMP;
            tokens = realloc(tokens, bufsize);

            if (!tokens) 
            {
                fprintf(stderr, "ERROR4: allocation point\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    tokens[position] = NULL;
    return tokens;
}

char *read_line(void)
{
    int bufsize = BUFBUMP;
    int position = 0;
    char *carray = malloc(sizeof(char) * bufsize);
    int c;

    if (!carray) 
    {
        fprintf(stderr, "ERROR1: allocation point\n");
        exit(EXIT_FAILURE);
    }

    while (1) 
    {
        // Read a character
        c = getchar();

        // If we hit EOF, replace it with a null character and return.
        if (c == EOF || c == '\n') 
        {
            carray[position] = '\0';
            return carray;
        } 

        else {
            carray[position] = c;
        }

        ++position;

        // If we have exceeded the carray, reallocate.
        if (position >= bufsize) 
        {
            bufsize += BUFBUMP;
            carray = realloc(carray, bufsize);

            if (!carray) 
            {
                fprintf(stderr, "ERROR2: allocation point\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

void loop()
{
    char *line;
    char** args;
    int position = 0;

    do {
        printf("csis> ");
        line = read_line();
        args = split_line(line);
        while(args[position] != NULL)
        {
            printf("%s\n", args[position]);
            ++position;
        }
        position = 0;
    } while (1);
}

int main(int argc, char **argv)
{
    loop();

    return EXIT_SUCCESS;
}

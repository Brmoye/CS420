#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFBUMP 1024

int execute(char **args)
{
    pid_t pid, wpid;
    int status;

    if(strcmp(args[0],"exit") == 0)
    {
        return 0;
    }

    pid = fork();
    if (pid == 0) {
        execvp(args[0], args);
        exit(EXIT_FAILURE);
    } 
    else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }  
    return 1;
}

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
    int status = 1;

    do {
        printf("csis> ");
        line = read_line();
        args = split_line(line);
        
        status = execute(args);
    } while (status);
}

int main(int argc, char **argv)
{
    loop();

    return EXIT_SUCCESS;
}

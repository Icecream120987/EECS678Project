#include "main.h"


//ac is the argument counter and **argv is the array of strings 
int main (int ac, char **argv){
    char *prompt = "[QUASH]$ ";
    char *lineptr = NULL, *lineptr_copy = NULL;
    size_t n = 0;
    size_t char_read;
    const char *delim = " \n";
    int num_tokens = 0;
    char *token;
    int i;

    (void)ac; (void)argv;
    while(1){
        printf("%s", prompt);
        char_read = getline(&lineptr, &n, stdin);
        //getline allocated memories dynamically
        if (char_read == -1){
            printf("Exiting...\n");
            //return (-1);
        }
        lineptr_copy = malloc(sizeof(char) * char_read);
        if (lineptr_copy == NULL){
            perror("tsh: memory allocation error");
            //return (-1);
        }

        strcpy(lineptr_copy, lineptr);
        //printf("%s\n", lineptr);

        token = strtok(lineptr, delim);

        while (token != NULL){
            num_tokens++;
            token = strtok(NULL, delim);
        }

        num_tokens++;

        argv = malloc(sizeof(char *) * num_tokens);

        token = strtok(lineptr_copy, delim);

        for (i = 0; token != NULL; i++){
            argv[i] = malloc(sizeof(char) * strlen(token));
            strcpy(argv[i], token);

            token = strtok(NULL, delim);
        }
        argv[i] = NULL;
        execmd(argv);
    }
    free(lineptr_copy);
    free(lineptr);

    return 0;
}
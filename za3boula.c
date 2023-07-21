#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pipe_strings(char* input, char* output, size_t output_size)
{
    // Keep reading input until NULL character is reached or output is full
    while (*input != '\0' && output_size > 1)
    {
        // Copy current character from input to output
        *output = *input;

        // Move to next character in both input and output strings
        input++;
        output++;
        output_size--;

        // Add NULL character to end of output string
        *output = '\0';
    }
}

int main()
{
    char* line[2];
    line[0] = malloc(sizeof(char) * 1024);
    line[1] = malloc(sizeof(char) * 1024);

    // Read input string from user
    printf("Enter a string: ");
    fgets(line[1], 1024, stdin);

    // Remove newline character from input string
    line[1][strlen(line[1]) - 1] = '\0';

    // Pass input string to pipe_strings function
    pipe_strings(line[1], line[0], 1024);

    // Print output string
    printf("Output: %s\n", line[0]);

    // Free memory allocated for strings
    free(line[0]);
    free(line[1]);

    return 0;
}

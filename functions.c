#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

// Function to make an array of structures
void make_aos(int *wordlist_size, struct words **wordlist)
{   
    // Allocate memory for the array of structures
    *wordlist = malloc(sizeof(struct words) * (*wordlist_size));
    
    // Check if memory is allocated
    if (*wordlist == NULL)
    {
        printf("Error: Unable to allocate memory\n");
        exit(1);
    }
}

// Function to read data from the file and store it in an array of structures
void get_data(char *file_name,int *wordlist_size, struct words **wordlist)
{
    // Open the file
    FILE *file = fopen(file_name, "r");

    // Check if the file is opened
    if (file == NULL)
    {
        printf("Error: Unable to open file %s\n", file_name);
        exit(1);
    }

    // array to store one line of the file 
    char line[200];
    // counter to keep track of the number of words(lines)
    int c = 0;

    // Read the file line by line
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Check if the array is full
        if (c >= *wordlist_size)
        {
            // Increase the size of the array by 1000
            *wordlist_size += 1000;
            // Reallocate memory for the array
            *wordlist = realloc(*wordlist, sizeof(struct words) * (*wordlist_size));

            // Check if memory is allocated
            if (*wordlist == NULL)
            {
                printf("Error: Unable to allocate memory\n");
                exit(1);
            }

        }

        // Structure to store the data
        struct words new_word;

        // Tokenize the line
        char *token = strtok(line, " \t\n");

        // Store the data in the structure
        new_word.word = strdup(token);

        token = strtok(NULL, " \t\n");
        new_word.score = atof(token);

        token = strtok(NULL, " \t\n");
        new_word.SD = atof(token);

        // Tokenize the SIS array
        char *arr_token = strtok(NULL, ", []\t\n");
        int i = 0;

        // Store the SIS array in the structure
        while (arr_token != NULL)
        {
            new_word.SIS_array[i] = atoi(arr_token);
            arr_token = strtok(NULL, ", []\t\n");
            i++;
        }

        // Store the structure in the array
        (*wordlist)[c] = new_word;
        c++;

    }
    // Close the file
    fclose(file);
}

// Function to free memory allocated for the array of structures
void free_data(struct words *wordlist)
{
    // Free the memory allocated for each word
    for (int i = 0; wordlist[i].word != NULL; i++) {
        free(wordlist[i].word);
    }
    // Free the memory allocated for the array
    free(wordlist);
}

// Function to perform Sentiment Analysis using VADER
void sentiment_analysis(struct words *wordlist, char *validation_file)
{
    // Open the validation file
    FILE *val_file = fopen(validation_file, "r");

    // Check if the file is opened
    if (val_file == NULL)
    {
        printf("Error: Unable to open file %s\n", validation_file);
        exit(1);
    }

    // Read the file line by line
    char line[200];

    // Perform the sentiment analysis
    while (fgets(line, sizeof(line), val_file) != NULL)
    {
        // Variables to store the total score and the number of words in each line
        float total_score = 0;
        int c = 0;
        
        // Copy the line to another variable
        char line_copy[200];
        strcpy(line_copy, line);

        // Remove the newline character put by fgets
        line_copy[strlen(line_copy) - 1] = '\0';

        // Convert the line to lowercase
        for (int i = 0; line[i] != '\0'; i++)
        {
            line[i] = tolower(line[i]);
        }
        
        // Tokenize the line
        char *token = strtok(line, " \n\t!,.");

        // Calculate the total score
        while (token != NULL)
        {
            // iterate through the wordlist
            for (int i = 0; wordlist[i].word != NULL; i++)
            {
                // Compare the token with the word in the wordlist
                if (strcmp(token, wordlist[i].word) == 0)
                {
                    // Add the score of the word to the total score
                    total_score += wordlist[i].score;
                }
            }
            c++;
            // Get the next word
            token = strtok(NULL, " \n\t!,.");
        }
        
        // Check if the number of words is greater than 0
        if (c > 0)
        {
            // Calculate the average score
            total_score = total_score / c;
            // Print the line and the total score (%-100s is used to print the string in 100 characters width to the left and %10.2f is used to print the float with 2 decimal places)
            printf("%-100s %10.2f", line_copy, total_score);
            printf("\n");
        }

    }
    
    // Close the file
    fclose(val_file);
}
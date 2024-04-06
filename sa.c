// Import the necessary libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"


int main(int argc, char *argv[])
{   
    // Check if the number of arguments is correct
    if (argc != 3)
    {
        // Print the usage of the program
        printf("Usage: %s <SA_dictionary> <Validation_file>\n", argv[0]);
        return 1;
    }

    // Get the file name and the validation file
    char *file_name = argv[1];
    char *validation_file = argv[2];

    // initialize the wordlist
    int wordslist_size = 5000;
    struct words *wordlist = NULL;
    
    // Make the array of structures
    make_aos(&wordslist_size, &wordlist);

    // Get the data from the file and store it in the wordlist
    get_data(file_name, &wordslist_size, &wordlist);

    // Print the header
    printf("              String sample                                                                               Score\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");

    // Perform the sentiment analysis
    sentiment_analysis(wordlist, validation_file);

    // Free the data
    free_data(wordlist);

    return 0;
}
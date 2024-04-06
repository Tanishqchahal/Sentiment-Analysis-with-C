#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Structure to store the words, their scores, standard deviation and SIS array
struct words
{
    char *word;
    float score;
    float SD;
    int SIS_array[10];
};

// Function to make an array of struct
void make_aos(int *wordlist_size, struct words **wordlist);

// Function to read data from the file and store it in an array of struct
void get_data(char *file_name,int *wordlist_size, struct words **wordlist);

// Funstion to free memory allocated for the array of struct
void free_data(struct words *wordlist);

// Function to perform Sentiment Analysis using VADER
void sentiment_analysis(struct words *wordlist, char *validation_file);

#endif
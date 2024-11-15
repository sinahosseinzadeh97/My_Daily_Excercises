#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to process the file and calculate statistics
int textStates(char *filename) {
    // Array to store counts for words of each length from 1 to 20
    int length_count[20] = {0};
    int total_words = 0;
    int uppercase_words = 0;
    char word[21];

    // Open the file for reading
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file:");
        return -1;
    }

    // Read each word from the file
    while (fscanf(file, "%20s", word) == 1) { // Correctly use fscanf
        int len = strlen(word);

        // Ignore words longer than 20 characters
        if (len > 20) continue;

        // Update the length count
        length_count[len - 1]++;
        total_words++;

        // Check if the word is all uppercase
        int is_upper = 1;
        for (int i = 0; i < len; i++) {
            if (!isupper(word[i])) {
                is_upper = 0;
                break;
            }
        }
        if (is_upper) uppercase_words++; // Increment the uppercase word count
    }

    // Close the file
    fclose(file);

    // Print statistics for word lengths
    for (int i = 0; i < 20; i++) {
        if (length_count[i] > 0) {
            printf("%d string/s with length %d\n", length_count[i], i + 1);
        }
    }

    // Calculate and print the percentage of uppercase words
    double uppercase_percentage = (total_words > 0) ? (uppercase_words * 100.0 / total_words) : 0;
    printf("%.2f%% with all capital letters\n", uppercase_percentage);

    // Return the total number of words
    return total_words;
}

int main(void) {
    // Prompt user for the filename
    char filename[100];
    printf("Please enter the filename:\n");
    scanf("%s", filename);

    // Call textStates function and print the result
    int total_words = textStates(filename);
    if (total_words != -1) {
        printf("Total number of words: %d\n", total_words);
    }

    return 0;
}

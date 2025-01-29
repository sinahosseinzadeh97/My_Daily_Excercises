#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 100  // Maximum number of rows in ASCII file
#define MAX_COLS 100  // Maximum number of columns per row

// Function to read the ASCII file into a 2D array
int read_file(const char *filename, char ascii_art[MAX_ROWS][MAX_COLS], int *rows, int *cols) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: The file cannot be opened.\n");
        return 0;
    }

    *rows = 0;
    while (fgets(ascii_art[*rows], MAX_COLS, file)) {
        int len = strlen(ascii_art[*rows]);
        if (ascii_art[*rows][len - 1] == '\n') {
            ascii_art[*rows][len - 1] = '\0';  // Remove newline character
            len--;
        }
        if (len > *cols) {
            *cols = len;  // Update the max number of columns
        }
        (*rows)++;
    }

    fclose(file);
    return 1;
}

// Function to get user input for coordinates and square size
void get_user_input(int *x, int *y, int *N) {
    printf("Enter the number of coordinates x (row): ");
    scanf("%d", x);
    printf("Enter the number of coordinates y (column): ");
    scanf("%d", y);
    printf("Enter the size of the square (N): ");
    scanf("%d", N);
}

// Function to check if the selected square is within the ASCII art limits
int is_square_valid(int x, int y, int N, int rows, int cols) {
    return (x + N <= rows) && (y + N <= cols);
}

// Function to compute character statistics
void compute_statistics(int x, int y, int N, char ascii_art[MAX_ROWS][MAX_COLS], int rows, int cols) {
    int char_count[256] = {0};  // ASCII character frequency array
    int total_chars = N * N;

    // Count character occurrences in the selected NxN square
    for (int i = x; i < x + N; i++) {
        for (int j = y; j < y + N; j++) {
            char_count[(unsigned char)ascii_art[i][j]]++;  // Increment count of the character
        }
    }

    // Print character frequencies as percentages
    printf("Character Frequencies:\n");
    for (int i = 0; i < 256; i++) {
        if (char_count[i] > 0) {
            printf("%c -> %.1f%%\n", i, (char_count[i] / (float)total_chars) * 100);
        }
    }
}

int main() {
    char ascii_art[MAX_ROWS][MAX_COLS] = {0};
    int rows = 0, cols = 0;

    // Read the ASCII file
    if (!read_file("landscape.txt", ascii_art, &rows, &cols)) {
        return 1;  // Exit if the file could not be read
    }

    int x, y, N;
    get_user_input(&x, &y, &N);

    // Validate the square selection
    if (!is_square_valid(x, y, N, rows, cols)) {
        printf("ERROR!! The square to analyze is out of limits.\n");
        return 1;
    }

    // Compute and display character statistics
    compute_statistics(x, y, N, ascii_art, rows, cols);

    return 0;
}

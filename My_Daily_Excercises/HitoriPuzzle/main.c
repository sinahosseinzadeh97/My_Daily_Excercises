#include <stdio.h>

#define MAX_SIZE 10

typedef struct {
    int number;
    int isShaded;  // -1 for unknown, 1 for shaded, 0 for unshaded
} Cell;

Cell grid[MAX_SIZE][MAX_SIZE];
int gridSize;

// Checks for duplicate numbers in the same row and column
int checkDuplicates(int row, int col) {
    // Check the row for duplicates
    for (int j = 0; j < gridSize; j++) {
        if (j != col && !grid[row][j].isShaded && grid[row][j].number == grid[row][col].number) {
            return 0; // Duplicate found
        }
    }
    // Check the column for duplicates
    for (int i = 0; i < gridSize; i++) {
        if (i != row && !grid[i][col].isShaded && grid[i][col].number == grid[row][col].number) {
            return 0; // Duplicate found
        }
    }
    return 1; // No duplicates found
}

// Checks if adjacent cells are shaded
int checkAdjacentShaded(int row, int col) {
    // Check above
    if (row > 0 && grid[row - 1][col].isShaded == 1) return 0;
    // Check below
    if (row < gridSize - 1 && grid[row + 1][col].isShaded == 1) return 0;
    // Check left
    if (col > 0 && grid[row][col - 1].isShaded == 1) return 0;
    // Check right
    if (col < gridSize - 1 && grid[row][col + 1].isShaded == 1) return 0;
    return 1; // No adjacent shaded cells
}

// Depth-first search to check connectivity of unshaded cells
void dfs(int row, int col, int visited[][MAX_SIZE]) {
    // Bounds check
    if (row < 0 || col < 0 || row >= gridSize || col >= gridSize) return;
    if (visited[row][col] || grid[row][col].isShaded == 1) return;

    visited[row][col] = 1;

    // Recursively visit neighbors
    dfs(row - 1, col, visited);
    dfs(row + 1, col, visited);
    dfs(row, col - 1, visited);
    dfs(row, col + 1, visited);
}

// Checks if all unshaded cells are connected
int checkConnectivity() {
    int visited[MAX_SIZE][MAX_SIZE] = {0};
    int found = 0;

    // Find the first unshaded cell to start DFS
    for (int i = 0; i < gridSize && !found; i++) {
        for (int j = 0; j < gridSize && !found; j++) {
            if (grid[i][j].isShaded == 0) {
                dfs(i, j, visited);
                found = 1;
            }
        }
    }
    // If no unshaded cell found, connectivity check fails
    if (!found) return 0;

    // Verify all unshaded cells are connected
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (grid[i][j].isShaded == 0 && !visited[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

// Recursive function to solve the grid
int solve(int row, int col) {
    // Move to the next row if end of column is reached
    if (col == gridSize) {
        col = 0;
        row++;
        // If end of grid is reached, check connectivity
        if (row == gridSize) {
            return checkConnectivity();
        }
    }

    // If the cell is undetermined (-1), attempt shading and unshading
    if (grid[row][col].isShaded == -1) {
        // Try shading the cell
        grid[row][col].isShaded = 1;
        if (checkAdjacentShaded(row, col)) {
            if (solve(row, col + 1)) return 1;
        }

        // Try leaving the cell unshaded
        grid[row][col].isShaded = 0;
        if (checkDuplicates(row, col)) {
            if (solve(row, col + 1)) return 1;
        }

        // Reset cell to undetermined state
        grid[row][col].isShaded = -1;
        return 0;
    } else {
        // Proceed to the next cell if cell state is fixed
        return solve(row, col + 1);
    }
}

int main() {
    printf("Enter grid size (maximum %d): ", MAX_SIZE);
    scanf("%d", &gridSize);

    printf("Enter puzzle numbers:\n");
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            scanf("%d", &grid[i][j].number);
            grid[i][j].isShaded = -1; // Initialize all cells as undetermined
        }
    }

    if (solve(0, 0)) {
        printf("Solution found:\n");
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                if (grid[i][j].isShaded == 1) {
                    printf("X ");
                } else {
                    printf("%d ", grid[i][j].number);
                }
            }
            printf("\n");
        }
    } else {
        printf("No solution found.\n");
    }

    return 0;
}

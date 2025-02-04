#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100  // Maximum number of products
#define MAX_CODE_LEN 20   // Maximum length for product code

typedef struct {
    char product_code[MAX_CODE_LEN];
    float unit_cost;
    int quantity;
} Product;

int read_warehouse(const char *filename, Product warehouse[], int *count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening warehouse file");
        return 0;
    }
    
    *count = 0;
    while (fscanf(file, "%[^,],%f,%d\n", warehouse[*count].product_code, 
                  &warehouse[*count].unit_cost, &warehouse[*count].quantity) == 3) {
        (*count)++;
    }
    
    fclose(file);
    return 1;
}

int read_movements(const char *filename, char movements[][MAX_CODE_LEN], int variations[], int *count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening movements file");
        return 0;
    }
    
    *count = 0;
    while (fscanf(file, "%[^,],%d\n", movements[*count], &variations[*count]) == 2) {
        (*count)++;
    }
    
    fclose(file);
    return 1;
}

int find_product(Product warehouse[], int count, const char *code) {
    for (int i = 0; i < count; i++) {
        if (strcmp(warehouse[i].product_code, code) == 0) {
            return i;
        }
    }
    return -1;
}

void process_movements(Product warehouse[], int warehouse_count, char movements[][MAX_CODE_LEN], int variations[], int movement_count) {
    float total_value = 0;
    for (int i = 0; i < warehouse_count; i++) {
        total_value += warehouse[i].unit_cost * warehouse[i].quantity;
    }

    for (int i = 0; i < movement_count; i++) {
        int index = find_product(warehouse, warehouse_count, movements[i]);

        if (index == -1) {
            printf("ERROR: product %s not existent.\n", movements[i]);
            continue;
        }

        float unit_cost = warehouse[index].unit_cost;
        int current_quantity = warehouse[index].quantity;
        int variation = variations[i];

        if ((variation < 0 && -variation > current_quantity) || (variation > 0 && current_quantity + variation > 10000)) {
            printf("ERROR: Invalid operation for %s!\n", movements[i]);
            continue;
        }

        printf("%s the quantity of %s by %d\n", variation > 0 ? "Increasing" : "Decreasing", movements[i], abs(variation));
        printf("Previous total value: %.2f€\n", total_value);
        
        warehouse[index].quantity += variation;
        total_value += unit_cost * variation;

        printf("New total value: %.2f€\n\n", total_value);
    }
}

void write_updated_warehouse(const char *filename, Product warehouse[], int count) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error writing updated warehouse file");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%.2f,%d\n", warehouse[i].product_code, warehouse[i].unit_cost, warehouse[i].quantity);
    }

    fclose(file);
}

int main() {
    Product warehouse[MAX_PRODUCTS];
    char movements[MAX_PRODUCTS][MAX_CODE_LEN];
    int variations[MAX_PRODUCTS];

    int warehouse_count = 0, movement_count = 0;

    if (!read_warehouse("warehouse.txt", warehouse, &warehouse_count)) {
        return 1;
    }
    
    if (!read_movements("movements.txt", movements, variations, &movement_count)) {
        return 1;
    }

    process_movements(warehouse, warehouse_count, movements, variations, movement_count);
    write_updated_warehouse("warehouse2.txt", warehouse, warehouse_count);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define some constants to make the program flexible and easy to modify
#define MAX_READINGS 1000  // Maximum number of readings per patient
#define MAX_PATIENTS 100   // Maximum number of patients
#define MAX_LINE_LENGTH 100 // Maximum length of a line in the file

// Define a structure to store a single reading
// A structure is like a container that can hold multiple pieces of data
typedef struct {
    char hour[6]; // To store the time in "hh:mm" format (e.g., "17:00")
    int index;    // To store the glycaemic index (e.g., 210)
} Reading;

// Define a structure to store a patient's data
typedef struct {
    char ID[10];               // To store the patient's unique ID (e.g., "1BF0")
    Reading readings[MAX_READINGS]; // An array to store all exceeding readings for this patient
    int count;                 // To count how many times this patient exceeded the limit
} Patient;

// Function to compare two patients for sorting
// This is used by the qsort() function to sort patients by the number of exceeding readings
int compare_patients(const void *a, const void *b) {
    Patient *patientA = (Patient *)a; // Cast the void pointer to a Patient pointer
    Patient *patientB = (Patient *)b; // Cast the void pointer to a Patient pointer
    return patientB->count - patientA->count; // Sort in descending order (most exceeding readings first)
}

int main() {
    // Open the file "glucometer.txt" for reading
    FILE *file = fopen("glucometer.txt", "r");
    if (!file) {
        perror("Failed to open file"); // Print an error message if the file cannot be opened
        return 1; // Exit the program with an error code
    }

    // Create an array to store all patients
    Patient patients[MAX_PATIENTS];
    int patient_count = 0; // To keep track of how many patients we have

    char line[MAX_LINE_LENGTH]; // To store each line read from the file
    while (fgets(line, sizeof(line), file)) { // Read the file line by line
        char ID[10], hour[6]; // Variables to store the patient ID and time
        int index;            // Variable to store the glycaemic index
        float temp;           // Variable to store temperature (not used in this program)
        int bpm;              // Variable to store heart rate (not used in this program)

        // Parse the line into its components using sscanf
        // sscanf reads data from the string (line) and stores it in the variables
        sscanf(line, "%s %s %d %f %d", ID, hour, &index, &temp, &bpm);

        // Check if the glycaemic index exceeds 200
        if (index > 200) {
            // Look for the patient in the list of patients
            int found = 0; // A flag to check if the patient is already in the list
            for (int i = 0; i < patient_count; i++) {
                if (strcmp(patients[i].ID, ID) == 0) { // Compare the patient ID
                    // If the patient is found, add the reading to their list
                    strcpy(patients[i].readings[patients[i].count].hour, hour); // Copy the time
                    patients[i].readings[patients[i].count].index = index;     // Copy the index
                    patients[i].count++; // Increment the count of exceeding readings
                    found = 1; // Set the flag to indicate the patient was found
                    break; // Exit the loop since we found the patient
                }
            }

            // If the patient is not in the list, add them as a new patient
            if (!found) {
                strcpy(patients[patient_count].ID, ID); // Copy the patient ID
                strcpy(patients[patient_count].readings[0].hour, hour); // Copy the time
                patients[patient_count].readings[0].index = index;     // Copy the index
                patients[patient_count].count = 1; // Set the count of exceeding readings to 1
                patient_count++; // Increment the total number of patients
            }
        }
    }

    // Close the file after reading
    fclose(file);

    // Sort the patients by the number of exceeding readings
    // qsort is a built-in function for sorting arrays
    qsort(patients, patient_count, sizeof(Patient), compare_patients);

    // Print the results
    for (int i = 0; i < patient_count; i++) { // Loop through each patient
        for (int j = 0; j < patients[i].count; j++) { // Loop through each exceeding reading
            printf("%s %s %d\n", patients[i].ID, patients[i].readings[j].hour, patients[i].readings[j].index);
        }
    }

    return 0; // End the program successfully
}

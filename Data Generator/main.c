#include <stdio.h>
#include <stdlib.h>

#define min_lobster_name 3 /// Minimum length of a lobster name
#define max_lobster_name 20 /// Maximum length of a lobster name

int main() {
    /// Variable declaration
    unsigned long number_of_lobsters, index, bag_size; /// Variables for the number of lobsters, loop index, and bag size
    unsigned long min_lobster_value, max_lobster_value, min_lobster_size, max_lobster_size; /// Variables for lobster value and size ranges
    FILE *output, *input; /// File pointers for input and output files
    short unsigned name_length, j; /// Variables for the length of lobster names and loop index for name generation

    /// Open input and output files
    input = fopen("input.txt", "r"); /// Open input file for reading
    output = fopen("output.txt", "w"); /// Open output file for writing

    /// Error handling for file operations
    if (input == NULL || output == NULL) {
        fprintf(stderr, "Failed to open files"); /// Print error message if file operations fail
        return 1; /// Exit the program with an error code
    }

    /// Reading input values from the input file
    fscanf(input, "%lu", &bag_size); /// Read the maximum bag size
    fscanf(input, "%lu", &number_of_lobsters); /// Read the number of lobsters
    fscanf(input, "%lu", &min_lobster_value); /// Read the minimum lobster value
    fscanf(input, "%lu", &max_lobster_value); /// Read the maximum lobster value
    fscanf(input, "%lu", &min_lobster_size); /// Read the minimum lobster size
    fscanf(input, "%lu", &max_lobster_size); /// Read the maximum lobster size

    /// Writing the bag size to the output file
    fprintf(output, "%lu\n", bag_size);

    /// Generating randomized lobster data
    for (index = 0; index < number_of_lobsters; index++) {
        /// Print progress message every 100,000 lobsters
        if (index % 100000 == 0) printf("generating...\n");

        /// Generate a random name length within the specified range
        name_length = min_lobster_name + rand() % (max_lobster_name - min_lobster_name);

        /// Generate a random name of the specified length
        for (j = 0; j < name_length; j++)
            fprintf(output, "%c", 'a' + rand() % ('z' - 'a'));

        /// Generate and write a random size within the specified range
        fprintf(output, " %lu", min_lobster_size + rand() % (max_lobster_size - min_lobster_size));

        /// Generate and write a random value within the specified range
        fprintf(output, " %lu\n", min_lobster_value + rand() % (max_lobster_value - min_lobster_value));
    }

    /// Clean up: close input and output files
    fclose(input); /// Close the input file
    fclose(output); /// Close the output file

    return 0; /// Exit the program successfully
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "lobster.h"

int main()
{
    /// Variable declaration
    unsigned long long bag_size, lobster_number = 0;
    clock_t start, end;

    start = clock();  /// Start the clock for timing

    FILE *input, *output;  /// File pointers for input and output files

    lobster* lobster_collection = malloc(sizeof(lobster)); /// Allocate initial memory for the lobster collection

    /// Open input and output files
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    /// Check if file opening succeeded
    if (input == NULL || output == NULL)
    {
        fprintf(stderr, "Failed to open files\n");
        return 1;
    }

    /// Read the bag size from the input file
    fscanf(input, "%llu", &bag_size);

    /// Read each lobster's attributes from the input file
    while (fscanf(input, "%s %llu %llu",
                  lobster_collection[lobster_number].name,
                  &lobster_collection[lobster_number].size,
                  &lobster_collection[lobster_number].value) != EOF)
    {
        /// Only consider lobsters that can fit in the bag
        if (lobster_collection[lobster_number].size <= bag_size)
        {
            lobster_number++; /// Increment the number of lobsters
            lobster_collection = realloc(lobster_collection, sizeof(lobster) * (lobster_number + 2)); /// Reallocate memory for the new lobster
        }
    }

    /// Call the dynamic programming function to solve the problem
    dynamic_programming_lobster(lobster_collection, lobster_number, bag_size, output);

    end = clock(); /// End the clock

    /// Print the elapsed time to the output file
    fprintf(output, "\nTime: %lf seconds\n", (double)((end - start)) / CLOCKS_PER_SEC);

    /// Clean up: free allocated memory and close files
    free(lobster_collection);
    fclose(input);
    fclose(output);

    return 0;
}

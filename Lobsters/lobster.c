#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "lobster.h"

/// Function to set a value in the matrix at a specified row and column
void set_matrix_value(matrix *target_matrix, unsigned long long row_index, unsigned long long column_index, unsigned long long element_value){
	unsigned long position;
	position = row_index * target_matrix->no_cols + column_index; /// Calculate the position in the linear array
	*(target_matrix->matrix_element + position) = element_value;  /// Set the value at the calculated position
}

/// Function to get a value from the matrix at a specified row and column
unsigned long long get_matrix_value(matrix *target_matrix, unsigned long long row_index, unsigned long long column_index){
	return *(target_matrix->matrix_element + row_index * target_matrix->no_cols + column_index); /// Return the value at the calculated position
}

/// Function to get the maximum of two values
unsigned long long get_max(unsigned long long val1, unsigned long long val2){
	return (val1>val2) ? val1 : val2;  /// Return the larger of the two values
}

/// Function implementing the dynamic programming solution for the lobster knapsack problem
void dynamic_programming_lobster(lobster *lobster_collection, unsigned long long no_objects, unsigned long long max_capacity, FILE* output){
	matrix dynamic_matrix; /// Declare the dynamic programming matrix
	unsigned long long objects_iterator; /// Iterator for the objects
	unsigned long long size_iterator; /// Iterator for the sizes (capacities)
	unsigned long long knapsack_value; /// Final value of the knapsack
	unsigned long long current_size; /// Current size being considered
	unsigned long long current_object; /// Current object being considered

	dynamic_matrix.no_rows = no_objects + 1; /// Number of rows in the matrix
	dynamic_matrix.no_cols = max_capacity + 1; /// Number of columns in the matrix

	/// Allocate memory for the matrix elements
	dynamic_matrix.matrix_element = malloc((dynamic_matrix.no_rows) * (dynamic_matrix.no_cols) * sizeof(unsigned long long));

	/// Dynamic Programming Algorithm
	for(objects_iterator=0; objects_iterator<=no_objects; objects_iterator++)
	{
		for(size_iterator=0; size_iterator<=max_capacity; size_iterator++)
		{
			/// Initialize the first row and first column to 0
			if(size_iterator==0 || objects_iterator==0)
			{
				set_matrix_value(&dynamic_matrix, objects_iterator, size_iterator, 0);
			}
			/// If the current object's size is less than or equal to the current capacity
			else if (lobster_collection[objects_iterator-1].size <= size_iterator)
			{
				/// Set the value to the maximum of including or excluding the current object
				set_matrix_value(&dynamic_matrix, objects_iterator, size_iterator,
						get_max(lobster_collection[objects_iterator-1].value +
							get_matrix_value(&dynamic_matrix, objects_iterator-1, size_iterator-lobster_collection[objects_iterator-1].size),
							get_matrix_value(&dynamic_matrix, objects_iterator-1, size_iterator)));
			}
			/// If the current object's size is greater than the current capacity
			else {
				/// Set the value to the value of excluding the current object
				set_matrix_value(&dynamic_matrix, objects_iterator, size_iterator, get_matrix_value(&dynamic_matrix, objects_iterator-1, size_iterator));
			}
		}
	}

	/// Get the final value of the knapsack
	knapsack_value = get_matrix_value(&dynamic_matrix, dynamic_matrix.no_rows - 1, dynamic_matrix.no_cols - 1);

	current_size = dynamic_matrix.no_cols - 1; /// Initialize current size
	current_object = dynamic_matrix.no_rows - 1; /// Initialize current object

	/// Get the used elements
	while(current_object != 0 && current_size != 0) {
		/// If the value in the current cell is different from the value in the cell above
		if(get_matrix_value(&dynamic_matrix, current_object, current_size) != get_matrix_value(&dynamic_matrix, current_object-1, current_size))
		{
			/// Print the name of the included object
			fprintf(output, "%s\n", lobster_collection[current_object-1].name);
			/// Update the current size
			current_size = (current_size > lobster_collection[current_object-1].size) ? current_size - lobster_collection[current_object-1].size : 0;
		}
		current_object--; /// Move to the previous object
	}

	/// Free the allocated memory for the matrix
	free(dynamic_matrix.matrix_element);

	/// Print the final value of the knapsack
	fprintf(output, "\n=== Value in the knapsack %llu ===", knapsack_value);
}

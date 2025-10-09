#include "array.h"

/**
 * @brief Initializes the Array struct.
 * * This function sets the element count to 0 and initializes all values in the 
 * underlying array to 0, preparing the struct for use.
 * * @param data A pointer to the `struct Array` to be initialized.
 */
void initialize( struct Array* data )
{
	data->count = 0;
	for ( int i = 0; i < SIZE; i++ )
	{
		data->values[i] = 0;
	}
}

/**
 * @brief Adds an element to the next available position at the end of the array.
 * * @param data A pointer to the `struct Array`.
 * @param element The integer to add.
 * @return `true` if the element was added successfully, `false` if the array is full.
 */
bool add( struct Array* data, int element )
{
	if ( data->count >= SIZE )
	{
		return false; // Array is full
	}
	data->values[data->count] = element;
	data->count++;
	return true;
}

/**
 * @brief Adds an element at a specific index, shifting subsequent elements to the right.
 * * If the index is out of the current bounds, it's adjusted:
 * - An index `< 0` is treated as `0`.
 * - An index `> count` is treated as `count` (appends to the end).
 * * @param data A pointer to the `struct Array`.
 * @param element The integer to add.
 * @param index The target index for the new element.
 * @return `true` if the addition was successful, `false` if the array is full.
 */
bool addAt( struct Array* data, int element, int index )
{
	if ( data->count >= SIZE )
	{
		return false; // Array is full
	}

	// Normalize index to be within the bounds [0, count]
	if ( index < 0 )
	{
		index = 0;
	}
	if ( index > data->count )
	{
		index = data->count;
	}

	// Shift elements to the right to make space for the new element
	for ( int i = data->count; i > index; i-- )
	{
		data->values[i] = data->values[i - 1];
	}

	// Insert the new element
	data->values[index] = element;
	data->count++;

	return true;
}

/**
 * @brief Finds the first index of a given element in the array.
 * * @param data The `struct Array` (passed by value).
 * @param element The integer to find.
 * @return The index of the element's first occurrence, or `-1` if not found.
 */
int find( struct Array data, int element )
{
	for ( int i = 0; i < data.count; i++ )
	{
		if ( data.values[i] == element )
		{
			return i;
		}
	}
	return -1; // Element not found
}

/**
 * @brief Checks if the array contains a specific element.
 * * @param data The `struct Array` (passed by value).
 * @param element The integer to check for.
 * @return `true` if the element is in the array, `false` otherwise.
 */
bool contains( struct Array data, int element )
{
	// Reuse the find function for efficiency
	return find( data, element ) != -1;
}

/**
 * @brief Removes the element at a specific index, shifting subsequent elements left.
 * * @param data A pointer to the `struct Array`.
 * @param index The index of the element to remove.
 * @return `true` if removal was successful, `false` if the index is out of bounds.
 */
bool removeAt( struct Array * data, int index)
{
	// Check for invalid index (must be within [0, count-1])
	if ( index < 0 || index >= data->count )
	{
		return false;
	}

	// Shift elements to the left to fill the gap
	for ( int i = index; i < data->count - 1; i++ )
	{
		data->values[i] = data->values[i + 1];
	}

	data->count--;

	return true;
}

/**
 * @brief Displays the array's contents to a specified output file.
 * * @param data The `struct Array` (passed by value).
 * @param out A pointer to the output file stream.
 * @param all If `true`, displays all `SIZE` elements and the array's capacity.
 * If `false`, displays only the valid `count` elements and the element count.
 */
void display( struct Array data, FILE* out, bool all )
{
	if ( all )
	{
		fputs( "\t", out );
		for ( int i = 0; i < SIZE; i++ )
		{
			fprintf( out, "%d", data.values[i] );
			if ( i < SIZE - 1 )
			{
				fputs( ", ", out );
			}
		}
		fputs( "\n", out );
		fprintf( out, "\tSIZE of array: %d\n", SIZE );
	}
	else
	{
		// Only print the comma-separated list if there are elements
		if ( data.count > 0 )
		{
			fputs( "\t", out );
			for ( int i = 0; i < data.count; i++ )
			{
				fprintf( out, "%d", data.values[i] );
				if ( i < data.count - 1 )
				{
					fputs( ", ", out );
				}
			}
			fputs( "\n", out );
		}
		fprintf( out, "\tCount of elements in array: %d\n", data.count );
	}
}

/**
 * @brief Resets the array to its initial, empty state.
 * * @param data A pointer to the `struct Array` to clear.
 */
void clear( struct Array* data )
{
	// Re-initializing the struct effectively clears it
	initialize( data );
}
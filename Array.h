#pragma once

#include <stdint.h>

typedef struct Array {
	uint32_t total_lenght;
	uint32_t used_lenght;
	void * content;
} Array;


Array newArray(size_t lenght, size_t size_of_element);

void freeArray(Array array);

#define deleteElementAtIndex(array, index, type)   \
	size_t ix = index;   \
	type * arr = (type *)array.content;   \
	\
	type tmp = arr[array.used_lenght - 1];   \
	arr[array.used_lenght - 1] = arr[ix];   \
	arr[ix] = tmp;   \
	array.used_lenght -= 1

#define getElement(array, index, type)  (((type *)array.content)[index])

#define deleteElement(array, elem, type)   \
	int i = 0;   \
	while(getElement(array, i, type) != elem)   \
		i++;   \
	\
	deleteElementAtIndex(array, i, type)

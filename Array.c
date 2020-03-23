#include "Array.h"

#include <stdlib.h>

Array
newArray(size_t lenght,
         size_t size_of_element)
{
	return (Array){ .total_lenght = lenght
	              , .used_lenght = lenght
	              , .content = malloc(lenght * size_of_element) };
}

void freeArray(Array array) {
	free(array.content);
}

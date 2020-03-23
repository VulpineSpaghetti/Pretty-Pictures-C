#include "IndexPath.h"

#include <stdlib.h>


// TODO: Generalize this kind of a function
void
diamondPath(Point origin,
            Array indices)
{
	int compare(const void * a, const void * b) {
		int ax = abs(origin.x - ((Point *)a)->x);
		int ay = abs(origin.y - ((Point *)a)->y);
		int bx = abs(origin.x - ((Point *)b)->x);
		int by = abs(origin.y - ((Point *)b)->y);

		if(ax - bx != 0)
			return (ax - bx);
		return (ay - by);
	}

	qsort(indices.content, indices.used_lenght, sizeof(Point), compare);
}

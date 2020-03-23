#include "Point.h"

#include <stdlib.h>

Point
getRelativePosition(StartingPoint startingPoint,
                    Resolution resolution)
{
	int absX, absY;

	switch (startingPoint) {
		case TopLeft:
			absX = 0;
			absY = 2;
			break;

		case TopMiddle:
			absX = 1;
			absY = 2;
			break;

		case TopRight:
			absX = 2;
			absY = 2;
			break;

		case MiddleLeft:
			absX = 0;
			absY = 1;
			break;

		default:
		case TheMiddle:
			absX = 1;
			absY = 1;
			break;

		case MiddleRight:
			absX = 2;
			absY = 1;
			break;

		case BottomLeft:
			absX = 0;
			absY = 0;
			break;

		case BottomMiddle:
			absX = 1;
			absY = 0;
			break;

		case BottomRight:
			absX = 2;
			absY = 0;
			break;
	}

	return (Point){ .x = (resolution.x * absX) / 2
	              , .y = (resolution.y * absY) / 2};
}


Array getAllIndices(Resolution resolution) {
	int size = resolution.x * resolution.y;
	Point * points = malloc(size * sizeof(Point));
	int i = 0;

	for(int x = 0; x < resolution.x; x++) {
		for(int y = 0; y < resolution.y; y++) {
			points[i] = (Point){x,y};
			i++;
		}
	}

	return (Array){ .used_lenght = size
	              , .total_lenght = size
	              , .content = points };
}

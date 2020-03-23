#pragma once

#include <stdint.h>

#include "Array.h"


typedef struct Point {
	int16_t x;
	int16_t y;
} Point;

typedef Point Resolution;

typedef enum StartingPoint {
	TopLeft,
	TopMiddle,
	TopRight,
	MiddleLeft,
	TheMiddle,
	MiddleRight,
	BottomLeft,
	BottomMiddle,
	BottomRight
} StartingPoint;


Point
getRelativePosition(StartingPoint startingPoint,
                    Resolution resolution);


Array getAllIndices(Resolution resolution);

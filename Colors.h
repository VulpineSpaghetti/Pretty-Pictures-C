#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "Array.h"


typedef struct Color {
	int8_t red;
	int8_t green;
	int8_t blue;
	bool isSet;
} Color;

typedef Color ColorCombinator(Array colors);

typedef Color ColorPicker(Color combinedColor, Array colors);


Array makeAllColors(void);

Color average(Array colors);

Color pickClosest(Color combinedColor, Array colors);

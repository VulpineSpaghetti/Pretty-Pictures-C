#include "Colors.h"

#include <math.h>
#include <stdlib.h>
#include <stdbool.h>


Color
calculateDifference(Color left,
                    Color right)
{
	return (Color){ .red = left.red - right.red
	              , .green = left.green - right.green
	              , .blue = left.blue - right.blue };
}


bool
isSmallerThan(Color left,
              Color right)
{
	return (left.red + left.green + left.blue < right.red + right.green + right.blue);
}


Array makeAllColors(void) {
	int max = pow(2, 8);
	Color * colors = malloc(max * max * max * sizeof(Color));
	int i = 0;

	for(int r = 0; r < max; r++) {
		for(int g = 0; g < max; g++) {
			for(int b = 0; b < max; b++) {
				colors[i] = (Color){ .red = r, .green = g, .blue = b };
				i++;
			}
		}
	}

	return (Array){ .total_lenght = max * max * max
	              , .used_lenght = max * max * max
	              , .content = colors };
}


Color average(Array colors) {
	int red = 0;
	int green = 0;
	int blue = 0;
	int actualNumberOfColors = 0;

	for(int i = 0; i < colors.used_lenght; i++) {
		if(getElement(colors, i, Color).isSet == False)
			continue;

		red += getElement(colors, i, Color).red;
		green += getElement(colors, i, Color).green;
		blue += getElement(colors, i, Color).blue;
		actualNumberOfColors++;
	}

	return (Color){ .red = red / actualNumberOfColors
	              , .green = green / actualNumberOfColors
	              , .blue = blue / actualNumberOfColors
	              , .isSet = true };
}


Color
pickClosest(Color combinedColor,
            Array colors)
{
	int closestColorIndex = 0;
	Color difference = calculateDifference(combinedColor, getElement(colors, 0, Color));
	Color newDiff;

	for(int i = 1; i < colors.used_lenght; i++) {
		newDiff = calculateDifference(combinedColor, getElement(colors, i, Color));

		if(isSmallerThan(newDiff, difference)) {
			difference = newDiff;
			closestColorIndex = i;
		}
	}

	return getElement(colors, closestColorIndex, Color);
}

#include "Point.h"
#include "IndexPath.h"
#include "Array.h"
#include "Colors.h"

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>


typedef enum PictureSize {
	_320x200p,
	_1280x720p,
	_1920x1080p,
	_2560x1440p,
	_4K
} PictureSize;

Array
makeArt(PictureSize pictureSize,
        IndexPath indexPath,
        ColorCombinator colorCombinator,
        ColorPicker colorPicker);

Resolution pictureSizeToResolution(PictureSize pictureSize);

int main(void) {
	makeArt(_320x200p, diamondPath, average, pickClosest);
	return 1;
}

void
makeArt(PictureSize pictureSize,
        StartingPoint startingPoint,
        IndexPath indexPath,
        ColorCombinator colorCombinator,
        ColorPicker colorPicker)
{
	Resolution imageRes = pictureSizeToResolution(pictureSize);
	Point origin = getRelativePosition(startingPoint, imageRes);
	int size = imageRes.x * imageRes.y;
	Array indices = getAllIndices(imageRes);
	Array pixels = newArray(size, sizeof(Color));
	Array availableColors = makeAllColors();
	Array nearbyColors = (Array){8,8,malloc(8 * sizeof(Color))};

	// Sorts indices
	indices = indexPath(origin, indices);

#define pixelAt(point) (pixels[point.x + point.y * imageRes.x])

	// Picks starting colors
	{
		int max = pow(2, 8);
		srand(time(NULL));

		Color color = (Color){rand() % max, rand() % max, rand() % max, true};
		Point newPoint = (Point){ .x = origin.x - 1
		                        , .y = origin.y };
		pixelAt(newPoint) = color;
		deleteElement(indices, newPoint, Point);
		deleteElement(availableColors, color, Color);

		color = (Color){rand() % max, rand() % max, rand() % max, true};
		newPoint = (Point){ .x = origin.x + 1
		                  , .y = origin.y };
		pixelAt(newPoint) = color;
		deleteElement(indices, newPoint, Point);
		deleteElement(availableColors, color, Color);

		color = (Color){rand() % max, rand() % max, rand() % max, true};
		newPoint = (Point){ .x = origin.x
		                  , .y = origin.y - 1 };
		pixelAt(newPoint) = color;
		deleteElement(indices, newPoint, Point);
		deleteElement(availableColors, color, Color);

		color = (Color){rand() % max, rand() % max, rand() % max, true};
		newPoint = (Point){ .x = origin.x
		                  , .y = origin.y + 1 };
		pixelAt(newPoint) = color;
		deleteElement(indices, newPoint, Point);
		deleteElement(availableColors, color, Color);
	}

	for(int i = 0; i < indices.used_lenght; i++) {
		Point index = indices[i];

		Point tmpIndex = (Point){ .x = index.x - 1
		                        , .y = index.y };
		getElement(nearbyColors, 0, Color) = pixelAt(tmpIndex);

		tmpIndex = (Point){ .x = index.x - 1
		                  , .y = index.y + 1 };
		getElement(nearbyColors, 1, Color) = pixelAt(tmpIndex);

		tmpIndex = (Point){ .x = index.x
		                  , .y = index.y + 1 };
		getElement(nearbyColors, 2, Color) = pixelAt(tmpIndex);

		tmpIndex = (Point){ .x = index.x + 1
		                  , .y = index.y + 1 };
		getElement(nearbyColors, 3, Color) = pixelAt(tmpIndex);

		tmpIndex = (Point){ .x = index.x + 1
		                  , .y = index.y };
		getElement(nearbyColors, 4, Color) = pixelAt(tmpIndex);

		tmpIndex = (Point){ .x = index.x + 1
		                  , .y = index.y - 1};
		getElement(nearbyColors, 5, Color) = pixelAt(tmpIndex);

		tmpIndex = (Point){ .x = index.x
		                  , .y = index.y - 1};
		getElement(nearbyColors, 6, Color) = pixelAt(tmpIndex);

		tmpIndex = (Point){ .x = index.x - 1
		                  , .y = index.y - 1};
		getElement(nearbyColors, 7, Color) = pixelAt(tmpIndex);

		Color combinedColor = colorCombinator(nearbyColors);
		Color pickedColor = colorPicker(combinedColor, availableColors);

		pixelAt(index) = pickedColor;
	}

	saveArt(imageRes, pixels);

	freeArray(indices);
	freeArray(availableColors);
	freeArray(nearbyColors);

	saveArt(imageRes, pixels);

	freeArray(pixels);
}

void
saveArt(Resolution imageRes,
        Array pixels)
{
	// TODO finish
}

Resolution pictureSizeToResolution(PictureSize pictureSize) {
	switch(pictureSize) {
		default:
		case _320x200p:
		return (Resolution){320,200};

		case _1280x720p:
		return (Resolution){1280,720};

		case _1920x1080p:
		return (Resolution){1920,1080};

		case _2560x1440p:
		return (Resolution){2560,1440};

		case _4K:
		return (Resolution){2*1920,2*1080};
	}
}

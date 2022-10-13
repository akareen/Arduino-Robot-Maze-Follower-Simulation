#include "formulas.h"

int overlap(int min1st, int max1st, int min2nd, int max2nd) {
    return ((min2nd <= max1st) && (max1st <= max2nd))
            || ((min1st <= min2nd) && (min2nd <= max1st))
            || ((min2nd <= min1st) && (min1st <= max2nd))
            || ((min1st <= max2nd) && (max2nd <= max1st));
}

int checkOverlap(int object1X, int object1width, int object1Y, int object1height,
                 int object2X, int object2width, int object2Y, int object2height) {
    int xOverlap = overlap(object1X, object1X + object1width,  object2X, object2X + object2width);
    int yOverlap = overlap(object1Y, object1Y + object1height, object2Y, object2Y + object2height);
    return (xOverlap && yOverlap);
}



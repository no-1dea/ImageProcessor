#include "negative_filter.h"

void NegativeFilter::ChangePixel(Color& pixel) {
    pixel.blue = 255 - pixel.blue;
    pixel.green = 255 - pixel.green;
    pixel.red = 255 - pixel.red;
}

#include "gray_scale_filter.h"
#include <cstdint>

void GrayScaleFilter::ChangePixel(Color& pixel) {
    uint8_t new_color = 0.114 * pixel.blue + 0.587 * pixel.green + 0.299 * pixel.red;

    pixel.blue = new_color;
    pixel.green = new_color;
    pixel.red = new_color;
}

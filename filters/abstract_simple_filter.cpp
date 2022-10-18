#include "abstract_simple_filter.h"

void AbstractSimpleFilter::Apply(Picture& picture) {
    for (size_t y = 0; y < picture.GetHeight(); ++y) {
        for (size_t x = 0; x < picture.GetWidth(); ++x) {
            ChangePixel(picture.GetPixel(y, x));
        }
    }
}

#include "crop_filter.h"
#include <algorithm>

CropFilter::CropFilter(size_t width, size_t height) : width_(width), height_(height) {
}

void CropFilter::Apply(Picture& picture) {
    picture.ChangeWidth(std::min(width_, picture.GetWidth()));
    picture.ChangeHeight(std::min(height_, picture.GetHeight()));
}

#pragma once

#include "abstract_filter.h"
#include "../picture.h"

class CropFilter : public AbstractFilter {
public:
    CropFilter(size_t width, size_t height);

    void Apply(Picture& picture) override;

private:
    size_t width_;
    size_t height_;
};

#pragma once

#include "abstract_simple_filter.h"
#include "../color.h"

class GrayScaleFilter : public AbstractSimpleFilter {
protected:
    void ChangePixel(Color& pixel) override;
};

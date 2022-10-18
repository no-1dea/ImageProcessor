#pragma once

#include "abstract_simple_filter.h"
#include "../color.h"

class NegativeFilter : public AbstractSimpleFilter {
protected:
    void ChangePixel(Color& pixel) override;
};

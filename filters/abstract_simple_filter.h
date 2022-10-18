#pragma once

#include "abstract_filter.h"
#include "../color.h"
#include "../picture.h"

class AbstractSimpleFilter : public AbstractFilter {
public:
    void Apply(Picture& picture) override;

protected:
    virtual void ChangePixel(Color& pixel) = 0;
};
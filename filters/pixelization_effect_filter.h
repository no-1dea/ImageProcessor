#pragma once

#include "../color.h"
#include "../picture.h"
#include "abstract_filter.h"

class PixelizationEffectFilter : public AbstractFilter {
public:
    explicit PixelizationEffectFilter(size_t diameter);

    void Apply(Picture& picture) override;

protected:
    size_t diameter_;
};

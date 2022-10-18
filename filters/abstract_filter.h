#pragma once

#include "../picture.h"

class AbstractFilter {
public:
    virtual void Apply(Picture& picture) = 0;

    virtual ~AbstractFilter() = default;
};

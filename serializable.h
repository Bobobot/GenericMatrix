#pragma once

#include <iostream>

struct Serializable {
    virtual void write(std::ostream &) const {}
    virtual void read(std::istream &)  {}
    virtual ~Serializable() {}
};

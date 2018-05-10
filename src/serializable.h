#pragma once

#include <iostream>

struct Serializable {
	virtual void write(std::ostream &) const = 0;
	virtual void read(std::istream &) = 0;
	virtual ~Serializable() {}
};

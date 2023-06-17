#ifndef MADPODRACING_HPP
# define MADPODRACING_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Pod
{
	public:
		int x;
		int y;
		int prev_x;
		int prev_y;

		Pod() : x(0), y(0), prev_x(-1), prev_y(-1) {}
};

#endif

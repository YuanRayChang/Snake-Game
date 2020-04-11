#ifndef BARRIER_H
#define BARRIER_H

#include <vector>
#include "SDL.h"

class Barrier {
public:
	Barrier(bool Addbarrier = 0);
	std::vector<SDL_Point> getBody() const;
	bool BarrierCell(int x, int y) const;
	int BarrierSize() const;

private:
	std::vector<SDL_Point> body;
};

#endif
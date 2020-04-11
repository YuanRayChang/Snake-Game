#include "barrier.h"

Barrier::Barrier(bool Addbarrier) {
	if (Addbarrier == 1) {
		SDL_Point tmp;
		for (int i = 0; i < 8; ++i)
		{
			tmp.x = i + 10;
			tmp.y = 10;
			body.push_back(tmp);
		}
	}
}

std::vector<SDL_Point> Barrier::getBody() const {
	return body;
}

bool Barrier::BarrierCell(int x, int y) const {
	for (auto const &item : body) {
		if (x == item.x && y == item.y) {
			return true;
		}
	}
	return false;
}

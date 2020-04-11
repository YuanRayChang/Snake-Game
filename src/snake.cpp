#include "snake.h"
#include <cmath>
#include <iostream>
#include <random>

void Snake::Update(const Barrier &barrier) {
	// We first capture the head's cell before updating.
	SDL_Point prev_cell{
			static_cast<int>(head_x),
			static_cast<int>(head_y)};
	UpdateHead();
	// Capture the head's cell after updating.
	SDL_Point current_cell{
			static_cast<int>(head_x),
			static_cast<int>(head_y)};

	// Check if snake hit barrier
	if (barrier.BarrierCell(head_x, head_y)) {
		//std::cout << "hit barrier!" << std::endl;
		UpdateHead_barrier();
		current_cell.x = static_cast<int>(head_x);
		current_cell.y = static_cast<int>(head_y);
	}

	// Update all of the body vector items if the snake head has moved to a new cell.
	if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
		UpdateBody(current_cell, prev_cell);
	}
}

void Snake::UpdateHead() {
	switch (direction) {
		case Direction::kUp:
			head_y -= speed;
			break;

		case Direction::kDown:
			head_y += speed;
			break;

		case Direction::kLeft:
			head_x -= speed;
			break;

		case Direction::kRight:
			head_x += speed;
			break;
	}

	// Wrap the Snake around to the beginning if going off of the screen.
	head_x = fmod(head_x + grid_width, grid_width);
	head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
	// Add previous head location to vector
	body.push_back(prev_head_cell);

	if (!growing) {
		// Remove the tail from the vector.
		body.erase(body.begin());
	} else {
		growing = false;
		size++;
	}

	// Check if the snake has died.
	for (auto const &item : body) {
		if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
			alive = false;
		}
	}
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
	if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
		return true;
	}
	for (auto const &item : body) {
		if (x == item.x && y == item.y) {
			return true;
		}
	}
	return false;
}

// Change direction when hitting barrier, and direction is random.
void Snake::UpdateHead_barrier() {
	std::random_device randNum;
	int even = randNum()%2;
	switch (direction) {
		case Direction::kUp:
			if (even == 0) {
				direction = Direction::kLeft;
			}
			else {
				direction = Direction::kRight;
			}
			head_y += speed;
			break;

		case Direction::kDown:
			if (even == 0) {
				direction = Direction::kLeft;
			}
			else {
				direction = Direction::kRight;
			}
			head_y -= speed;
			break;

		case Direction::kLeft:
			if (even == 0) {
				direction = Direction::kDown;
			}
			else {
				direction = Direction::kUp;
			}
			head_x += speed;
			break;

		case Direction::kRight:
			if (even == 0) {
				direction = Direction::kDown;
			}
			else {
				direction = Direction::kUp;
			}			
			head_x -= speed;
			break;
	}

	// Wrap the Snake around to the beginning if going off of the screen.
	head_x = fmod(head_x + grid_width, grid_width);
	head_y = fmod(head_y + grid_height, grid_height);
}

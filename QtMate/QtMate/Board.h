#pragma once
#include <iostream>

using Color = char;

class Board
{
public:
	Board() {
		std::cout << "Board::Board()" << std::endl;
	}
	~Board() {
		std::cout << "Board::~Board()" << std::endl;
	}
};


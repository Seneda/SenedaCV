#include "img.hpp"


bool operator==(const Pixel &lhs, const Pixel &rhs) {
    return (lhs.r == rhs.r and
            lhs.g == rhs.g and
            lhs.b == rhs.b and
            lhs.i == rhs.i);
}

bool operator==(const Pixel &lhs, const int* &rhs) {
    return (lhs.r == rhs[0] and
            lhs.g == rhs[1] and
            lhs.b == rhs[2] and
            lhs.i == rhs[3]);
}

bool operator==(const Pixel &lhs, const int &rhs) {
    return (lhs.i == rhs);
}

Pixel operator "" _p(const char* rgbi, size_t len) {
    Pixel pixel;
    std::istringstream iss(rgbi);
    iss >> pixel.r;
    iss >> pixel.g;
    iss >> pixel.b;
    iss >> pixel.i;
    return pixel;
};

PixelGrid PixelGrid::convolve(PixelGrid kernel) {
	PixelGrid p(10,10);
	return p;
}

void printImage(std::string name, PixelGrid image){
	std::cout << std::endl << name << std::endl;
	for (int r = 0; r < image.rows; r++){
		for (int c = 0; c < image.columns; c++){
			std::cout << "  ";
			std::cout << image[r][c].i << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


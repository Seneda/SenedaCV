#include "img.hpp"


PixelGrid PixelGrid::convolve(PixelGrid kernel){
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

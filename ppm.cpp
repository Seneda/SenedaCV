#include "ppm.hpp"
#include <fstream>
#include <string>
#include <iostream>

PixelGrid openImage(char* filename){
	std::string magic, meta;
	std::ifstream file;
	file.open(filename, std::ifstream::in);
	std::getline(file, magic);
	std::getline(file, meta);
	//std::cout << "Meta " << meta << std::endl;
	//std::cout << "Magic " << magic << std::endl;
	int h, w;
	file >> h >> w;
	//std::cout << "H/W : " << h << " / " << w << std::endl;
	PixelGrid image(magic, meta, h,w);
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			float r, g, b;
			file >> r >> g >> b;
			Pixel pixel(r, g, b);
			image[i][j] = pixel;
		} 
	}
	return image;
}

void printImage(PixelGrid image){
	std::cout << image.magic << std::endl;
	std::cout << image.meta << std::endl;
	std::cout << image.height <<  ' ' << image.width << std::endl;
	for (int i = 0; i < image.height; i++){
		for (int j = 0; j < image.width; j++){
			std::cout << (int)image[i][j].r*2 << ' ';
			std::cout << (int)image[i][j].r << ' ';
			std::cout << (int)image[i][j].r/5 << "  ";
		} 
		
		std::cout << std::endl;
	}
}

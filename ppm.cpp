#include "ppm.hpp"
#include <fstream>
#include <string>
#include <iostream>

PPMImage openImage(char* filename){
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
	PPMImage image(magic, meta, h,w);
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

void printImage(PPMImage image){
	std::ofstream file;
	file.open((char*)"/tmp/image.ppm"); 
	file << image.magic << std::endl;
	file << image.meta << std::endl;
	file << image.height <<  ' ' << image.width << std::endl;
	for (int i = 0; i < image.height; i++){
		for (int j = 0; j < image.width; j++){
			file << (int)image[i][j].i << ' ';
			file << (int)image[i][j].i << ' ';
			file << (int)image[i][j].i << ' ';
		} 
		
		file << std::endl;
	}
}

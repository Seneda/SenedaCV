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
	file.open((char*)"image.ppm"); 
	file << image.magic << std::endl;
	file << image.meta << std::endl;
	file << image.height <<  ' ' << image.width << std::endl;
	file << (int)image.max() << std::endl;
	for (int i = 0; i < image.height; i++){
		for (int j = 0; j < image.width; j++){
			file << (int)image[i][j].i << ' ';
			file << (int)image[i][j].i << ' ';
			file << (int)image[i][j].i << ' ';
		} 
		
		file << std::endl;
	}
}

float PPMImage::min(){
	float min = (*this)[0][0].i;
	for (int i=0; i < width; i++){
		for (int j=0; j < width; j++){
			if ((*this)[i][j].i < min) {
				min = (*this)[i][j].i;
			}
		}	
	}
	return min;
}

float PPMImage::max(){
	float max = (*this)[0][0].i;
	for (int i=0; i < width; i++){
		for (int j=0; j < width; j++){
			if ((*this)[i][j].i > max) {
				max = (*this)[i][j].i;
			}
		}	
	}
	return max;
}

void PPMImage::normalise(){
	std::cout << "The min is " << this->min() << std::endl;
	std::cout << "The max is " << this->max() << std::endl;
	std::cout << "The range is " << this->range() << std::endl;
	float min0 = this->min();
	float range0 = this->range();
	for (int i=0; i < width; i++){
		for (int j=0; j < width; j++){
			(*this)[i][j].i = ((*this)[i][j].i - min0 ) / range0 * 255;
		}	
	}
}

PPMImage PPMImage::convolve(PixelGrid kernel){
	PPMImage conv(magic, meta, height-kernel.height+1, width-kernel.width+1);
	std::cout << conv.height << ' ' << conv.width << std::endl;
	for (int i = 0; i < conv.width; i++){
		for (int j = 0; j < conv.height; j++){
			// Compute value for pixel i,j
			float intensity = 0;
			std::cout << intensity << std::endl;

			for (int x = 0; x < kernel.width; x++){
				for (int y = 0; y < kernel.height; y++){
					 std::cout << i << ' ' << j << ' ' << x << ' ' << y << ' ' << kernel[x][y].i << ' ' << (*this)[i+x][j+y].i << ' ' <<intensity << std::endl;

					 intensity += kernel[x][y].i * (*this)[i+x][j+y].i;
				}
			} 
			conv[i][j].i = intensity;
			std::cout << intensity << std::endl;
		}
	}
	
	return conv;
}

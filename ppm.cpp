#include "ppm.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <limits>

PPMImage openImage(char* filename){
	std::string magic, meta;
	std::ifstream file;
	file.open(filename, std::ifstream::in);
	std::cout << "Opened" << std::endl;
	std::getline(file, magic);
	std::getline(file, meta);
	//std::cout << "Meta " << meta << std::endl;
	//std::cout << "Magic " << magic << std::endl;
	int rows, cols;
	file >> cols >> rows;
	std::cout << "rows: " << rows << "  cols: " << cols << std::endl;
	int max;
	file >> max;
	//std::cout << "H/W : " << h << " / " << w << std::endl;
	
	PPMImage image(magic, meta, rows, cols);
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			float r, g, b;
			file >> r >> g >> b;
			Pixel pixel(r, g, b);
			//std::cout << i << ',' << j << ' ' << pixel.i << ' ';
			image[i][j] = pixel;
		} 
		//std::cout << std::endl;
	}
	return image;
}

void printImage(std::string name, PPMImage image){
	std::cout << std::endl << name << std::endl;
	for (int r = 0; r < image.rows; r++){
		for (int c = 0; c < image.columns; c++){
			std::cout << "  ";
			std::cout << image[r][c].i << ' ';
		}
		//std::cout << std::endl;
	}
}

void saveImage(PPMImage image){
	std::ofstream file;
	file.open((char*)"image.ppm"); 
	file << image.magic << std::endl;
	file << image.meta << std::endl;
	file << image.columns <<  ' ' << image.rows << std::endl;
	file << (int)image.max() << std::endl;
	for (int i = 0; i < image.rows; i++){
		for (int j = 0; j < image.columns; j++){
			file << (int)image[i][j].i << ' ';
			file << (int)image[i][j].i << ' ';
			file << (int)image[i][j].i << "   ";
		} 
		
		file << std::endl;
	}
}

float PPMImage::min(){
	float min = std::numeric_limits<int>::max();
	for (int i=0; i < columns*rows; i++){
			if ((*this)[0][i].i < min) {
				min = (*this)[0][i].i;
			}	
	}
	return min;
}

float PPMImage::max(){
	float max = std::numeric_limits<int>::min();
	for (int i=0; i < columns*rows; i++){
			if ((*this)[0][i].i > max) {
				max = (*this)[0][i].i;
			}	
	}
	return max;
}

void PPMImage::normalise(){
	std::cout << "Normalising" << std::endl;

	std::cout << "The min is " << this->min() << std::endl;
	std::cout << "The max is " << this->max() << std::endl;
	std::cout << "The range is " << this->range() << std::endl;
	float min0 = this->min();
	float range0 = this->range();
	for (int r=0; r < rows; r++){
		for (int c=0; c < columns; c++){
			//std::cout << (*this)[r][c].i << "->";
			(*this)[r][c].i = (((*this)[r][c].i - min0)/range0)*1000;	
			if ((*this)[r][c].i < 0 ){
				std::cout << "ERROR at " << r << ' ' << c << (*this)[r][c].i<<std::endl;
			}
			//std::cout << (*this)[r][c].i << ' ';
		}	
		//std::cout << std::endl;
	}
	std::cout << std::endl;
}

PPMImage PPMImage::convolve(PixelGrid kernel){
	std::cout << "Convolving" << std::endl;
	PPMImage conv(magic, meta, rows-kernel.rows+1, columns-kernel.columns+1);
	std::cout << conv.rows << ' ' << conv.columns << std::endl;
	for (int r = kernel.rows-1; r < rows; r++){
		for (int c = kernel.columns-1; c < columns; c++){
			// Compute value for pixel i,j
			float intensity = 0;
			//std::cout << r << ',' << c << ' ';
			for (int x = 0; x < kernel.rows; x++){
				for (int y = 0; y < kernel.columns; y++){
					 intensity += kernel[x][y].i * (*this)[r-x][c-y].i;
				}
			} 
			conv[r-kernel.rows+1][c-kernel.columns+1].i = intensity;
			//std::cout << intensity << "   ";
		}
		//std::cout << "endrow" << std::endl;
		
	}
	std::cout <<  "end" << std::endl;
	return conv;
}

#include "ppm.hpp"
#include <fstream>
#include <string>
#include <iostream>

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
			std::cout << i << ',' << j << ' ' << pixel.i << ' ';
			image[i][j] = pixel;
		} 
		std::cout << std::endl;
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
		std::cout << std::endl;
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
	float min = (*this)[0][0].i;
	for (int i=0; i < columns; i++){
		for (int j=0; j < columns; j++){
			if ((*this)[i][j].i < min) {
				min = (*this)[i][j].i;
			}
		}	
	}
	return min;
}

float PPMImage::max(){
	float max = (*this)[0][0].i;
	for (int i=0; i < rows; i++){
		for (int j=0; j < columns; j++){
			if ((*this)[i][j].i > max) {
				max = (*this)[i][j].i;
			}
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
			std::cout << (*this)[r][c].i << '-';
			
			(*this)[r][c].i = (*this)[r][c].i - min0;	
			std::cout << (*this)[r][c].i << ' ';
		}	
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

PPMImage PPMImage::convolve(PixelGrid kernel){
	std::cout << "Convolving" << std::endl;
	PPMImage conv(magic, meta, rows-kernel.rows+1, columns-kernel.columns+1);
	std::cout << conv.rows << ' ' << conv.columns << std::endl;
	for (int r = 0; r < rows; r++){
		for (int c = 0; c < columns; c++){
			// Compute value for pixel i,j
			float intensity = 0;
			//std::cout << intensity << std::endl;
			std::cout << (*this)[r][c].i << intensity << ' ';

			for (int x = 0; x < kernel.rows; x++){
				for (int y = 0; y < kernel.columns; y++){
					 //std::cout << i << ' ' << j << ' ' << x << ' ' << y << ' ' << kernel[x][y].i << ' ' << (*this)[i+x][j+y].i << ' ' <<intensity << std::endl;

					 intensity += kernel[x][y].i * (*this)[r-x][c-y].i;
				}
			} 
			conv[r][c].i = intensity;
		}
		std::cout << std::endl;
	}
	
	return conv;
}

#include "ppm.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <limits>
#include <vector>
#include <cmath>

PPMImage openImage(const char* filename){
	std::string magic, meta;
	std::ifstream file;
	file.open(filename, std::ifstream::in);
	std::cout << "Opened " << filename << std::endl;
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
			RGBPixel pixel(r, g, b);
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
			std::cout << image[r][c].r << ' ' << image[r][c].g << ' ' << image[r][c].b << ' ' << image[r][c].i << "   ";
		}
		//std::cout << std::endl;
	}
}

void saveImage(PPMImage image){
	std::ofstream file;
	char* name = (char*)"image.ppm";
	file.open(name); 
	file << image.magic << std::endl;
	file << image.meta << std::endl;
	file << image.columns <<  ' ' << image.rows << std::endl;
	if ((int)image.max() == 0){
		file << 1 << std::endl;
	} else {
		file << (int)image.max() << std::endl;
	}
	for (int i = 0; i < image.rows; i++){
		for (int j = 0; j < image.columns; j++){
			file << (int)image[i][j].r << ' ';
			file << (int)image[i][j].g << ' ';
			file << (int)image[i][j].b << "   ";
		} 
		
		file << std::endl;
	}
}

void PPMImage::saveImage(const char* name){
	std::ofstream file;
	//char* name = (char*)"image.ppm";
	std::cout << "Saving image to " << name << std::endl;
	file.open(name); 
	file << magic << std::endl;
	file << meta << std::endl;
	file << columns << ' ' << rows << std::endl;
	if ((int)max() == 0){
		file << 1 << std::endl;
	} else {
		file << (int)max() << std::endl;
	}
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++){
			file << (int)(*this)[i][j].r << ' ';
			file << (int)(*this)[i][j].g << ' ';
			file << (int)(*this)[i][j].b << "   ";
		} 
		
		file << std::endl;
	}
}

float PPMImage::min(){
	float min = std::numeric_limits<int>::max();
	for (int i=0; i < columns*rows; i++){
		if ((*this)[0][i].r < min) {
			min = (*this)[0][i].r;
		}
		if ((*this)[0][i].g < min) {
			min = (*this)[0][i].g;
		}
		if ((*this)[0][i].b < min) {
			min = (*this)[0][i].b;
		}
	}
	return min;
}
////
////float PPMImage::max(){
////	float max = std::numeric_limits<int>::min();
////	for (int i=0; i < columns*rows; i++){
////		if ((*this)[0][i].i > max) {
////			max = (*this)[0][i].i;
////		}
////	}
////	return max;
////}
//
//float PPMImage::max(){
//	float max = std::numeric_limits<int>::min();
//	ForEachPixel([&max, this](int r, int c)
//		{
//			if ((*this)[r][c].i > max) {
//				max = (*this)[r][c].i;
//			}
//		}
//	);
//	return max;


float PPMImage::max(){
	float max = std::numeric_limits<int>::min();
	FOR_PIXELS
			if ((*this)[r][c].r > max) {
				max = (*this)[r][c].r;
			}
			if ((*this)[r][c].g > max) {
				max = (*this)[r][c].g;
			}
			if ((*this)[r][c].b > max) {
				max = (*this)[r][c].b;
			}
	END_FOR_PIXELS
	return max;
}

void PPMImage::normalise(){
	/*

	  */
	std::cout << "Normalising" << std::endl;
	std::cout << "The min is " << min() << std::endl;
	std::cout << "The max is " << max() << std::endl;
	std::cout << "The range is " << range() << std::endl;

	float min0 = min();
	float range0 = range();
	for (int r=0; r < rows; r++){
		for (int c=0; c < columns; c++){
			//std::cout << (*this)[r][c].i << "->";
			(*this)[r][c] = (((*this)[r][c].i - min0)/range0)*1000;
			if ((*this)[r][c].i < 0 ){
				std::cout << "ERROR at " << r << ' ' << c << (*this)[r][c].i<<std::endl;
			}
		}
	}
	std::cout << std::endl;
}

void PPMImage::magnitudise(){
	std::cout << "Magnitudise" << std::endl;
	std::cout << "The min is " << this->min() << std::endl;
	std::cout << "The max is " << this->max() << std::endl;

	for (int r=0; r < rows; r++){
		for (int c=0; c < columns; c++){
			if ((*this)[r][c].i < 0 ){	
				(*this)[r][c] = -1*(*this)[r][c].i;
			} 
		}	
	}
}

PPMImage PPMImage::convolve(const PixelGrid<MonoPixel> kernel)const{
	std::cout << "Convolving" << std::endl;
	PPMImage conv(magic, meta, rows-kernel.rows+1, columns-kernel.columns+1);
//	std::cout << conv.rows << ' ' << conv.columns << std::endl;
	for (int r = kernel.rows-1; r < rows; r++){
		for (int c = kernel.columns-1; c < columns; c++){
			float red = 0;
			float green = 0;
			float blue = 0;
			for (int x = 0; x < kernel.rows; x++){
				for (int y = 0; y < kernel.columns; y++){
					red += kernel[x][y].i * (*this)[r-x][c-y].r;
					green += kernel[x][y].i * (*this)[r-x][c-y].g;
					blue += kernel[x][y].i * (*this)[r-x][c-y].b;
				}
			}
			conv[r-kernel.rows+1][c-kernel.columns+1] = RGBPixel(red, green, blue);
		}
	}
//	std::cout <<  "end of convolution" << std::endl;
	return conv;
}

void PPMImage::threshold(float thresh){
	std::cout << "Threshold at " << thresh << std::endl;
	std::cout << "The min is " << this->min() << std::endl;
	std::cout << "The max is " << this->max() << std::endl;
	std::cout << "The range is " << this->max() << std::endl;

	thresh = this->min() + thresh*this->range();
	float min0 = this->min();
	float max0 = this->max();
	for (int r=0; r < rows; r++){
		for (int c=0; c < columns; c++){
			if ((*this)[r][c].i > thresh ){	
				(*this)[r][c] = max0;
			} 
			else {
				(*this)[r][c] = min0;
			}
		}	
	}
}

PPMImage PPMImage::apply_kernels(std::vector<PixelGrid<MonoPixel>> kernels){
	PPMImage output = *this;
	for (int k = 0; k < kernels.size(); k++){
		std::cout << "convolving with " << std::endl;
		printImage("K", kernels[k]);
		output = output.convolve(kernels[k]);
	}
	return output;
}

PPMImage PPMImage::resize(int out_rows, int out_columns)const{
	PPMImage output = PPMImage(magic, meta, out_rows, out_columns);
	
	for (int r=0; r < out_rows; r++){
		for (int c=0; c < out_columns; c++){
			// Convert r,c into old style coordinates
			float r_real = (float)r / out_rows * rows;
			float c_real = (float)c / out_columns * columns;
			int r_0 = floor(r_real);
			int r_1 = ceil(r_real);
			int c_0 = floor(c_real);
			int c_1 = ceil(c_real);
			float r_d = r_real - r_0;
			float c_d = c_real - c_0;
			/*   tl--t------tr
			 *   |   |      | 
			 *   |---p------|
			 *   |   |      |
			 *   |   |      |
			 *   |   |      |
			 *   bl--b------br  */
			float tl, tr, bl, br;

			float t, b, R, G, B;

			tl = (*this)[r_0][c_0].r;
			tr = (*this)[r_0][c_1].r;
			bl = (*this)[r_1][c_0].r;
			br = (*this)[r_1][c_1].r;
			t = tr + (tr - tl)*c_d;
			b = br + (br - bl)*c_d;
			R = b + (b - t)*r_d;
			tl = (*this)[r_0][c_0].g;
			tr = (*this)[r_0][c_1].g;
			bl = (*this)[r_1][c_0].g;
			br = (*this)[r_1][c_1].g;
			t = tr + (tr - tl)*c_d;
			b = br + (br - bl)*c_d;
			G = b + (b - t)*r_d;
			tl = (*this)[r_0][c_0].b;
			tr = (*this)[r_0][c_1].b;
			bl = (*this)[r_1][c_0].b;
			br = (*this)[r_1][c_1].b;
			t = tr + (tr - tl)*c_d;
			b = br + (br - bl)*c_d;
			B = b + (b - t)*r_d;

			output[r][c] = RGBPixel(R,G,B);
			// r / rows * this->rows() same for cols
			// find the 4 vals adjacent and the distances from each
			// Do a weighted sum (possibly split into x and y separately)
			// Set output[r][c] = val;
		}
	}
	return output;
}


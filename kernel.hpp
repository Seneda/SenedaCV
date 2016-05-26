#ifndef KERNEL_HPP
#define KERNEL_HPP
#include "img.hpp"	
#include <string>				
					

PixelGrid readKernel(std::string filename);
/*
PixelGrid edge_x() {
	PixelGrid kernel(1,3);
	kernel[0][0].i = -1;
	kernel[0][1].i = 0;
	kernel[0][2].i = 1;
	return kernel;
}

PixelGrid edge_x_big() {
	PixelGrid kernel(1,5);
	kernel[0][0].i = -1;
	kernel[0][1].i = -0.5;
	kernel[0][2].i = 0;
	kernel[0][3].i = 0.5;
	kernel[0][4].i = 1;
	return kernel;
}

PixelGrid edge_x_bigger() {
	PixelGrid kernel(1,5);
	kernel[0][0].i = -1;
	kernel[0][1].i = -0.5;
	kernel[0][2].i = -0.25;
	kernel[0][2].i = 0;
	kernel[0][2].i = 0.25;
	kernel[0][3].i = 0.5;
	kernel[0][4].i = 1;
	return kernel;
}

PixelGrid edge_y() {
	PixelGrid kernel(3,1);
	kernel[0][0].i = -1;
	kernel[0][1].i = 0;
	kernel[0][2].i = 1;
	return kernel;
}

PixelGrid edge_y_big() {
	PixelGrid kernel(5,1);
	kernel[0][0].i = -1;
	kernel[0][1].i = -0.5;
	kernel[0][2].i = 0;
	kernel[0][3].i = 0.5;
	kernel[0][4].i = 1;
	return kernel;
}

PixelGrid edge_y_bigger() {
	PixelGrid kernel(5,1);
	kernel[0][0].i = -1;
	kernel[0][1].i = -0.5;
	kernel[0][2].i = -0.25;
	kernel[0][2].i = 0;
	kernel[0][2].i = 0.25;
	kernel[0][3].i = 0.5;
	kernel[0][4].i = 1;
	return kernel;
}

PixelGrid edge_x_thresh() {
	PixelGrid kernel(1,3);
	kernel[0][0].i = -1;
	kernel[0][1].i = 2;
	kernel[0][1].i = -1;
	return kernel;
}

PixelGrid block_blur() {
	PixelGrid kernel(3,3);
	kernel[0][0].i = 1;
	kernel[0][1].i = 0.125;
	kernel[0][2].i = 1;
	kernel[0][3].i = 0.125;
	kernel[0][4].i = 0.5;
	kernel[0][5].i = 0.125;
	kernel[0][6].i = 1;
	kernel[0][7].i = 0.125;
	kernel[0][8].i = 1;
	return kernel;
}

PixelGrid no_change(){
	PixelGrid kernel(1, 1);
	kernel[0][0].i = 0.1;
	printImage("Kernel at creation", kernel);
	return kernel;
}
*/
#endif

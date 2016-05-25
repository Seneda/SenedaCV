#ifndef KERNEL_HPP
#define KERNEL_HPP
#include "img.hpp"					
					
/*
PixelGrid edge_x() {
	PixelGrid kernel(2,2);
	kernel[0][0].i = -1;
	kernel[0][1].i = -1;
	kernel[1][0].i = 1;
	kernel[1][1].i = 1;
	return kernel;
}
*/
PixelGrid edge_x() {
	PixelGrid kernel(1,3);
	kernel[0][0].i = -1;
	kernel[0][1].i = 0;
	kernel[0][2].i = 1;
	return kernel;
}

PixelGrid no_change(){
	PixelGrid kernel(1,1);
	kernel[0][0].i = 1;
	printImage("Kernel at creation", kernel);
	return kernel;
}

PixelGrid edge_y() {
	PixelGrid kernel(0,2);
	kernel[0][0].i = -1;
	kernel[0][1].i = 1;
	return kernel;
}

#endif

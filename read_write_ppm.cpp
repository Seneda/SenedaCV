#include <iostream>
#include <string>
#include <fstream>
#include "ppm.hpp"
#include "kernel.hpp"
using namespace std;

int main() {
	string magic, meta;
	// open file
	std::ifstream file;
	file.open((char*)"instructions.txt", std::ifstream::in);
	
	//read image name
	string image_filename_string;
	std::getline(file, image_filename_string);
	cout << "Image: " << image_filename_string << endl;
	const char* image_filename = image_filename_string.c_str();
	
	PPMImage image = openImage(image_filename);
	
	//read image name
	string output_filename_string;
	std::getline(file, output_filename_string);
	cout << "Kernel : " << output_filename_string << endl;
	const char* output_filename = output_filename_string.c_str();
	
	// Read kernel name
	string kernel_name;
	string kernel_string;
	std::getline(file, kernel_string);
	cout << kernel_string << endl;
	const char* kernelname = kernel_string.c_str();
	PixelGrid kernel = readKernel(kernelname);
	printImage("Kernel", kernel);
	
	
	PPMImage output = image.convolve(kernel);

	output.magnitudise();
	output.normalise();
	output.saveImage(output_filename);
	cout << "DONE" << std::endl;
}

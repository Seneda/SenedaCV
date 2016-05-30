#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "ppm.hpp"
#include "kernel.hpp"

using namespace std;

PPMImage apply_kernels(PPMImage input, vector<PixelGrid> kernels){
	PPMImage output = PPMImage("", "", 0, 0);
	for (int k = 0; k < kernels.size(); k++){
		output = input.convolve(kernels[k]);
	}
	return output;
}


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
	
	string kernel_string;
	const char* kernelname;
	vector <PixelGrid> kernels;
	// Read kernel name
	for (int i=0; i < 2; i++){
		std::getline(file, kernel_string);
		cout << kernel_string << endl;
		kernelname = kernel_string.c_str();
		PixelGrid kernel = readKernel(kernelname);
		printImage("Kernel", kernel);
		kernels.push_back(kernel);
	}
	
	PPMImage output = apply_kernels(image, kernels);
	output.magnitudise();
	output.normalise();
	output.saveImage(output_filename);
	cout << "DONE" << std::endl;
}

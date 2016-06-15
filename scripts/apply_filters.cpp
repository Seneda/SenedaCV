#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "../cv/ppm.hpp"
#include "../cv/kernel.hpp"

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

	string kernel_string;
	const char* kernelname;
	vector <PixelGrid<MonoPixel>> kernels;
	kernels.push_back(gaussian(5, 1));

	// Read kernel name
	int i = 0 ;
	while (file) {//(int i=0; i < 6; i++){
		i ++;
		std::getline(file, kernel_string);
		if (kernel_string != "") {
			cout << "kernel " << i << kernel_string << endl;
			kernelname = kernel_string.c_str();
			PixelGrid<MonoPixel> kernel = readKernel(kernelname);
			printImage("Kernel", kernel);
			kernels.push_back(kernel);
		}
	}
	cout << "****************" << endl;
	image = image.resize(image.rows, image.columns);
	image = image.convolve(gaussian(5,1));
	cout << " GO \n" << endl;
	PPMImage x_grad = image.convolve(readKernel("kernels/edge_x"));
	PPMImage y_grad = image.convolve(readKernel("kernels/edge_y"));
//	x_grad.autorange();
//	y_grad.autorange();
	cout << x_grad.min() << endl;
	cout << y_grad.min() << endl;

//	printImage("image", output);
	cout << y_grad.min() << endl;
	x_grad.saveImage("X-grad.ppm");
	y_grad.saveImage("Y-grad.ppm");
	cout << "DONE" << std::endl;

	PPMImage agg = PPMImage(image.magic, image.meta, x_grad.rows, x_grad.columns);
	FOR_PIXELS_IN_GRID(agg)
    		if (abs(x_grad[r][c].i) > abs(y_grad[r][c].i)) {
				agg[r][c] = x_grad[r][c];
			} else {
				agg[r][c] = y_grad[r][c];
			}
			agg[r][c].i *= sqrt(abs(agg[r][c].i));
			agg[r][c].i /= 100;
	END_FOR_PIXELS
	agg.autorange();
	agg.saveImage("agg.ppm");

}

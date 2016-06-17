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
//	image = image.resize(image.rows, image.columns);
//	image = image.convolve(gaussian(5,1));
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
	cout << "X min " << x_grad.min() << "X max " << x_grad.max() << std::endl;
	cout << "Y min " << y_grad.min() << "Y max " << y_grad.max() << std::endl;

	PPMImage agg = PPMImage(image.magic, image.meta, x_grad.rows, x_grad.columns);
	PPMImage ang = PPMImage(image.magic, image.meta, agg.rows, agg.columns);
	PPMImage color = image.resize(agg.rows, agg.columns);

	FOR_PIXELS_IN_GRID(agg)
			agg[r][c] = sqrt(x_grad[r][c] * x_grad[r][c] +
							 y_grad[r][c] * y_grad[r][c]);
			ang[r][c] = atan2(y_grad[r][c], x_grad[r][c]) * 180 / PI + 180;

			color[r][c].r *= agg[r][c].i/color[r][c].i;
			color[r][c].g *= agg[r][c].i/color[r][c].i;
			color[r][c].b *= agg[r][c].i/color[r][c].i;
	END_FOR_PIXELS
	agg.autorange();
	agg.saveImage("agg.ppm");
	ang = ang.resize(ang.rows/3, ang.columns/3);
	ang.saveImage("ang.ppm");
//	color.autorange();
	float min = color.min();
	FOR_PIXELS_IN_GRID(color)
			   color[r][c] += -1*min;
	END_FOR_PIXELS
	color.saveImage("color.ppm");

}
#ifndef IMG_HPP
#define IMG_HPP
#include <string>
#include <iostream>
#include <sstream>

struct RGBPixel{
	float r;
	float g;
	float b;
	float i;

    RGBPixel();
	RGBPixel(float red, float green, float blue);
    void calculate_intensity();

    void operator= (float intensity);
	operator float ();
};

RGBPixel operator"" _rgb(const char *rgbi, size_t len);

struct MonoPixel{
	float i;

    MonoPixel();
	MonoPixel(float intensity);

	void operator= (float intensity);
    explicit operator float ();
};

template<class T=RGBPixel>
class PixelGrid {
	T* pixels;
	public:
	int rows, columns;
	PixelGrid(int r, int c){
		rows = r;
		columns = c;
		pixels = new T[r*c];
	}
	//  image[row][col]
	T* operator[](int i){
		return &pixels[i*columns];
	}
	PixelGrid<T> convolve(PixelGrid<MonoPixel> kernel);
};

void printImage(std::string name, PixelGrid<MonoPixel> image);

bool operator==(const RGBPixel &lhs, const RGBPixel &rhs);
bool operator==(const MonoPixel &lhs, const MonoPixel &rhs);

#endif

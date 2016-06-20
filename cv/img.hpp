#ifndef IMG_HPP
#define IMG_HPP
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <functional>

struct RGBPixel{
	float r;
	float g;
	float b;
	float i;

    RGBPixel();
	RGBPixel(float red, float green, float blue);
    void calculate_intensity();

    void operator= (float intensity);
    void operator+= (float intensity);
	operator float ();
};


struct MonoPixel{
	float i;

    MonoPixel();
	MonoPixel(float intensity);

	void operator= (float intensity);
    void operator+= (float intensity);
    explicit operator float ();
};

struct AnglePixel{
	float i;

	AnglePixel();
	AnglePixel(float angle);

	void operator= (float intensity);
	void operator+= (float intensity);
	explicit operator float ();
};

#define ITER_ROWS for (int r=0; r < rows; r++)
#define ITER_COLS for (int c=0; c < columns; c++)
#define FOR_PIXELS for (int r=0; r < rows; r++) { for (int c=0; c < columns; c++) {
#define FOR_PIXELS_IN_GRID(grid) for (int r=0; r < grid.rows; r++) { for (int c=0; c < grid.columns; c++) {
#define END_FOR_PIXELS } }
template<class T=RGBPixel>
class PixelGrid {
	T* pixels;
	public:
	void operator= (float* values) {
		for (int i = 0; i < rows*columns; i++) {
			pixels[i] = values[i];
		}
	}
	bool  operator== (float*);
	int rows, columns;

	PixelGrid(int r, int c){
		rows = r;
		columns = c;
		pixels = new T[r*c];
	}
	virtual ~PixelGrid(){
		delete[] pixels;
	}
	PixelGrid<T>(const PixelGrid<T> &rhs) {
		rows = rhs.rows;
		columns = rhs.columns;
		pixels = new T[rows*columns];
		FOR_PIXELS_IN_GRID(rhs)
				pixels[r*columns+c] = rhs[r][c];
		END_FOR_PIXELS
	}
	void operator=(const PixelGrid<T> &rhs) {
		rows = rhs.rows;
		columns = rhs.columns;
        delete[] pixels;
        pixels = new T[rows*columns];
		FOR_PIXELS_IN_GRID(rhs)
				(*this)[r][c] = rhs[r][c];
		END_FOR_PIXELS
	}
	//  image[row][col]
	T* operator[](int i){
		return &pixels[i*columns];
	}
	const T* operator[](int i)const{
		return &pixels[i*columns];
	}
	PixelGrid<T> convolve(PixelGrid<MonoPixel> kernel);
	void normalise();
    void autorange();
    float max();
    float max_abs();
    float min();
    float min_abs();
	float sum();
//    template<typename F>
//    void ForEachPixel(F function) {
//        for (int r=0; r < rows; r++) {
//            for (int c=0; c < columns; c++) {
//                function(r, c);
//            }
//        }
//    }
//    void print_pixels() {
//        ForEachPixel(
//        [](int r, int c)
//         {
//            if (r==c) {
//                std::cout << r << " == " << c << std::endl;
//            } else {
//                std::cout << r << " != " << c << std::endl;
//            }
//        });
//    }
    PixelGrid<T> resize(int out_rows, int out_columns);

};

void printImage(std::string name, PixelGrid<MonoPixel> image);


PixelGrid<MonoPixel> ConvertToMonopixel(PixelGrid<RGBPixel> old);


bool operator==(const RGBPixel &lhs, const RGBPixel &rhs);
bool operator==(const MonoPixel &lhs, const MonoPixel &rhs);
bool operator==(const RGBPixel &lhs, const std::string &rhs);
bool operator==(const AnglePixel &lhs, const float rhs);
#endif

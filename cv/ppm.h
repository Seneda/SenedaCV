#ifndef PPM_H
#define PPM_H

struct Pixel{
	float r;
	float g;
	float b;
	Pixel() {
		r = 0;
		g = 0;
		b = 0;
	}
	Pixel(float r, float g, float b){
		this->r = r;
		this->g = g;
		this->b = b;
	}
};

class PixelGrid {
	int height, width;
	Pixel* pixels;
	public:
		PixelGrid(int h, int w){
			height = h;
			width = w;
			pixels = new Pixel[h*w];
		}
	Pixel* operator[](int i){
		return &pixels[i*width];
	}
};
#endif

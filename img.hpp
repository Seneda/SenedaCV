#ifndef IMG_HPP
#define IMG_HPP

struct Pixel{
	float r;
	float g;
	float b;
	float i;
	Pixel() {
		r = 0;
		g = 0;
		b = 0;
	}
	Pixel(float r, float g, float b){
		this->r = r;
		this->g = g;
		this->b = b;
		this->i = (r+g+b)/3;
	}
};

class PixelGrid {
	Pixel* pixels;
	public:
	int height, width;
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

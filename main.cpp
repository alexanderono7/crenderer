#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor blue  = TGAColor(0, 0,   255,   255);

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
	for (float x = x0; x <= x1; x++) {
		float t = (x-x0)/(float)(x1-x0);
		int y = y0*(1.-t) + (y1*t);
        image.set(x, y, color);
    }
}

int main(int argc, char** argv) {
    //creation of new image object, completely black
	TGAImage image(100, 100, TGAImage::RGB);
    //set random pixel to be red
	image.set(52, 41, red);

    // draw line
    line(0, 0, 25, 80, image, blue);
    line(0, 0, 80, 25, image, red);
	image.flip_vertically(); // i want to have the origin (0,0) at the left bottom corner of the image
	image.write_tga_file("output1.tga");
	return 0;
}


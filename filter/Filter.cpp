#include "Filter.h"
using namespace std;
using namespace imaging;
void Filter::gray(Image *i){
	int x = 0,y = 0;
	while (x<i->getWidth()){
		while (y < i->getHeight()){
			Color pixel = i->getPixel(x, y);
			int sum = pixel.x + pixel.y + pixel.z;
			pixel.x = sum / 3;
			pixel.y = sum / 3;
			pixel.z = sum / 3;
			i->setPixel(x, y, pixel);
			y++;
		}
		y = 0;
		x++;
	}
}

void Filter::color(Image *i, Color c){
	int j = 0;
	int x = 0, y = 0;
	while (x<i->getWidth()){
		while (y < i->getHeight()){
			Color pixel = i->getPixel(x, y);
			pixel.x = pixel.x * c.x / 255.0;
			pixel.y = pixel.y * c.y / 255.0;
			pixel.z = pixel.z * c.z / 255.0;
			i->setPixel(x, y, pixel);
			y++;
		}
		y = 0;
		x++;
	}
}

void Filter::blur(Image *i){
	int x = 0;
	int y = 0;
	Color *result = new Color[i->getWidth()*i->getHeight()];
	while (x < i->getWidth()){
		while (y < i->getHeight()){
			int neigborpixel = 1;
			int r = i->getPixel(x, y).x;
			int g = i->getPixel(x, y).y;
			int b = i->getPixel(x, y).z;
			if (x != 0){
				r = r + i->getPixel(x-1, y).x;
				g = g + i->getPixel(x-1, y).y;
				b = b + i->getPixel(x-1, y).z;
				neigborpixel++;
				if (y != 0){
					r = r + i->getPixel(x - 1, y-1).x;
					g = g + i->getPixel(x - 1, y-1).y;
					b = b + i->getPixel(x - 1, y-1).z;
					neigborpixel++;
				}
				if (y < i->getHeight() - 1){
					r = r + i->getPixel(x - 1, y+1).x;
					g = g + i->getPixel(x - 1, y+1).y;
					b = b + i->getPixel(x - 1, y+1).z;
					neigborpixel++;
				}
			}
			if (x <i->getWidth() - 1){
				r = r + i->getPixel(x + 1, y).x;
				g = g + i->getPixel(x + 1, y).y;
				b = b + i->getPixel(x + 1, y).z;
				neigborpixel++;
				if (y != 0){
					r = r + i->getPixel(x + 1, y-1).x;
					g = g + i->getPixel(x + 1, y-1).y;
					b = b + i->getPixel(x + 1, y-1).z;
					neigborpixel++;
				}
				if (y < i->getHeight() - 1){
					r = r + i->getPixel(x + 1, y+1).x;
					g = g + i->getPixel(x + 1, y+1).y;
					b = b + i->getPixel(x + 1, y+1).z;
					neigborpixel++;
				}
			}
			if (y < i->getHeight() - 1){
				r = r + i->getPixel(x, y+1).x;
				g = g + i->getPixel(x, y+1).y;
				b = b + i->getPixel(x, y+1).z;
				neigborpixel++;
			}
			if (y != 0){
				r = r + i->getPixel(x, y-1).x;
				g = g + i->getPixel(x, y-1).y;
				b = b + i->getPixel(x, y-1).z;
				neigborpixel++;
			}
			r = r / neigborpixel;
			b = b / neigborpixel;
			g = g / neigborpixel;
			Color newp;
			newp.x = r;
			newp.y = g;
			newp.z = b;
			result[x+ y*i->getWidth()] = newp;
			y++;
		}
		y = 0;
		x++;
	}
	x = 0;
	y = 0;
	while (x < i->getWidth()){
		while (y < i->getHeight()){
			i->setPixel(x,y,result[x +y*i->getWidth()]);
			y++;
		}
		y = 0;
		x++;
	}
	delete[] result;
}

void Filter::median(Image *i){
	int x = 0, y = 0;
	Color *result = new Color[i->getWidth()*i->getHeight()];
	while (x < i->getWidth()){
		while (y < i->getHeight()){
			int neigborpixel = 1;
			vector<int>r;
			vector<int>g;
			vector<int>b;
			r.push_back(i->getPixel(x, y).x);
			g.push_back(i->getPixel(x, y).y);
			b.push_back(i->getPixel(x, y).z);
			if (x != 0){
				r.push_back(i->getPixel(x-1, y).x);
				g.push_back(i->getPixel(x-1, y).y);
				b.push_back(i->getPixel(x-1, y).z);
				neigborpixel++;
				if (y != 0){
					r.push_back(i->getPixel(x-1, y-1).x);
					g.push_back(i->getPixel(x-1, y-1).y);
					b.push_back(i->getPixel(x-1, y-1).z);
					neigborpixel++;
				}
				if (y < i->getHeight() - 1){
					r.push_back(i->getPixel(x-1, y+1).x);
					g.push_back(i->getPixel(x-1, y+1).y);
					b.push_back(i->getPixel(x-1, y+1).z);
					neigborpixel++;
				}
			}
			if (x <i->getWidth() - 1){
				r.push_back(i->getPixel(x+1, y).x);
				g.push_back(i->getPixel(x+1, y).y);
				b.push_back(i->getPixel(x+1, y).z);
				neigborpixel++;
				if (y != 0){
					r.push_back(i->getPixel(x+1, y-1).x);
					g.push_back(i->getPixel(x+1, y-1).y);
					b.push_back(i->getPixel(x+1, y-1).z);
					neigborpixel++;
				}
				if (y < i->getHeight() - 1){
					r.push_back(i->getPixel(x+1, y+1).x);
					g.push_back(i->getPixel(x+1, y+1).y);
					b.push_back(i->getPixel(x+1, y+1).z);
					neigborpixel++;
				}
			}
			if (y < i->getHeight() - 1){
				r.push_back(i->getPixel(x, y + 1).x);
				g.push_back(i->getPixel(x, y + 1).y);
				b.push_back(i->getPixel(x, y + 1).z);
				neigborpixel++;
			}
			if (y != 0){
				r.push_back(i->getPixel(x, y-1).x);
				g.push_back(i->getPixel(x, y-1).y);
				b.push_back(i->getPixel(x, y-1).z);
				neigborpixel++;
			}
			std::sort(std::begin(r), std::end(r));
			std::sort(std::begin(g), std::end(g));
			std::sort(std::begin(b), std::end(b));
			Color newp;
			newp.x = r[floor(r.size() / 2)];
			newp.y = g[floor(g.size() / 2)];
			newp.z = b[floor(b.size() / 2)];
			result[x + y*i->getWidth()] = newp;
			y++;
		}
		y = 0;
		x++;
	}
	x = 0;
	y = 0;
	while (x < i->getWidth()){
		while (y < i->getHeight()){
			i->setPixel(x, y, result[x + y*i->getWidth()]);
			y++;
		}
		y = 0;
		x++;
	}
	delete[] result;
}

void Filter::diff(Image *i){
	int x = 0, y = 0;
	Color *result = new Color[i->getWidth()*i->getHeight()];
	while (x < i->getWidth()){
		while (y < i->getHeight()){
			int neigborpixel = 1;
			vector<int>r;
			vector<int>g;
			vector<int>b;
			r.push_back(i->getPixel(x, y).x);
			g.push_back(i->getPixel(x, y).y);
			b.push_back(i->getPixel(x, y).z);
			if (x != 0){
				r.push_back(i->getPixel(x - 1, y).x);
				g.push_back(i->getPixel(x - 1, y).y);
				b.push_back(i->getPixel(x - 1, y).z);
				neigborpixel++;
				if (y != 0){
					r.push_back(i->getPixel(x - 1, y - 1).x);
					g.push_back(i->getPixel(x - 1, y - 1).y);
					b.push_back(i->getPixel(x - 1, y - 1).z);
					neigborpixel++;
				}
				if (y < i->getHeight() - 1){
					r.push_back(i->getPixel(x - 1, y + 1).x);
					g.push_back(i->getPixel(x - 1, y + 1).y);
					b.push_back(i->getPixel(x - 1, y + 1).z);
					neigborpixel++;
				}
			}
			if (x <i->getWidth() - 1){
				r.push_back(i->getPixel(x + 1, y).x);
				g.push_back(i->getPixel(x + 1, y).y);
				b.push_back(i->getPixel(x + 1, y).z);
				neigborpixel++;
				if (y != 0){
					r.push_back(i->getPixel(x + 1, y - 1).x);
					g.push_back(i->getPixel(x + 1, y - 1).y);
					b.push_back(i->getPixel(x + 1, y - 1).z);
					neigborpixel++;
				}
				if (y < i->getHeight() - 1){
					r.push_back(i->getPixel(x + 1, y + 1).x);
					g.push_back(i->getPixel(x + 1, y + 1).y);
					b.push_back(i->getPixel(x + 1, y + 1).z);
					neigborpixel++;
				}
			}
			if (y < i->getHeight() - 1){
				r.push_back(i->getPixel(x, y + 1).x);
				g.push_back(i->getPixel(x, y + 1).y);
				b.push_back(i->getPixel(x, y + 1).z);
				neigborpixel++;
			}
			if (y != 0){
				r.push_back(i->getPixel(x, y - 1).x);
				g.push_back(i->getPixel(x, y - 1).y);
				b.push_back(i->getPixel(x, y - 1).z);
				neigborpixel++;
			}
			std::sort(std::begin(r), std::end(r));
			std::sort(std::begin(g), std::end(g));
			std::sort(std::begin(b), std::end(b));
			Color newp;
			newp.x = r[r.size()-1] - r[0];
			newp.y = g[g.size()-1] - g[0];
			newp.z = b[b.size()-1] - b[0];
			result[x + y*i->getWidth()] = newp;
			y++;
		}
		y = 0;
		x++;
	}
	x = 0;
	y = 0;
	while (x < i->getWidth()){
		while (y < i->getHeight()){
			i->setPixel(x, y, result[x + y*i->getWidth()]);
			y++;
		}
		y = 0;
		x++;
	}
	delete[] result;
}


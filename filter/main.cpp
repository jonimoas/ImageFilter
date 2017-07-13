#include "Image.h"
#include "cpi_format.h"
#include "ppm_format.h"
#include <iostream>
#include "Filter.h"

using namespace std;
using namespace imaging;

int main(int argc, char* argv[]){
	Filter f;
	string filename = argv[argc - 1];
	int z = 1;
	Image *i = new Image(0,0,false);
	if (filename.find("ppm") != std::string::npos) {
		std::cout << "ppm image file detected, parsing" << '\n';
		PPMImageReader p;
		i = p.read(argv[argc - 1]);
		if (i->getWidth() != 0){
			std::cout << "parsed" << '\n';
		}
	}
	else{
		if (filename.find("cpi") != std::string::npos) {
			std::cout << "cpi image file detected, parsing" << '\n';
			CPIImageReader c;
			i = c.read(argv[argc - 1]);
			if (i->getWidth() != 0){
				std::cout << "parsed" << '\n';
			}
		}
		else{
			if (filename.find("rle") != std::string::npos) {
				std::cout << "not supported" << '\n';
				z = argc + 1;
			}
			else{
				std::cout << "invalid image file" << '\n';
				z = argc + 1;
			}
		}
	}
	if (i->getWidth() == 0){
		z = argc + 1;
	}
	while (z < argc - 1){
		string argcheck = argv[z];
		if (argcheck.find("-f") != std::string::npos){
			z++;
		}
		else{
			if (argcheck.find("median") != std::string::npos){
				std::cout << "median filter requested,applying" << '\n';
				f.median(i);
				z++;
			}
			else{
				if (argcheck.find("diff") != std::string::npos){
					std::cout << "diff filter requested,applying" << '\n';
					f.diff(i);
					z++;
				}
				else{
					if (argcheck.find("gray") != std::string::npos){
						std::cout << "gray filter requested,applying" << '\n';
						f.gray(i);
						z++;
					}
					else{
						if (argcheck.find("blur") != std::string::npos){
							std::cout << "blur filter requested,applying" << '\n';
							f.blur(i);
							z++;
						}
						else{
							if (argcheck.find("color") != std::string::npos){
								Color c;
								c.x = atoi(argv[z + 1]);
								c.y = atoi(argv[z + 2]);
								c.z = atoi(argv[z + 3]);
								if (0 <= c.x <= 255 && 0 <= c.y <= 255 && 0 <= c.z <= 255){
									std::cout << "color filter requested,applying" << '\n';
									f.color(i, c);
									z = z + 4;
								}
								else{
									std::cout << "invalid colors specified" << '\n';
									z = argc + 1;
								}
							}
							else{
								cout << "invalid filter, quitting" << '\n';
								z = argc + 1;
							}
						}
					}
				}
			}
		}
	}
	if (z != argc + 1){
		if (filename.find("ppm") != std::string::npos) {
			PPMImageWriter pw;
			pw.write(filename, *i);
			std::cout << "filter application complete" << '\n';

		}
		else{
			if (filename.find("cpi") != std::string::npos) {
				CPIImageWriter cw;
				cw.write(filename, *i);
				std::cout << "filter application complete" << '\n';
			}
		}
	}
	system("PAUSE");
	return 0;
}
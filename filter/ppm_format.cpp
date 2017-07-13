#include "ppm_format.h"
#include "Image.h"
#include <fstream>
#include <iostream>
#include <vector>

// Insert implementation code for the PPMImageWriter and PPMImageReader classes here
//

using namespace std;
using namespace imaging;


void PPMImageWriter::write(std::string filename, const imaging::Image & src){
	std::ofstream file;
	file.open(filename,ios::out|ios::binary|ios::trunc);
	file << "P6\n" << src.getWidth() << "\n" << src.getHeight() << "\n" << "255"<<"\b"<<" ";
	unsigned int i = 0;
	while (i <= src.getWidth()*src.getHeight() * 3){
		file << *(src.getRawDataPtr() + i);
		i++;
	}
	file.close();
}



imaging::Image * PPMImageReader::read(std::string filename){
	streampos size;
	unsigned char * data;
	data = new unsigned char[10];
	ifstream file(filename, ios::in | ios::binary | ios::ate);
	if (!file){
		cout << "file not found, exiting";
		Image *result = new Image(0, 0, false);
		delete[] data;
		return result;
	}
	if (file.is_open()){
		size = file.tellg();
		data = new unsigned char[size];
		file.seekg(0, ios::beg);
		file.read((char*)data, size);
		file.close();
	}
	file.close();
	string height;
	string width;
	int i = 3;
	while (data[i]>=48 && data[i]<58){
		width.push_back(data[i]);
		i++;
	}
	if (data[i] == '#'){
		while (data[i] != '\n'){ 
			i++;
		}
	}
	i++;
	while (data[i] >= 48 && data[i]<58){
		height.push_back(data[i]);
		i++;
	}
	if (data[i] == '#'){
		while (data[i] != '\n'){
			i++;
		}
	}
	if (data[i] == '#'){
		while (data[i] != '\n'){
			i++;
		}
	}
	i = i + 2;
	Component *buffer = new Component[atoi(width.c_str())*atoi(height.c_str())*3];
	int z = 0;
	while (i <= size){
		buffer[z] = data[i];
		i++;
		z++;
	}
	delete[] data;
	Image *result = new Image(atoi(width.c_str()), atoi(height.c_str()), buffer, true);
	return result;
}

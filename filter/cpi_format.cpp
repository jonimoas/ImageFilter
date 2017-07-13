#include "cpi_format.h"
#include "Image.h"
#include <fstream>
#include<iostream>
// Insert implementation code for the CPImageWriter and CPIImageReader classes here
//
using namespace std;
using namespace imaging;


void CPIImageWriter::write(std::string filename, const imaging::Image & src){
	std::ofstream file;
	file.open(filename, ios::out | ios::binary | ios::trunc);
	file << "CPI" <<(char)1<<(char)2<<(char)1<< (char)(src.getWidth()%256) << (char)(src.getWidth()/256) << (char)(src.getHeight()%256) << (char)(src.getHeight()/256);
	unsigned int i = 0;
	while (i <= src.getWidth()*src.getHeight() * 3){
		file << *(src.getRawDataPtr() + i);
		i++;
	}
	file.close();
}


imaging::Image * CPIImageReader::read(std::string filename){
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
	long width = 0,height=0;
	width = data[7] * 256 + data[6];
	height = data[9] * 256 + data[8];
	Component *buffer = new Component[width*height * 3];
	int i = 10;
	while (i <= size){
		buffer[i - 10] = data[i];
		i++;
	}
	delete[] data;
	Image *result = new Image(width, height, buffer, false);
	return result;
}
	


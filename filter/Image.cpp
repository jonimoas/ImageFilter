//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2013
//
//

#include "Image.h"
#include <algorithm>
#include <iostream>
#include <vector>
namespace imaging 
{

//-------------------------------- Image class implementation goes here ---------------------------------------------------

		// data accessors
		Component * Image::getRawDataPtr() const{
			return buffer;
		}
		// Obtain a pointer to the internal data
		// This is NOT a copy of the internal image data, but rather 
		// a pointer to the internally allocated space, so DO NOT
		// attempt to delete the pointer. 

		Color Image::getPixel(unsigned int x, unsigned int y) const{
			Color result;
			if (0 <=x <= width &&0<= y <= height){
				if (interleaved){
					result.x = buffer[3*y*width + 3*x];
					result.y = buffer[3*y*width + 3*x +1];
					result.z = buffer[3*y*width + 3*x + 2];
					return result;

				}
				else{
					result.x = buffer[x + y*width];
					result.y = buffer[height*width + x + y*width];
					result.z = buffer[height*width*2 + x + y*width];
					return result;
				}
			}
			result.x = 0;
			result.y = 0;
			result.z = 0;
			return result;
			
		}// get the color of the image at location (x,y)
		// Do any necessary bound checking. Also take into account
		// the "in0terleaved" flag to fetch the appropriate data
		// Return a black (0,0,0) color in case of an out-of-bounds
		// x,y pair

		// data mutators
		void Image::setPixel(unsigned int x, unsigned int y, Color value){
			if (0<=x <= width&&0<=y <= height){
				if (interleaved){
					buffer[3 * y*width + 3 * x] = value.x;
					buffer[3 * y*width + 3 * x + 1] = value.y;
					buffer[3 * y*width + 3 * x + 2] = value.z;
				}
				else{
					buffer[x + y*width]=value.x;
					buffer[height*width + x + y*width]=value.y;
					buffer[height*width * 2 + x + y*width]=value.z;
				}
			}
		}
		
		// Set the RGB values for an (x,y) pixel. Do all 
		// necessary bound checks and respect the "interleaved"
		// flag when updating our data.

		void Image::setData(const Component * & data_ptr){
			buffer = new Component[width*height * 3];
			int i = 0;
			while (i < width*height * 3){
				buffer[i] = *(data_ptr + i);
				i++;
			}
		}
		
		
		// Copy the data from data_ptr to the internal buffer.
		// The function ASSUMES a proper size for the incomming data array.

		// internal format representation methods
		void Image::convertToInterleavedImage(){
			if (!interleaved){
				Component* pointtemp = buffer;
				std::vector<Component> temp;
				int i = 0;
				while (i < width*height){
					temp.push_back(*pointtemp);
					temp.push_back(*(pointtemp+height*width));
					temp.push_back(*(pointtemp+2*height*width));
					pointtemp++;
					i++;
				}
				i = 0;
				while (i < height*width * 3){
					buffer[i] = temp[i];
					i++;
				}
				interleaved = true;
			}
		}
		
		
		// Re-arrange the data in the buffer to be in interleaved mode, 
		// i.e. as RGBRGBRGBRGB. If data already in interleaved mode, do nothing.

		void Image::convertToColorPlaneImage(){
			if (interleaved){
				Component* pointtemp = buffer;
				Component* temp = new Component[width*height * 3];
				int i = 0;
				while (i < width*height){
					temp[i] = *pointtemp;
					temp[height*width + i] = *(pointtemp+1);
					temp[2*height*width+i] = *(pointtemp+2);
					i++;
					pointtemp=pointtemp+3;
				}
				i = 0;
				while (i < height*width * 3){
					buffer[i] = temp[i];
					i++;
				}
				interleaved = false;
			}
		}
		// Re-arrange the data in the buffer to be in color plane mode, 
		// i.e. as RRRRGGGGBBBB. If data already in color plane mode, do nothing.
		

		// constructors and destructor
		Image::Image(unsigned int width, unsigned int height, bool interleaved){
			this->width = width;
			this->height = height;
			this->interleaved = interleaved;
		}
		Image::Image(unsigned int width, unsigned int height, const Component * data_ptr, bool interleaved){
			this->width = width;
			this->height = height;
			buffer = new Component[width*height * 3];
			setData(data_ptr);
			this->interleaved = interleaved;
		}
		Image::Image(const Image &src){
			this->height = src.getHeight();
			this->width = src.getWidth();
			this->interleaved = src.isInterleaved();
			buffer = new Component[width*height * 3];
			int i = 0;
			while (i < width*height * 3){
				buffer[i] = *(src.getRawDataPtr() + i);
				i++;
			}
		}
		Image::~Image(){
			delete buffer;
		}

	
	
//-------------------------------- Helper functions -----------------------------------------------------------------------

	bool isSuffix(std::string & filename, const std::string suffix)
	{
		std::string low_caps_filename = filename;
		std::string dot_suffix = '.' + suffix;
		
		// make the string lowercase.
		std::transform(low_caps_filename.begin(), low_caps_filename.end(), low_caps_filename.begin(), ::tolower );

		//make the suffix lowercase.
		std::transform(dot_suffix.begin(), dot_suffix.end(), dot_suffix.begin(), ::tolower );
		
		size_t pos = low_caps_filename.rfind(dot_suffix);
		
		if (pos == std::string::npos) // did not find it
			return false;

		if (pos < low_caps_filename.length()-dot_suffix.length()) // found it, but not at the end
			return false;
		
		return true; // now we are positive. :)
	}

	void replaceSuffix(std::string & filename, const std::string suffix)
	{
		size_t pos = filename.rfind('.');
		if (pos==std::string::npos)
			return;

		filename.resize(pos+1);
		filename+=suffix;
	}


} // namespace imaging
//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2013
//
//

#ifndef _IMAGE
#define _IMAGE

#include "Color.h"
#include "Logger.h"

// macro to make a class "logged" to a file (see class Logged)
#define LOGGED_CLASS(a) class a : public Logged

// We put every class or function associated with the image storage, compression and manipulation 
// in the "imaging" namespace
namespace imaging
{


//------------------------------------ class Image ------------------------------------------------
// 
// It is the class that represents a generic data container for an image. It holds the actual buffer
// of the pixel values and provides methods for accessing them either as individual pixels or as
// a memory block.
//    The Image class alone does not provide any functionality for loading and storing an image, as
// it is the product / input to such a procedure. The image I/O classes ImageReader / ImageWriter
// are responsible for this task and therefore provide the interfaces for all subclasses that
// implement support for specific formats.
//    The internal buffer of an image Object can be configured in either an "interleaved" mode or 
// a non-interleaved "color plane" one. In the interleaved mode, the pixels are stored in RGB, RGB, RGB ... 
// order, meaning that the color components are iterated for all pixels from left to right and top to 
// bottom of the image. In the color plane mode, the R values are stored first for all the pixels, 
// then the G and finally the B channels. Note that the buffer variable holding these data is the same
// size, regardless of its internal representation (3 X width X height bytes). The flag "interleaved"
// indicates whether the internal buffer representation is interleaved or not.
//    You must provide implementations to turn the buffer form an interleaved representation to a
// color plane mode and vice versa ( convertToInterleavedImage() and convertToColorPlaneImage() ).
// Remember to also switch the value of the "interleaved" flag accordingly.

	class Image
	{
	public:
		enum channel_t {RED=0,GREEN, BLUE};          // now you can use the names RED, GREEN, BLUE instead of 0,1,2
		                                             // to index individual channels
	protected:
		Component * buffer;                          // Holds the image data

		bool interleaved;                            // indicates the internal ordering of the color channels (see description above)
		unsigned int width, height;                  // width and height of the image (in pixels)

	public:
		// metric accessors
		const unsigned int getWidth() const {return width;}      // returns the width of the image
		const unsigned int getHeight() const {return height;}    // returns the height of the image

		// data accessors
		Component * getRawDataPtr() const;                       // Obtain a pointer to the internal data
		                                                         // This is NOT a copy of the internal image data, but rather 
		                                                         // a pointer to the internally allocated space, so DO NOT
		                                                         // attempt to delete the pointer. 

		Color getPixel(unsigned int x, unsigned int y) const;    // get the color of the image at location (x,y)
		                                                         // Do any necessary bound checking. Also take into account
		                                                         // the "interleaved" flag to fetch the appropriate data
		                                                         // Return a black (0,0,0) color in case of an out-of-bounds
		                                                         // x,y pair

		// data mutators
		void setPixel(unsigned int x, unsigned int y, Color value); // Set the RGB values for an (x,y) pixel. Do all 
		                                                            // necessary bound checks and respect the "interleaved"
		                                                            // flag when updating our data.

		void setData(const Component * & data_ptr);                 // Copy the data from data_ptr to the internal buffer.
		                                                            // The function ASSUMES a proper size for the incomming data array.

		// internal format representation methods
		void convertToInterleavedImage();                           // Re-arrange the data in the buffer to be in interleaved mode, 
		                                                            // i.e. as RGBRGBRGBRGB. If data already in interleaved mode, do nothing.

		void convertToColorPlaneImage();                            // Re-arrange the data in the buffer to be in color plane mode, 
		                                                            // i.e. as RRRRGGGGBBBB. If data already in color plane mode, do nothing.
		bool isInterleaved() const {return interleaved;}

		// constructors and destructor
		Image(unsigned int width, unsigned int height, bool interleaved=false);
		Image(unsigned int width, unsigned int height, const Component * data_ptr, bool interleaved=false);
		Image(const Image &src);
		~Image();

	};


	//==============================================================================================================
	// 
	// Image I/O classes (or "reader/writer" class interfaces
	// They define the structure of any reader or writer for opening/saving an image (of class Image) from/to a 
	// file of a specific format. All specific format readers and writers MUST inherit from these classes
	// Note: The classes are "logged", i.e. they provide log output functionality for convenience

	LOGGED_CLASS ( ImageReader )
	{
	protected:
		const std::string suffix;
	public:
		ImageReader(std::string suffix_to_use) 
			: suffix(suffix_to_use) {};
		const std::string getFormatSuffix() {return suffix;}
		virtual Image * read(std::string filename) = 0;
	};

	LOGGED_CLASS( ImageWriter )
	{
	protected:
		const std::string suffix;
	public:
		ImageWriter(std::string suffix_to_use)
			: suffix(suffix_to_use) {};
		const std::string getFormatSuffix() {return suffix;}
		virtual void write(std::string filename, const Image & src) = 0;
	};
	
	
	//==============================================================================================================

	
	// helper functions:

	// Returns true if the suffix of the filename (after the last '.') equals the "suffix" parameter.
	// The function returns false in any other case, including the case when no '.' is found. 
	// Caution: the function should be case insensitive. E.g. requesting a "ppm" suffix for a filename
	// named "MyPicture.PPM" should return true. 
	bool isSuffix(std::string & filename, const std::string suffix);

	// Locates the part of a filename trailing the last '.' symbol and replaces it with the given
	// suffix. If no '.' is found, the function does nothing.
	void replaceSuffix(std::string & filename, const std::string suffix);


} //namespace imaging

#endif
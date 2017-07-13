//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2013
//
//
//-------------------------------------------------------------

#ifndef _PPM
#define _PPM

#include "Image.h"

namespace imaging
{

	class PPMImageWriter : public ImageWriter
	{
	public:
		virtual void write(std::string filename, const Image & src);
		PPMImageWriter() 
			: ImageWriter("ppm") {}
		
	};

	class PPMImageReader : public ImageReader
	{
	public:
		virtual Image * read(std::string filename);
		PPMImageReader() 
			: ImageReader("ppm") {}
	};



} //namespace imaging

#endif
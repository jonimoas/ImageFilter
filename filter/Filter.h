//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2014
//
//
//-------------------------------------------------------------

#ifndef _FILTER
#define _FILTER

#include "Image.h"
#include <algorithm>
#include <math.h>
#include "Color.h"
#include <string>
#include <iostream>
#include <vector>

namespace imaging
{
	class Filter
	{
	// Προσθέστε αν θέλετε πεδία και μεθόδους
	public:
		
		Filter () {};
		virtual ~Filter() {};
		virtual void gray(Image *i);
		void color(Image *i, Color c);
		void blur(Image *i);
		void median(Image *i);
		void diff(Image *i);
	};

}
#endif
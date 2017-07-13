//------------------------------------------------------------
//
// C++ course tutorial code 
//
// G. Papaioannou, 2013
//
//-------------------------------------------------------------

#ifndef _COLOR
#define _COLOR


namespace imaging 
{
	// create an alias for the 0.255 values (8bit color channel):
	typedef unsigned char Component;

	class Color 
	{
	public: 
		Component x,y,z;
	};
}

#endif _COLOR
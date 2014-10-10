//!
//! @file 			Point.hpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 		n/a
//! @created 		2013-04-17
//! @last-modified	2014-10-10
//! @brief 			Represents a 2D point with x and y co-ordinates.
//! @details
//!		See README.rst in root dir for more info.
//!		

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//====================================== HEADER GUARD ===========================================//
//===============================================================================================//

#ifndef M_LIN_INTERP_POINT_H
#define M_LIN_INTERP_POINT_H



namespace MbeddedNinja
{
	namespace MLinInterpNs
	{

		//===============================================================================================//
		//=================================== PUBLIC TYPEDEFS ===========================================//
		//===============================================================================================//

		//! @brief	Helper class for PositionInfo
		//! @details	Each point requires 8bytes of RAM (64bits)
		template <class xType, class yType> class Point
		{
			public:
				//! @brief	Base constructor.
				Point<xType, yType>(xType xValIn, yType yValIn);

				//! @brief	Simplified constructor, initialises values to 0.
				Point();
				//===============================================================================================//
				//======================================= PUBLIC VARIABLES ======================================//
				//===============================================================================================//

				//! @brief 		Time (in milliseconds) from start
				//! @details	Maximum time you can store is approx 71.6mins (2^32us)
				xType xVal;
			
				//! @brief		Position (in absolute mechanical degrees) to be in at
				//!				time timeUs, relative to the start position.
				yType yVal;
		};
		
		
		template <class xType, class yType> Point<xType, yType>::Point(xType xValIn, yType yValIn)
		{
			xVal = xValIn;
			yVal = yValIn;
		};
	

		template <class xType, class yType> Point<xType, yType>::Point()
		{
			Point<xType, yType>(0, 0);
		};
	
	} // namespace MLinInterpNs
} // namespace MbeddedNinja

#endif // #ifndef M_LIN_INTERP_POINT_H

// EOF

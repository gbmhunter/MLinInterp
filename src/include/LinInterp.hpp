//!
//! @file 		LinInterp.h
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/04/17
//! @brief 		Performs fast linear interpolation.
//! @details
//!				See README.rst

//===============================================================================================//
//====================================== HEADER GUARD ===========================================//
//===============================================================================================//

#ifndef LIN_INTERP_H
#define LIN_INTERP_H

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

#include <stdint.h>
#include <cstdio>
#include <stdio.h>

#include "./Point.h"
//#include "./Comms/include/UartDebug.h"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace LinInterpNs
{

	//using namespace Fp;

	using namespace PointNs;

	//! Prints general debug messages.
	#define linInterpPRINT_DEBUG						(0)		

	//===============================================================================================//
	//=================================== PUBLIC TYPEDEFS ===========================================//
	//===============================================================================================//

	//! @brief		Helper class for LinInterp class. Used as the returned object
	//!				from LinInterp.Interp().
	template <class yType> class InterpResult
	{
		public:
			//! @brief		True if linear interpolation was successful, otherwise false.
			bool success;

			//! @brief		The result of the linear interpolation. If success == false,
			//!				then this will return 0.
			yType yVal;
	};

	template <class xType, class yType> class LinInterp
	{
		public:
			//! @brief		Constructor
			LinInterp();
			
			//! @brief		Performs linear interpolation of xVal, using the 
			//!				points defined in pointA.
			//! @returns	The result, of type InterpResult<yType> (a helper class).
			InterpResult<yType> Interp(xType xVal);
		
			//! @brief		Total number of points stored in pointA
			//! @todo		If user forgets to do this, memory leaks could occur.
			//! 				Make this automatic (use std::vector???)
			uint32_t numPoints;
			
			//! @brief		Updated by the algorithm.
			//! @todo		Make private, and provide access to READ ONLY
			uint32_t sectionNum;
			
			//! @brief 		Pointer to an array of x,y data points.
			Point<xType, yType>* pointA;
			
			//! @brief		Buffer for formulating debug messages.
			//! @todo		Make private
			char debugBuff[100];

		private:
			//! @brief		Prints debug information.
			//! @details	Platform dependant implementation (uses pre-compiler checks).
			void PrintDebug(const char* msg);
	};

	//! @brief 		Constructor
	template <class xType, class yType> LinInterp<xType, yType>::LinInterp()
	{
		#if(linInterpPRINT_DEBUG == 1)
			PrintDebug((char*)"LIN-INTERP: Initialising...\r\n");
		#endif
		
		// Nothing to do here
		
		#if(linInterpPRINT_DEBUG == 1)
			PrintDebug((char*)"LIN-INTERP: Initialisation complete.\r\n");
		#endif
	}

	//! @brief 		Interpolates xVal and returns yVal
	template <class xType, class yType> InterpResult<yType> LinInterp<xType, yType>::Interp(xType xVal)
	{
		// Find which segment xVal is in
		// Start at i=1, since can't interpolate
		// with just one point
		uint32_t i = 1;

		while(pointA[i].xVal < xVal)
		{
			// Look for first x value in array which is greater than
			// x value of point to interpolate

			
			// Protection against exceeding array count
			if(i == numPoints - 1)
			{
				//! @todo	Return null or exception
				InterpResult<yType> result;
				result.success = false;
				//result.yVal = 0x0;
				return result;
			}
			

			i++;
		}
		
		sectionNum = i;
		
		#if(linInterpPRINT_DEBUG == 1)
			snprintf(debugBuff, sizeof(debugBuff), "LIN-INTERP: Index = %u\r\n", 
				i);
			PrintDebug(debugBuff);
		#endif

		// Calculate x and y differences
		int32_t xDiff = (int32_t)pointA[i].xVal - (int32_t)pointA[i-1].xVal;
		yType yDiff = pointA[i].yVal - pointA[i-1].yVal;
		
		#if(linInterpPRINT_DEBUG == 1)
			snprintf(debugBuff, sizeof(debugBuff), "LIN-INTERP: xDiff = %u, yDiff = %f\r\n", 
				xDiff, yDiff);
			PrintDebug(debugBuff);
		#endif
		
		InterpResult<yType> result;
		//result.yVal = fp<FP_08>(((double)(xVal-pointA[i-1].xVal)*Fix2Float<FP_08>(yDiff.intValue))/(double)xDiff) + pointA[i-1].yVal;
		result.yVal = (yType)(((double)(xVal-pointA[i-1].xVal)*(yDiff))/(double)xDiff) + pointA[i-1].yVal;
		
		// If code has reached here, interpolation must of been successful
		result.success = true;		

		return result;
	}

	template <class xType, class yType> void LinInterp<xType, yType>::PrintDebug(const char* msg)
	{
		// Implementation is platform-dependant
		#if(__linux__)
			printf(msg);
		#elif(PSOC)
			UartDebug::PutString(msg);
		#endif
	}

} // namespace LinInterpNs

#endif // #ifndef LIN_INTERP_H

// EOF

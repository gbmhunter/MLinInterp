//!
//! @file 			LinInterpTest.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 		n/a
//! @created		2013-05-23
//! @last-modified 	2014-10-10
//! @brief 			Performs unit tests on LinInterp library.
//! @details
//!				See README.rst in the repo's root dir for more info.


//===== SYSTEM LIBRARIES =====//
#include <stdio.h>
#include <stdint.h>

//===== USER LIBRARIES =====//
#include "MUnitTest/api/MUnitTestApi.hpp"

//===== USER SOURCE =====//
#include "../api/MLinInterpApi.hpp"


using namespace MbeddedNinja::MLinInterpNs;

MTEST(TestInPositiveNumberSpaceWithPositiveGradient)
{
	LinInterp<double, double> linInterp;
	Point<double, double> pointA[2];
	pointA[0].xVal = 0.0;
	pointA[0].yVal = 0.0;
	pointA[1].xVal = 1.0;
	pointA[1].yVal = 1.0;

	linInterp.pointA = pointA;
	linInterp.numPoints = 2;
	
	InterpResult<double> result = linInterp.Interp(0.5);

	CHECK_EQUAL(OK, result.status);
	CHECK_EQUAL(0.5, result.yVal);
}

MTEST(TestInPositiveNumberSpaceWithNegativeGradient)
{
	LinInterp<double, double> linInterp;
	Point<double, double> pointA[2];
	pointA[0].xVal = 0.0;
	pointA[0].yVal = 1.0;
	pointA[1].xVal = 1.0;
	pointA[1].yVal = 0.0;

	linInterp.pointA = pointA;
	linInterp.numPoints = 2;
	
	InterpResult<double> result = linInterp.Interp(0.5);

	CHECK_EQUAL(OK, result.status);
	CHECK_EQUAL(0.5, result.yVal);
}

MTEST(TestInNegativeNumberSpaceWithPositiveGradient)
{
	LinInterp<double, double> linInterp;
	Point<double, double> pointA[2];
	pointA[0].xVal = 0.0;
	pointA[0].yVal = -1.0;
	pointA[1].xVal = 1.0;
	pointA[1].yVal = 0.0;

	linInterp.pointA = pointA;
	linInterp.numPoints = 2;
	
	InterpResult<double> result = linInterp.Interp(0.5);
	
	CHECK_EQUAL(OK, result.status);
	CHECK_EQUAL(-0.5, result.yVal);
}

MTEST(TestInNegativeNumberSpaceWithNegativeGradient)
{
	LinInterp<double, double> linInterp;
	Point<double, double> pointA[2];
	pointA[0].xVal = 0.0;
	pointA[0].yVal = 0.0;
	pointA[1].xVal = 1.0;
	pointA[1].yVal = -1.0;

	linInterp.pointA = pointA;
	linInterp.numPoints = 2;
	
	InterpResult<double> result = linInterp.Interp(0.5);
	
	CHECK_EQUAL(OK, result.status);
	CHECK_EQUAL(-0.5, result.yVal);
}

MTEST(ZeroGradientTest)
{
	LinInterp<double, double> linInterp;
	Point<double, double> pointA[2];
	pointA[0].xVal = 0.0;
	pointA[0].yVal = 1.0;
	pointA[1].xVal = 1.0;
	pointA[1].yVal = 1.0;

	linInterp.pointA = pointA;
	linInterp.numPoints = 2;
	
	InterpResult<double> result = linInterp.Interp(0.5);
	
	CHECK_EQUAL(OK, result.status);
	CHECK_EQUAL(1.0, result.yVal);
}

/*
TEST(XValuesDoNotIncreaseMonotomicallyTest)
{
	LinInterp<double, double> linInterp;
	Point<double, double> pointA[2];
	pointA[0].xVal = 1.0;
	pointA[0].yVal = 0.0;
	pointA[1].xVal = 0.0;
	pointA[1].yVal = 1.0;

	linInterp.pointA = pointA;
	linInterp.numPoints = 2;
	
	InterpResult<double> result = linInterp.Interp(0.5);
	
	// LinInterp.Interp() should of returned success == false,
	// and yVal == 0.
	CHECK_EQUAL(OK, result.status);
	CHECK_CLOSE(0, result.yVal, 0.01);
}
*/

MTEST(xValueBelowMinimumTest)
{
	LinInterp<double, double> linInterp;
	Point<double, double> pointA[2];
	pointA[0].xVal = 0.0;
	pointA[0].yVal = 0.0;
	pointA[1].xVal = 1.0;
	pointA[1].yVal = 1.0;

	linInterp.pointA = pointA;
	linInterp.numPoints = 2;
	
	// Ask for interpolation above maximum x-value in point array
	InterpResult<double> result = linInterp.Interp(-1.0);
	
	// LinInterp.Interp() should of returned closest y-value, and status X_VALUE_OUT_OF_RANGE
	CHECK_EQUAL(X_VALUE_OUT_OF_RANGE, result.status);
	CHECK_CLOSE(0.0, result.yVal, 0.01);
}

MTEST(xValueAboveMaximumTest)
{
	LinInterp<double, double> linInterp;
	Point<double, double> pointA[2];
	pointA[0].xVal = 0.0;
	pointA[0].yVal = 0.0;
	pointA[1].xVal = 1.0;
	pointA[1].yVal = 1.0;

	linInterp.pointA = pointA;
	linInterp.numPoints = 2;
	
	// Ask for interpolation above maximum x-value in point array
	InterpResult<double> result = linInterp.Interp(2.0);
	
	// LinInterp.Interp() should of returned closest y-value, and status X_VALUE_OUT_OF_RANGE
	CHECK_EQUAL(X_VALUE_OUT_OF_RANGE, result.status);
	CHECK_CLOSE(1.0, result.yVal, 0.01);
}

MTEST(OnlyLooksAtNumPointsTest)
{
	LinInterp<double, double> linInterp;
	Point<double, double> pointA[3];
	pointA[0].xVal = 0.0;
	pointA[0].yVal = 0.0;
	pointA[1].xVal = 1.0;
	pointA[1].yVal = 1.0;
	pointA[2].xVal = 2.0;
	pointA[2].yVal = 2.0;

	linInterp.pointA = pointA;
	
	// Only tell the engine about 2 of the 3 points
	linInterp.numPoints = 2;
	
	// Ask for interpolation above maximum x-value in point array
	InterpResult<double> result = linInterp.Interp(1.5);
	
	// LinInterp.Interp() should of returned closest y-value, and status X_VALUE_OUT_OF_RANGE
	CHECK_EQUAL(X_VALUE_OUT_OF_RANGE, result.status);
	CHECK_CLOSE(1.0, result.yVal, 0.01);
}

MTEST(SectionNumTest)
{
	LinInterp<double, double> linInterp;
	Point<double, double> pointA[3];
	pointA[0].xVal = 0.0;
	pointA[0].yVal = 0.0;
	pointA[1].xVal = 1.0;
	pointA[1].yVal = 1.0;
	pointA[2].xVal = 2.0;
	pointA[2].yVal = 2.0;

	linInterp.pointA = pointA;
	
	linInterp.numPoints = 3;
	
	// Ask for interpolation below minimum x-value in point array
	InterpResult<double> result = linInterp.Interp(-1);	
	CHECK_EQUAL(0, result.sectionNum);
	
	// Ask for interpolation between pointA[0] and pointA[1]
	result = linInterp.Interp(0.5);
	CHECK_EQUAL(1, result.sectionNum);
	
	// Ask for interpolation between pointA[1] and pointA[2]
	result = linInterp.Interp(1.5);	
	CHECK_EQUAL(2, result.sectionNum);
	
	// Ask for interpolation above pointA[2]
	result = linInterp.Interp(2.5);	
	CHECK_EQUAL(3, result.sectionNum);
}

//!
//! @file 		LinInterpTest.h
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/05/23
//! @brief 		Performs unit tests on LinInterp library.
//! @details
//!				See README.rst

// Relys on point library working correctly

#include <stdio.h>
#include <stdint.h>

// LinInterp library (library under test)
#include "../include/LinInterp.h"

// Uses UnitTest++ library for testing.
#include "./UnitTest++/src/UnitTest++.h"

using namespace LinInterpNs;

TEST(TestInPositiveNumberSpaceWithPositiveGradient)
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

	CHECK_EQUAL(result.success, true);
	CHECK_EQUAL(0.5, result.yVal);
}

TEST(TestInPositiveNumberSpaceWithNegativeGradient)
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

	CHECK_EQUAL(result.success, true);
	CHECK_EQUAL(0.5, result.yVal);
}

TEST(TestInNegativeNumberSpaceWithPositiveGradient)
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
	
	CHECK_EQUAL(result.success, true);
	CHECK_EQUAL(-0.5, result.yVal);
}

TEST(TestInNegativeNumberSpaceWithNegativeGradient)
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
	
	CHECK_EQUAL(result.success, true);
	CHECK_EQUAL(-0.5, result.yVal);
}

TEST(ZeroGradientTest)
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
	
	CHECK_EQUAL(result.success, true);
	CHECK_EQUAL(1.0, result.yVal);
}

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
	
	// LinInterp.Intrerp should of returned success == false,
	// and yVal == 0.
	CHECK_EQUAL(result.success, false);
	CHECK_EQUAL(result.yVal, 0);
}

int main()
{
	// Run unit tests
	return UnitTest::RunAllTests();
}

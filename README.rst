=====================================
Embedded Linear Interpolation Library
=====================================

.. image:: https://travis-ci.org/gbmhunter/Cpp-LinInterp.png?branch=master   
	:target: https://travis-ci.org/gbmhunter/Cpp-LinInterp

- Author: gbmhunter <gbmhunter@gmail.com> (http://www.cladlab.com)
- Created: 2012/10/23
- Last Modified: 2013/08/27
- Version: v1.2.0.0
- Company: CladLabs
- Project: n/a
- Language: C++
- Compiler: GCC	
- uC Model: All
- Computer Architecture: All
- Operating System: n/a
- Documentation Format: Doxygen
- License: GPLv3

Description
===========

A light-weight, fast linear interpolation library designed for use
on embedded systems (but can also run on any machine which has
a G++ compiler).
 
Requires point array to be setup separately. 

X values should increase monotonically (i.e. x+1 is always > x).
If x values in point array DO NOT increase monotonically 
then BEHAVIOUR IS UNDEFINED. Y values
can do whatever they want.

xType and yType should be numeric types which support the operators +, -, /, * 
(e.g. uint32_t, int32_t, double e.t.c).

Comes with unit tests to ensure correct operation.

Internal Dependencies:
======================
	
- Point (src/). Helper class which encapsulates a single point for the linear interpolation algorithm.
- UnitTest++ (test/UnitTest++). Lightweight library for unit testing.
		
External Dependencies
=====================

- None

Usage
=====

::

	// Create linear interpolation object, that uses doubles for both
	// x and y values.
	LinInterp<double, double> linInterp;
	
	// Create points for the linear interpolation to
	// use (data types must be the same as those for
	// LinInterp).
	Point<double, double> pointA[2];
	
	// Initial point, at (0,0)
	pointA[0].xVal = 0.0;
	pointA[0].yVal = 0.0;
	// (1,2) Slope of 2 from previous point
	pointA[1].xVal = 1.0;
	pointA[1].yVal = 2.0;
	// (2,6) Slope of 4 from previous point
	pointA[2].xVal = 2.0;
	pointA[2].yVal = 6.0;

	linInterp.pointA = pointA;
	linInterp.numPoints = 2;
	
	// Linear interpolate the value of x=0.5
	InterpResult<double> result = linInterp.Interp(0.5);
	// This prints "Result = 1.0"
	printf("Result = %f\r\n, result.yVal);
	
	// Linear interpolate the value of x=1.5 
	result = linInterp.Interp(1.5);
	// This prints "Result = 4"
	printf("Result = %f\r\n, result.yVal);

	
See test/LinInterpTest.cpp for more examples.
	
Issues
======

For known bugs, desired enhancements e.t.c, see GitHub issues section.
	
Changelog
=========

======== ========== ===================================================================================================
Version  Date       Comment
======== ========== ===================================================================================================
v1.2.0.0 2013/08/27 Added .travis.yml file in root directory for Travis CI compatibility. Added Travis CI build status image to top of README.
v1.1.0.1 2013/06/08 Changelog now in table format.
v1.1.0.0 2013/05/31 Added root Makefile that compiles everything and runs unit tests. Fixed parameter order in test checks. Deleted object and .d files.
v1.0.0.1 2013/05/24 Fixed formatting issue with bullet points in README.rst.
v1.0.0.0 2013/05/24 Initial commit.


======== ========== ===================================================================================================
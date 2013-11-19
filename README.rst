=====================================
Embedded Linear Interpolation Library
=====================================

.. image:: https://travis-ci.org/gbmhunter/Cpp-LinInterp.png?branch=master   
	:target: https://travis-ci.org/gbmhunter/Cpp-LinInterp

- Author: gbmhunter <gbmhunter@gmail.com> (http://www.cladlab.com)
- Created: 2012/10/23
- Last Modified: 2013/11/19
- Version: v1.4.0.0
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

A light-weight, fast linear interpolation library designed for use on embedded systems (but can also run on any machine which has a G++ compiler).
 
Requires point array to be setup separately. 

x-values in point array should increase monotonically (i.e. x+1 is always > x). If x values in point array DO NOT increase monotonically then BEHAVIOUR IS UNDEFINED. Y values can do whatever they want.

x-values passed to the interpolation engine which are outside of range provided in the point array return the closest y-value, which will either be y(x-min) or y(x-max). I have found this to be the safest behaviour when running on an embedded system. ``InterpResult.status`` will return ``X_VALUE_OUT_OF_RANGE``.

xType and yType should be numeric types which support the operators +, -, /, * 
(e.g. uint32_t, int32_t, double e.t.c).

Calling LinInterp::Interp() returns a InterpResult object which has a ``yType y_val``, ``status_t status`` and `sectionNum` object. Read the ``y_val`` to get the result of the interpolation. ``status`` tells you additional information about the interpolation, which could be either:

====================== ===========================================================================================================
``status`` Enumeration Description
====================== ===========================================================================================================
OK						     Interpolation was o.k., x-value provided was within range given by the point array (``pointA``).
X_VALUE_OUT_OF_RANGE   x-value provided to interpolation engine was out of the range in pointA. In this case, `InterpResult.yval` will be the closest value (either y(xmin) or y(xmax)). 
====================== ===========================================================================================================

The ``sectionNum`` object tells you which "section" the interpolation occurred in. Section 0 is before the first x-value in ``pointA``, section 1 is between the 1st and 2nd x-value, section 2 is between the 2nd and 3rd x-value, ..., section ``numPoints`` is after the last x-value in the ``pointA``.

Comes with unit tests to ensure correct operation. Run the command ``make`` from the command-line to compile the project and run the unit tests.

Internal Dependencies
=====================
	
- Point (src/). Helper class which encapsulates a single point for the linear interpolation algorithm.
- UnitTest++ (test/UnitTest++). Lightweight library for unit testing.
		
External Dependencies
=====================

None

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
v1.4.0.0 2013/11/19 ``InterpResult`` now contains a variable called ``sectionNum``, which indicates which section the interpolation occurred in. Got rid of public ``LinInterp.sectionNum`` variable. Added info about this to the README. Closes #15, closes #14.
v1.3.1.1 2013/11/19 Fixed table formatting issue in README and added more info about returned statuses.
v1.3.1.0 2013/11/19 Added unit test ``OnlyLooksAtNumPointsTest`` to make sure linear interpolation engine only uses the number of points specified by ``LinInterp.numPoints``.
v1.3.0.0 2013/11/19 Replaced ``bool success`` variable in InterpResult with a ``status_t status`` variable, to support x-values outside of range given in ``pointA``. Added info about out-of-range x-values to README. Removed unnecessary white-space from README. Removed x-values increasing monotonically test as behaviour is undefined in this case. Added build info to README.
v1.2.0.1 2013/08/27 Removed semi-colon from end of heading in README.
v1.2.0.0 2013/08/27 Added .travis.yml file in root directory for Travis CI compatibility. Added Travis CI build status image to top of README.
v1.1.0.1 2013/06/08 Changelog now in table format.
v1.1.0.0 2013/05/31 Added root Makefile that compiles everything and runs unit tests. Fixed parameter order in test checks. Deleted object and .d files.
v1.0.0.1 2013/05/24 Fixed formatting issue with bullet points in README.rst.
v1.0.0.0 2013/05/24 Initial commit.
======== ========== ===================================================================================================
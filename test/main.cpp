//!
//! @file 			main.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-10-10
//! @last-modified 	2014-10-10
//! @brief 			Contains main entry point for unit tests.
//! @details
//!					See README.rst in root dir for more info.

//===== SYSTEM LIBRARIES =====//
// none

//====== USER LIBRARIES =====//
#include "MUnitTest/api/MUnitTestApi.hpp"

//===== USER SOURCE =====//
// none


int main()
{

	// Run all unit tests and return the result
	return MbeddedNinja::TestRegister::RunAllTests();
	
}

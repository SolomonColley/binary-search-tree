/**
This is an exception class. It is used for throwing any
std::logic_error pretaining to not being able to find
something (e.g. a node that does not exist).

@author		Solomon Colley
@file		NotFoundException.cpp
@since		04/22/2019
*/

#include "NotFoundException.h"  

// -------------------------------------------------------------------------------------
// Constructor Section.
// -------------------------------------------------------------------------------------

NotFoundException::NotFoundException(const string& message)
	: logic_error("Not Found Exception: " + message)
{
}  // end parameterized constructor

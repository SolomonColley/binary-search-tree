/**
This is an exception class. It is used for throwing any
std::logic_error pretaining to a violation of a precondition
(e.g. a data structure being empty when it cannot be).

@author		Solomon Colley
@file		PreconditionException.cpp
@since		04/22/2019
*/

#include "PreconditionException.h"  

// -------------------------------------------------------------------------------------
// Constructor Section.
// -------------------------------------------------------------------------------------

PreconditionException::PreconditionException(const std::string& message)
	: std::logic_error("Precondition Exception: " + message)
{
}  // end parameterized constructor

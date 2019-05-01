/**
This is an exception class. It is used for throwing any
std::logic_error pretaining to a violation of a precondition
(e.g. a data structure being empty when it cannot be).

@author		Solomon Colley
@file		PreconditionException.h
@since		04/22/2019
*/

#pragma once

#include <stdexcept>
#include <string>

using namespace std;

class PreconditionException : public logic_error
{
public:
	// -------------------------------------------------------------------------------------
	// Constructor Section.
	// -------------------------------------------------------------------------------------

	PreconditionException(const string& message = "");
}; // end PrecondViolatedExcep 

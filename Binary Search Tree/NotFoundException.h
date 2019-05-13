/**
This is an exception class. It is used for throwing any
std::logic_error pretaining to not being able to find
something (e.g. a node that does not exist).

@author		Solomon Colley
@file		NotFoundException.h
@since		04/22/2019
*/

#pragma once

#include <stdexcept>
#include <string>

class NotFoundException : public std::logic_error
{
public:
	// -------------------------------------------------------------------------------------
	// Constructor Section.
	// -------------------------------------------------------------------------------------

	NotFoundException(const std::string& message = "");
}; // end NotFoundException 

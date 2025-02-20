#pragma once

#include <string>
#include <iostream>
#include <sstream>

bool g_IsEditor = true;

// print
//
// Engine function to print to console. Allows for a more flexible logging system.
// Example usage: print("Variable X Name:", 23, "more text");
template<typename... Args>
void print(Args&&... args)
{
	std::ostringstream oss;

	(oss << ... << args);
	std::cout << oss.str() << std::endl;
}

// printerr
//
// Engine function to print error to console.
// Example usage: printerr("Variable X Name:", 23, "more text");
template<typename... Args>
void printerr(Args&&... args)
{
	std::ostringstream oss;
	(oss << ... << args);
	std::cerr << oss.str() << std::endl;
}
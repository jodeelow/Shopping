#pragma once
#include "controller.h"
#include <string>
#include <exception>
using namespace std;

class CoatException : public exception
{
private:
	string message;

public:
	CoatException(const string& message);
	string get_message() const;
};

class CoatValidator {
private:
	Controller controller;

public:
	CoatValidator(const Controller& controller);
	void validate_add(const Coat& c);

	void validate_remove(string search_size, string search_colour, string search_photograph);
	//void validate_update();
};

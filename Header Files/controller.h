#pragma once
#include "repository.h"
#include "HTMLRepository.h"
#include "CSVRepository.h"

class Controller
{
private:

	Repository coats_repo;

public:

	Controller();

	Repository get_coats_repo() const;
	/*
	* returns an object of type vector
	*/

	bool remove_element_controller(string search_size, string search_colour, string search_photograph);

	bool update_element_controller(string search_size, string search_colour, string search_photograph, Coat c);

	void add_element_controller(Coat c);

	void print_elements() const;

	int get_size_of_dynamic_array() const;

	bool valid_coat(Coat c);
	/*
	* checks if the coat already exists in the list
	*/

	void create_10_coats();

	//void aaaaa();

	void read_coats(string filename);
	void write_coats(string filename);

	~Controller();

};

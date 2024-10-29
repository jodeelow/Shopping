#pragma once
#include "domain.h"
#include <string>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

class Repository
{
protected:
	vector<Coat> coats;

public:
	Repository();
	Repository(vector<Coat> coats);
	vector<Coat> get_coats() const;
	void add_coat(Coat c);
	bool remove_coat(string search_size, string search_colour, string search_photograph);
	bool update_coat(string search_size, string search_colour, string search_photograph, Coat c);
	/*
	* function used for updating an element from the list of elements
	* the item is searched by the size, colour and link to its photo
	* if it was found and updated, the function returns true, false otherwise
	*/
	void read_coats(string filename);

	virtual void write_coats(string filename);

	virtual ~Repository();
};


#include "repository.h"
#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

Repository::Repository()
{
}

Repository::Repository(vector<Coat> coats) : coats{ coats }
{
}

vector<Coat> Repository::get_coats() const
{
	return this->coats;
}

void Repository::add_coat(Coat c)
{
	this->coats.push_back(c);
}

bool Repository::remove_coat(string search_size, string search_colour, string search_photograph)
{
	int found_position = -1;
	int i = 0;
	for (i = 0; i < this->coats.size() && found_position == -1; i++)
	{
		if (this->coats[i].get_size() == search_size && this->coats[i].get_colour() == search_colour && this->coats[i].get_photograph() == search_photograph)
			found_position = i;
	}
	if (found_position != -1)
	{
		this->coats.erase(this->coats.begin() + found_position);
		return true;
	}
	return false;
}

bool Repository::update_coat(string search_size, string search_colour, string search_photograph, Coat c)
{
	bool found = false;
	int i = 0;
	for (i = 0; i < this->coats.size() && !found; i++)
	{
		if (this->coats[i].get_size() == search_size && this->coats[i].get_colour() == search_colour && this->coats[i].get_photograph() == search_photograph)
			found = true;
	}
	if (found)
		this->coats[i - 1] = c;

	return found;
}

void Repository::read_coats(string filename)
{
	ifstream fin(filename);
	if (!fin.is_open())
		return;

	Coat c;
	while (fin >> c)
	{
		this->add_coat(c);
		//cout << c << endl;
	}

	fin.close();
}

void Repository::write_coats(string filename)
{
	ofstream fout(filename);
	if (!fout.is_open())
		return;

	for (const auto& coat : this->coats)
		fout << coat;

	fout.close();
}

Repository::~Repository()
{
}

#include "domain.h"
#include <iostream>
#include <string>
#include <assert.h>
#include <sstream>
using namespace std;

Coat::Coat(string coat_size, string coat_colour, double coat_price, int coat_quantity, string coat_photograph)
{
	this->size = coat_size;
	this->colour = coat_colour;
	this->price = coat_price;
	this->quantity = coat_quantity;
	this->photograph = coat_photograph;
}

string Coat::get_size() const
{
	return this->size;
}

string Coat::get_colour() const
{
	return this->colour;
}

double Coat::get_price() const
{
	return this->price;
}

int Coat::get_quantity() const
{
	return this->quantity;
}

string Coat::get_photograph() const
{
	return this->photograph;
}

void Coat::set_size(string new_size)
{
	this->size = new_size;
}

void Coat::set_colour(string new_colour)
{
	this->colour = new_colour;
}

void Coat::set_price(double new_price)
{
	this->price = new_price;
}

void Coat::set_quantity(int new_quantity)
{
	this->quantity = new_quantity;
}

void Coat::set_photograph(string new_photograph)
{
	this->photograph = new_photograph;
}

void Coat::print_coat() const
{
	cout << this->get_size() << ", " << this->get_colour() << ", " << this->get_price() << " lei, " << this->get_quantity() << ", " << this->get_photograph() << endl;
}

Coat::~Coat()
{
}

vector<string> take_input(string str, char delimiter)
{
	vector<string> input_result;
	stringstream ss(str);
	string attribute;
	while (getline(ss, attribute, delimiter))
		input_result.push_back(attribute);

	return input_result;
}

istream& operator>>(istream& is, Coat& c)
{
	string line;
	getline(is, line);

	vector<string> attributes = take_input(line, ',');
	if (attributes.size() != 5)
		return is;
	c.set_size(attributes[0]);
	c.set_colour(attributes[1]);
	c.set_price(stod(attributes[2]));
	c.set_quantity(stoi(attributes[3]));
	c.set_photograph(attributes[4]);

	return is;
}

ostream& operator<<(ostream& os, const Coat& c)
{
	os << c.size << "," << c.colour << "," << c.price << "," << c.quantity << "," << c.photograph << "\n";
	return os;
}

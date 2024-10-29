#pragma once
#include <utility>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Coat
{
private:

	string size;
	string colour;
	double price;
	int quantity;
	string photograph;

public:

	Coat(string coat_size = "", string coat_colour = "", double coat_price = 0, int coat_quantity = 0, string coat_photograph = "");

	string get_size() const;

	string get_colour() const;

	double get_price() const;

	int get_quantity() const;

	string get_photograph() const;

	void set_size(string new_size);

	void set_colour(string new_colour);

	void set_price(double new_price);

	void set_quantity(int new_quantity);

	void set_photograph(string new_photograph);

	void print_coat() const;

	~Coat();

	friend istream& operator>>(istream& is, Coat& c);

	friend ostream& operator<<(ostream& os, const Coat& c);

	friend vector<string> take_input(string str, char delimiter);
};


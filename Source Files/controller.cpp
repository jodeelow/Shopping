#include "controller.h"
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
using namespace std;

Controller::Controller()
{
}

Repository Controller::get_coats_repo() const
{
	return this->coats_repo;
}

void Controller::add_element_controller(Coat c)
{
	this->coats_repo.add_coat(c);
}

bool Controller::remove_element_controller(string search_size, string search_colour, string search_photograph)
{
	bool found;
	found = this->coats_repo.remove_coat(search_size, search_colour, search_photograph);
	return found;
}

bool Controller::update_element_controller(string search_size, string search_colour, string search_photograph, Coat c)
{
	bool found;
	found = this->coats_repo.update_coat(search_size, search_colour, search_photograph, c);
	return found;
}

int Controller::get_size_of_dynamic_array() const
{
	int size;
	size = this->get_coats_repo().get_coats().size();
	return size;
}

bool Controller::valid_coat(Coat c)
{
	bool found = false;
	for (const auto& coat : this->coats_repo.get_coats())
	{
		if (coat.get_size() == c.get_size() && coat.get_colour() == c.get_colour() && coat.get_photograph() == c.get_photograph())
			found = true;
	}
	return !found;
}

void Controller::create_10_coats()
{
	Coat c{ "l", "black", 960, 5, "https://www.zalando.ro/antioch-palton-clasic-black-ai722t042-q11.html?size=L&allophones=0&wmc=SEM400_NB_GO._3625232631_17072920796_137263143538.&opc=2211&mpp=google" };
	//Coat c{ "l", "black", 960, 5, "link1" };
	this->add_element_controller(c);
	Coat c1{ "s", "brown", 960, 12, "https://www.zalando.ro/antioch-palton-clasic-black-ai722t042-q11.html?size=L&allophones=0&wmc=SEM400_NB_GO._3625232631_17072920796_137263143538.&opc=2211&mpp=google" };
	//Coat c1{ "s", "brown", 960, 12, "link1" };
	this->add_element_controller(c1);
	Coat c2{ "m", "black", 960, 50, "https://www.zalando.ro/antioch-palton-clasic-black-ai722t042-q11.html?size=L&allophones=0&wmc=SEM400_NB_GO._3625232631_17072920796_137263143538.&opc=2211&mpp=google" };
	//Coat c2{ "m", "black", 960, 50, "link1" };
	this->add_element_controller(c2);
	Coat c3{ "xl", "beige", 710, 67, "https://www.zalando.ro/antioch-palton-clasic-beige-ai721u000-b11.html?size=46&allophones=0&wmc=SEM400_NB_GO._3625232631_17072920796_137263143538.&opc=2211&mpp=google" };
	//Coat c3{ "xl", "beige", 710, 67, "link2" };
	this->add_element_controller(c3);
	Coat c4{ "m", "beige", 710, 33, "https://www.zalando.ro/antioch-palton-clasic-beige-ai721u000-b11.html?size=46&allophones=0&wmc=SEM400_NB_GO._3625232631_17072920796_137263143538.&opc=2211&mpp=google" };
	//Coat c4{ "m", "beige", 710, 33, "link2" };
	this->add_element_controller(c4);
	Coat c5{ "xxs", "white", 299, 2, "https://www.aboutyou.ro/p/pull-bear/palton-de-primavara-toamna-13807062" };
	//Coat c5{ "xxs", "white", 299, 2, "link3" };
	this->add_element_controller(c5);
	Coat c6{ "l", "white", 299, 62, "https://www.aboutyou.ro/p/pull-bear/palton-de-primavara-toamna-13807062" };
	//Coat c6{ "l", "white", 299, 62, "link3" };
	this->add_element_controller(c6);
	Coat c7{ "m", "white", 299, 36, "https://www.aboutyou.ro/p/pull-bear/palton-de-primavara-toamna-13807062" };
	//Coat c7{ "m", "white", 299, 36, "link3" };
	this->add_element_controller(c7);
	Coat c8{ "m", "blue", 410, 22, "https://www.zalando.ro/pier-one-trenci-dark-blue-pi922na0g-k11.html?size=S&allophones=0&wmc=SEM400_NB_GO._3625232631_17072920796_137263143538.&opc=2211&mpp=google" };
	//Coat c8{ "m", "blue", 410, 22, "link4" };
	this->add_element_controller(c8);
	Coat c9{ "l", "green", 410, 55, "https://www.zalando.ro/pier-one-trenci-dark-blue-pi922na0g-k11.html?size=S&allophones=0&wmc=SEM400_NB_GO._3625232631_17072920796_137263143538.&opc=2211&mpp=google" };
	//Coat c9{ "l", "green", 410, 55, "link4" };
	this->add_element_controller(c9);
}

void Controller::print_elements() const
{
	int i = 0;
	for (const auto& coat : this->coats_repo.get_coats())
	{
		/*cout << "Coat " << i + 1 << ": ";
		coat.print_coat();
		i++;*/
		cout << "Coat " << i + 1 << ": " << coat;
		i++;
	}
}

void Controller::read_coats(string filename)
{
	ifstream fin(filename);
	if (!fin.is_open())
		return;

	Coat c;
	while (fin >> c)
	{
		this->add_element_controller(c);
		//cout << c << endl;
	}
		
	fin.close();
}

void Controller::write_coats(string filename)
{
	ofstream fout(filename);
	if (!fout.is_open())
		return;

	for (const auto& coat : this->get_coats_repo().get_coats())
		fout << coat;

	fout.close();
}

Controller::~Controller()
{
}




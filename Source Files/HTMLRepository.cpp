#include "HTMLRepository.h"
#include <fstream>

HTMLRepository::HTMLRepository()
{
}

void HTMLRepository::write_coats(string filename)
{
	ofstream fout(filename);
	if (!fout.is_open())
		return;

	fout << "<!DOCTYPE html>\n" << "<html>\n" << "<head>\n" << "\t<title>basket</title>\n" << "</head>\n" << "<body>\n";
	fout << "\t<table border=" << "\"1\"" << ">\n" << "\t\t<tr>\n" << "\t\t\t<td>size</td>\n" << "\t\t\t<td>colour</td>\n" << "\t\t\t<td>price</td>\n" << "\t\t\t<td>quantity</td>\n" << "\t\t\t<td>photograph</td>\n";
	fout << "\t\t</tr>\n";

	for (const auto& coat : this->coats)
	{
		fout << "\t\t<tr>\n";
		fout << "\t\t\t<td>" << coat.get_size() << "</td>\n";
		fout << "\t\t\t<td>" << coat.get_colour() << "</td>\n";
		fout << "\t\t\t<td>" << coat.get_price() << "</td>\n";
		fout << "\t\t\t<td>" << coat.get_quantity() << "</td>\n";
		fout << "\t\t\t<td><a href=" << "\"" << coat.get_photograph() << "\"" << ">Link</a>" << "</td>\n";
		fout << "\t\t</tr>\n";
	}

	fout << "\t</table>\n" << "</body>\n" << "</hmtl>\n";
	fout.close();
}

HTMLRepository::~HTMLRepository()
{
}

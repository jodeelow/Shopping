#include "CSVRepository.h"
#include <fstream>

CSVRepository::CSVRepository()
{
}

void CSVRepository::write_coats(string filename)
{
	ofstream fout(filename);
	if (!fout.is_open())
		return;

	for (const auto& coat : this->coats)
		fout << coat;

	fout.close();
}

CSVRepository::~CSVRepository()
{
}
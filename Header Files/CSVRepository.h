#pragma once
#include "repository.h"
class CSVRepository : public Repository
{
public:
	CSVRepository();
	void write_coats(string filename) override;
	~CSVRepository();
};


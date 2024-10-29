#pragma once
#include "repository.h"
class HTMLRepository : public Repository
{
public:
	HTMLRepository();
	void write_coats(string filename) override;
	~HTMLRepository();
};


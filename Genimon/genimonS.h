#ifndef GENIMONS_H
#define GENIMONS_H

#include "genimon.h"
using namespace std;

class GenimonS : public Genimon
{
public:
	GenimonS(char typeC, string nomC);
	void setRareté();
};

#endif


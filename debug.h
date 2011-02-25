#ifndef _DEBUG_H
#define _DEBUG_H

#include <stdio.h>
#include "options.h"

#define DEBUG(OPT,FORMAT,...) \
	if ((OPT)&OPT_FLAG_DEBUG) \
		fprintf(stdout,FORMAT,##__VA_ARGS__)

#endif

#ifndef _OPTIONS_H
#define _OPTIONS_H

typedef long options_t;

enum option_flags
{
	OPT_FLAG_DEBUG = 0x1
};

#define OPT_INIT(OPT) (OPT) = 0x0

#define OPT_SET(OPT,FLAG) OPT |= (FLAG)

#define OPT_GET(OPT,FLAG) (OPT)&(FLAG)

#endif

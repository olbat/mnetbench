#ifndef _OPTIONS_H
#define _OPTIONS_H

typedef long long options_t;

enum option_flag
{
	OPT_FLAG_PRINTER_HTML = 0x100000,
	OPT_FLAG_PRINTER_CLASSIC = 0x10000,

	OPT_FLAG_TEST_BANDWIDTH = 0x1000,
	OPT_FLAG_TEST_LATENCY = 0x100,

	OPT_FLAG_DEBUG = 0x10,
	OPT_FLAG_QUIET = 0x1
};

struct option_name
{
	enum option_flag flag;
	char sname;
};

#define OPT_INIT(OPT) (OPT) = \
	OPT_FLAG_TEST_LATENCY \
	| OPT_FLAG_PRINTER_CLASSIC

#define OPT_SET(OPT,FLAG) OPT |= (FLAG)
#define OPT_UNSET(OPT,FLAG) OPT &= ~(FLAG)

#define OPT_GET(OPT,FLAG) ((OPT)&(FLAG))


options_t parse_options(int argc, char **argv);

#endif

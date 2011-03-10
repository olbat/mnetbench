#include <getopt.h>
#include <stdio.h>
#include <string.h>

#include "options.h"
#include "mnetbench.h"

options_t parse_options(int argc, char **argv)
{
	int c;
	options_t ret;

	OPT_INIT(ret);
	
	while (1)
	{
		static struct option long_options[] =
		{
			{"test-latency",	optional_argument, 0,	'l'},
			{"test-bandwidth",	optional_argument, 0,	'b'},

			{"print-classic",	no_argument,	0,	'c'},
			{"print-html",	no_argument,	0,	'x'},

			{"debug",	no_argument,	0,	'd'},
			{"quiet",	no_argument,	0,	'q'},
			{"help",	no_argument,	0,	'h'},
			{0, 0, 0, 0}
		};
		int option_index = 0;

		c = getopt_long (argc, argv, "l::b::cxdqh", long_options, &option_index);

		/* Detect the end of the options. */
		if (c == -1)
			break;

		switch (c)
		{
			case 0:
				/* A flag is set */
				break;

			case 'd':
				OPT_SET(ret,OPT_FLAG_DEBUG);
				break;
			case 'q':
				OPT_SET(ret,OPT_FLAG_QUIET);
				break;
			case 'l':
				OPT_SET(ret,OPT_FLAG_TEST_LATENCY);
				opt_test_args.latency = optarg;
				break;
			case 'b':
				OPT_SET(ret,OPT_FLAG_TEST_BANDWIDTH);
				opt_test_args.bandwidth = optarg;
				break;
			case 'c':
				OPT_SET(ret,OPT_FLAG_PRINTER_CLASSIC);
				break;
			case 'x':
				OPT_UNSET(ret,OPT_FLAG_PRINTER_CLASSIC);
				OPT_SET(ret,OPT_FLAG_PRINTER_HTML);
				break;
			case 'h':
				fprintf(stderr,"usage: %s <...>\n",*argv);
				break;

			case '?':
				/* getopt_long already printed an error message. */
				//OPT_SET(ret,OPT_FLAG_TEST_LATENCY);
				fprintf(stdout,"DEFAULT OPDSDT\n");
				break;

			default:
				fprintf(stdout,"DEFAULT OPT\n");
		}
	}

	if (optind < argc)
	{
		while (optind < argc)
		{
			fprintf (stderr,"%s is not a valid option\n",
				argv[optind++]);
		}
	}

	return ret;
}

char *opt_test_parse_option(char *namebuff, char *valbuff, char *str)
{
	char *basestr, *sepstr;
	basestr = str;
	sepstr = 0;
	while (*str)
	{
		if (*str == ' ')
			continue;
		if (*str == ':')
			sepstr = str;
		if (*str == ',')
			break;
		str++;
	}

	if (!sepstr)
		sepstr = str;
		
	memcpy(namebuff,basestr,sepstr-basestr);
	namebuff[sepstr-basestr] = 0;

	if (sepstr != str)
	{
		memcpy(valbuff,sepstr+1,str-sepstr-1);
		valbuff[str-sepstr-1] = 0;
	}
	else
		*valbuff = 0;
		

	if (*str)
		str++;
	
	return str;
}

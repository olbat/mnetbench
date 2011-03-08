#include <getopt.h>
#include <stdio.h>

#include "options.h"


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
				if (optarg)
					fprintf(stdout,"OPT OMG:%s\n",optarg);
				break;
			case 'b':
				OPT_SET(ret,OPT_FLAG_TEST_BANDWIDTH);
				if (optarg)
					fprintf(stdout,"OPT OMG:%s\n",optarg);
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
